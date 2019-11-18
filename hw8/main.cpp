#include <iostream>
#include <string>
#include <sstream>
#include <opencv/cv.hpp>

template <typename _Tp>
void resize_bilinear(const cv::Mat &org_img, cv::Mat &new_img) {
    double x_rate = (double)new_img.cols / org_img.cols;
    double y_rate = (double)new_img.rows / org_img.rows;

    for (int x = 0; x < new_img.cols; x++) {
        for (int y = 0; y < new_img.rows; y++) {
            int x_org = (int)(x / x_rate);
            int y_org = (int)(y / y_rate);

            double fx1 = (double)x / x_rate - x_org;
            double fx2 = 1 - fx1;
            double fy1 = (double)y / y_rate - y_org;
            double fy2 = 1 - fy1;

            double w1 = fx2 * fy2;
            double w2 = fx1 * fy2;
            double w3 = fx2 * fy1;
            double w4 = fx1 * fy1;

            _Tp P1 = org_img.at<_Tp>(y_org, x_org);
            _Tp P2 = org_img.at<_Tp>(y_org, x_org + 1);
            _Tp P3 = org_img.at<_Tp>(y_org + 1, x_org);
            _Tp P4 = org_img.at<_Tp>(y_org + 1, x_org + 1);

            new_img.at<_Tp>(y, x) = w1 * P1 + w2 * P2 + w3 * P3 + w4 * P4;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0]
            << " <filename>"
            << " <size_x>"
            << " <size_y>"
            << std::endl;
        exit(-1);
    }
    std::string filename(argv[1]);
    int after_x = std::stoi(argv[2]);
    int after_y = std::stoi(argv[3]);

    cv::Mat before;
    before = cv::imread(filename, CV_LOAD_IMAGE_COLOR);
    if (!before.data) {
        std::cerr << "Error while reading image" << std::endl;
        exit(-1);
    }
    std::stringstream winname;
    winname << "Before (" << before.cols << "x" << before.rows << ")\n";
    cv::imshow(winname.str(), before);
    cv::waitKey(0);

    cv::Mat after(after_y, after_x, CV_8UC3);
    resize_bilinear<cv::Vec3b>(before, after);

    winname.str("");
    winname << "After (" << after.cols << "x" << after.rows << ")\n";
    cv::imshow(winname.str(), after);
    cv::waitKey(0);

    return 0;
}