#pragma once
#include <string>
#include "Utilities.h"
#include "Piece.h"

namespace Chess {
	namespace Engine {
		class Tile {
		private:
			Pieces::Piece* piece;
			bool empty;

		public:
			Tile();
			~Tile();
			Tile(const Tile& t);

			void addPiece(char newPiece, int newPlayer);
			void removePiece();
			int killPiece();

			Tile& operator =(Tile obj);

			inline bool hasPiece() const {return not empty;}

			inline bool isFirstMov() const {return piece->isFirst();}

			inline int checkPlayer() const {return piece->checkColor();}

			inline Pieces::Piece* checkPiecePoint() {return piece;}

			inline Pieces::Piece checkPiece() const {return *piece;}

			inline char checkPieceType() const {return piece->checkType();}
		};
	}
}