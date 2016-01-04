#include "FileInput.h"

using namespace cv;
FileInput::FileInput(std::string filePath) : filePath(filePath) {
    cap = VideoCapture(filePath);
}

Frame FileInput::getFrame() {
    Mat mat;
    if (cap.read(mat)) {
        return mat;
    } else {
        throw NoInput("file", filePath);
    }
    
}
