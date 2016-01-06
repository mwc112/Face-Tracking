#ifndef MAIN_VM
#define MAIN_VM
#include "Input.h"
#include <string.h>

class VideoManager{

public:
  Frame getFrame();
  void flipFrame(bool);
  void changeVideo(int camera);
  void changeVideo(std::string path);
  VideoManager();
private:
  Input* ci = NULL;
  bool flip;
};

#endif
