#include <iostream>
#include <string>
#include <vector>

#include <opencv2/opencv.hpp>
#include <opencv2/stitching.hpp>
#include <opencv2/xfeatures2d.hpp>

#include "utils.hpp"
#include "matcher_methods.hpp"
#include "descriptor_methods.hpp"
#include "panoramic_utils2.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " [directory]\n";
        return 1;
    }

    std::string directory = argv[1];
    std::vector<cv::Mat> images, cylindricalImages;
    cv::Mat stitchedImage;
    double angle;

    // reads all the images and puts them into a vector of images
    analyzeImages(directory, images);

    // SURF descriptor
    Result resSURF;
    cv::Ptr<cv::xfeatures2d::SURF> det = cv::xfeatures2d::SURF::create();

    // Setting the angle
    if (directory.find("dolomites"))
        angle = 27;
    else
        angle = 33;

    // Computing the cylindrical formula for every image
    for (size_t i = 0; i < images.size(); i++)
        cylindricalImages.push_back(PanoramicUtils::cylindricalProj(images[i], angle));

    // computes features 2:2
    for (size_t i = 0; i < cylindricalImages.size(); i += 2)
    {
        // get curr pair of images
        cv::Mat img1 = cylindricalImages[i];
        cv::Mat img2 = cylindricalImages[i + 1];

        // SURF descriptor
        resSURF = useSURF(det, img1, img2);

        // Matching of the two images
        bruteForceL2(img1, img2, resSURF, 0);

        // FindHomography

        // end-cycle
        img1.release();
        img2.release();
    }

    return 0;
}
