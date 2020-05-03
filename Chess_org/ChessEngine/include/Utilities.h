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
	unsigned char pos;
	
//	0000 1111	h
//	1111 0000	w	4
	

	Position() noexcept
		: pos(0) {}

	Position(const int& h, const int& w) noexcept {
		pos = (h & 0xF) | ((w & 0xF) << 4);
	}

	bool isNull() noexcept { return pos == 0xFF; }

	bool operator ==(const Position& rhs) const noexcept { return pos == rhs.pos; }

	int checkH() const noexcept { return pos & 0xF; }

	int checkW() const noexcept { return (pos >> 4) & 0xF; }

};

struct Move {
	unsigned int move;
	
//	0000 0000 0000 0000 0000 0000 0000 0111 -> source h
//	0000 0000 0000 0000 0000 0000 0011 1000 -> source w			3
//	0000 0000 0000 0000 0000 0001 1100 0000 -> dest h			6
//	0000 0000 0000 0000 0000 1110 0000 0000 -> dest w			9
//	0000 0000 0000 1111 1111 0000 0000 0000 -> type				12
//	0000 0000 0001 0000 0000 0000 0000 0000 -> castleKing		20
//	0000 0000 0010 0000 0000 0000 0000 0000 -> castleQueen		21
//	0000 0000 0100 0000 0000 0000 0000 0000 -> promote			22
//	0000 0000 1000 0000 0000 0000 0000 0000 -> capture			23
//	1111 1111 0000 0000 0000 0000 0000 0000 -> typePromoted		24
	

	//Type, Source, Dest, Capture, Prom, cK, cQ

	Move() noexcept {
		move = 0;
	}

	Move(const char& type, const int& sh, 
			const int& sw, const int& dh, 
			const int& dw, const bool& capture, 
			const bool& prom, const bool& cK, const bool& cQ) noexcept {

		move = 0 |
			(sh & 7) | 
			(sw & 7) << 3 | 
			(dh & 7) << 6 | 
			(dw & 7) << 9| 
			(type & 0xFF) << 12 |
			(cK & 1) << 20 | 
			(cQ & 1) << 21 | 
			(prom & 1) << 22 | 
			(capture & 1) << 23;
	}

	Move(const char& tpro, const char& type, const int& sh,
		const int& sw, const int& dh,
		const int& dw, const bool& capture,
		const bool& prom, const bool& cK, const bool& cQ) noexcept {

		move = 0 |
			(sh & 7) |
			(sw & 7) << 3 |
			(dh & 7) << 6 |
			(dw & 7) << 9 |
			(type & 0xFF) << 12 |
			(cK & 1) << 20 |
			(cQ & 1) << 21 |
			(prom & 1) << 22 |
			(capture & 1) << 23 |
			(tpro & 0xFF) << 24;
	}

	Move(const char& type, const int& sh,
		const int& sw, const int& dh,
		const int& dw) noexcept {

		move = 0 |
			(sh & 7) |
			(sw & 7) << 3 |
			(dh & 7) << 6 |
			(dw & 7) << 9 |
			(type & 0xFF) << 12;
	}

	bool operator<(const Move& rhs) const noexcept { return move < rhs.move; }

	Position getSource() const noexcept { return { move & 7, (move >> 3) & 7 }; }

	Position getDestination() const noexcept { return { (move >> 6) & 7, (move >> 9) & 7 }; }

	bool isCapture() const noexcept { return (move >> 23) & 1; }

	bool isPromotion() const noexcept { return (move >> 22) & 1; }

	bool isCastleKingside() const noexcept { return (move >> 20) & 1; }

	bool isCastleQueenside() const noexcept { return (move >> 21) & 1; }

	char getType() const noexcept { return (move >> 12) & 0xFF; }

	char getPromotedType() const noexcept { return (move >> 24) & 0xFF; }

	bool operator ==(const Move& m) const noexcept { return this->move == m.move; }

};