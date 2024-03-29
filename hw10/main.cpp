// #define _SHOW_CORRESPONDENCE_IMG

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"

extern "C" {
#include "nrutil.h"
void mrqmin(float x[], float y[], float sig[], int ndata, float a[], int ia[],
            int ma, float **covar, float **alpha, float *chisq,
            void (*funcs)(float, float [], float *, float [], int), float *alamda);
}

using namespace std;
using namespace cv;

struct Data {
  float x;
  float y;
  float xp;
  float yp;
};

static std::vector<Data> data_vec;

Mat add_gaussian_noise(const Mat &src, double mean = 0.0, double std = 1.0) {
    Mat noise_src(src.size(), src.type());
    randn(noise_src, Scalar::all(mean), Scalar::all(std));

    Mat ret;
    src.convertTo(ret, src.type());
    addWeighted(ret, 1.0, noise_src, 1.0, 0.0, ret);

    return ret;
}

std::vector<pair<Point2f, Point2f>> get_correspondences(const Mat &left, const Mat &right, Mat *corr_img = nullptr) {
    const int DIST_THRESH = 30;

    Ptr<Feature2D> feature_extractor;
    feature_extractor = ORB::create();
    std::vector<KeyPoint> left_keypoints, right_keypoints;
    Mat left_descriptors, right_descriptors;
    feature_extractor->detectAndCompute(left, Mat(), left_keypoints, left_descriptors);
    feature_extractor->detectAndCompute(right, Mat(), right_keypoints, right_descriptors);

    Ptr<DescriptorMatcher> matcher;
    std::vector<DMatch> matches;
    matcher = DescriptorMatcher::create("BruteForce-Hamming");
    matcher->match(left_descriptors, right_descriptors, matches);
    matches.erase(
            remove_if(matches.begin(), matches.end(), [](DMatch i) -> bool {
              return i.distance > DIST_THRESH;
            }), matches.end());

    if (corr_img != nullptr) {
        drawMatches(left, left_keypoints, right, right_keypoints, matches, *corr_img);
    }
    std::vector<pair<Point2f, Point2f>> ret;
    ret.reserve(matches.size());
    for (auto i : matches) {
        ret.emplace_back(left_keypoints[i.queryIdx].pt, right_keypoints[i.trainIdx].pt);
    }
    return ret;
}

void func_xp(float x, float a[], float *y, float dyda[], int na) {
    auto &d = data_vec[roundf(x)];
    float divisor = (a[7] * d.x + a[8] * d.y + 1);
    *y = (a[1] * d.x + a[2] * d.y + a[3]) / divisor;
    dyda[1] = d.x / divisor;
    dyda[2] = d.y / divisor;
    dyda[3] = 1 / divisor;
    dyda[7] = -d.x * *y / divisor;
    dyda[8] = -d.y * *y / divisor;
}

void func_yp(float x, float a[], float *y, float dyda[], int na) {
    auto &d = data_vec[roundf(x)];
    float divisor = (a[7] * d.x + a[8] * d.y + 1);
    *y = (a[4] * d.x + a[5] * d.y + a[6]) / divisor;
    dyda[4] = d.x / divisor;
    dyda[5] = d.y / divisor;
    dyda[6] = 1 / divisor;
    dyda[7] = -d.x * *y / divisor;
    dyda[8] = -d.y * *y / divisor;
}

void run_mrqmin(std::vector<pair<Point2f, Point2f>> &correspondences, float a[], const int ma) {
    int ndata = correspondences.size();
    auto *x = ::vector(1, ndata);
    auto *y = ::vector(1, ndata);
    auto *sig = ::vector(1, ndata);
    auto *ia = ivector(1, ma);
    auto **covar = matrix(1, ma, 1, ma);
    auto **alpha = matrix(1, ma, 1, ma);
    float chisq;
    float alamda;

    iota(x + 1, x + ndata + 1, 1);
    fill(sig + 1, sig + ndata + 1, 1);
    for_each(correspondences.begin(), correspondences.end(), [](const auto &i) {
      data_vec.push_back({i.first.x, i.first.y, i.second.x, i.second.y});
    });

    for (int i = 1; i <= ndata; i++) y[i] = data_vec[i - 1].xp;
    ia[1] = ia[2] = ia[3] = ia[7] = ia[8] = 1;
    alamda = -1;
    mrqmin(x, y, sig, ndata, a, ia, ma, covar, alpha, &chisq, func_xp, &alamda);

    for (int i = 1; i <= ndata; i++) y[i] = data_vec[i - 1].yp;
    ia[1] = ia[2] = ia[3] = 0;
    ia[4] = ia[5] = ia[6] = 1;
    alamda = -1;
    mrqmin(x, y, sig, ndata, a, ia, ma, covar, alpha, &chisq, func_yp, &alamda);

    free_vector(x, 1, ndata);
    free_vector(y, 1, ndata);
    free_vector(sig, 1, ndata);
    free_ivector(ia, 1, ma);
    free_matrix(covar, 1, ma, 1, ma);
    free_matrix(alpha, 1, ma, 1, ma);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <LeftImg>" << " <RightImg>" << endl;
        exit(-1);
    }
    Mat left_img = imread(argv[1]);
    Mat right_img = imread(argv[2]);

    const int ma = 8;
    auto a = ::vector(1, ma);
    fill(a + 1, a + ma + 1, 2);

#ifdef _SHOW_CORRESPONDENCE_IMG
    Mat corr_img;
    auto correspondences = get_correspondences(left_img, right_img, &corr_img);
    imshow("Correspondences (Original)", corr_img);
    waitKey(0);
#else
    auto correspondences = get_correspondences(left_img, right_img);
#endif
    run_mrqmin(correspondences, a, ma);
    cout << "===== Original image =====" << endl;
    cout << "# of correspondences: " << correspondences.size() << endl;
    cout << "a = [";
    for (int i = 1; i < ma; i++) {
        cout << a[i] << ", ";
    }
    cout << a[ma] << "]" << endl;
    cout << "Accuracy of estimation: " << endl << endl;

    const double gaussian_std[] = {1, 10, 30};
    for (auto std : gaussian_std) {
        auto left_img_noise = add_gaussian_noise(left_img, 0, std);
        auto right_img_noise = add_gaussian_noise(right_img, 0, std);
#ifdef _SHOW_CORRESPONDENCE_IMG
        stringstream winname;
        winname << "Correspondences (Gaussian std = " << std << ")";
        correspondences = get_correspondences(left_img, right_img, &corr_img);
        imshow(winname.str(), corr_img);
        waitKey(0);
#else
        correspondences = get_correspondences(left_img_noise, right_img_noise);
#endif
        run_mrqmin(correspondences, a, ma);
        cout << "===== Gaussian noise with std=" << std << " =====" << endl;
        cout << "# of correspondences: " << correspondences.size() << endl;
        cout << "a = [";
        for (int i = 1; i < ma; i++) {
            cout << a[i] << ", ";
        }
        cout << a[ma] << "]" << endl;
        cout << "Accuracy of estimation: " << endl << endl;
    }

    free_vector(a, 1, ma);
    return 0;
}

#undef _SHOW_CORRESPONDENCE_IMG