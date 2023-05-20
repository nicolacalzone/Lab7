#include <iostream>
#include <string>
#include <dirent.h>
#include <vector>
#include <opencv2/opencv.hpp>

void analyzeImages(std::string &directory, std::vector<cv::Mat> &images)
{
    int lenght;

    if (directory.find("lab"))
        lenght = 12;
    else
        lenght = 23;

    for (int i = 1; i <= lenght; i++)
    {
        std::string filename;
        if (i < 10)
            filename = "i0" + std::to_string(i); // orders the images
        else
            filename = "i" + std::to_string(i); // orders the images

        std::string filepathBmp = directory + "/" + filename + ".bmp";
        std::string filepathPng = directory + "/" + filename + ".png";

        cv::Mat image;
        if (FILE *file = fopen(filepathBmp.c_str(), "r"))
        {
            fclose(file);
            image = cv::imread(filepathBmp, cv::IMREAD_COLOR);
        }
        else if (FILE *file = fopen(filepathPng.c_str(), "r"))
        {
            fclose(file);
            image = cv::imread(filepathPng, cv::IMREAD_COLOR);
        }

        images.push_back(image);
    }
}