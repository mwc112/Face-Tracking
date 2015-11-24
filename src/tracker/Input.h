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

#endif