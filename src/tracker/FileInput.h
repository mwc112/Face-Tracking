#ifndef FILE_INPUT_H
#define FILE_INPUT_H

#include "Input.h"

class FileInput: public Input {
public:
    FileInput(std::string filePath);
    cv::Mat getFrame();
private:
    cv::VideoCapture cap;
};

#endif