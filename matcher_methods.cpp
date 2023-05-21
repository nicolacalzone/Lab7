#include <array>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include "utils.hpp"

const std::string dir = "../ResultImages/";

cv::Mat stitchImages(cv::Mat img1, cv::Mat img2, Result res)
{
    const int MIN_MATCH = 10;
    std::vector<char> matchesMask;
    int mean_X, mean_Y = {};
    int old_X, old_Y = {};
    cv::Mat result;
    std::vector<cv::DMatch> matches = res.matches;

    if (matches.size() > MIN_MATCH)
    {
        std::vector<cv::Point2f> src_pts, dst_pts;
        for (const auto &m : matches)
        {
            src_pts.push_back(res.kp1[m.queryIdx].pt);
            dst_pts.push_back(res.kp2[m.trainIdx].pt);
        }

        std::cout << src_pts.size() << std::endl; // FUNZIONA
        std::cout << dst_pts.size() << std::endl;

        cv::Mat M = cv::findHomography(src_pts, dst_pts, cv::RANSAC);

        cv::imshow("homography", M);
        cv::waitKey();

        cv::warpPerspective(img1, result, M,
                            cv::Size(img2.cols, img1.rows)); // le immagini presentano parti nere..
                                                             // quando si somma aggiungono parti nere
        result(cv::Rect(0, 0, img2.cols, img2.rows)) = img2;

        cv::imshow("warp", result);
        cv::waitKey();

        std::cout << "warpPerspective done" << std::endl;

        return result;
    }
    else
    {
        std::cout << "Not enough matches: " << matches.size() << " out of a minimum: " << MIN_MATCH << std::endl;
        return cv::Mat();
    }
}

/*
 *
 *   for ORB
 *
 */
Result bruteForceHamming(cv::Mat &img1, cv::Mat &img2, Result &res, int i1, int i2)
{
    if (!img1.empty() && img1.type() != CV_8U)
        img1.convertTo(img1, CV_8U);
    if (!img2.empty() && img2.type() != CV_8U)
        img2.convertTo(img2, CV_8U);

    std::cout << "conversione 1 eseguita " << std::endl;

    if (!res.descriptor1.empty() && res.descriptor1.type() != CV_8U)
        res.descriptor1.convertTo(res.descriptor1, CV_8U);
    if (!res.descriptor2.empty() && res.descriptor2.type() != CV_8U)
        res.descriptor2.convertTo(res.descriptor2, CV_8U);

    std::cout << "conversione 2 eseguita " << std::endl;

    cv::BFMatcher bf(cv::NORM_HAMMING, true);
    std::vector<cv::DMatch> matches;
    bf.match(res.descriptor1, res.descriptor2, matches);

    std::cout << "Match eseguito" << std::endl;

    std::sort(matches.begin(), matches.end());

    cv::drawMatches(img1, res.kp1, img2, res.kp2, matches, res.stitch);

    if (!res.stitch.empty())
        std::cout << "draw Matches eseguito " << std::endl;

    cv::imwrite(dir + std::to_string(i1) + " " + std::to_string(i2) + " - ORB.png", res.stitch);

    res.matches = matches;
    return res;
}

/*
 *
 *   for SIFT and SURF (non utilizzato perché non filtra le linee... ma funziona meglio)
 *
 */
Result bruteForceL2(cv::Mat &img1, cv::Mat &img2, Result &res, int flag, int i1, int i2)
{
    // Convert images to 8-bit unsigned integer type
    if (!img1.empty() && img1.type() != CV_8U)
        img1.convertTo(img1, CV_8U);
    if (!img2.empty() && img2.type() != CV_8U)
        img2.convertTo(img2, CV_8U);

    std::cout << "conversione eseguita " << std::endl;

    cv::BFMatcher matcher(cv::NORM_L2);
    std::vector<cv::DMatch> matches;
    matcher.match(res.descriptor1, res.descriptor2, matches);

    std::cout << "match eseguito" << std::endl;

    cv::drawMatches(img1, res.kp1, img2, res.kp2, matches, res.stitch);

    std::string file = "";

    if (!res.stitch.empty())
    {
        std::cout << "draw Matches eseguito " << std::endl;
    }

    if (flag == 0) // SURF
    {
        // cv::imshow(file, imgMatches);
        cv::imwrite(dir + file + std::to_string(i1) + " " + std::to_string(i2) + " - SURF.png",
                    res.stitch);
        // cv::waitKey();
    }
    /*  else if (flag == 1) // SIFT
      {
          // cv::imshow(file, imgMatches);
          cv::imwrite(dir + file + std::to_string(i1) + " " + std::to_string(i2) + " - SIFT.png",
                      imgMatches);
          // cv::waitKey();
      } */
    else
    {
        std::cout << "ERRORE, SURF = 0";
    }

    res.matches = matches;
    return res;
}
