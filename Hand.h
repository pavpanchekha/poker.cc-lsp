/*
 *  Hand.h
 *  
 *
 *  Created by John Nevard on 5/5/10.
 *  Copyright 2010 John Nevard. All rights reserved.
 *
 */

#ifndef __HAND__
#define __HAND__

#include "Dealer.h"

class Hand {
public:
	Hand(const string& name) : name(name) { }
	
	virtual void getHand(const VC& hand) = 0;
	virtual VC discard() = 0;
	virtual void add(const VC& cards) = 0;
	virtual VC reveal() const = 0;
	
	string getName() const { return name; }
private:
	string name;
};

#endif