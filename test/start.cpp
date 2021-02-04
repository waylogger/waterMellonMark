#ifndef MATILDA_H
#define MATILDA_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/application.h>

class Matilda_window: public Gtk::Window{

public:
	Matilda_window();
	virtual ~Matilda_window();
	
protected:
	//signal handlers:
	void on_button_clicked();

	//Member widgets:
	Gtk::Button exit_button;
};
#endif
