#ifndef MATILDA_H
#define MATILDA_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/application.h>
#include <gtkmm/box.h>
#include <iostream>
class Matilda_window: public Gtk::Window{

public:
	Matilda_window();
	virtual ~Matilda_window();
	
protected:
	//signal handlers:
	void on_button_clicked();

	//Member widgets:
	Gtk::Box h1_box;
	Gtk::Button run_button;
	Gtk::Button exit_button;
};
#endif
