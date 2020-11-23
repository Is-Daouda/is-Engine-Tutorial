#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED

#include "../../../isEngine/system/entity/MainObject.h"
#include "../../../isEngine/system/entity/parents/Destructible.h"
#include "../../../isEngine/system/entity/parents/ScorePoint.h"
#include "../../../isEngine/system/entity/parents/Step.h"

#include "../../gamesystem_ext/GameSystemExtended.h"

class Bonus : public is::MainObject, public is::Destructible, public is::ScorePoint, public is::Step
{
public:
    Bonus(sf::Texture &tex, float x, float y);
    void step(float const &DELTA_TIME);
};

#endif // BONUS_H_INCLUDED
