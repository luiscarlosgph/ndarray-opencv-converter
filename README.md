ndarray-opencv-converter
------------------------
If you have a C++ computer vision pipeline that uses OpenCV and you want to expose it to Python, this is your library.

Dependencies
------------
* Python >= 3.8.2
      
* [OpenCV](https://github.com/opencv/opencv) >= 3.4.3 (last tested to be working 4.5.1). Skip this step if you have OpenCV already installed in your system. Otherwise, you can install it running:

      
      # Ubuntu/Debian
      $ sudo apt update
      $ sudo apt install libopencv-dev python3-opencv
      
* [Numpy](https://pypi.org/project/numpy/) >= 1.20.0. Skip this step if you have Numpy already installed in your system. Otherwise, you can install it running:

      # Ubuntu/Debian
      $ sudo apt update
      $ sudo apt install python3-pip
      $ python3 -m pip install numpy --user

* libboost_python >= 1.70.0 (last tested to be working 1.75.0)
      
      $ wget https://dl.bintray.com/boostorg/release/1.75.0/source/boost_1_75_0.tar.gz
      $ tar xf boost_1_75_0.tar.gz
      $ cd boost_1_75_0/
      $ ./bootstrap.sh --with-python=/usr/bin/python3
      $ ./b2 --with-python link=static cxxflags="-std=c++11 -fPIC" variant=release stage
      $ sudo ./b2 --with-python link=static cxxflags="-std=c++11 -fPIC" variant=release install

Usage
-----
Let's assume you have a library called ```superlibrary```, with header ```superlibrary.h``` and implementation ```superlibrary.cpp``` (which should contain your Python wrapper). For example:

**superlibrary.h**

```cpp
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
```

**superlibrary.cpp**

```cpp
#include <boost/python.hpp>
#include "superlibrary.h"
#include "ndcv.h" // NOTE: Header-only library that does the conversion magic, you need to keep it!

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
//       add_library(superlibrary SHARED superlibrary.cpp)
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
```

In the example above, the conversion between an ndarray (what Python passes) and cv::Mat (what your library expects) is performed transparently, and the code just works. If you do not include ```ndcv.h``` and the converter code marked with a NOTE is commented out, an error will show up when you run your Python script (e.g. [exemplary_program.py](https://github.com/luiscarlosgph/ndarray-opencv-converter/blob/main/exemplary_program.py)) using the library :

```
Traceback (most recent call last):
  File "exemplary_program.py", line 8, in <module>
    blur = superlibrary.cool_function(im)
Boost.Python.ArgumentError: Python argument types in
    superlibrary.cool_function(numpy.ndarray)
did not match C++ signature:
    cool_function(cv::Mat)
```

Exemplary programs in C++ and Python that use **the same** .so library (superlibrary.so, whose code is shown above) here: 

* [exemplary_program.cpp](https://github.com/luiscarlosgph/ndarray-opencv-converter/blob/main/exemplary_program.cpp)
* [exemplary_program.py](https://github.com/luiscarlosgph/ndarray-opencv-converter/blob/main/exemplary_program.py)

How to test this repo
---------------------

```bash
$ git clone https://github.com/luiscarlosgph/ndarray-opencv-converter.git
$ cd ndarray-opencv-converter
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
$ cd ..

# To test the C++ program that uses the library (exemplary_program.cpp)
$ build/exemplary_program

# To test the Python script that uses the library (exemplary_program.py)
$ python3 exemplary_program.py
```

Credits
-------
The code in this repo is based on [numpy-boost-python-opencv](https://github.com/yati-sagade/blog-content/blob/master/content/numpy-boost-python-opencv.rst) and [pyboostcvconverter](https://github.com/Algomorph/pyboostcvconverter).

License
-------
This project is distributed under an [MIT license](https://github.com/luiscarlosgph/ndarray-opencv-converter/blob/main/LICENSE).
