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
			Pieces::Piece checkPiece() const;
			bool hasPiece() const;
			char checkPieceType() const;
			bool isFirstMov() const;
			int checkPlayer() const;
			void addPiece(char newPiece, int newPlayer);
			void removePiece();
			int killPiece();
			Pieces::Piece* checkPiecePoint();
			Tile& operator =(Tile obj);
		};
	}
}