/**
 * @brief  Lean library to demo the header-only ndarray-opencv-converter (ndcv.h).
 * @author Luis Carlos Garcia Peraza Herrera (luiscarlos.gph@gmail.com).
 * @date   17 Feb 2021.
 */

#ifndef SUPERLIBRARY_H
#define SUPERLIBRARY_H

#include <opencv2/imgproc/imgproc.hpp>

// TODO: Define your classes/functions here

// Exemplary function that we want to use from C++ but also expose to Python
cv::Mat coolFunction(const cv::Mat &im);

// Exemplary class that we want to use in C++ but also expose to Python
class CoolClass {
  public:
    cv::Mat toGray(const cv::Mat &im);
};

#endif
