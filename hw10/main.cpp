#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0]
                  << " <LeftImg>"
                  << " <RightImg>"
                  << std::endl;
        exit(-1);
    }
    cv::Mat leftImg = cv::imread(argv[1]);
    cv::Mat rightImg = cv::imread(argv[2]);

    cv::imshow("Left", leftImg);
    cv::waitKey(0);
    cv::imshow("Right", rightImg);
    cv::waitKey(0);

    return 0;
}
