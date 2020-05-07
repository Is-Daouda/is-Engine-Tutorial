#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include "../../../isEngine/system/entity/MainObject.h"
#include "../../../isEngine/system/entity/parents/ScorePoint.h"

class Obstacle : public is::MainObject, public is::ScorePoint
{
public:
    Obstacle(sf::Texture &tex, float x, float y);
    void step(float const& DELTA_TIME);
};

#endif // BLOC_H_INCLUDED
