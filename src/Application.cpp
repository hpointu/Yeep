#include <iostream>
#include <sstream>

#include "Application.hpp"
#include "Const.hpp"
#include "Node.hpp"
#include "Hud.hpp"
Application::Application()
{

}
void Application::init()
{
	sf::WindowSettings settings;
	settings.AntialiasingLevel = 2;
	window.Create(sf::VideoMode(W_WIDTH, W_HEIGHT, 32), "Dies Irae", sf::Style::Close, settings);

	view = new sf::View(sf::Vector2f(0, 0), sf::Vector2f(W_WIDTH/2,W_HEIGHT/2));
	view->Zoom(SCALE);
	currentZoom = SCALE;

	world = new World();

	physics_enabled = true;

	hud = new Hud();
}

void Application::_processEvents()
{
	sf::Event e;
	while(window.GetEvent(e))
	{
		switch(e.Type)
		{

		// Fermeture de fenêtre
		case sf::Event::Closed:
			window.Close();
			break;

		case sf::Event::MouseButtonPressed:
			if(e.MouseButton.Button == sf::Mouse::Left)
			{
				mouseMode = Application::Normal;
				clickPos = window.ConvertCoords(window.GetInput().GetMouseX(), window.GetInput().GetMouseY());
				Body * b = world->getHighestBodyOnPos(clickPos);
				if(b)
					world->selectBody(b);
				else
					world->clearSelection();
			}
			break;

		case sf::Event::KeyPressed:
			if(e.Key.Code == sf::Key::J)
			{
				if(world->getSelection().size() == 2)
					world->joinSelection();
				else if(world->getSelection().size() == 3)
					1==1;
				world->clearSelection();
			}
			if(e.Key.Code == sf::Key::Back)
			{
				world->resetForces();
			}
			if(e.Key.Code == sf::Key::P)
			{
				physics_enabled = !physics_enabled;
				hud->refresh();
			}
			if(e.Key.Code == sf::Key::A)
			{
				sf::Vector2f mousePos = window.ConvertCoords(
							window.GetInput().GetMouseX(),
							window.GetInput().GetMouseY()
							);
				Body *b = new Node(world->PWorld(), mousePos.x, mousePos.y);
				world->addBody(b);
				world->clearSelection();
				world->selectBody(b);
				mouseMode = Application::Move;
			}
			if(e.Key.Code == sf::Key::G)
			{
				if(mouseMode == Application::Move)
					mouseMode = Application::Normal;
				else
					mouseMode = Application::Move;

				std::cout << "mouseMode is now changed" << std::endl;
			}
			if(e.Key.Code == sf::Key::Delete)
			{
				std::vector<Body*> sel = world->getSelection();
				for(unsigned int i=0; i<sel.size(); i++)
				{
					world->enqueueToDelete(sel[i]);
				}
			}

			if(e.Key.Code == sf::Key::Left)
				view->Move(-5, 0);
			if(e.Key.Code == sf::Key::Right)
				view->Move(5, 0);
			if(e.Key.Code == sf::Key::Up)
				view->Move(0, -5);
			if(e.Key.Code == sf::Key::Down)
				view->Move(0, 5);
			break;

		default:
			break;
		}

		if(e.Type == sf::Event::MouseWheelMoved)
		{
			int delta = e.MouseWheel.Delta;
			delta /= abs(delta);
			float zoom = 1.f + (float)delta/10;

			currentZoom *= zoom;
			view->Zoom(zoom);
		}
		if((e.Type == sf::Event::MouseMoved))
		{
			sf::Vector2f mousePos = window.ConvertCoords(
						window.GetInput().GetMouseX(),
						window.GetInput().GetMouseY()
						);
			if(mouseMode == Application::Move)
			{
				world->moveSelection(mousePos);
			}
		}
	}

}
void Application::run()
{
	PausableClock clock;
	int frameCpt = 0;


	clock.Play();
	while(window.IsOpened())
	{

		window.Clear(sf::Color(255, 255, 255));
		_processEvents();

		if(physics_enabled)
			world->step();

		window.SetView(*view);
		world->render(&window);
		window.SetView(window.GetDefaultView());
		hud->render(&window);
		window.SetView(*view);

		window.Display();

		// FPS
		frameCpt++;
		if(clock.GetElapsedTime() > 1)
		{
			std::stringstream ss;
			ss << frameCpt;
			std::cout << "fps: " << ss.get() << std::endl;
			clock.Reset();
			frameCpt = 0;
		}
	}
}
