/**
 * @brief  Lean library to demo the header-only ndarray-opencv-converter (ndcv.h).
 * @author Luis Carlos Garcia Peraza Herrera (luiscarlos.gph@gmail.com).
 * @date   17 Feb 2021.
 */

#include "ndcv.h" // NOTE: Header-only library that does the conversion magic, you need to keep it!
#include "superlibrary.h"

// TODO: Implement your library here

// Exemplary function that we want to use from C++ but also expose to Python
cv::Mat coolFunction(const cv::Mat &im) {
  cv::Mat smoothIm;
  cv::GaussianBlur(im, smoothIm, cv::Size(15, 15), 0, 0);
  return smoothIm;
}

// Exemplary class that we want to use in C++ but also expose to Python
cv::Mat CoolClass::toGray(const cv::Mat &im) {
  cv::Mat greyIm;
  cv::cvtColor(im, greyIm, cv::COLOR_BGR2GRAY);
 return greyIm;
}

// NOTE: conversion magic, you need to keep it!
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
  // NOTE: conversion magic, you need to keep it!
  init_ar();
  boost::python::to_python_converter<cv::Mat, matToNDArrayBoostConverter>();
  matFromNDArrayBoostConverter();

  // TODO: Expose your functions and classes to Python here
  
  // Example 1: this is how you expose a function
  boost::python::def("cool_function", coolFunction);
  
  // Example 2: this is how you expose a class and its methods
  boost::python::class_<CoolClass>("CoolClass", boost::python::init<>())
    .def("to_gray", &CoolClass::toGray);
}
