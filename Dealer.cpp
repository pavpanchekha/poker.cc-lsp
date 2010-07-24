/*
 *  Dealer.cpp
 *  
 *
 *  Created by John Nevard on 5/5/10.
 *  Copyright 2010 John Nevard. All rights reserved.
 *
 */

#include "Dealer.h"

Dealer::Dealer() : c(D) {
	reset();	
}

void Dealer::reset() {
	nl = D;
	c[0] = Card(0);
	for (int i = 1; i < D; ++i) {
		int j = rand() % (i + 1);
		c[i] = c[j];
		c[j] = Card(i);
	}
}

VC Dealer::deal(int n) {
	if (n > nl) throw EmptyDeckException();
	VC h;
	while (--n >= 0)
		h.push_back(c[--nl]);
	return h;
}
