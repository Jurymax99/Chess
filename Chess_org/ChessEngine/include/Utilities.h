#pragma once
#include <algorithm>
#include <iostream>
#include <tuple>

//players
#define RED 1
#define GREEN -1

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

#define DEPTH 5

//FAST
#define OUTPUT MINIMAL
#define MODE RELEASE

/*
//ALL DEBUG
#define OUTPUT NORMAL
#define MODE DEBUG
*/


struct Position {
	char pos;
	/*
	0000 1111	h
	1111 0000	w	4
	*/

	Position()
		: pos(0) {}

	Position(const int& h, const int& w) {
		pos = (h & 7) | (w << 4);
	}

	inline bool isNull() { return pos == 0xFF; }

	inline bool operator ==(const Position& rhs) const { return (pos & 0xF) == (rhs.pos & 0xF) and (pos & 0xF0) == (rhs.pos & 0xF0); }

	inline int checkH() const { return pos & 0xF; }

	inline int checkW() const { return pos >> 4; }

};

struct Move {
	unsigned int move;
	/*
	0000 0000 0000 0000 0000 0111 -> source h
	0000 0000 0000 0000 0011 1000 -> source w		3
	0000 0000 0000 0001 1100 0000 -> dest h			6
	0000 0000 0000 1110 0000 0000 -> dest w			9
	0000 0000 0001 0000 0000 0000 -> capture		12
	0000 0000 0010 0000 0000 0000 -> promote		13
	0000 0000 0100 0000 0000 0000 -> castleKing		14
	0000 0000 1000 0000 0000 0000 -> castleQueen	15
	1111 1111 0000 0000 0000 0000 -> type			16
	*/

	//Type, Source, Dest, Capture, Prom, cK, cQ

	Move() {
		move = 0;
	}

	Move(const char& type, const int& sh, 
			const int& sw, const int& dh, 
			const int& dw, const bool& capture, 
			const bool& prom, const bool& cK, const bool& cQ) {

		move = (sh & 7) | 
			(sw & 7) << 3 | 
			(dh & 7) << 6 | 
			(dw & 7) << 9| 
			(capture & 1) << 12 | 
			(prom & 1) << 13 | 
			(cK & 1) << 14 | 
			(cQ & 1) << 15 | 
			(type & 0xFF) << 16;
	}

	bool operator<(const Move& rhs) const{
		return move < rhs.move;
	}

	inline Position getSource() const { return { move & 7, (move >> 3) & 7 }; }

	inline Position getDestination() const { return { (move >> 6) & 7, (move >> 9) & 7 }; }

	inline bool isCapture() const { return (move >> 12) & 1; }

	inline bool isPromotion() const { return (move >> 13) & 1; }

	inline bool isCastleKingside() const { return (move >> 14) & 1; }

	inline bool isCastleQueenside() const { return (move >> 15) & 1; }

	inline char getType() const { return (move >> 16) & 0xFF; }

	bool operator ==(const Move& m) const{
		return this->move == m.move;
	}

};

