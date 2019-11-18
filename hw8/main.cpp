#include <iostream>
#include <opencv/cv.hpp>

int main() {
    cv::Mat before = cv::imread("../img/Lenna.png", CV_LOAD_IMAGE_COLOR);
    if (!before.data) {
        std::cerr << "Error while reading image" << std::endl;
        return -1;
    }
    cv::imshow("before", before);
    cv::waitKey(0);

    cv::Mat after(cv::Size(before.rows, before.cols), CV_8UC3);
    for (int y = 0; y < before.rows; y++) {
        for (int x = 0; x < before.cols; x++) {
            after.at<cv::Vec3b>(y, x)[0] = before.at<cv::Vec3b>(y, x)[2];
            after.at<cv::Vec3b>(y, x)[1] = before.at<cv::Vec3b>(y, x)[1];
            after.at<cv::Vec3b>(y, x)[2] = before.at<cv::Vec3b>(y, x)[0];
        }
    }

    cv::imshow("after", after);
    cv::waitKey(0);

    return 0;
}