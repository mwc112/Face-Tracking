#ifndef WM_GUI
#define WM_GUI
#include <dlib/dlib/gui_widgets.h>
#include "Settings.h"

class Win : public dlib::drawable_window{
public:
  Win(); 
  ~Win();
  dlib::image_widget image;

private:
  dlib::list_box cameras;
  void on_camera_select(unsigned long i);
  void on_off_clicked();
  dlib::button off;
};

#endif


