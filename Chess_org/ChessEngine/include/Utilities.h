#pragma once
#include "Color.h"
#include <algorithm>
#include <iostream>
#include <tuple>

//players
#define RED 1
#define GREEN 2

//app modes
#define RELEASE 0
#define DEBUG 1

//file accessing modes
#define VISUAL 0
#define OUTSIDE 1
#define ENVIRONMENT VISUAL

//output modes
#define NORMAL 0
#define LESS 1
#define MINIMAL 2

//FAST
#define OUTPUT MINIMAL
#define MODE RELEASE

/*
//ALL DEBUG
#define OUTPUT NORMAL
#define MODE DEBUG
*/


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

struct PiecePosition {
	char type;
	int h, w;

	PiecePosition()
		: type('V'), h(0), w(0) {}

	PiecePosition(char type, int h, int w)
		: type(type), h(h), w(w) {}

	bool isNull() const{
		return type == 'V' and h == -1 and w == -1;
	}

	bool operator ==(const PiecePosition& rhs) const {
		return type == rhs.type and h == rhs.h and w == rhs.w;
	}

	bool operator <(const PiecePosition& rhs) const{
		return std::tie(h, w, type) < std::tie(rhs.h, rhs.w, rhs.type);
	}

};

struct Move {
	char type;
	Position source, destination;
	bool capture, move, castleKing, castleQueen, promote, check;
	char killed;

	bool operator<(const Move& rhs) const {
		return std::tie(type, source.w, source.h, destination.w, destination.h,
			move, capture, check, castleKing, castleQueen)
			< std::tie(rhs.type, rhs.source.w, rhs.source.h, rhs.destination.w, rhs.destination.h,
				rhs.move, rhs.capture, rhs.check, rhs.castleKing, rhs.castleQueen);
	}
};