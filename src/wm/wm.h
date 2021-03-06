#ifndef __MAIN_C__
#define __MAIN_C__

#include <stdio.h>
#include <unordered_map>
#include <vector>
#include <unistd.h>
#include <iostream>

extern "C" {
#include <X11/Xlib.h>
}

/* Holds points in 2D space */

struct point {
	int x, y;
	point(int x, int y) :
			x(x), y(y) {}
	point() :
			x(0), y(0) {}
};

class wm {
  
public:
	//Enum used for direction being looked in to choose screen
	enum Direction {
		Left, Middle, Right, Unknown
	};
  
	void setFocusScreen(Direction);

	wm() {
		Display *d = XOpenDisplay(NULL);
		int revert_to_return;
    //this sleep is required so that the window is open
    //  when we get our window.
		usleep(1000000);
		XGetInputFocus(d, &ourWindow, &revert_to_return);
		XCloseDisplay(d);
	}
  
private:
  Status getRootWindows(Display*, Window**, unsigned int*);
  Status getWindowsAttr(Display*, Window*, int, XWindowAttributes*);
  void printAttr(Display*, Window*, XWindowAttributes*, int);
  void setFocusTo(Display*, int, int);
  std::vector<Window> getClientWindowList(Display*);
  Window ourWindow;
};

#endif
