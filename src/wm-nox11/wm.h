#ifndef WM_H
#define WM_H

class wm {

public:
	typedef enum Direction {
		Left, Middle, Right, Unknown
	} Direction;

	void setFocusScreen(Direction);
};

#endif
