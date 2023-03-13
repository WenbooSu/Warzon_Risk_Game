//
//  main.cpp
//  DeckOfCards
//
//  Created by Brandon Tse on 2023-02-05.
//

#include <iostream>
#include "Card.h"

int cardDriver(int argc, const char * argv[]) {
    //creating deck and populating it and displaying size
    Deck d1;
    d1.createDeck(4);
    std::cout << d1.baseDeck.size() << "\n";
    //creating a player hand and adding cards from deck to it
    playerHand p1;
    p1.add(d1.draw());
    p1.add(d1.draw());
    p1.add(d1.draw());
    p1.add(d1.draw());
    //displaying that deck size changed
    std::cout << d1.baseDeck.size() << "\n";
    //shows the cards that are in the hand and showing that play method works
    p1.showHand();
    p1.play(1, d1);
    p1.showHand();
    p1.play(2, d1);
    //showing that its readded to deck
    std::cout << d1.baseDeck.size() << "\n";
    return 0;
}
