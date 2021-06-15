#include "Menu/Exit.h"


Exit::Exit()
{
}

Exit::~Exit()
{
}

const StageInfo Exit::execute(sf::RenderWindow& window)
{
	window.close();
	return StageInfo();
}
