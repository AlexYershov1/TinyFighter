#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "macros.h"
#include "ResourcesManager.h"

class ManaAndHealth
{
public:
	ManaAndHealth();

	~ManaAndHealth();
	void draw(sf::RenderWindow&) const;
	void move(); //move with the view and stay on the screen

	void increaseMana(const sf::Time&); //increase over time
	void decreaseMana(float);
	void decreaseMana(ActionType); //decrease sccording to action
	bool decreaseHealth(float);

	void setLocation(int); //sets location according to player number
	void setIcon(CharacterType);
	float getMana() const;
	float getHealth() const;

	bool isFaded() const;	//to help determin if dead
private:
	void setPositions();

	struct Bar
	{
		float value;
		std::pair<sf::RectangleShape, sf::RectangleShape> rectangles;
		
		void update(float addition, float maxValue) //update vaues and rectangles
		{
			value += addition;
			if (value > maxValue)
				value = maxValue;
			else if (value < 0)
				value = 0;
			auto fraction = value / maxValue;
			rectangles.second.setSize({ BAR_WIDTH * fraction ,BAR_HEIGHT });
		}
	};

	Bar m_manaBar;
	Bar m_healthBar;
	sf::Sprite m_charIcon;
	sf::Vector2f m_blockOffset; //to place on StatesSection
	sf::Clock m_fading;	
};
