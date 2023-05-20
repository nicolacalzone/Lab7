#ifndef UTILS_H
#define UTILS_H

/*
    USEFUL FUNCTIONS
*/

void analyzeImages(std::string &directory, std::vector<cv::Mat> &images);

/*
    USEFUL STRUCTURES
*/

struct Result
{
    std::vector<cv::KeyPoint> kp1, kp2;
    cv::Mat descriptor1, descriptor2;
};

#endif // UTILS_H