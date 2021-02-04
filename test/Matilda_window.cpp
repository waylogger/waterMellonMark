#include "Matilda_window.h"


Matilda_window::Matilda_window():
		exit_button("exit"), run_button("run") {
	this->set_default_size(800,600);
	this->set_border_width(10);
	
	//set widgets signals
	exit_button.signal_clicked().connect(sigc::mem_fun(*this,&Matilda_window::on_button_clicked));
	this->add(h1_box);	
	h1_box.pack_start(exit_button);
	h1_box.pack_start(run_button);
	run_button.show();
	exit_button.show();
	h1_box.show();
//	exit_button.show();
}

Matilda_window::~Matilda_window(){}

void Matilda_window::on_button_clicked(){
	this->close();
}
