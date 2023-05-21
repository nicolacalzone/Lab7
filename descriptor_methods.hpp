#ifndef METHODS_H
#define METHODS_H

#include <opencv2/core.hpp>
#include <opencv2/xfeatures2d.hpp>
#include "utils.hpp"

// used
Result useSURF(cv::Ptr<cv::xfeatures2d::SURF> det,
               cv::Mat &img1,
               cv::Mat &img2);
Result useORB(cv::Ptr<cv::ORB> det,
              cv::Mat &img1,
              cv::Mat &img2);

// unused
Result useSIFT(cv::Mat &img1, cv::Mat &img2);

// for reduntant operations
void internalOp(cv::Mat &img1,
                cv::Mat &img2,
                Result &res,
                cv::Ptr<cv::Feature2D> det);

#endif // METHODS_H