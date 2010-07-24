/*
 *  Card.h
 *  
 *
 *  Created by John Nevard on 5/5/10.
 *  Copyright 2010 John Nevard. All rights reserved.
 *
 */

#ifndef __CARD__
#define __CARD__

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

enum Suit {CLUB, DIAMOND, HEART, SPADE};

enum Val {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
	JACK, QUEEN, KING, ACE};

class Card {
public:
	explicit Card(int vs = -1);
	Val value() const;
	Suit suit() const;
	int card() const;
	bool operator<(const Card& c) const;
	bool operator>(const Card& c) const;
	bool operator<=(const Card& c) const;
	bool operator>=(const Card& c) const;
	bool operator==(const Card& c) const;
	bool operator!=(const Card& c) const;
	
	friend ostream& operator<<(ostream& os, const Card& c);
	
private:
	int vs;
};

#endif
