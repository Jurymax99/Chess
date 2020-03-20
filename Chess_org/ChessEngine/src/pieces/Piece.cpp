#include "Piece.h"

namespace Chess {
	namespace Pieces {
		Piece::Piece()
		{
			color = 0;
			type = 'V';
		}

		void Piece::newPlayer(int newPlayer){
			color = newPlayer;
		}

		void Piece::newType(char newType) {
			type = newType;
		}

		int Piece::checkColor() const {
			return color;
		}

		char Piece::checkType() const {
			return type;
		}

		bool Piece::isFirst() const {
			return first;
		}

		void Piece::firstMove()
		{
			first = false;
		}
	}
}