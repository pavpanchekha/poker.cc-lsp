/*
 *  HandA.h
 *  
 *
 *  Created by John Nevard on 5/5/10.
 *  Copyright 2010 John Nevard. All rights reserved.
 *
 */

#include "Hand.h"

class HandPavel : public Hand {
public:
	HandPavel(const string& name, int nPlayers);
	
	void getHand(const VC& hand);
	VC discard();
	void add(const VC& cards);
	VC reveal() const;
	void clear();
	
private:
	int nPlayers;
	VC c;
};
