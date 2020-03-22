#include "Tile.h"

namespace Chess {
	namespace Engine {
		void Tile::addPiece(char newPiece, int newPlayer) {
			if (empty) {
				if (newPiece != 'P' and
					newPiece != 'R' and
					newPiece != 'N' and
					newPiece != 'Q' and
					newPiece != 'B' and
					newPiece != 'K'){
					std::cout << "The piece type does not exist" << std::endl;
				}
				else {
					using namespace Pieces;
					empty = false;
					piece = new Piece;
					//std::cout << "Allocating space for piece" << std::endl;
					piece-> newPlayer(newPlayer);
					piece-> newType(newPiece);
				}
			}
			else {
				std::cout << "There was already another piece in the tile" << std::endl;
			}
		}

		void Tile::removePiece(){
			if (not empty) {
				delete piece;
				//std::cout << "Disallocating space for piece" << std::endl;
				empty = true;
			}
			else {
				std::cout << "Tile was already empty" << std::endl;
			}
		}

		int Tile::killPiece(){
			if (not empty) {
				int points = piece->checkPoints();
				delete piece;
				//std::cout << "Disallocating space for piece" << std::endl;
				empty = true;
				return points;
			}
			else {
				std::cout << "Tile was already empty" << std::endl;
				return 0;
			}
		}

		bool Tile::hasPiece() const {
			return not empty;
		}

		bool Tile::isFirstMov() const {
			return piece -> isFirst();
		}

		int Tile::checkPlayer() const {
			return piece -> checkColor();
		}

		Pieces::Piece* Tile::checkPiecePoint() {
			return piece;
		}

		Tile& Tile::operator=(Tile obj) {
			this->empty = obj.empty;
			if (not obj.empty) {
				std::cout << "Disallocating piece in " << this->piece << std::endl;
				delete this->piece;
				this->piece = new Pieces::Piece(*obj.piece);
			}
			else {
				this->piece = nullptr;
			}
			return *this;
		}

		Tile::Tile() {
			empty = true;
			piece = nullptr;
		}

		Tile::~Tile() {
			//Memory leak
			//Disallocating memory space
			//std::cout << "Destroying " << piece << std::endl;
			if (not empty) {
				delete piece;
				empty = true;
			}
			else {
				//std::cout << "Tile was already empty" << std::endl;
			}
		}

		Pieces::Piece Tile::checkPiece() const {
			return *piece;
		}

		char Tile::checkPieceType() const {
			return piece -> checkType();
		}
	}
}