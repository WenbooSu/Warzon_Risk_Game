//
// Created by Administrator on 2023/4/15.
//
#ifndef A2_PLAYERSTRATEGY_H
#define A2_PLAYERSTRATEGY_H
#include "Player.h"

class PlayerStrategy {
public:
    virtual void issueOrder() = 0;
    virtual vector<Territory*> toAttack() = 0;
    virtual vector<Territory*> toDefend() = 0;
    void setPlayer(Player*);
    Player* getPlayer();
    //virtual void changeStrategy();
    vector<Territory*> territories;
protected:
    Player* player;
};

class HumanPlayerStrategy : public PlayerStrategy {
public:
    HumanPlayerStrategy(Player*);
    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
};

class AggressivePlayerStrategy: public PlayerStrategy{
public:
    AggressivePlayerStrategy();
    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
};

class CheaterPlayerStrategy: public PlayerStrategy{
public:
    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
};

class NeutralPlayerStrategy: public PlayerStrategy{
public:
    NeutralPlayerStrategy();
    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
    void changeStrategy();
};
#endif //A2_PLAYERSTRATEGY_H
