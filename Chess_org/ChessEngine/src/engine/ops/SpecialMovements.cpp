#include "Board.h"
#include "Utilities.h"

namespace Chess {
	namespace Engine {

		bool Board::castleKingside(int player) {
			int h;
			int w_r = 7;	//rook file
			int w_k = 4;	//king file
			Player *mover, *enemy;
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
			for (int i = w_k + 1; i < w_r; ++i) {
				//if (enemy->findThreat(h, i)) {
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
			int totChecked = whoChecked(player_checked);

			main(h,w_k).removePiece();
			main(h,w_r).removePiece();
			w_r = 7;
			w_k = 4;
			main(h,w_k).addPiece('K', player);
			main(h,w_r).addPiece('R', player);
			mover->setKing(h, w_k);
			if (totChecked == 0) {
				return true;
			}
			else if (totChecked == 1) {
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
				else {
					return true;
				}
			}
			else if (totChecked == 2) {
				return false;
			}
			return false;
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
			for (int i = w_r + 2; i < w_k; ++i) {
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
			int totChecked = whoChecked(player_checked);
			main(h,w_k).removePiece();
			main(h,w_r).removePiece();
			w_r = 0;
			w_k = 4;
			main(h,w_k).addPiece('K', player);
			main(h,w_r).addPiece('R', player);
			mover->setKing(h, w_k);
			if (totChecked == 0) {
				return true;
			}
			else if (totChecked == 1) {
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
				else {
					return true;
				}
			}
			else if (totChecked == 2) {
				return false;
			}
			return false;
		}

		bool Board::isChecked(int& player) {
			//See if any king is in the positions threatened by other player
			player == RED ? Green.updateThreats(*this, true) : Red.updateThreats(*this, true);
			Position RedKing = Red.checkKingPosition();
			Position GreenKing = Green.checkKingPosition();

			if (main(RedKing.checkH(),RedKing.checkW()).isThreatened() == GREEN) {
				if (MODE == DEBUG) {
					std::cout << "Red king is in check" << std::endl;
				}

				player = RED;
				return true;
			}
			if (main(GreenKing.checkH(),GreenKing.checkW()).isThreatened() == RED) {
				if (MODE == DEBUG) {
					std::cout << "Green king is in check" << std::endl;
				}
				player = GREEN;
				return true;
			}
			player = 0;
			return false;
		}


		// if only 1 player checked returns 1 and count = id of the player
		// else returns a 2 
		// if nobody is checked returns a 0
		int Board::whoChecked(int& player) {
			player == RED ? Green.updateThreats(*this, true) : Red.updateThreats(*this, true);
			int count = 0;
			Position RedKing = Red.checkKingPosition();
			Position GreenKing = Green.checkKingPosition();

			if (main(RedKing.checkH(),RedKing.checkW()).isThreatened() == GREEN) {
				if (MODE == DEBUG) {
					std::cout << "Red king is in check" << std::endl;
				}

				player = RED;
				++count;
			}
			if (main(GreenKing.checkH(),GreenKing.checkW()).isThreatened() == RED) {
				if (MODE == DEBUG) {
					std::cout << "Green king is in check" << std::endl;
				}
				player = GREEN;
				++count;
			}
			return count;
		}
	}
}