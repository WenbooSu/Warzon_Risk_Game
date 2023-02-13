//
//  Card.cpp
//  DeckOfCards
//
//  Created by Brandon Tse on 2023-02-05.
//

#include "Card.hpp"
#include <iostream>
//this is the paramater constructor
Card::Card(std::string set){
    this->CardType = set;
}
//copy constructor uses this to take value and apply it to itself
Card::Card(const Card& c){
    this->CardType = c.CardType;
}
//creates a random int in the range of 0 to deck size
int Deck::random(){
    return rand()% baseDeck.size();
}
//calls random to get position to draw from the deck then copys the card before removing from deck
Card Deck::draw(){
    int temp = random();
    Card handCard = Card(baseDeck.at(temp));
    baseDeck.erase(baseDeck.begin() + temp);
    return handCard;
}
//just pushes card to the back of deck
void Deck::returnCard(Card c1){
    baseDeck.push_back(c1);
}
//just creates equal to number passed to it of each type
void Deck::createDeck(int number){
    for(int i =0;i<number;i++){
        baseDeck.push_back(Card("bomb"));
        baseDeck.push_back(Card("airlift"));
        baseDeck.push_back(Card("diplomacy"));
        baseDeck.push_back(Card("reinforcement"));
    }
}
//Takes a card to be added to the players hand
void playerHand::add(Card c1){
    hand.push_back(c1);
}
//this for loops over players hand to display what types of cards he has
void playerHand::showHand(){
    for(int i=0;i< hand.size();i++)
    {
        std::cout<<hand[i].CardType <<"\n";
    }
}
//displays the card being played returning the card before erasing it from players hand
Order playerHand::play(int handPos,Deck &d1){
    std::cout<< "playing the card " << hand[handPos].CardType <<"\n";
    d1.returnCard(hand[handPos]);
    hand.erase(hand.begin()+handPos);
    Order o1;
    return o1;
}
