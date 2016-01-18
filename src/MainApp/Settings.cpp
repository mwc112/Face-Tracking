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
	return maxCamera + 1;
}

Settings* Settings::getInstance() {
	static Settings instance;
	return &instance;
}

Settings::Settings() {
	currCamera = 1;
	trackingState = true;
	flipFrame = true;
	equaliseFrame = false;
	int i = -1;
	maxCamera = 1;

}

void Settings::addVideoObserver(VideoManager* vm) {
	vm->changeVideo(currCamera);
	vm->flipFrame(flipFrame);
	observers.push_back(vm);
}
