#ifndef INPUT_H
#define INPUT_H

#include "Frame.h"

class Input {
public:
	virtual Frame getFrame() =0;
};

class NoInput: std::exception {
public:
	const std::string inputType;
	const std::string inputLocation;
	NoInput(std::string inputType, std::string inputLocation) :
			inputType(inputType), inputLocation(inputLocation) {
	}
};
#endif
