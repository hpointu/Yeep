#include "Application.hpp"

int main(int argc, char **argv)
{

	Application *a = Application::getInstance();
	a->init();
	a->run();

	return 0;
}


