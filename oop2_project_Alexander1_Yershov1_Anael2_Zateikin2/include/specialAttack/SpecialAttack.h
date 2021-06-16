#pragma once
#include "../Character/Character.h"
#include <exception>
#include <memory>

class Arena;

class SpecialAttack : public GameObject
{
public:
	SpecialAttack(const sf::Vector2f&, AttackType, Character*);
	virtual void update(const sf::Time&) = 0;
	virtual void move(const sf::Time&, Arena&) {}
	AttackType getKind() const { return m_kind; }
	void setHit() { m_action.first = ActionType::hit; }
	bool isMe(Character* character) const { return m_owner->isMe(character); }
	virtual ~SpecialAttack();

protected:
	Animation m_animation;
	Character* m_owner;
	AttackType m_kind;
private:

};