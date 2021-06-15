#pragma once
#include "../Character/Character.h"
#include <exception>
#include <memory>

class SpecialAttack : public GameObject
{
public:
	SpecialAttack(const sf::Vector2f&, AttackType, std::shared_ptr<Character>);
	virtual void update(const sf::Time&) = 0;
	AttackType getKind() const { return m_kind; }
	void setHit() { m_action.first = ActionType::hit; }
	bool isMe(Character* character) const { return m_owner->isMe(character); }
	virtual ~SpecialAttack();

protected:
	Animation m_animation;
	std::shared_ptr<Character> m_owner;
	AttackType m_kind;
private:

};