#ifndef INPUT_H
#define INPUT_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

class Input {
public:
    virtual cv::Mat getFrame() =0;
};


class NoInput : std::exception {
public:
    const std::string inputType;
    const std::string inputLocation;
    NoInput(std::string inputType, std::string inputLocation) : inputType(inputType), inputLocation(inputLocation) {}
};
#endif