#ifndef WM_GUI
#define WM_GUI
#include <dlib/dlib/gui_widgets.h>
#include "Settings.h"
#include "grid_widget.h"
#include "HeadTracker.h"

class Win : public dlib::drawable_window{
public:
  Win(); 
  ~Win();
  dlib::image_widget image;
  void set_focus(Direction d);
private:
  dlib::list_box cameras;
  void on_camera_select(unsigned long i);
  void on_off_clicked();
  void on_flip_clicked();
  dlib::toggle_button off, flip_frame;
  dlib::label detection_label;
  grid_widget grid;
};

#endif

