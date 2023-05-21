// MIE
#include "matcher_methods.hpp"
#include "descriptor_methods.hpp"
#include "panoramic_utils2.hpp"
#include "utils.hpp"
#include "Stitch.h"

// STD
#include <iostream>
#include <string>
#include <vector>

// OPENCV
#include <opencv2/opencv.hpp>
#include <opencv2/stitching.hpp>
#include <opencv2/xfeatures2d.hpp>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " /Path/to/Chosen/Dataset/" << endl;
        return -1;
    }

    std::string directory = argv[1]; // directory name
    double angle;                    // FoV
    if (directory.find("dolomites") != std::string::npos)
        angle = 27;
    else
        angle = 33;

    std::vector<cv::Mat> images, cylindricalImages, stitchedImages; // images = vector where images read are put
                                                                    // cylindricalImages = vector where cylindrical
                                                                    // images are put
    analyzeImages(directory, images);                               // reads all the images and puts them into a vector of images

    Result resORB; // ORB descriptor
    cv::Ptr<cv::ORB> det = cv::ORB::create();
    Result result;
    cv::Mat final;

    // Result resSURF;
    //  cv::Ptr<cv::xfeatures2d::SURF> det = cv::xfeatures2d::SURF::create();

    // Computing the cylindrical formula for every image
    for (int i = 0; i < images.size(); i++)
        cylindricalImages.push_back(PanoramicUtils::cylindricalProj(images[i], angle));

    // Computing BruteForce Matching for every pair of images
    for (int curr = 0; curr <= cylindricalImages.size() - 2; curr++)
    {
        int next = curr + 1;

        cv::Mat img1 = cylindricalImages[curr];
        cv::Mat img2 = cylindricalImages[next];

        /*
        ORB descriptor
        */
        resORB = useORB(det, img1, img2);
        cout << "ORB: " << curr << endl;

        result = bruteForceHamming(img1, img2, resORB, curr, next);
        // result = bruteForceL2(img1, img2, resORB, 0, curr, next);

        cout << "BF: " << curr << endl;

        final = stitchImages(img1, img2, result);
        stitchedImages.push_back(final);
    }

    cout << "arrivo qui" << endl;

    cv::imshow("final", final);
    cv::waitKey();

    Stitch stitch(stitchedImages[0]);
    for (int curr = 1; curr <= stitchedImages.size() - 1; curr++)
        stitch.append(stitchedImages[curr]);
    stitch.save();
    stitch.show();

    return 0;
}
