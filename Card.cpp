/*
 *  Card.cpp
 *  
 *
 *  Created by John Nevard on 5/5/10.
 *  Copyright 2010 John Nevard. All rights reserved.
 *
 */

#include "Card.h"

string suit_names[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
string val_names[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
	"Nine", "Ten", "Jack", "Queen", "King", "Ace"};


Card::Card(int vs) : vs(vs) { }

Val Card::value() const { return static_cast<Val>(vs >> 2); }

Suit Card::suit() const { return static_cast<Suit>(vs & 3); }

int Card::card() const { return vs; }

bool Card::operator<(const Card& c) const {
	return value() < c.value();
}

bool Card::operator>(const Card& c) const {
	return value() > c.value();
}

bool Card::operator<=(const Card& c) const {
	return value() <= c.value();
}

bool Card::operator>=(const Card& c) const {
	return value() >= c.value();
}

bool Card::operator==(const Card& c) const {
	return vs == c.vs;
}

bool Card::operator!=(const Card& c) const {
	return vs != c.vs;
}

ostream& operator<<(ostream& os, const Card& c) {
	return os << val_names[c.value()] << " of " <<
			suit_names[c.suit()];
}