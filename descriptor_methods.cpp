#include <array>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>
#include "utils.hpp"
#include "descriptor_methods.hpp"

Result useSURF(cv::Ptr<cv::xfeatures2d::SURF> &det, cv::Mat &img1, cv::Mat &img2)
{

    Result res;
    internalProcedure(img1, img2, res, det);

    return res;
}

Result useSIFT(cv::Mat &img1, cv::Mat &img2)
{
    cv::Ptr<cv::SIFT> det = cv::SIFT::create();

    Result res;
    internalProcedure(img1, img2, res, det);

    return res;
}

Result useORB(cv::Mat &img1, cv::Mat &img2)
{
    cv::Ptr<cv::ORB> det = cv::ORB::create();

    Result res;
    internalProcedure(img1, img2, res, det);

    return res;
}

void internalProcedure(cv::Mat &img1, cv::Mat &img2, Result &res, cv::Ptr<cv::Feature2D> det)
{
    det->detectAndCompute(img1, cv::noArray(), res.kp1, res.descriptor1);
    det->detectAndCompute(img2, cv::noArray(), res.kp2, res.descriptor2);
}