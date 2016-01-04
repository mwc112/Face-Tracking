#include "Settings.h"
#include <stdio.h>
#include <iostream>
#include "CameraInput.h"

int Settings::getCamera() {
  return currCamera;
}

bool Settings::getManager() {
  return manager;
}
 
void Settings::setCamera(int camera) {
  currCamera = camera;
  for (int i = 0; i < observers.size(); i++){
    observers[i]->changeVideo(currCamera);
  } 
}


void Settings::toggleManager() {
  manager = !manager;
  std::cout << manager << std::endl;
}

int Settings::getCameraCount(){
  return maxCamera + 1;
}

Settings* Settings::getInstance(){
  static Settings instance;
  return &instance;
}

Settings::Settings(){
  currCamera = 0;
  manager = true;
  int i = -1;
  try { 
    while(true){
      CameraInput ci = CameraInput(i + 1);
      ci.getFrame();
      i += 1;
    } 
  } catch (NoInput e) {
    maxCamera = i;
  } 
  
}

void Settings::addVideoObserver(VideoManager* vm){
  vm->changeVideo(currCamera);
  observers.push_back(vm);  
}
