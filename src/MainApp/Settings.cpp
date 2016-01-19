#include "Settings.h"
#include <stdio.h>
#include <iostream>
#include "CameraInput.h"

int Settings::getCamera() {
	return currCamera;
}

bool Settings::getTrackingState() {
	return trackingState;
}

void Settings::setCamera(int camera) {
	currCamera = camera;
	for (int i = 0; i < observers.size(); i++) {
		observers[i]->changeVideo(currCamera);
	}
}

bool Settings::toggleTrackingState() {
	trackingState = !trackingState;
	return trackingState;
}

bool Settings::toggleEqualiseFrame() {
	equaliseFrame = !equaliseFrame;
	for (int i = 0; i < observers.size(); i++) {
		observers[i]->equaliseFrame(equaliseFrame);
	}
	return equaliseFrame;
}
bool Settings::getEqualiseFrame() {
	return equaliseFrame;
}
bool Settings::toggleFlipFrame() {
	flipFrame = !flipFrame;
	for (int i = 0; i < observers.size(); i++) {
		observers[i]->flipFrame(flipFrame);
	}
	return flipFrame;
}
bool Settings::getFrameFlipped() {
	return flipFrame;
}
int Settings::getCameraCount() {
	return cameraCount;
}

Settings* Settings::getInstance() {
	static Settings instance;
	return &instance;
}

Settings::Settings() :
    currCamera(0), trackingState(true),
    flipFrame(true), equaliseFrame(false),
    cameraCount(0) {
	int i = 0;
	try {
		while (true) {
			CameraInput ci = CameraInput(i);
			ci.getFrame();
			i += 1;
		}
	} catch (...) {
		cameraCount = i;
	}
}

void Settings::addVideoObserver(VideoManager* vm) {
	vm->changeVideo(currCamera);
	vm->flipFrame(flipFrame);
	observers.push_back(vm);
}
