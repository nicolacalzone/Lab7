#ifndef UTILS_H
#define UTILS_H

/*
    USEFUL FUNCTIONS
*/
void analyzeImages(std::string directory, std::vector<cv::Mat> &images);

/*
    USEFUL STRUCTURES
*/
struct Result
{
    /*
        original Result values:
            -keypoints
            -descriptors
    */
    std::vector<cv::KeyPoint> kp1, kp2;
    cv::Mat descriptor1, descriptor2;

    // additional for Stitch
    cv::Mat stitch;
    std::vector<cv::DMatch> matches;
};

#endif // UTILS_H