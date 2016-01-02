#include "FileInput.h"

using namespace cv;
FileInput::FileInput(std::string filePath) {
    cap = VideoCapture(filePath);
}

Mat FileInput::getFrame() {
    Mat mat;
    if (cap.read(mat)) {
        return mat;
    } else {
        //TODO Throw Exception
        throw "file";
    }
    
}