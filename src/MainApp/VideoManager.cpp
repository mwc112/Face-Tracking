//class VideoManager{
//
//public:
//  Mat getFrame();
//  void changeVideo(int camera);
//  void changeVideo(String path);
//  VideoManager();
//private:
//  input ci;
//}
#include "VideoManager.h"
#include "CameraInput.h"
#include "FileInput.h"
#include <iostream>
#include <stdio.h>

Frame VideoManager::getFrame(){
  Frame f = ci->getFrame();
  if (flip){
    f.flip();
  }
  return f;
}

void VideoManager::flipFrame(bool f){
  flip = f;
}

void VideoManager::changeVideo(int camera){
  this->ci = new CameraInput(camera);
}

void VideoManager::changeVideo(std::string path){
  ci = new FileInput(path);
}

VideoManager::VideoManager(){
}
 
