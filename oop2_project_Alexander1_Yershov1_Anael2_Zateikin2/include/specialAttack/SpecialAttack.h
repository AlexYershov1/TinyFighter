#pragma once
#include "../Character/Character.h"
#include <exception>
#include <memory>

class SpecialAttack : public GameObject
{
public:
	SpecialAttack(const sf::Vector2f&, AttackType, std::shared_ptr<Character>);
	virtual void update(const sf::Time&) = 0;
	virtual ~SpecialAttack();

protected:
	Animation m_animation;
	std::shared_ptr<Character> m_owner;
private:

};