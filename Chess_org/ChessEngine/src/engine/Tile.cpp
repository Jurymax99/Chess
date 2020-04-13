#include "Tile.h"

namespace Chess {
	namespace Engine {
		Tile::Tile() {
			// empty 
			tile = 0 |
				(1 << 2);
		}

		Tile::Tile(const Tile& t){
			tile = t.tile;
		}

		Tile& Tile::operator=(Tile obj) {
			this->tile = obj.tile;
			return *this;
		}

		void Tile::addPiece(char newPiece, int newPlayer) {
			//		empty
			if ((tile >> 2) & 1) {
				if (newPiece != 'P' and
					newPiece != 'R' and
					newPiece != 'N' and
					newPiece != 'Q' and
					newPiece != 'B' and
					newPiece != 'K') {
					std::cout << "The piece type does not exist" << std::endl;
				}
				else {
					tile = 0 |					//not empty
						(1 << 3) |					//first
						((newPlayer & 3) << 4) |	//player
						((newPiece & 0xFF) << 6);	//type
				}
			}
			else {
				std::cout << "There was already another piece in the tile" << std::endl;
			}
		}

		void Tile::removePiece() {
			//		not empty
			if (not ((tile >> 2) & 1)) {
				//	empty
				tile = 0 |
					(1 << 2);
			}
			else {
				std::cout << "Tile was already empty" << std::endl;
			}
		}

		int Tile::checkPoints() const {
			switch ((tile >> 6) & 0xFF) {
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

		int Tile::killPiece() {
			//		not empty
			if (not ((tile >> 2) & 1)) {
				int score = checkPoints();
				//	empty
				tile = 0 |
					(1 << 2);
				return score;
			}
			else {
				std::cout << "Tile was already empty" << std::endl;
				return 0;
			}
		}
	}
}
