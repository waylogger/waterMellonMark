#include "Matilda_window.h"




int main(int argc, char* argv[]) {
		
	auto app = Gtk::Application::create(argc,argv,"Matilda");

	Matilda_window* mw = new Matilda_window;

	return app->run(*mw);
}
