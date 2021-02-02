#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

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
//-------------------------------------------------------------------------------------------------
class Window {
	double wth = 0;
	double hth = 0;
	std::string lbl;
	sf::RenderWindow wnd;
	std::vector<sf::Drawable*> elements;
	std::vector<sf::Texture* > textures;
	
	const void draw() { for ( long unsigned int i = 0; i < elements.size(); ++i) {wnd.draw(*elements[i]); } }
	public:
	Window(const double w, const double h, const std::string& l)
		: wth{w}, hth{h}, lbl{l}, wnd(sf::VideoMode(w,h),l) {}
	
	const long unsigned int num_of_elements() const { return elements.size(); }
	void attach(sf::Drawable* d) { elements.push_back(d); }
	void save_texture(sf::Texture* t) { textures.push_back(t);}

	void show() {
	
		while (wnd.isOpen()) {
		sf::Event event;
        	while (wnd.pollEvent(event))   {
            		if (event.type == sf::Event::Closed)
       		         wnd.close();
	       		}
        	wnd.clear();
		this->draw();
        	wnd.display();
		}	
	}
};
//-------------------------------------------------------------------------------------------------
class Texture {
	sf::Texture tr;
	std::string path;
	//---------------------------------------------------------------------
	std::string check_texture_path( const std::string& p) {
		bool find_it = std::filesystem::exists(p);
		return find_it ? p : TEXTURE_PLACEHOLDER_PATH;
	}
	//---------------------------------------------------------------------
	public:
	Texture(const std::string& p) { path = this->check_texture_path(p);  tr.loadFromFile(path); }
	sf::Texture* get_primary() { return &tr; }
};
//-------------------------------------------------------------------------------------------------
int main(){
	const std::string base_dir = loc_prefix + "assets/baseimages/";
	const std::string mark_dir = loc_prefix + "assets/marks/";
	const std::string test_base = base_dir + "matild.jpeg";
	const std::string test_mark = "node_mark.png";

	sf::Sprite sp;
	Texture* tx = new Texture(test_base);
	sp.setTexture(*tx->get_primary());

	Window* wnd = new Window(800,600,"matilda");
	wnd->attach(&sp);
	wnd->save_texture(tx->get_primary());
	wnd->show();

    return 0;

}













