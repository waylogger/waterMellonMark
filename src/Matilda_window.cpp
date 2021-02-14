#include "./Matilda_window.h"
// ------------------------------------------------------------------------------------------------
Matilda_window::Matilda_window()
{
	// event-signals zone
	this->set_events(
		Gdk::ENTER_NOTIFY_MASK | 
		Gdk::LEAVE_NOTIFY_MASK | 	
		Gdk::BUTTON_MOTION_MASK | 
		Gdk::KEY_PRESS_MASK
	);	
	// ----------------------------------------------------------------------------------------
	this->signal_key_press_event().connect(
			sigc::bind<const unsigned int>(sigc::mem_fun(*this,&Matilda_window::just_key),0)
		);	
	// ---------------------------------------------
	// init zone
	photos_extension 	= new std::vector<std::filesystem::path>{".jpeg",".jpg"};
	stickers_extension 	= new std::vector<std::filesystem::path>{".png"};
	stickers		= new std::vector<Gtk::EventBox*>;
	photos			= new std::vector<Gtk::EventBox*>;
	raw_photos		= new std::vector<Gtk::Image*>;
	raw_stickers		= new std::vector<Gtk::Image*>;
	// ---------------------------------------------
	//connect styles
 	this->styles = Gtk::CssProvider::create();
	std::ifstream ifs {"./view/matilda.css"};
	this->css 		= new Glib::ustring;
	while (ifs) {std::string s; std::getline(ifs,s); *this->css += s;}
	this->styles->load_from_data(*css);
	this->style_context = Gtk::StyleContext::create();	
	this->screen 		= this->get_screen();
	this->style_context->add_provider_for_screen(this->screen, styles, GTK_STYLE_PROVIDER_PRIORITY_USER);
	//window
	this->set_resizable(false);
	this->set_resize_mode(Gtk::ResizeMode::RESIZE_QUEUE);
	this->set_default_size(1920,800);
//	this->set_position(Gtk::WindowPosition::WIN_POS_CENTER);
	this->set_title("matilda_main_window");
	this->main_box			= new Gtk::Box();

	this->main_box->set_resize_mode(Gtk::ResizeMode::RESIZE_QUEUE);
	this->init_new_widget(this->main_box,"main_box",{1900,800},this);
	//left
	this->photos_window 		= new Gtk::ScrolledWindow();
	this->photos_box 		= new Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL);
	this->photos_controls 		= new Gtk::Box;
	this->load_photos_button 	= new Gtk::Button();
	this->photos_address_entry 	= new Gtk::Entry();
	this->photos_grid		= new Gtk::Grid();
	// ---------------------------------------------
	this->init_new_widget(photos_box,"photos_box",{300,900},main_box);
		this->init_new_widget(photos_controls,"photos_controls",{100,50},photos_box);
			this->init_new_widget(photos_address_entry,"photos_address_entry",{50,50},photos_controls);
			photos_address_entry->set_text("/home/wlr/Desktop/work/waterMellonMark/assets/baseimages");
			this->init_new_widget(load_photos_button,"load_photos_button",{100,50},photos_controls);
			load_photos_button->set_label("Фото");
			load_photos_button->signal_clicked().connect(
				sigc::mem_fun(*this,&Matilda_window::choose_photos_dir));
		this->init_new_widget(photos_window,"photos_window",{0,900},photos_box);
			this->init_new_widget(photos_grid,"photos_grid",{100,1000},this->photos_window);
	//center
	this->center_box		= new Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL);
	this->cont_draw_box		= new Gtk::Box;
	this->draw_box			= new Gtk::Fixed;
		this->draw_box->set_resize_mode(Gtk::ResizeMode::RESIZE_QUEUE);

		this->draw_box->set_border_width(0);
		listTargets.push_back( Gtk::TargetEntry("STRING")); 
		listTargets.push_back( Gtk::TargetEntry("text/plain")); 

		this->draw_box->drag_dest_set(listTargets);
		this->draw_box->signal_drag_data_received().connect(
			sigc::mem_fun(*this, &Matilda_window::central_image_drop_drag_data)
		);

	this->buttons_box		= new Gtk::Box();
	this->run_button		= new Gtk::Button("Запуск");
	this->clear_button		= new Gtk::Button("Сброс");
	this->total_clear_button	= new Gtk::Button("Общий сброс");
	this->save_button		= new Gtk::Button("Сохранение");
	this->random_button		= new Gtk::Button("Random");
	this->stickers_filters		= new Gtk::ComboBoxText;
	this->filters_text		= new Gtk::Label("overlay:",true);
	this->central_img		= new Gtk::Image();

	this->init_new_widget(this->center_box,"center_box",{1310,900},this->main_box);

	this->init_new_widget(this->cont_draw_box,"center_draw_box",{1076,650},this->center_box);
	this->init_new_widget(this->draw_box,"center_draw_box",{1076,700},this->cont_draw_box);

	margin_set(this->cont_draw_box,0);

	this->init_new_widget(this->buttons_box,"central_buttons_box",{700,50},this->center_box);
		this->init_new_widget(this->run_button,"control_button",{75,50},this->buttons_box);
		this->init_new_widget(this->random_button,"control_button",{75,50},this->buttons_box);
		this->init_new_widget(this->save_button,"control_button",{75,50},this->buttons_box);
		this->init_new_widget(this->clear_button,"control_button",{75,50},this->buttons_box);
		this->init_new_widget(this->total_clear_button,"control_button",{75,50},this->buttons_box);
		this->init_new_widget(this->filters_text,"filters_text",{100,50},this->buttons_box);
		this->init_new_widget(this->stickers_filters,"stickers_filters",{100,50},this->buttons_box);
	

		this->stickers_filters->append("random");
		this->stickers_filters->append("murphy");
		this->stickers_filters->append("screen");
		this->stickers_filters->set_active(0);

	run_button->signal_clicked().connect	
						(sigc::mem_fun(*this,&Matilda_window::run));
	save_button->signal_clicked().connect
						(sigc::mem_fun(*this,&Matilda_window::save));
	total_clear_button->signal_clicked().connect
						(sigc::mem_fun(*this,&Matilda_window::total_clear));
	clear_button->signal_clicked().connect
						(sigc::mem_fun(*this,&Matilda_window::clear));
	random_button->signal_clicked().connect
						(sigc::mem_fun(*this,&Matilda_window::random));
	stickers_filters->signal_changed().connect
						(sigc::mem_fun(*this,&Matilda_window::stickers_filters_apply));
	//right
	// ---------------------------------------------
	this->stickers_window		= new Gtk::ScrolledWindow();
	this->stickers_box		= new Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL);
	this->stickers_controls 	= new Gtk::Box;
	this->load_stickers_button 	= new Gtk::Button();
	this->stickers_address_entry 	= new Gtk::Entry();
	this->stickers_grid		= new Gtk::Grid();
	// ---------------------------------------------
	this->init_new_widget(this->stickers_box,"stickers_box",{300,700},main_box);
		this->init_new_widget(this->stickers_controls,"stickers_controls",{250,50},stickers_box);
			this->init_new_widget(stickers_address_entry,"stickers_address_entry",{50,50},stickers_controls);
			stickers_address_entry->set_text("/home/wlr/Desktop/work/waterMellonMark/assets/marks");
			this->init_new_widget(load_stickers_button,"load_stickers_button",{100,50},stickers_controls);
			load_stickers_button->set_label("Стикеры     ");
			load_stickers_button->signal_clicked().connect(
				sigc::mem_fun(*this,&Matilda_window::choose_stickers_dir));
		this->init_new_widget(stickers_window,"stickers_window",{0,900},stickers_box);
			init_new_widget(this->stickers_grid,"stickers_grid",{100,1000},this->stickers_window);

}
// ------------------------------------------------------------------------------------------------
Matilda_window::~Matilda_window(){
	std::cerr << "Destructor is run:" << std::endl;
/*
	delete this->stickers_controls;
	delete this->load_stickers_button;
	delete this->photos_controls;
	delete this->load_photos_button;
*/

}
// ------------------------------------------------------------------------------------------------
void Matilda_window::init_new_widget( Gtk::Widget* widget, const Glib::ustring& name, const std::pair<int,int>& size, Gtk::Container* port){
	widget->set_name(name);
	widget->set_size_request(size.first,size.second);
	widget->show();
	port->add(*widget);
}
// ------------------------------------------------------------------------------------------------
void Matilda_window::init_new_widget( Gtk::Widget* widget, const Glib::ustring& name, const std::pair<int,int>& size, Gtk::Grid* port, const int pos){
	widget->set_name(name);
	widget->set_size_request(size.first,size.second);
	widget->show();
	int x = pos%2;
	int y = pos/2;
	port->attach(*widget,x,y);
}
// ------------------------------------------------------------------------------------------------
void Matilda_window::init_new_widget( Gtk::Widget* widget, const Glib::ustring& name, const std::pair<int,int>& size, Gtk::Fixed* port, const int x, const int y){
	widget->set_name(name);
	widget->set_size_request(size.first,size.second);
	widget->show();
	port->put(*widget,x,y);
}
// ------------------------------------------------------------------------------------------------
void Matilda_window::choose_photos_dir() {
	Glib::ustring inp = this->photos_address_entry->get_text();
	if (inp.size() != 0 ) {
		this->photos_read_and_place(inp,photos_grid);
		return;
	}
	Gtk::FileChooserDialog dialog("Пожалуйста, выберите папку", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
	dialog.set_transient_for(*this);
	dialog.add_button("Отмена",Gtk::RESPONSE_CANCEL);	
	dialog.add_button("Выбрать",Gtk::RESPONSE_OK);
	int result = dialog.run();
	if (result == Gtk::RESPONSE_OK) { 
		const Glib::ustring path = dialog.get_filename();
		this->photos_address_entry->set_text(path);
		this->photos_read_and_place(path,photos_grid);
}
}
// ------------------------------------------------------------------------------------------------
void Matilda_window::choose_stickers_dir() {

	Glib::ustring inp = this->stickers_address_entry->get_text();
	if (inp.size() != 0 ) {
		this->stickers_read_and_place(inp,photos_grid);
		return;
	}
	Gtk::FileChooserDialog dialog("Пожалуйста, выберите папку", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
	dialog.set_transient_for(*this);
	dialog.add_button("Отмена",Gtk::RESPONSE_CANCEL);	
	dialog.add_button("Выбрать",Gtk::RESPONSE_OK);
	int result = dialog.run();
	if (result == Gtk::RESPONSE_OK) { 
		const Glib::ustring path = dialog.get_filename();
		this->stickers_address_entry->set_text(path);
		this->stickers_read_and_place(path,stickers_grid);
}
}
// ------------------------------------------------------------------------------------------------
void Matilda_window::stickers_read_and_place(const Glib::ustring& path, Gtk::Grid* grid){
	for (auto& p: *this->stickers) {p->hide(); delete p;}
	this->stickers->erase(stickers->begin(),stickers->end());
	for (auto& p: *this->raw_stickers) {p->hide(); delete p;}
	this->raw_stickers->erase(raw_stickers->begin(),raw_stickers->end());
//-------------------------------------
    int inx = 0;
    for(auto& p: std::filesystem::directory_iterator(std::string(path))){
		if (std::find(this->stickers_extension->begin(), this->stickers_extension->end(),p.path().extension()) == this->stickers_extension->end()) continue;
		Gtk::Image* img = new Gtk::Image(p.path());	
		auto pixbuf = img->get_pixbuf();
		auto newbuf = pixbuf->scale_simple(this->stickers_width,this->stickers_height,Gdk::InterpType::INTERP_NEAREST);
		Gtk::Image* nimg = new Gtk::Image(newbuf);
		Gtk::Image* simg = new Gtk::Image(newbuf);
		nimg->show();
		Gtk::EventBox* eb = new Gtk::EventBox;	
		Gtk::EventBox* seb = new Gtk::EventBox;

		eb->set_events(Gdk::ENTER_NOTIFY_MASK | Gdk::LEAVE_NOTIFY_MASK | Gdk::BUTTON_MOTION_MASK | Gdk::KEY_PRESS_MASK | Gdk::BUTTON_PRESS_MASK);
		seb->set_events(
		Gdk::ENTER_NOTIFY_MASK | 
		Gdk::LEAVE_NOTIFY_MASK | 
		Gdk::BUTTON_MOTION_MASK | 
		Gdk::KEY_PRESS_MASK | 
		Gdk::BUTTON_PRESS_MASK |
		Gdk::SCROLL_MASK);
		eb->drag_source_set(listTargets);
		seb->drag_source_set(listTargets);


		eb->signal_drag_data_get().connect(
			sigc::bind<const unsigned int>(sigc::mem_fun(*this,&Matilda_window::stickers_drag_data_set),inx)
		);	
		seb->signal_drag_data_get().connect(
			sigc::bind<const unsigned int>(sigc::mem_fun(*this,&Matilda_window::stickers_drag_data_set),inx)
		);	
		seb->signal_button_press_event().connect(
			sigc::bind<const unsigned int>(sigc::mem_fun(*this,&Matilda_window::click_sticker),inx)
		);
		seb->signal_scroll_event().connect(
			sigc::bind<const unsigned int>(sigc::mem_fun(*this,&Matilda_window::scroll_it),inx)
			);


		this->init_new_widget(eb,"stickers_grid_eventbox",{this->stickers_width,this->stickers_height},this->stickers_grid,this->stickers->size());
		this->init_new_widget(nimg,"stickers_grid_img",{0,0},eb);
		this->init_new_widget(simg,"stickers_grid_img_on_table",{this->stickers_width,this->stickers_height},seb);
		nimg->set_opacity(0.9);
		//---------------------------------------------------------------------------------
		eb->signal_enter_notify_event().connect (
			//binding signal handlers
			sigc::bind<const unsigned int>(sigc::mem_fun(*this,&Matilda_window::enter_crossing_stickers),inx)
		);
		eb->signal_leave_notify_event().connect(
			sigc::bind<const unsigned int>(sigc::mem_fun(*this,&Matilda_window::leave_crossing_stickers),inx)
		);
/*
		eb->signal_button_press_event().connect(
			sigc::bind<const unsigned int>(sigc::mem_fun(*this,&Matilda_window::photo_activate),inx)
		);
*/
		//---------------------------------------------------------------------------------
		eb->set_margin_right(5);
		eb->set_margin_left(5);
		eb->set_margin_top(5);
		eb->set_margin_bottom(5);
		//----------------------------------------
		stickers->push_back(eb);
		small_stickers.push_back(seb);
		stickers_rotate_rate.push_back(0);
		stickers_scale_rate.push_back(1);
		stickers_size.push_back({this->stickers_width,this->stickers_height});

		raw_stickers->push_back(img);
		++inx;
	}
}
// ------------------------------------------------------------------------------------------------
void Matilda_window::photos_read_and_place(const Glib::ustring& path, Gtk::Grid* grid){
	for ( unsigned int i = 0; i < photos->size(); ++i) {
		Gtk::EventBox* eb = (*photos)[i];
		delete eb;	
	}
	
	for (auto& a: *raw_photos) { delete a; }
	this->photos->erase(photos->begin(),photos->end());
	this->photos->erase(photos->begin(),photos->end());
	this->raw_photos->erase(raw_photos->begin(),raw_photos->end());

	unsigned int inx = 0;
    for(auto& p: std::filesystem::directory_iterator(std::string(path))){
		if (std::find(this->photos_extension->begin(), this->photos_extension->end(),p.path().extension()) == this->photos_extension->end()) continue;
		Gtk::Image* img = new Gtk::Image(p.path());	
		auto pixbuf = img->get_pixbuf();
		auto newbuf = pixbuf->scale_simple(135,135,Gdk::InterpType::INTERP_NEAREST);
		Gtk::Image* nimg = new Gtk::Image(newbuf);
		nimg->set_opacity(0.9);
		nimg->show();
		Gtk::EventBox* eb = new Gtk::EventBox;	
		eb->set_events(Gdk::ENTER_NOTIFY_MASK | Gdk::LEAVE_NOTIFY_MASK | Gdk::BUTTON_MOTION_MASK | Gdk::BUTTON_PRESS_MASK);
		
		//nimg->set_state_flags(Gtk::STATE_FLAG_PRELIGHT);
		this->init_new_widget(eb,"photos_grid_eventbox",{125,125},this->photos_grid,this->photos->size());
		this->init_new_widget(nimg,"photos_grid_img",{0,0},eb);
		//---------------------------------------------------------------------------------
		eb->signal_enter_notify_event().connect (
			//binding signal handlers
			sigc::bind<const unsigned int>(sigc::mem_fun(*this,&Matilda_window::enter_crossing_photos),inx)

		);
		eb->signal_leave_notify_event().connect(
			sigc::bind<const unsigned int>(sigc::mem_fun(*this,&Matilda_window::leave_crossing_photos),inx)
		);

		eb->signal_button_press_event().connect(
			sigc::bind<const unsigned int>(sigc::mem_fun(*this,&Matilda_window::photo_activate),inx)
		);
		//---------------------------------------------------------------------------------
		margin_set(eb,5);

		photos->push_back(eb);
		raw_photos->push_back(img);
		inx++;
	}
}
//-------------------------------------------------------------------------------------------------
void margin_set(Gtk::Widget* widget, const int margin){
		widget->set_margin_right(5);
		widget->set_margin_left(5);
		widget->set_margin_top(5);
		widget->set_margin_bottom(5);

}
//-------------------------------------------------------------------------------------------------
	void			Matilda_window::save(){ std::cout << "save_button_is_pressed\n";};
//-------------------------------------------------------------------------------------------------
	void			Matilda_window::run(){ std::cout << "run_button_is_pressed\n";};
//-------------------------------------------------------------------------------------------------
	void			Matilda_window::clear(){ this->clear_central_image();};
//-------------------------------------------------------------------------------------------------
	void			Matilda_window::total_clear(){ std::cout << "total_clear_button_is_pressed\n";};
//-------------------------------------------------------------------------------------------------
	void			Matilda_window::random(){ std::cout << "random_button_is_pressed\n";};
//-------------------------------------------------------------------------------------------------
	void			Matilda_window::stickers_filters_apply(){ std::cout << this->stickers_filters->get_active_text() + ": filters was applyed\n";};
//-------------------------------------------------------------------------------------------------
	bool			Matilda_window::hover()			{ std::cout << "HOVER\n"; return true;};
// ----------------------------------------------------------------------------------------
	void			Matilda_window::clear_central_image()	{for ( auto& a: this->small_stickers) draw_box->remove(*a);}
// ----------------------------------------------------------------------------------------
	void 			Matilda_window::clear_draw_box()	{ draw_box->remove(*this->central_img);}
//-----------------------------------------------------------------------	
bool 			Matilda_window::enter_crossing_photos(GdkEventCrossing* ce, const unsigned int i) {	
				(*photos)[i]->set_state_flags(Gtk::STATE_FLAG_PRELIGHT);
				return true;
	}
// ----------------------------------------------------------------------------------------
	bool 			Matilda_window::leave_crossing_photos(GdkEventCrossing* ce, const unsigned int i) {	
				(*photos)[i]->unset_state_flags(Gtk::STATE_FLAG_PRELIGHT);
				return true;
	}
// ----------------------------------------------------------------------------------------
	bool 			Matilda_window::enter_crossing_stickers(GdkEventCrossing* ce, const unsigned int i) {	
				(*stickers)[i]->set_state_flags(Gtk::STATE_FLAG_PRELIGHT);
				return true;
	}
// ----------------------------------------------------------------------------------------
	bool 			Matilda_window::leave_crossing_stickers(GdkEventCrossing* ce, const unsigned int i) {	
				(*stickers)[i]->unset_state_flags(Gtk::STATE_FLAG_PRELIGHT);
				return true;
	}
// ----------------------------------------------------------------------------------------
	bool			Matilda_window::photo_activate(GdkEventButton*, const unsigned int i) {
		this->clear_central_image();
		this->clear_draw_box();
		auto buf0 = (*raw_photos)[i]->get_pixbuf();
		central_img->set(buf0->scale_simple(1076,700,Gdk::InterpType::INTERP_HYPER));
		init_new_widget(central_img,"central_img",{0,0},draw_box,0,0);
		return true;
	}
// ----------------------------------------------------------------------------------------
	bool	Matilda_window::just_key(GdkEventKey* key_event, const unsigned int){
		return true;
	}
// ----------------------------------------------------------------------------------------
	bool Matilda_window::copy_sticker( const unsigned int inx) {
		return true;
	}
// ----------------------------------------------------------------------------------------
	bool Matilda_window::click_sticker(GdkEventButton* b, const unsigned int inx) {
		//delete sticker		
		if ( b->button == 1 && ((b->state & Gdk::MOD1_MASK) == Gdk::MOD1_MASK) )draw_box->remove(*small_stickers[inx]);
		else if ( b->button == 1 && ((b->state & Gdk::CONTROL_MASK) == Gdk::CONTROL_MASK) ) return copy_sticker(inx);
		return true;
	}
// ----------------------------------------------------------------------------------------
	bool Matilda_window::scale_sticker(GdkEventScroll* scroll, const unsigned int inx) {
	// -------------------- fetch imag;
	Gtk::Image* par_img = dynamic_cast<Gtk::Image*>((*stickers)[inx]->get_child());
	Glib::RefPtr< Gdk::Pixbuf > pixbuf = par_img->get_pixbuf(); 
	// --------------------	copy image
	Gtk::Image* img = new Gtk::Image(pixbuf);
	Glib::RefPtr< Gdk::Pixbuf > old_pixbuf = img->get_pixbuf(); 
	// -------------------- prepare data
	double d = scroll->direction == GdkScrollDirection::GDK_SCROLL_UP ? 0.2 : -0.2;
	const double zoom = this->calc_zoom_for_scale(inx,d);
	const double surface_w = old_pixbuf->get_width() * zoom;
	const double surface_h = old_pixbuf->get_height() * zoom;
	// --------------------- prepace Cairo objects
	Cairo::RefPtr<Cairo::Region> 		region = Cairo::Region::create();
	Cairo::RefPtr<Cairo::ImageSurface> 	surface = Cairo::ImageSurface::create(Cairo::Format::FORMAT_ARGB32,surface_w,surface_h);
	Cairo::RefPtr<Cairo::Context> 		cr = Cairo::Context::create(surface);

	// ---------------------
	Glib::RefPtr<Gdk::Window> 		win = this->small_stickers[inx]->get_window();
	Glib::RefPtr<Gdk::DrawingContext> 	draw_context = win->begin_draw_frame(region);
	// --------------------- change image
	cr->translate (surface_w*0.5, surface_h*0.5);
	cr->rotate_degrees(stickers_rotate_rate[inx]);
	cr->scale(zoom,zoom);
	cr->translate(-this->stickers_width/2,-this->stickers_height/2);
	// --------------------- apply
	Gdk::Cairo::set_source_pixbuf(cr,old_pixbuf);
	cr->paint();
	// --------------------- clear
	win->end_draw_frame(draw_context);
	delete img;
	// --------------------- save_results
	Glib::RefPtr<Gdk::Pixbuf> nbuf = Gdk::Pixbuf::create(cr->get_target(),0,0,surface_w,surface_h);
	Gtk::Image* res_im = dynamic_cast<Gtk::Image*>(small_stickers[inx]->get_child());
	res_im->set(nbuf);
		return true;
	}
// ------------------------------------------------------------------------------------------------
	bool Matilda_window::rotate_sticker(GdkEventScroll* scroll, const unsigned int inx) {
	// ------------------------------------------------	
	Gtk::Image* par_img = dynamic_cast<Gtk::Image*>((*stickers)[inx]->get_child());
	Glib::RefPtr< Gdk::Pixbuf > pixbuf = par_img->get_pixbuf(); 
	// ------------------------------------------------	
	Gtk::Image* img = new Gtk::Image(pixbuf);
	// ------------------------------------------------	
	Glib::RefPtr< Gdk::Pixbuf > old_pixbuf = img->get_pixbuf(); 
	Glib::RefPtr<Gdk::Window> win = small_stickers[inx]->get_window();
	Cairo::RefPtr<Cairo::Region> region = Cairo::Region::create();
	Glib::RefPtr<Gdk::DrawingContext> draw_context = win->begin_draw_frame(region);
	// ------------------------------------------------	
	double d = scroll->direction == GdkScrollDirection::GDK_SCROLL_UP ? 5 : -5;
	const double zoom = stickers_scale_rate[inx];
	const double degree = calc_degree_for_rotate_sticker(inx,d);
	const double surface_w = old_pixbuf->get_width() * zoom;
	const double surface_h = old_pixbuf->get_height() * zoom;
	// ------------------------------------------------	
	Cairo::RefPtr<Cairo::ImageSurface> surface = Cairo::ImageSurface::create(Cairo::Format::FORMAT_ARGB32,surface_w,surface_h);
	Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);
	//rotate by central point
	cr->translate (surface_w*0.5, surface_h*0.5);
	cr->rotate_degrees(degree);
	cr->scale(zoom,zoom);
	cr->translate(-this->stickers_width/2,-this->stickers_height/2);
	Gdk::Cairo::set_source_pixbuf(cr,old_pixbuf);
	cr->paint();
	win->end_draw_frame(draw_context);
	// ------------------------------------------------	
	dynamic_cast<Gtk::Image*>(small_stickers[inx]->get_child())->set(Gdk::Pixbuf::create(cr->get_target(),0,0,surface_w,surface_h));
	delete img;
	return true;
	}
// ------------------------------------------------------------------------------------------------	
	bool Matilda_window::scroll_it(GdkEventScroll* scroll, const unsigned int inx) {

		return (scroll->state & Gdk::CONTROL_MASK) == Gdk::CONTROL_MASK ? scale_sticker(scroll,inx) : rotate_sticker(scroll,inx);
	}
// ------------------------------------------------------------------------------------------------	
	void Matilda_window::stickers_drag_data_set(
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
	void Matilda_window::central_image_drop_drag_data(
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
		Glib::RefPtr<Gdk::Pixbuf> pixbuf = dynamic_cast<Gtk::Image*>(sticker->get_child())->get_pixbuf();
		this->init_new_widget(
			sticker,
			"name",
			{sticker->get_width(),sticker->get_height()},
			this->draw_box,
			x-pixbuf->get_width()/2,
			y-pixbuf->get_height()/2);
		context->drag_finish(false,false,time);

	}
	
// ------------------------------------------------------------------------------------------------
	double Matilda_window::calc_degree_for_rotate_sticker(const unsigned int inx, const double degree) {
		this->stickers_rotate_rate[inx] += degree;
		return this->stickers_rotate_rate[inx];
	}
// ------------------------------------------------------------------------------------------------
	double Matilda_window::calc_zoom_for_scale (const unsigned int inx, const double zoom){
		const double total_zoom = this->stickers_scale_rate[inx] + zoom;
		if (total_zoom < 2.3 && total_zoom > 0.4 )
			stickers_scale_rate[inx] = total_zoom;
		return stickers_scale_rate[inx];
	}


