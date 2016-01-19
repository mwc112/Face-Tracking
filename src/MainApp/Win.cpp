#include "Win.h"
#include <iostream>
#include <stdio.h>
#include <list>
#include <string.h>
#include <dlib/dlib/array.h>

Win::Win() :
		image(*this), cameras(*this), off(*this), grid(*this, 1, 2), detection_label(
				*this), flip_frame(*this), equalise_frame(*this) {
	Settings* settings = Settings::getInstance();
	set_size(220 + 640 + 10, 10 + 480 + 10);
	set_title("MyEye configuration");
	dlib::array<std::string> l;
	for (int i = 0; i < settings->getCameraCount(); i++) {
		auto str = "cam " + std::to_string(i);
		l.push_back(str);
	}

	dlib::list_box_style_default s;
	cameras.load(l);
	cameras.set_style(s);
	cameras.set_pos(10, 10);
	cameras.set_size(50, 36);
	cameras.set_click_handler(*this, &Win::on_camera_select);
	if (settings->getCameraCount() > 0) {
		cameras.select(settings->getCamera());
	}
	detection_label.set_pos(10, 260);
	detection_label.set_text("No Detection");

	grid.set_pos(10, 50);
	grid.set_size(200, 200);
	grid.construct_grid();

	image.set_pos(220, 10);

	off.set_click_handler(*this, &Win::on_off_clicked);
	off.set_pos(60, 10);
	update_on_off_button(settings->getTrackingState());

	flip_frame.set_click_handler(*this, &Win::on_flip_clicked);
	flip_frame.set_pos(110, 10);
	update_flip_button(settings->getFrameFlipped());

	equalise_frame.set_click_handler(*this, &Win::on_equalise_clicked);
	equalise_frame.set_pos(150, 10);
	update_equalise_button(settings->getEqualiseFrame());
	show();
}

void Win::on_camera_select(unsigned long i) {
	Settings* settings = Settings::getInstance();
	if (i != settings->getCamera()) {
		settings->setCamera(i);
	}
}
void Win::on_equalise_clicked() {
	Settings* settings = Settings::getInstance();
	update_equalise_button(settings->toggleEqualiseFrame());
}
void Win::update_equalise_button(bool equalised) {
	if (equalised) {
		equalise_frame.set_name("no equalise");
		equalise_frame.set_checked();
	} else {
		equalise_frame.set_name("equalise");
		equalise_frame.set_unchecked();
	}
}

void Win::on_flip_clicked() {
	Settings* settings = Settings::getInstance();
	update_flip_button(settings->toggleFlipFrame());
}

void Win::update_flip_button(bool flipped) {
	if (flipped) {
		flip_frame.set_name("unflip");
		flip_frame.set_checked();
	} else {
		flip_frame.set_name("flip");
		flip_frame.set_unchecked();
	}
}

void Win::on_off_clicked() {
	Settings* settings = Settings::getInstance();
	update_on_off_button(settings->toggleTrackingState());

}
void Win::update_on_off_button(bool trackingState) {
	if (trackingState) {
		off.set_name("turn off");
		off.set_unchecked();
	} else {
		off.set_name("turn on");
		off.set_checked();
	}
}
Win::~Win() {
	close_window();
}

std::string directionName(Direction d);

void Win::set_focus(Direction d) {
	switch (d) {
	case Left: {
		grid.set_focus(0, 0);
		detection_label.set_text(directionName(d));
		break;
	}
		;
	case Right: {
		grid.set_focus(1, 0);
		detection_label.set_text(directionName(d));
		break;
	}
		;
	case Middle: {
		break;
	}
		;
	case Unknown: {
		break;
	}
		;
	}
}
