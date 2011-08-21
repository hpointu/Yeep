#include <SFML/Graphics.hpp>
#include "Singleton.h"
#include <iostream>

class ImageManager : public Singleton<ImageManager>
{
	friend class Singleton<ImageManager>;
	
private:
	ImageManager()
	{
		if(!play.LoadFromFile("res/play.png"))
		{
			std::cout << "Erreur de chargement de l'image" << std::endl;
		}
		if(!pause.LoadFromFile("res/pause.png"))
		{
			std::cout << "Erreur de chargement de l'image" << std::endl;
		}
		
	}
	
	sf::Image play, pause;
	
public:
	sf::Image* getImage(std::string str)
	{
		if(str == "play")
		{
			return &play;
		}
		
		if(str == "pause")
		{
			return &pause;
		}
		return NULL;
	}
};
