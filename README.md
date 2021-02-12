ndarray-opencv-converter
------------------------
If you have a computer vision pipeline in C++ and you want to expose it to Python, this is your library.

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

Credits
-------
The code in this repo is based on [numpy-boost-python-opencv](https://github.com/yati-sagade/blog-content/blob/master/content/numpy-boost-python-opencv.rst) and [pyboostcvconverter](https://github.com/Algomorph/pyboostcvconverter).

License
-------
This project is distributed under an MIT license.
