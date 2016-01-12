#include "wm.h"
#include <X11/extensions/Xrandr.h>
#include <climits>
#include <iostream>

bool pointInPolygon(windowRect wr, int x, int y);

Status wm::get_root_windows(Display *d, Window **children_windows_ret,
                                         unsigned int *num_children_ret){
  Window root_window = XDefaultRootWindow(d);
  Window root, parent;
  if ((XQueryTree(d, root_window, &root, &parent,
                                children_windows_ret, num_children_ret))==0){
    return 0;
  }
}

Status wm::get_windows_attr(Display *d, Window *children_windows,
                           int num_children, XWindowAttributes *attrs_ret){
  for(int i = 0; i < num_children; i++){
    if(XGetWindowAttributes(d, children_windows[i], attrs_ret+i)==0){
      return 0;
    }
  }
}

void wm::print_attr(Display* d, Window *children_windows, XWindowAttributes *attrs,
                                            int num_children){
  char* name;

  for(int i = 0; i < num_children; i++){
    XFetchName(d, children_windows[i], &name);
    printf("Name: %s\nx: %i  y: %i  size: %i, %i\n\n", name, attrs[i].x,
                                   attrs[i].y, attrs[i].width, attrs[i].height);
  }
}


struct point {
    int x, y;
    point(int x, int y) : x(x), y(y) {}
    point() : x(0), y(0) {}
};




point calculate_screen_center(XRRCrtcInfo *info) {
    return point(info->width/2 + info->x, info->height/2 + info->y);
}

void calculate_screen_centers(Display *d, point &left, point &right) {
    XRRScreenResources *screens = XRRGetScreenResources(d, DefaultRootWindow(d));
    XRRCrtcInfo *info = NULL;
    point leftmost(INT_MAX, INT_MAX), rightmost(0,0);  
    bool leftmostset = false, rightmostset = false;  
    for (int i = 0; i < screens->ncrtc; i++) {
        info = XRRGetCrtcInfo(d, screens, screens->crtcs[i]);
        if (info->width > 0 && info->height > 0) {
            point sc = calculate_screen_center(info);
            if (sc.x < leftmost.x) {
                leftmost = sc;
                leftmostset = true;
            }
            if (sc.x > rightmost.x) {
                rightmost = sc;
                rightmostset = true;
            }
        }
        XRRFreeCrtcInfo(info);
    }
    
    if (!(rightmostset && leftmostset)) {
        exit(345);
    } 
    XRRFreeScreenResources(screens);
    left = leftmost;
    right = rightmost;
}
using namespace std;

void wm::set_focus_screen(Direction direction){
    Display *d = XOpenDisplay(NULL);
    Screen *s = DefaultScreenOfDisplay(d);
    point left, right;
    calculate_screen_centers(d, left, right);
    if(direction == Left){
        set_focus_to(d, left.x, left.y);
    }
    else if(direction == Right){
        set_focus_to(d, right.x, right.y);
    }
    XCloseDisplay(d);
}

void wm::set_focus_to(Display* d, int x, int y){

	auto windows = get_client_window_list(d);

	int i;
	for(i = 3; i < windows.size(); i++){
		bool in = pointInPolygon(windows[i], x, y);
		if(in){
			break;
		}
	}


	int root_x, root_y;
	get_pointer_location(d, &root_x, &root_y);
	
	int move_x = x - root_x;
	int move_y = y - root_y;

	//XWarpPointer(d, None, None, 0, 0, 0, 0, move_x, move_y);
	
	XSetInputFocus(d, windows[i].window, RevertToNone, CurrentTime);
	XFlush(d);
}

void wm::get_pointer_location(Display *d, int *x_ret, int *y_ret){
	bool got_pointer = false;
  Window *c_wins;
  unsigned int num_child;
  Window r_win, c_win;
  int win_x, win_y;
  unsigned int mask;

  get_root_windows(d, &c_wins, &num_child);

  for(int i = 0; i < num_child; i++){
    got_pointer = XQueryPointer(d, c_wins[i], &r_win, &c_win,
                                        x_ret, y_ret, &win_x, &win_y,
                                        &mask);
  }
}

bool pointInPolygon(windowRect wr, int x, int y) {
    std::cout << (x > wr.x)  << ": x:" << wr.x << " W:" << wr.w  << ":" << (y > wr.y) << ":" << (y < wr.y + wr.h)  << std::endl;
	return (x > wr.x && x < wr.x + wr.w && y > wr.y && y < wr.y + wr.h);

}


std::vector<windowRect> wm::get_client_window_list(Display* d){
	Atom a = XInternAtom(d, "_NET_CLIENT_LIST" , true);
  Atom actualType;
  int format;
  unsigned long bytesAfter;
  unsigned char *data;
  unsigned long length;
  int status = XGetWindowProperty(d,
                XDefaultRootWindow(d),
                a,
                0L,
                (~0L),
                false,
                AnyPropertyType,
                &actualType,
                &format,
                &length,
                &bytesAfter,
                &data);
	
	std::vector<windowRect> windows;
  if (status >= Success && length)
  {
     long *array = (long*)data;
     for (int k = 0; k < length; k++)
     {
				Window root;
				Window parent;
				Window* children;
				unsigned int nchildren;
				XQueryTree(d, array[k], &root, &parent, &children, &nchildren);
				XWindowAttributes attr;
				XGetWindowAttributes(d, parent, &attr);
				
                windows.push_back(windowRect(parent, attr.x, attr.y, attr.width, attr.height));
                
     }
  }
  return windows;
}

void wm::save_pointer(Window w){
	if(win_mouse->find(w) == win_mouse->end()){
		return;
	}
}
