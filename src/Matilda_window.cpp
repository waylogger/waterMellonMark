#include "./Matilda_window.h"




Matilda_window::Matilda_window()
{
	//window
	this->set_resizable(false);
	this->set_default_size(1200,800);
	this->set_position(Gtk::WindowPosition::WIN_POS_CENTER);
	this->set_title("matilda_main_window");

	this->main_box			= new Gtk::Box();
	this->init_new_widget(this->main_box,"main_box",{1200,800},this);

	//left
	this->photos_window 		= new Gtk::ScrolledWindow();
	this->photos_box 		= new Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL);
	this->photos_controls 		= new Gtk::Box;
	this->load_photos_button 	= new Gtk::Button();
	this->photos_address_entry 	= new Gtk::Entry();
	
	this->init_new_widget(photos_box,"photos_box",{300,700},main_box);
		this->init_new_widget(photos_controls,"photos_controls",{100,50},photos_box);
			this->init_new_widget(photos_address_entry,"photos_address_entry",{50,50},photos_controls);
			this->init_new_widget(load_photos_button,"load_photos_button",{100,50},photos_controls);
		this->init_new_widget(photos_window,"photos_window",{0,800},photos_box);
	//center
	this->center_box		= new Gtk::Box();
	this->init_new_widget(this->center_box,"center_box",{600,800},this->main_box);

	//right
	this->stickers_box		= new Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL);
	this->stickers_window		= new Gtk::ScrolledWindow();
	this->stickers_controls 	= new Gtk::Box(Gtk::Orientation::ORIENTATION_HORIZONTAL);
	this->load_stickers_button 	= new Gtk::Button();
	this->stickers_address_entry 	= new Gtk::Entry();

	this->init_new_widget(this->stickers_box,"stickers_box",{300,700},main_box);
		this->init_new_widget(this->stickers_controls,"stickers_controls",{0,50},stickers_box);
			this->init_new_widget(load_stickers_button,"load_stickers_button",{100,50},stickers_controls);
			this->init_new_widget(stickers_address_entry,"stickers_address_entry",{50,50},stickers_controls);
		this->init_new_widget(stickers_window,"stickers_window",{0,800},stickers_box);
/*
	stickers_box.set_size_request(350,200);
	center_box.set_size_request(600,200);	

	stickers_window.set_size_request(200,700);
//	photo_window.set_size_request(200,700);

	stickers_controls->set_size_request(0,100);
	load_stickers_button->set_size_request(100,50);


	//pos

	//name
	//centr
	main_box.set_name("main_box");
	center_box.set_name("center");
	// --------------------------------------
	//left
//	photo_window.set_name("photo_window");
	// --------------------------------------
	//right
	stickers_controls->set_name("stickers_controls");
	stickers_window.set_name("stickers_window");
	load_stickers_button->set_name("load_sticker_button");
	stickers_box.set_name("stickers");

	//complectation
	//main window
	this->add(main_box);
	main_box.add(center_box);
	main_box.add(stickers_box);
	// --------------------------------------
	// --------------------------------------
	//right
	stickers_controls->add(*load_stickers_button);
	stickers_box.add(*stickers_controls);
	stickers_box.add(stickers_window);
	// --------------------------------------
	//show
	stickers_box.show_all_children();
	main_box.show_all_children();
	this->show_all_children();
*/
	//connect styles
 	this->styles = Gtk::CssProvider::create();
	this->styles->load_from_path("./view/matilda.css");
	this->style_context = Gtk::StyleContext::create();	
	this->screen = this->get_screen();
	this->style_context->add_provider_for_screen(this->screen, styles, GTK_STYLE_PROVIDER_PRIORITY_USER);
}


Matilda_window::~Matilda_window(){
	std::cerr << "Destructor is run:" << std::endl;
	delete this->stickers_controls;
	delete this->load_stickers_button;

	delete this->photos_controls;
	delete this->load_photos_button;
}


void Matilda_window::init_new_widget( Gtk::Widget* widget, const Glib::ustring& name, const std::pair<int,int>& size, Gtk::Container* port){
	widget->set_name(name);
	widget->set_size_request(size.first,size.second);
	widget->show();
	port->add(*widget);
}
