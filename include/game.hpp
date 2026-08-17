#ifndef GAME_HPP
#define GAME_HPP

#include "ENG_Dingus.hpp"

void mainTick();
void controls();

class GameObject : public ENG_Dingus
{
private:
public:
    GameObject()
    {}
};

#endif