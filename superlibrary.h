/**
 * @brief  Lean library to demo the header-only ndarray-opencv-converter (ndcv.h).
 * @author Luis Carlos Garcia Peraza Herrera (luiscarlos.gph@gmail.com).
 * @date   22 August 2019.
 */

#ifndef COOLSTUFF_H
#define COOLSTUFF_H

#include <boost/python.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// NOTE: this is the header-only library that does the conversion magic, you need to include it
#include "ndcv.h"

// TODO: Your code goes here!

// Exemplary function that we want to use from C++ but also expose to Python
cv::Mat coolFunction(const cv::Mat &im) {
  cv::Mat smoothIm;
  cv::GaussianBlur(im, smoothIm, cv::Size(5, 5), 0, 0);
  return smoothIm;
}

// Exemplary class that we want to use in C++ but also expose to Python
class CoolClass {
  public:
    cv::Mat toGray(const cv::Mat &im) {
      cv::Mat greyIm;
      cv::cvtColor(im, greyIm, cv::COLOR_BGR2GRAY);
      return greyIm;
    }
};

// NOTE: this does the magic, you need to keep it
static void *init_ar() {
  Py_Initialize();
  import_array();
  return NULL;
}

// NOTE: you should change the name of the library from 'superlibrary' to something more
//       appropriate, but, you must call the output library file with the same name.
//       That is, in your CMakeLists.txt:
//
//       add_library(superlibrary SHARED superlibrary.h)
//                        /\
//                        || These two must be equal!
//                        \/
BOOST_PYTHON_MODULE(superlibrary) {
  // NOTE: this does the magic, you need to keep it
  init_ar();
  boost::python::to_python_converter<cv::Mat, matToNDArrayBoostConverter>();
  matFromNDArrayBoostConverter();

  // TODO: Expose your functions and classes here
  
  // Example 1: this is how you expose a function
  //boost::python::def("coolFunction", coolFunction);
  
  // Example 2: this is how you expose a class and its methods
  //boost::python::class_<CoolClass>("CoolClass", boost::python::init<>())
  //    .def("toGray", &CoolClass::toGray);
}

#endif
