#ifndef STITCH_H
#define STITCH_H

#include <opencv2/opencv.hpp>

class Stitch
{
public:
    Stitch(cv::Mat initial_image);
    void append(cv::Mat image);
    void show();
    void save();

private:
    cv::Mat montage;
    int x, y;
};

#endif
