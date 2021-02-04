#ifndef MATILDA_WINDOW_H
#define MATILDA_WINDOW_H

#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/entry.h>
// ------------------------------------------------------------------------------------------------
#include <vector>
#include <iostream>
// ------------------------------------------------------------------------------------------------
class Matilda_window: public Gtk::Window{
	void init_new_widget( Gtk::Widget*, const Glib::ustring&, const std::pair<int,int>&, Gtk::Container*);
	public:
	Glib::RefPtr<Gtk::CssProvider> styles;
	Glib::RefPtr<Gtk::StyleContext> style_context;
	Glib::RefPtr<Gdk::Screen> screen;

	Matilda_window();
	virtual ~Matilda_window(); 
	//---------------------------------------------------------------------
	protected:
	std::vector<Gtk::Image> stickers;
	std::vector<Gtk::Image> photos;
	//---------------------------------------------------------------------
	Gtk::Box* main_box;

	Gtk::Box* center_box;
	Gtk::Button run_button;
	Gtk::Button clear_button;
	Gtk::Image preview;
	//---------------------------------------------------------------------
	Gtk::Box* 		stickers_box;
	Gtk::ScrolledWindow* 	stickers_window;
	Gtk::Box* 		stickers_controls;
	Gtk::Button* 		load_stickers_button;
	Gtk::Entry* 		stickers_address_entry;
	Gtk::Grid* 		stickers_grid;
	//---------------------------------------------------------------------
	Gtk::Box* 		photos_box;
	Gtk::ScrolledWindow* 	photos_window;
	Gtk::Box* 		photos_controls;
	Gtk::Button* 		load_photos_button;
	Gtk::Entry* 		photos_address_entry;
//	Gtk::Grid photos_grid;
};

#endif
