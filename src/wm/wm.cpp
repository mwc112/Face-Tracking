#include "wm.h"
#include <X11/extensions/Xrandr.h>
#include <climits>
#include <iostream>
#include <cstring>


/*** Functions returning Status return 0 if function fails ***/



/* Returns true if point (x, y) is within 2D polygon with coordinates
 * (wrx, wry), height wrh, width wrw                                 */

bool pointInPolygon(int wrx, int wry, int wrw, int wrh, int x, int y) {
	return (x > wrx && x < wrx + wrw && y > wry && y < wry + wrh);

}

/* Saves all children of the default root window in *childrenWindowsRet */

Status wm::getRootWindows(Display *d, Window **childrenWindowsRet,
		unsigned int *numChildrenRet) {
	Window rootWindow = XDefaultRootWindow(d);
	Window root, parent;
	if ((XQueryTree(d, rootWindow, &root, &parent, childrenWindowsRet,
			numChildrenRet)) == 0) {
		printf("ERROR: Failed to get root window children");
		return 0;
	}
	else
	{
		return 1;
	}
}

/* Saves array of attributes of childrenWindows in attrsRet.
 * In same order as in childrenWindows                         */

Status wm::getWindowsAttr(Display *d, Window *childrenWindows,
		int numChildren, XWindowAttributes *attrsRet) {
	Status status = 1;
	for (int i = 0; i < numChildren; i++) {
		if (XGetWindowAttributes(d, childrenWindows[i], attrsRet + i) == 0) {
			printf("ERROR: Failed to get attributes of window %li", childrenWindows[i]);
			status = 0;
		}
	}
	return status;
}

/* Prints name, x, y, width and height of all windows in childrenWindows */

void wm::printAttr(Display* d, Window *childrenWindows,
		XWindowAttributes *attrs, int numChildren) {
	char* name;

	for (int i = 0; i < numChildren; i++) {
		if(XFetchName(d, childrenWindows[i], &name) == 0)
		{
			printf("ERROR: Failed to get name of window %li", childrenWindows[i]);
		}
		else
		{
			printf("Name: %s\nx: %i  y: %i  size: %i, %i\n\n", name, attrs[i].x,
				attrs[i].y, attrs[i].width, attrs[i].height);
		}
	}
}

/* Returns point specifying centre of screen from screen information in info */

point calculateScreenCentres(XRRCrtcInfo *info) {
	return point(info->width / 2 + info->x, info->height / 2 + info->y);
}

/* Calculates screen centres of right and left screens displaying Display d.
 * Saves left centre in left and right centre in right
 * Exits with code 345 if fails to get centres of both screens             */

void calculateScreenCentres(Display *d, point &left, point &right) {
	XRRScreenResources *screens = XRRGetScreenResources(d,
			DefaultRootWindow(d));
	XRRCrtcInfo *info = NULL;
	point leftmost(INT_MAX, INT_MAX), rightmost(0, 0);
	bool leftmostset = false, rightmostset = false;
	for (int i = 0; i < screens->ncrtc; i++) {
		info = XRRGetCrtcInfo(d, screens, screens->crtcs[i]);
		if (info->width > 0 && info->height > 0) {
			point sc = calculateScreenCentres(info);
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
		exit(1);
	}
	XRRFreeScreenResources(screens);
	left = leftmost;
	right = rightmost;
}
using namespace std;

/* Calls to calculate screen centres and passes to setFocusTo */

void wm::setFocusScreen(Direction direction) {
	Display *d = XOpenDisplay(NULL);
	if(d == NULL)
	{
		printf("ERROR: Failed to open default display");
		return;
	}
	Screen *s = DefaultScreenOfDisplay(d);
	point left, right;
	calculateScreenCentres(d, left, right);
	if (direction == Left) {
		setFocusTo(d, left.x, left.y);
	} else if (direction == Right) {
		setFocusTo(d, right.x, right.y);
	}
	XCloseDisplay(d);
}

/* Builds message and sends to root window to focus window w on display d */

void focusAWindow(Display *d, Window w) {
	XClientMessageEvent ev;
	std::memset(&ev, 0, sizeof ev);
	ev.type = ClientMessage;
	ev.window = w;
	ev.message_type = XInternAtom(d, "_NET_ACTIVE_WINDOW", True);
	ev.format = 32;
	ev.data.l[0] = 1;
	ev.data.l[1] = CurrentTime;
	ev.data.l[2] = ev.data.l[3] = ev.data.l[4] = 0;
	if(XSendEvent(d, RootWindow(d, XDefaultScreen(d)), False,
		SubstructureRedirectMask | SubstructureNotifyMask, (XEvent*) &ev) == 0)
	{
		printf("ERROR: Failed to send focus event to window %li", w);
	}
}

/* Sets focus to top window under point (x, y) on display d */

void wm::setFocusTo(Display* d, int x, int y) {

	auto windows = getClientWindowList(d);

	int i;
	Window topmost;

	for (i = 3; i < windows.size(); i++) {
		XWindowAttributes attr;
		if(XGetWindowAttributes(d, windows[i], &attr) == 0)
		{
			printf("ERROR: Failed to get window attributes for window %li", windows[i]);
		}
		else if (attr.map_state == IsViewable
				&& pointInPolygon(attr.x, attr.y, attr.width, attr.height, x,
						y)) {
			topmost = windows[i];
		}
	}

	int root_x, root_y;

	int move_x = x - root_x;
	int move_y = y - root_y;

	if(XSetInputFocus(d, ourWindow, RevertToNone, CurrentTime) == 0)
	{
		printf("ERROR: Failed to get window focus to myeye window");
	}
	focusAWindow(d, topmost);

	XFlush(d);
}

/* Returns list of children of the root window */

std::vector<Window> wm::getClientWindowList(Display* d) {
	std::vector<Window> windows;
	Window root;
	Window parent;
	Window* children;
	unsigned int nchildren;
	if(XQueryTree(d, XDefaultRootWindow(d), &root,
													&parent, &children, &nchildren) == 0)
	{
		printf("ERROR: Failed to get children of root window");
	}
	for (int i = 0; i < nchildren; i++) {
		windows.push_back(children[i]);
	}
	return windows;
}
