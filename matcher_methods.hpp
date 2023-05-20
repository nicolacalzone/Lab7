#ifndef MATCHER_H
#define MATCHER_H

#include <opencv2/core.hpp>
#include "utils.hpp"

// functioning methods for feature matching
cv::Mat bruteForceL2(cv::Mat &img1, cv::Mat &img2, Result &res, int flag, int i1, int i2);
cv::Mat bruteForceHammingSorted(cv::Mat &img1, cv::Mat &img2, Result &res);

// Transformation-Rotation method
cv::Mat checkTransformRotation(cv::Mat img1, cv::Mat img2, std::vector<cv::DMatch> matches, Result res);

// Methods for Redundant operations:
void convertImages(cv::Mat &img1, cv::Mat &img2);

#endif // MATCHER_H