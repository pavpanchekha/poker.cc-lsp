/*
 *  Dealer.h
 *  
 *
 *  Created by John Nevard on 5/5/10.
 *  Copyright 2010 John Nevard. All rights reserved.
 *
 */

#ifndef __DEALER__
#define __DEALER__

#include "Card.h"

typedef vector<Card> VC;

const int D = 52;

class EmptyDeckException { };

class Dealer {
public:
	Dealer();
	VC deal(int n = 5);
	
	void reset();

private:
	VC c;
	int nl;
};

#endif