#include "gtest/gtest.h"
#include "X11/Xlib.h"
#include "../wm.h"


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(window_manager, can_repeatedly_set_focus_screen_left){

	wm w_m;

    for (auto i = 0; i < 5000; i++) {
	    w_m.set_focus_screen(wm::Left);
	}

}
TEST(window_manager, can_repeatedly_set_focus_screen_right){

	wm w_m;

    for (auto i = 0; i < 5000; i++) {
	    w_m.set_focus_screen(wm::Right);
	}

}


