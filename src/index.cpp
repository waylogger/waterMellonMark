#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

#include "./Window/Window.h"
#include "./Window/Texture.h"

#include <SFML/Graphics/RectangleShape.hpp>


const std::string loc_prefix = "./";
const std::string TEXTURE_PLACEHOLDER_PATH = loc_prefix + "assets/err_texture.png";
//-------------------------------------------------------------------------------------------------
class Image{
	public:
	Image(const std::string& path) {
	//read from database	
	}

	~Image(){ ; }
};
//-------------------------------------------------------------------------------------------------
class Image_set {
	private:
	std::vector<Image> imagesData;
	public:
	Image_set(const std::string& dirname) {
		//init database
		//imagesData.pushback();
	}
};
//-------------------------------------------------------------------------------------------------
class pairImageSet{
	Image_set* base_images = nullptr;
	Image_set* mark_images = nullptr;
	public:
	pairImageSet(const std::string& basedir, const std::string& marks) {
		base_images = new Image_set(basedir);
		mark_images = new Image_set(marks);
	}
	~pairImageSet(){
		delete base_images;
		delete mark_images;
	}
};

class Matilda_window: public wlr_gui::Window{

	std::vector<sf::Texture*> base_textures;
	std::vector<sf::Texture*> mark_textures;
	std::vector<sf::Sprite*>stickerMarks;
	std::vector<sf::Sprite*>bases;

	sf::RectangleShape background;

	unsigned int xpos = 0;
	unsigned int ypos = 0;

	public:	
	Matilda_window(
		const double w, 
		const double h, 
		const std::string& l, 
		const std::string& assets_dir,
		const std::string& base_dir, 
		const std::string& mark_dir) : wlr_gui::Window(w,h,l) {
	
		to_center();
		draw_background();
	

	//read markdir
	//fulling mark_textures
	}

	void to_center() {
		xpos = sf::VideoMode::getDesktopMode().width/2 - this->width()/2;
		ypos = sf::VideoMode::getDesktopMode().height/2 - this->height()/2;
		this->base()->setPosition(sf::Vector2i(xpos,ypos));
	}

	void draw_background() {
		background.setSize(sf::Vector2f(this->width(),this->height()));
		background.setFillColor(sf::Color(189, 183, 107));
		this->attach(&background);
	}
	void draw_spec() override {return;};
};
//-------------------------------------------------------------------------------------------------
int main(){
	const std::string assets_dir = loc_prefix + "assets/";
	const std::string base_dir = assets_dir + "baseimages/";
	const std::string mark_dir = assets_dir + "marks/";
	Matilda_window* mw = new Matilda_window(1200,600,"matilda",assets_dir,base_dir,mark_dir);

	mw->show();
    return 0;

}













