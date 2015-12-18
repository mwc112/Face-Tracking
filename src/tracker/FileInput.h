#ifndef FILE_INPUT_H
#define FILE_INPUT_H

#include "Input.h"

class FileInput: public Input {
public:
    FileInput(string filePath);
};

#endif