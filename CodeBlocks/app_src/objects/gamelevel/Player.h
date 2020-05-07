#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "../../../isEngine/system/entity/MainObject.h"
#include "../../../isEngine/system/entity/parents/Health.h"
#include "../../../isEngine/system/entity/parents/HurtEffect.h"
#include "../../../isEngine/system/function/GameKeyData.h"

class Player : public is::MainObject, public is::Health, public is::HurtEffect
{
public:
    Player(GameKeyData &gameKey);
    void loadResources(sf::Texture &tex);
    void step(float const &DELTA_TIME);

private:
    GameKeyData &m_gameKey;
    bool m_playerIsKO;
};

#endif // PLAYER_H_INCLUDED
