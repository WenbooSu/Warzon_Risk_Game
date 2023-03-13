//
//  Card.hpp
//  DeckOfCards
//
//  Created by Brandon Tse on 2023-02-05.
//

#ifndef Card_hpp
#define Card_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "Orders.h"

class Card{
public:
    std::string CardType;
    //constructor setting Card type
    Card(std::string set);
    //copy constructor
    Card(const Card& c);
};

class Deck{
public:
    //this is the Container of cards used to draw from
    std::vector<Card> baseDeck;
    //returns a card from the deck and removing it
    Card draw();
    //randomizes order of draw
    int random();
    //allows for cards to be returned to the deck
    void returnCard(Card);
    //this is used to populate the base deck with the amount of cards chosen
    void createDeck(int number);
};

class playerHand{
public:
    //This is the hand of cards each player will have
    std::vector<Card> hand;
    //Allows a card to be added to the hand
    void add(Card c1);
    //displays the type of each card the player has
    void showHand();
    //takes a int which is used to pick which card from the hand to remove and add back to deck
    Order play(int handPos,Deck &d1);
};

#endif /* Card_hpp */
