#include "Board.h"
#include "Utilities.h"

namespace Chess {
	namespace Engine {

		bool Board::castleKingside(int player) {
			int h;
			int w_r = 7;	//rook file
			int w_k = 4;	//king file
			Player *mover;
			if (player == RED) {
				h = 7;
				mover = &Red;
			}
			else if (player == GREEN) {
				h = 0;
				mover = &Green;
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			
			if (MODE == DEBUG) {
				std::cout << "Kingside castling can be done" << std::endl;
			}
			//Make the move
			main(h,w_r).removePiece();
			main(h,w_k).removePiece();
			w_r = 5;	//rook destination file
			w_k = 6;	//king destination file
			main(h,w_r).addPiece('R', player);
			main(h,w_k).addPiece('K', player);
			mover->setKing(h, w_k);
			target.possible = false;
			main(h,w_r).makeFirstMov();
			main(h,w_k).makeFirstMov();
			++halfMoves;
			++turn;
			mover->setCastleKing(false);
			mover->setCastleQueen(false);
			return true;
		}

		bool Board::castleQueenside(int player) {
			int h;
			int w_r = 0;	//rook file
			int w_k = 4;	//king file
			Player* mover;
			if (player == RED) {
				h = 7;
				mover = &Red;
			}
			else if (player == GREEN) {
				h = 0;
				mover = &Green;
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			if (MODE == DEBUG) {
				std::cout << "Queenside castling can be done" << std::endl;
			}
			//Make the move
			main(h,w_r).removePiece();
			main(h,w_k).removePiece();
			w_r = 3;	//rook destination file
			w_k = 2;	//king destination file
			main(h,w_r).addPiece('R', player);
			main(h,w_k).addPiece('K', player);
			mover->setKing(h, w_k);
			target.possible = false;
			main(h,w_r).makeFirstMov();
			main(h,w_k).makeFirstMov();
			++halfMoves;
			++turn;
			mover->setCastleKing(false);
			mover->setCastleQueen(false);
			return true;
		}

		bool Board::castleFakeKingside(int player) {
			int h;
			int w_r = 7;	//rook file
			int w_k = 4;	//king file
			Player* mover, *enemy;
			if (player == RED) {
				h = 7;
				mover = &Red;
				enemy = &Green;
			}
			else if (player == GREEN) {
				h = 0;
				mover = &Green;
				enemy = &Red;
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			if (not mover->checkCastleKing()) {
				if (MODE == DEBUG) {
					std::cout << "Cannot perform kingside castling\n";
				}
				return false;
			}
			//collision #2 Pieces in beetween
			for (int i = w_k + 1; i < w_r; ++i) {
				if (main(h,i).hasPiece()) {
					return false;
				}
			}
			enemy->updateThreats(*this, true);
			for (int i = w_k; i < w_r; ++i) {
				if ((-player) == main(h,i).isThreatened()) {
					if (MODE == DEBUG) {
						std::cout << "There is a threat in between" << std::endl;
					}
					return false;
				}
			}
			if (MODE == DEBUG) {
				std::cout << "Kingside castling can be done" << std::endl;
			}

			//Make the move
			main(h,w_r).removePiece();
			main(h,w_k).removePiece();
			w_r = 5;	//rook destination file
			w_k = 6;	//king destination file
			main(h,w_r).addPiece('R', player);
			main(h,w_k).addPiece('K', player);
			mover->setKing(h, w_k);
			int player_checked = player;
			bool totChecked = whoChecked(player_checked);

			main(h,w_k).removePiece();
			main(h,w_r).removePiece();
			w_r = 7;
			w_k = 4;
			main(h,w_k).addPiece('K', player);
			main(h,w_r).addPiece('R', player);
			mover->setKing(h, w_k);
			if (not totChecked) {
				return true;
			}
			if (player_checked == player) {
				if (MODE == DEBUG) {
					if (player == RED) {
						std::cout << "FAKEMOVE::The red king is in check" << std::endl;
					}
					else {
						std::cout << "FAKEMOVE::The green king is in check" << std::endl;
					}

				}
				return false;
			}
			return true;
		}
		
		bool Board::castleFakeQueenside(int player) {
			int h;
			int w_r = 0;	//rook file
			int w_k = 4;	//king file
			Player* mover, * enemy;
			if (player == RED) {
				h = 7;
				mover = &Red;
				enemy = &Green;
			}
			else if (player == GREEN) {
				h = 0;
				mover = &Green;
				enemy = &Red;
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			if (not mover->checkCastleQueen()) {
				if (MODE == DEBUG) {
					std::cout << "Cannot perform queenside castling\n";
				}
				return false;
			}
			//collision #2 Pieces in beetween
			for (int i = w_r + 1; i < w_k; ++i) {
				if (main(h,i).hasPiece()) {
					return false;
				}
			}
			enemy->updateThreats(*this, true);
			for (int i = w_r + 2; i <= w_k; ++i) {
				if ((-player) == main(h,i).isThreatened()) {
					if (MODE == DEBUG) {
						std::cout << "There is a threat in between" << std::endl;
					}
					return false;
				}
			}
			if (MODE == DEBUG) {
				std::cout << "Queenside castling can be done" << std::endl;
			}
			//Make the move
			main(h,w_r).removePiece();
			main(h,w_k).removePiece();
			w_r = 3;	//rook destination file
			w_k = 2;	//king destination file
			main(h,w_r).addPiece('R', player);
			main(h,w_k).addPiece('K', player);
			mover->setKing(h, w_k);
			int player_checked = player;
			bool totChecked = whoChecked(player_checked);
			main(h,w_k).removePiece();
			main(h,w_r).removePiece();
			w_r = 0;
			w_k = 4;
			main(h,w_k).addPiece('K', player);
			main(h,w_r).addPiece('R', player);
			mover->setKing(h, w_k);
			if (not totChecked) {
				return true;
			}
			if (player_checked == player) {
				if (MODE == DEBUG) {
					if (player == RED) {
						std::cout << "FAKEMOVE::The red king is in check" << std::endl;
					}
					else {
						std::cout << "FAKEMOVE::The green king is in check" << std::endl;
					}

				}
				return false;
			}
			return true;
		}

		bool Board::whoChecked(int& player) {
			switch (checkPlayer()) {
			case RED:
				if (Red.isThreatened(*this)) {
					player = RED;
					return true;
				}
				break;
			default:
				if (Green.isThreatened(*this)) {
					player = GREEN;
					return true;
				}
				break;
			}
			return false;
		}
	}
}