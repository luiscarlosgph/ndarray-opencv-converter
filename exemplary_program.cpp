#include <opencv2/imgcodecs.hpp>
#include "superlibrary.h"

int main(int argc, char **argv) {
  // Read demo image
  cv::Mat im = cv::imread("demo_image.png"); 
  
  // Use C++ coolFunction()
  cv::Mat blur = coolFunction(im);
  
  // Use C++ CoolClass::toGray()
  CoolClass cc;
  cv::Mat gray = cc.toGray(im);
  
  // Write output images
  cv::imwrite("blur.png", blur);
  cv::imwrite("gray.png", gray);
}
