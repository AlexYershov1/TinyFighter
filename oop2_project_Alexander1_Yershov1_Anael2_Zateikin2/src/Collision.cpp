#include "Collision.h"
#include <map>
#include <typeinfo>
#include <typeindex>
#include "Character/Player.h"
#include "Character/Enemy.h"
#include "specialAttack/DynamicAttack.h"
#include "specialAttack/StaticAttack.h"


Collision::Collision()
{
}

Collision& Collision::instance()
{
	static Collision instance;
	return instance;
}

namespace
{
    void playerEnemy(GameObject& player, GameObject& enemy)
    {
        auto& ply = static_cast<Character&>(player);
        auto& enm = static_cast<Character&>(enemy);

        twoCharactersCollision(ply, enm);
        twoCharactersCollision(enm, ply);
    }
    void dynamicAttackCharacter(GameObject& dynamicAttack, GameObject& character)
    {
        auto& attack = static_cast<DynamicAttack&>(dynamicAttack);
        auto& obj = static_cast<Character&>(character);

        //if dead
        if (!character.isAlive() && !character.isFaded())
            return;

        if (attack.ownerIsAlive() && attack.isMe(&obj)) 
            return;
        
        //if character is in freeze state or burning - decrease health
        if (obj.getActionType() != ActionType::Burning && obj.getActionType() != ActionType::Freezing)
            obj.decreaseHealth(SPECIAL_DINAM_DAMAGE);

        attack.getKind() == AttackType::FireDynamic ? obj.setActionType(ActionType::Burning) : obj.setActionType(ActionType::Freezing);
        
        attack.setHit();
    }
    void characterDynamicAttack(GameObject& character, GameObject& dynamicAttack)
    {
        dynamicAttackCharacter(dynamicAttack, character);
    }

    void staticAttackCharacter(GameObject& staticAttack, GameObject& character)
    {
        auto& attack = static_cast<StaticAttack&>(staticAttack);
        auto& obj = static_cast<Character&>(character);

        //if dead
        if (!character.isAlive() && !character.isFaded())
            return;

        if (attack.isMe(&obj))  //check if the attack was not created by the character
            return;

        if (obj.getActionType() != ActionType::Burning && obj.getActionType() != ActionType::Freezing)
            obj.decreaseHealth(SPECIAL_STATIC_DAMAGE);
        attack.getKind() == AttackType::FireStatic ? obj.setActionType(ActionType::Burning) : obj.setActionType(ActionType::Freezing);
    }
    void characterstaticAttack(GameObject& character, GameObject& staticAttack)
    {
        staticAttackCharacter(staticAttack, character);
    }


    using HitFunctionPtr = void (*)(GameObject&, GameObject&);
    using Key = std::pair<std::type_index, std::type_index>;
    using HitMap = std::map<Key, HitFunctionPtr>;

    HitMap initializeCollisionMap()
    {
        HitMap phm;
        phm[Key(typeid(Player), typeid(Enemy))] = &playerEnemy;
        phm[Key(typeid(Enemy), typeid(Player))] = &playerEnemy;
        phm[Key(typeid(DynamicAttack), typeid(Player))] = &dynamicAttackCharacter;
        phm[Key(typeid(Player), typeid(DynamicAttack))] = &characterDynamicAttack;
        phm[Key(typeid(DynamicAttack), typeid(Enemy))] = &dynamicAttackCharacter;
        phm[Key(typeid(Enemy), typeid(DynamicAttack))] = &characterDynamicAttack;
        phm[Key(typeid(StaticAttack), typeid(Player))] = &staticAttackCharacter;
        phm[Key(typeid(Player), typeid(StaticAttack))] = &characterstaticAttack;
        phm[Key(typeid(StaticAttack), typeid(Enemy))] = &staticAttackCharacter;
        phm[Key(typeid(Enemy), typeid(StaticAttack))] = &characterstaticAttack;
        phm[Key(typeid(Player), typeid(Player))] = &playerEnemy;

        
        return phm;
    }
    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
    {
        static HitMap collisionMap = initializeCollisionMap();
        auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
        if (mapEntry == collisionMap.end())
        {
            return nullptr;
        }
        return mapEntry->second;
    }
}
void Collision::processCollision(GameObject& obj1, GameObject& obj2)
{
    auto phf = lookup(typeid(obj1), typeid(obj2));
    if (!phf)   // collision is irrelevent between two objects 
    {
        return;
    }
    phf(obj1, obj2);
}
