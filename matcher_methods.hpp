#ifndef MATCHER_H
#define MATCHER_H

#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include "utils.hpp"

// functioning methods for feature matching
Result bruteForceL2(cv::Mat &img1,
                    cv::Mat &img2,
                    Result &res,
                    int flag /*1 SIFT - 0 SURF*/,
                    int i1, int i2 /*Current and Next position*/);

Result bruteForceHamming(cv::Mat &img1,
                         cv::Mat &img2,
                         Result &res,
                         int i1, int i2 /*Current and Next position*/);

// Transformation-Rotation method
cv::Mat stitchImages(cv::Mat img1, cv::Mat img2,
                     // std::vector<cv::DMatch> matches,
                     Result res);

#endif // MATCHER_H