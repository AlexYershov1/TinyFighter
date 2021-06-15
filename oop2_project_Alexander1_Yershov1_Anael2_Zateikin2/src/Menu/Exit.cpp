#include "Menu/Exit.h"


Exit::Exit()
{
}

Exit::~Exit()
{
}

void Exit::execute(sf::RenderWindow& window, Arena&)
{
	window.close();
}
