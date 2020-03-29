#pragma once
#include "Color.h"
#include <algorithm>
#include <iostream>

#define RED 1
#define GREEN 2

#define RELEASE 0
#define DEBUG 1
#define MODE RELEASE

#define VISUAL 0
#define OUTSIDE 1
#define ENVIRONMENT OUTSIDE

#define NORMAL 0
#define LESS 1
#define MINIMAL 2
#define OUTPUT LESS



struct Position {
	int h, w;

	Position()
		: h(0), w(0) {}

	Position(int h, int w)
		: h(h), w(w) {}

	bool isNull() {
		return h == -1 and w == -1;
	}

	bool operator ==(const Position& rhs) const{
		return h == rhs.h and w == rhs.w;
	}
};