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
	void init_new_widget( Gtk::Widget*, const Glib::ustring&, const std::pair<int,int>&, Gtk::Container*);
	void init_new_widget( Gtk::Widget*, const Glib::ustring&, const std::pair<int,int>&, Gtk::Grid*, const int);
	void init_new_widget( Gtk::Widget*, const Glib::ustring&, const std::pair<int,int>&, Gtk::Fixed*, const int x, const int y);

	void choose_photos_dir	();
	void choose_stickers_dir();
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
	protected:
	std::vector<Gtk::EventBox*>* stickers			= nullptr;
	std::vector<Gtk::EventBox*>* photos			= nullptr;

	std::vector<Gtk::Image*>* raw_photos			= nullptr;
	std::vector<Gtk::Image*>* raw_stickers			= nullptr;


	std::vector<Gtk::TargetEntry> listTargets;
	std::vector<Gtk::EventBox*> small_stickers;
	std::vector<unsigned int> drawed_stickers_inxs;


	//---------------------------------------------------------------------
	Gtk::Box* 		main_box;
	//---------------------------------------------------------------------
	//center
	void			save(){ std::cout << "save_button_is_pressed\n";};
	void			run(){ std::cout << "run_button_is_pressed\n";};
	void			clear(){ this->clear_central_image();};
	void			total_clear(){ std::cout << "total_clear_button_is_pressed\n";};
	void			random(){ std::cout << "random_button_is_pressed\n";};
	void			stickers_filters_apply(){ std::cout << this->stickers_filters->get_active_text() + ": filters was applyed\n";};
	bool			hover()			{ std::cout << "HOVER\n"; return true;};
	// ----------------------------------------------------------------------------------------
	void			clear_central_image()	{for ( auto& a: this->small_stickers) draw_box->remove(*a);}
	// ----------------------------------------------------------------------------------------
	void 			clear_draw_box()	{ draw_box->remove(*this->central_img);}
	//-----------------------------------------------------------------------	
	// signals
	// signals data
	// signals functions
	bool 			enter_crossing_photos(GdkEventCrossing* ce, const unsigned int i) {	
				(*photos)[i]->set_state_flags(Gtk::STATE_FLAG_PRELIGHT);
				return true;
	}
	// ----------------------------------------------------------------------------------------
	bool 			leave_crossing_photos(GdkEventCrossing* ce, const unsigned int i) {	
				(*photos)[i]->unset_state_flags(Gtk::STATE_FLAG_PRELIGHT);
				return true;
	}
	// ----------------------------------------------------------------------------------------
	bool 			enter_crossing_stickers(GdkEventCrossing* ce, const unsigned int i) {	
				(*stickers)[i]->set_state_flags(Gtk::STATE_FLAG_PRELIGHT);
				return true;
	}
	// ----------------------------------------------------------------------------------------
	bool 			leave_crossing_stickers(GdkEventCrossing* ce, const unsigned int i) {	
				(*stickers)[i]->unset_state_flags(Gtk::STATE_FLAG_PRELIGHT);
				return true;
	}
	// ----------------------------------------------------------------------------------------
	bool			photo_activate(GdkEventButton*, const unsigned int i) {
		this->clear_central_image();
		this->clear_draw_box();
		auto buf0 = (*raw_photos)[i]->get_pixbuf();
		central_img->set(buf0->scale_simple(1076,700,Gdk::InterpType::INTERP_HYPER));
		init_new_widget(central_img,"central_img",{0,0},draw_box,0,0);
		return true;
	}
	
	bool	just_key(GdkEventKey* key_event, const unsigned int){
		return true;
	}
	// ----------------------------------------------------------------------------------------
	bool delete_sticker(GdkEventButton* b, const unsigned int inx){
		if ( b->button == 1 && ((b->state & Gdk::MOD1_MASK) == Gdk::MOD1_MASK) )draw_box->remove(*small_stickers[inx]);
		return true;
	}
	
	bool rotate_sticker(GdkEventScroll* scroll, const unsigned int inx) {
		
	Gtk::Image* img = dynamic_cast<Gtk::Image*>(small_stickers[inx]->get_child());
	Glib::RefPtr< Gdk::Pixbuf > old_pixbuf = img->get_pixbuf(); 
	Glib::RefPtr<Gdk::Window> win = small_stickers[inx]->get_window();

	Cairo::RefPtr<Cairo::Context> cr = win->create_cairo_context();
	
	const double degree = 180;
	double w = img->get_width();
	double h = img->get_height();


	cr->translate (w*0.5, h*0.5);
	cr->rotate (degree*3.14/180);
	cr->translate (-0.5*w, -0.5*h);

	Gdk::Cairo::set_source_pixbuf(cr,old_pixbuf);
	cr->paint();
		return true;
	}


	// ----------------------------------------------------------------------------------------
	void stickers_drag_data_set(
		const Glib::RefPtr<Gdk::DragContext>& context,
		Gtk::SelectionData& selection_data, 
		guint info, 
		guint time, 
		const unsigned int inx){
			selection_data.set(
				selection_data.get_target(),
				8,
				(const guchar*)(std::to_string(inx).c_str()),
				64
			);
		}
	// ----------------------------------------------------------------------------------------
	void central_image_drop_drag_data(
		const Glib::RefPtr<Gdk::DragContext>& context, 
		int x, 
		int y,
		const Gtk::SelectionData& selection_data,
		guint info,
		guint time){

		std::string s = selection_data.get_data_as_string();
		unsigned int inx = std::stoul(s);
		if ( std::find(this->drawed_stickers_inxs.begin(),this->drawed_stickers_inxs.end(), inx) != this->drawed_stickers_inxs.end() ) {
			this->draw_box->remove(*this->small_stickers[inx]);	
		}
		else
			drawed_stickers_inxs.push_back(inx);
		Gtk::EventBox* sticker = small_stickers[inx];
		this->init_new_widget(sticker,"name",{125,125},this->draw_box,x-125/2,y-125/2);
		context->drag_finish(false,false,time);

	}
		
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
};



#endif
