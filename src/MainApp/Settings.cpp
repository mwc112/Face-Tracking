#include "Settings.h"
#include <stdio.h>
#include <iostream>


int Settings::getCamera() {
  return currCamera;
}

void Settings::setCamera(int camera) {
  currCamera = camera;
  for (int i = 0; i < observers.size(); i++){
    observers[i]->changeVideo(currCamera);
  } 
}

Settings* Settings::getInstance(){
  static Settings instance;
  return &instance;
}

Settings::Settings(){
  currCamera = 0;
}

void Settings::addVideoObserver(VideoManager* vm){
  vm->changeVideo(currCamera);
  observers.push_back(vm);  
}
