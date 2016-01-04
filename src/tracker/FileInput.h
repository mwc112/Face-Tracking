#ifndef FILE_INPUT_H
#define FILE_INPUT_H

#include "Input.h"
#include "opencv2/highgui/highgui.hpp"

class FileInput: public Input {
public:
    FileInput(std::string filePath);
    Frame getFrame();
private:
    cv::VideoCapture cap;
    std::string filePath;
};

#endif
