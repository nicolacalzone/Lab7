#include "Stitch.h"

Stitch::Stitch(cv::Mat initial_image) : montage(initial_image)
{
    x = montage.rows;
    y = montage.cols;
}

void Stitch::append(cv::Mat image)
{
    int x = image.rows;
    int y = image.cols;
    cv::Mat new_image;
    cv::resize(image, new_image, cv::Size(y, this->x));
    cv::hconcat(this->montage, new_image, this->montage);
}

void Stitch::show()
{
    cv::imshow("montage", this->montage);
    cv::waitKey();
    cv::destroyAllWindows();
}

void Stitch::save()
{
    cv::imwrite("../ResultImages/montage.png", this->montage);
}
