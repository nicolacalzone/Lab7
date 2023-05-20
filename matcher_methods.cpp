#include <array>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include "utils.hpp"

const std::string dir = "../ResultImages/";

void convertImages(cv::Mat &img1, cv::Mat &img2)
{
    // Convert images to 8-bit unsigned integer type

    if (!img1.empty() && img1.type() != CV_8U)
        img1.convertTo(img1, CV_8U);
    if (!img2.empty() && img2.type() != CV_8U)
        img2.convertTo(img2, CV_8U);
    img2.convertTo(img2, CV_8U);
}

cv::Mat checkTransformRotation(cv::Mat img1, cv::Mat img2, std::vector<cv::DMatch> matches, Result res)
{
    const int MIN_MATCH_COUNT = 10; // Set this to the desired value
    std::vector<char> matchesMask;

    if (matches.size() > MIN_MATCH_COUNT)
    {
        std::vector<cv::Point2f> src_pts, dst_pts;
        for (const auto &m : matches)
        {
            src_pts.push_back(res.kp1[m.queryIdx].pt);
            dst_pts.push_back(res.kp2[m.trainIdx].pt);
        }

        cv::Mat mask;
        cv::Mat M = cv::findHomography(src_pts, dst_pts, cv::RANSAC, 5.0, mask);
        matchesMask = mask.reshape(1, -1);

        int h = img1.rows;
        int w = img1.cols;
        std::vector<cv::Point2f> pts = {{0, 0}, {0, h - 1}, {w - 1, h - 1}, {w - 1, 0}};
        std::vector<cv::Point2f> dst;
        cv::perspectiveTransform(pts, dst, M);

        std::vector<cv::Point> poly;
        for (const auto &p : dst)
        {
            poly.push_back(cv::Point(static_cast<int>(p.x), static_cast<int>(p.y)));
        }
        cv::polylines(img2, poly, true, cv::Scalar(255), 3, cv::LINE_AA);
    }
    else
    {
        std::cout << "Not enough matches are found - " << matches.size() << "/" << MIN_MATCH_COUNT << std::endl;
        std::vector<char> matchesMask;
    }

    cv::Mat img3;
    cv::drawMatches(img1, res.kp1, img2, res.kp2, matches, img3,
                    cv::Scalar(0, 255, 0), cv::Scalar::all(-1), matchesMask,
                    cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    cv::imshow("Matches", img3);
    cv::waitKey();
}

/*
 *
 *   for SIFT and SURF (non utilizzato perché non filtra le linee... ma funziona meglio)
 *
 */
cv::Mat bruteForceL2(cv::Mat &img1, cv::Mat &img2, Result &res, int flag, int i1, int i2)
{
    convertImages(img1, img2);

    cv::BFMatcher bf(cv::NORM_L2);
    std::vector<std::vector<cv::DMatch>> matches;
    bf.knnMatch(res.descriptor1, res.descriptor2, matches, 1);

    std::vector<cv::DMatch> goodMatches;
    for (const auto &match : matches)
    {
        if (match[0].distance < 0.6 * match[1].distance)
        {
            goodMatches.push_back(match[0]);
        }
    }

    cv::Mat imgMatches;
    cv::drawMatches(img1, res.kp1, img2, res.kp2, matches, imgMatches);
    std::string file = "";

    if (flag == 0) // SURF
    {
        // cv::imshow(file, imgMatches);
        cv::imwrite(dir + file + std::to_string(i1) + " " + std::to_string(i2) + " - SURF.png",
                    imgMatches);
        // cv::waitKey();
    }
    else if (flag == 1) // SIFT
    {
        // cv::imshow(file, imgMatches);
        cv::imwrite(dir + file + std::to_string(i1) + " " + std::to_string(i2) + " - SIFT.png",
                    imgMatches);
        // cv::waitKey();
    }
    else
    {
        std::cout << "ERRORE - L2 Matcher_Methods.cpp";
    }

    return imgMatches;
}

/*
 *
 *   for ORB
 *
 */
cv::Mat bruteForceHammingSorted(cv::Mat &img1, cv::Mat &img2, Result &res)
{
    convertImages(img1, img2);
    convertImages(res.descriptor1, res.descriptor2);

    cv::BFMatcher bf(cv::NORM_HAMMING, true);

    std::vector<cv::DMatch> matches;
    bf.match(res.descriptor1, res.descriptor2, matches);

    std::sort(matches.begin(), matches.end());

    cv::Mat imgMatches;
    cv::drawMatches(img1, res.kp1, img2, res.kp2, matches, imgMatches);

    cv::imwrite(dir + /* std::to_string(i1) + " " + std::to_string(i2) + */ " - ORB.png", imgMatches);

    return imgMatches;
}
