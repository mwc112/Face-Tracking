#ifndef WM_H
#define WM_H

class wm {

public:
	typedef enum Direction {
		Left, Middle, Right, Unknown
	} Direction;

	void set_focus_screen(Direction);
};

#endif
