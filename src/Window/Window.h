#ifndef WLR_WINDOW
#define WLR_WINDOW

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace wlr_gui {
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
class Window { //for use need construct and call show();
	double wth = 0;
	double hth = 0;
	std::string lbl;

	sf::RenderWindow* wnd;
	std::vector<sf::Drawable*> elements;

	virtual void draw_spec() = 0;
	void draw(); 
	protected:
	double width() const {return wth;};
	double height() const {return hth;};
	
	sf::RenderWindow* base() const {return wnd;}
	public:
	Window(const double w, const double h, const std::string& l);
	const long unsigned int num_of_elements() const; 

	void attach(sf::Drawable* d);
	void show();
};
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
}//end of namespace wlr_gui
#endif
