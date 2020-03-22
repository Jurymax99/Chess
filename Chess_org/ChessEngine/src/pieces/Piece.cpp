#include "Piece.h"

namespace Chess {
	namespace Pieces {
		Piece::Piece(){
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

		int Piece::checkPoints() const {
			switch (type) {
				case 'P':
					return 1;
				case 'N':
				case 'B':
					return 3;
				case 'R':
					return 5;
				case 'Q':
					return 9;
				case 'K':
					std::cout << "WARNING::King has no numerical value" << std::endl;
					return -1;
				default:
					std::cout << "No known piece type" << std::endl;
					return -1;
			}
		}

		void Piece::firstMove()	{
			first = false;
		}

		bool Piece::operator <(Piece& a) const{
			if (checkPoints() == a.checkPoints()) {
				return checkType() < a.checkType();
			}
			return checkPoints() < a.checkPoints();
		}
	}
}