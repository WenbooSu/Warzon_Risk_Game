//
// Created by Administrator on 2023/4/15.
//
#ifndef A2_PLAYERSTRATEGY_H
#define A2_PLAYERSTRATEGY_H
#include "Player.h"

class PlayerStrategy {
public:
    virtual void issueOrder() = 0;
    virtual Territory* toAttack() = 0;
    virtual Territory* toDefend() = 0;
    void setPlayer(Player*);
    Player* getPlayer();
    virtual void changeStrategy();
private:
    Player* player;
};

class CheaterPlayerStrategy: public PlayerStrategy{
public:
    void issueOrder();
    Territory* toAttack();
    Territory* toDefend();
};

class NeutralPlayerStrategy:: public PlayerStrategy{
public:
    NeutralPlayerStrategy();
    void issueOrder()=0;
    Territory* toAttack()=0;
    Territory* toDefend()=0;
    void changeStrategy();
};

class AggressivePlayerStrategy: public PlayerStrategy{
public:
    AggressivePlayerStrategy();
    void issueOrder()=0;
    Territory* toAttack()=0;
    Territory* toDefend()=0;
};

#endif //A2_PLAYERSTRATEGY_H
