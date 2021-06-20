#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "macros.h"
#include "ResourcesManager.h"

class ManaAndHealth
{
public:
	ManaAndHealth();
	//ManaAndHealth(CharacterType); //for players

	~ManaAndHealth();
	void draw(sf::RenderWindow&) const;
	void increaseMana(const sf::Time&);
	//void increaseMana(const sf::Time&);
	void decreaseMana(float);
	void decreaseMana(ActionType);
	void decreaseHealth(float);

	void setLocation(int); //sets location according to player number
	void setIcon(CharacterType);
	float getMana() const;
	float getHealth() const;
private:
	struct Bar
	{
		float value;
		std::pair<sf::RectangleShape, sf::RectangleShape> rectangles;
		
		void update(float addition, float maxValue)
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


	//void decrease(float &, float) ;
};
