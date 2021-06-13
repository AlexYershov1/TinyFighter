#include "Collision.h"
#include <map>
#include <typeinfo>
#include <typeindex>
#include "Character/Player.h"
#include "Character/Enemy.h"


Collision::Collision()
{
}

Collision& Collision::instance()
{
	static Collision instance;
	return instance;
}

//collision between player and enemy - check which is punching
// 
//collision between character and special attack - check if the attack 
//was not created by the character

namespace
{

    void playerEnemy(GameObject& player, GameObject& enemy)
    {
        
        auto& ply = static_cast<Player&>(player);
        auto& enm = static_cast<Enemy&>(enemy);

        //check if someone is punching
        if ((ply.getActionType() == ActionType::Punching) && (ply.facing(enm)))
        {
            //check if facing enemy
            //for later - change to take damage and move to Character
            enm.setActionType(ActionType::Smacked);

        }
        else if ((enm.getActionType() == ActionType::Punching) && (enm.facing(ply)))
        {
            ply.setActionType(ActionType::Smacked);
        }
        
    }
    void enemyPlayer(GameObject& enemy, GameObject& player)
    {
        playerEnemy(player, enemy);
    }
    using HitFunctionPtr = void (*)(GameObject&, GameObject&);
    using Key = std::pair<std::type_index, std::type_index>;
    using HitMap = std::map<Key, HitFunctionPtr>;

    HitMap initializeCollisionMap()
    {
        HitMap phm;
        phm[Key(typeid(Player), typeid(Enemy))] = &playerEnemy;
        phm[Key(typeid(Enemy), typeid(Player))] = &enemyPlayer;

        //phm[Key(typeid(Character), typeid(SpecialAttack))] = &shipStation;

        //...
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
    if (!phf)
    {
        throw UnknownCollision(obj1, obj2);
    }
    phf(obj1, obj2);
}
