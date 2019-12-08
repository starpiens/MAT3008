#include <iostream>
#include <vector>
#include <algorithm>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"

using namespace std;
using namespace cv;

Mat add_gaussian_noise(const Mat &src, double mean = 0.0, double std = 1.0) {
    Mat noise_src(src.size(), src.type());
    randn(noise_src, Scalar::all(mean), Scalar::all(std));

    Mat ret;
    src.convertTo(ret, src.type());
    addWeighted(ret, 1.0, noise_src, 1.0, 0.0, ret);

    return ret;
}

vector<pair<Point2f, Point2f>> get_correspondences(const Mat &left, const Mat &right, Mat *corr_img = nullptr) {
    const int DIST_THRESH = 30;

    Ptr<Feature2D> feature_extractor;
    feature_extractor = ORB::create();
    vector<KeyPoint> left_keypoints, right_keypoints;
    Mat left_descriptors, right_descriptors;
    feature_extractor->detectAndCompute(left, Mat(), left_keypoints, left_descriptors);
    feature_extractor->detectAndCompute(right, Mat(), right_keypoints, right_descriptors);

    Ptr<DescriptorMatcher> matcher;
    vector<DMatch> matches;
    matcher = DescriptorMatcher::create("BruteForce-Hamming");
    matcher->match(left_descriptors, right_descriptors, matches);
    matches.end() = remove_if(matches.begin(), matches.end(), [](DMatch i) -> bool {
      return i.distance > DIST_THRESH;
    });
    if (corr_img != nullptr) {
        drawMatches(left, left_keypoints, right, right_keypoints, matches, *corr_img);
    }

    vector<pair<Point2f, Point2f>> ret;
    ret.reserve(matches.size());
    for (auto i : matches) {
        ret.emplace_back(left_keypoints[i.queryIdx].pt, right_keypoints[i.trainIdx].pt);
    }
    return ret;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0]
             << " <LeftImg>"
             << " <RightImg>"
             << endl;
        exit(-1);
    }
    Mat left_img = imread(argv[1]);
    Mat right_img = imread(argv[2]);
    Mat corr_img;

    right_img = add_gaussian_noise(right_img, 0, 50);
    auto correspondences = get_correspondences(left_img, right_img, &corr_img);
    imshow("matches", corr_img);
    waitKey(0);
    cout << correspondences.size();

    return 0;
}