#ifndef MATILDA_WINDOW_H
#define MATILDA_WINDOW_H

#include <gtkmm.h>

#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/eventbox.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/entry.h>
#include <gtkmm/dialog.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/textview.h>
#include <gtkmm/label.h>
#include <gtkmm/fixed.h>
#include <gtkmm/drawingarea.h>

// ------------------------------------------------------------------------------------------------
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <iterator>

void margin_set(Gtk::Widget* widget, const int margin);
bool is_set(const guint& state, const unsigned int set);
// ------------------------------------------------------------------------------------------------
class Matilda_window: public Gtk::Window{

	const double stickers_width = 125;
	const double stickers_height = this->stickers_width;
	public:
	Glib::RefPtr<Gtk::CssProvider>     styles;
	Glib::RefPtr<Gtk::StyleContext>	   style_context;
	Glib::RefPtr<Gdk::Screen> 	   screen;
	
	Matilda_window();
	virtual ~Matilda_window(); 
	Glib::ustring* 			    css 		= nullptr;
	std::vector<std::filesystem::path>* photos_extension 	= nullptr;
	std::vector<std::filesystem::path>* stickers_extension 	= nullptr;
	//---------------------------------------------------------------------
	private:
	std::vector<Gtk::EventBox*>* stickers			= nullptr;
	std::vector<Gtk::EventBox*>* photos			= nullptr;

	std::vector<double> stickers_rotate_rate;
	std::vector<double> stickers_scale_rate;
	std::vector<std::pair<double,double>> stickers_size;

	std::vector<Gtk::Image*>* raw_photos			= nullptr;
	std::vector<Gtk::Image*>* raw_stickers			= nullptr;


	std::vector<Gtk::TargetEntry> listTargets;
	std::vector<Gtk::EventBox*> small_stickers;
	std::vector<unsigned int> drawed_stickers_inxs;

	//---------------------------------------------------------------------
	Gtk::Box* 		center_box 			= nullptr;
	Gtk::Fixed*		draw_box			= nullptr;
	Gtk::Box*		cont_draw_box			= nullptr;
	Gtk::Box*		buttons_box			= nullptr;
	Gtk::Image*		central_img			= nullptr;
	Gtk::Button*		run_button			= nullptr;
	Gtk::Button*		clear_button			= nullptr;
	Gtk::Button*		save_button			= nullptr;
	Gtk::Button*		total_clear_button		= nullptr;
	Gtk::Button*		random_button			= nullptr;
	Gtk::ComboBoxText*	stickers_filters		= nullptr;
	Gtk::Label*		filters_text			= nullptr;
	//---------------------------------------------------------------------
	//left
	void photos_read_and_place(const Glib::ustring& path, Gtk::Grid*);
	Gtk::Box* 		photos_box			= nullptr;
	Gtk::ScrolledWindow* 	photos_window			= nullptr;
	Gtk::Box* 		photos_controls			= nullptr;
	Gtk::Button* 		load_photos_button 		= nullptr;
	Gtk::Entry* 		photos_address_entry 		= nullptr;
	Gtk::Button*		image_button 			= nullptr;
	Gtk::Grid* 		photos_grid			= nullptr;
	//---------------------------------------------------------------------
	//right
	void stickers_read_and_place(const Glib::ustring& path, Gtk::Grid*);
	Gtk::Box* 		stickers_box			= nullptr;
	Gtk::ScrolledWindow* 	stickers_window			= nullptr;
	Gtk::Box* 		stickers_controls		= nullptr;
	Gtk::Button* 		load_stickers_button		= nullptr;
	Gtk::Entry* 		stickers_address_entry		= nullptr;
	Gtk::Grid* 		stickers_grid			= nullptr;
	//---------------------------------------------------------------------
	Gtk::Box* 		main_box;
	//---------------------------------------------------------------------
	//center
	void			save();
	void			run();
	void			clear();
	void			total_clear();
	void			random();
	void			stickers_filters_apply();
	bool			hover();
	// ----------------------------------------------------------------------------------------
	void			clear_central_image();
	// ----------------------------------------------------------------------------------------
	void 			clear_draw_box();
	//-----------------------------------------------------------------------	
	bool 			enter_crossing_photos(GdkEventCrossing* ce, const unsigned int i);
	// ----------------------------------------------------------------------------------------
	bool 			leave_crossing_photos(GdkEventCrossing* ce, const unsigned int i);
	// ----------------------------------------------------------------------------------------
	bool 			enter_crossing_stickers(GdkEventCrossing* ce, const unsigned int i);
	// ----------------------------------------------------------------------------------------
	bool 			leave_crossing_stickers(GdkEventCrossing* ce, const unsigned int i);
	// ----------------------------------------------------------------------------------------
	bool			photo_activate(GdkEventButton*, const unsigned int i);
	// ----------------------------------------------------------------------------------------
	bool	just_key(GdkEventKey* key_event, const unsigned int);
	// ----------------------------------------------------------------------------------------
	bool copy_sticker( const unsigned int inx);
	// ----------------------------------------------------------------------------------------
	bool click_sticker(GdkEventButton* b, const unsigned int inx);
	// ----------------------------------------------------------------------------------------
	bool scale_sticker(GdkEventScroll* scroll, const unsigned int inx);
	// ----------------------------------------------------------------------------------------
	bool rotate_sticker(GdkEventScroll* scroll, const unsigned int inx);
	// ----------------------------------------------------------------------------------------
	bool scroll_it(GdkEventScroll* scroll, const unsigned int inx);
	// ----------------------------------------------------------------------------------------
	void stickers_drag_data_set(
		const Glib::RefPtr<Gdk::DragContext>& context,
		Gtk::SelectionData& selection_data, 
		guint info, 
		guint time, 
		const unsigned int inx);
	// ----------------------------------------------------------------------------------------
	void central_image_drop_drag_data(
		const Glib::RefPtr<Gdk::DragContext>& context, 
		int x, 
		int y,
		const Gtk::SelectionData& selection_data,
		guint info,
		guint time);


	void init_new_widget( Gtk::Widget*, const Glib::ustring&, const std::pair<int,int>&, Gtk::Container*);
	void init_new_widget( Gtk::Widget*, const Glib::ustring&, const std::pair<int,int>&, Gtk::Grid*, const int);
	void init_new_widget( Gtk::Widget*, const Glib::ustring&, const std::pair<int,int>&, Gtk::Fixed*, const int x, const int y);

	void choose_photos_dir	();
	void choose_stickers_dir();
	double calc_degree_for_rotate_sticker(const unsigned int inx, const double degree);
	double calc_zoom_for_scale (const unsigned int inx, const double zoom);


	};



#endif
