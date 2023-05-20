#ifndef MATCHER_H
#define MATCHER_H

#include <opencv2/core.hpp>
#include "utils.hpp"

/*
    non passo tramite puntatore img1, img2 e res perché richiamo più funzioni in task1.cpp
    e c'è il rischio di applicare modifiche alle immagini (conversioni ad CV_8U ecc)
*/
// functioning methods for Matching
cv::Mat bruteForceL2(cv::Mat img1, cv::Mat img2, Result, const int flag);
void bruteForceHammingSorted(cv::Mat img1, cv::Mat img2, Result res);
void bruteForceKNN(cv::Mat img1, cv::Mat img2, Result res, int flag);

/*  NON functioning ones for Matching   */
// void flannMatching(cv::Mat img1, cv::Mat img2, Result res, int flag);

/*  NON functioning method to detect Transform and/or Rotation  */
cv::Mat checkTransformRotation(cv::Mat img1, cv::Mat img2, std::vector<cv::DMatch> matches, Result res);

#endif // MATCHER_H