#pragma once
#include "Utilities.h"

namespace Chess {
	namespace Engine {
		class Tile {
		private:
			unsigned int tile;
			/*
			0000 0000 0000 0000 0000 0000 0011 -> threat
			0000 0000 0000 0000 0000 0000 0100 -> empty		2
			0000 0000 0000 0000 0000 0000 1000 -> first		3
			0000 0000 0000 0000 0000 0011 0000 -> player	4
			0000 0000 0000 0011 1111 1100 0000 -> type		6
			*/
		public:
			Tile();

			Tile(const Tile& t);

			Tile& operator =(Tile obj);

			void addPiece(char newPiece, int newPlayer);

			void removePiece();

			int checkPoints() const;

			int killPiece();

			inline bool hasPiece() const { return not ((tile >> 2) & 1); }

			inline int isThreatened() const { return ((tile & 3) == 3) ? -1 : tile & 3; }

			inline void setThreat(const int& player) { tile &= 0x3FFC; tile |= (player & 3); }

			inline void removeThreat() { tile &= 0x3FFC; }

			inline bool isFirstMov() const {return (tile >> 3) & 1;}

			inline void makeFirstMov() {tile &= 0x3FF7 ;}

			inline int checkPlayer() const { int res = (tile >> 4) & 3; return res == 3 ? -1 : res; };

			inline char checkPieceType() const { return (tile >> 6) & 0xFF; }
		};
	}
}