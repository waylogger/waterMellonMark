#include "./Matilda_window.h"


int main(int argc, char* argv[]) {
	
	auto app = Gtk::Application::create(argc,argv,"Matilda.WaterMarks");
	
	Matilda_window mw;
	
	return app->run(mw);

}

