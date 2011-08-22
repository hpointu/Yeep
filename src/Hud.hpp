#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Application.hpp"
class Hud
{
public:
    Hud();

	void render(sf::RenderTarget *t);

	void setFps(int val);
	void refresh();

private:
//	std::vector<sf::Drawable*> elems;

	sf::Sprite status;
	sf::Font font1;
	sf::String fps;

	sf::Image imgPlay;
	sf::Image imgPause;
};

#endif // HUD_HPP
