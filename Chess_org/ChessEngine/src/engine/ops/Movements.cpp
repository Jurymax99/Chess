#include "Board.h"
#include "Utilities.h"

namespace Chess {
	namespace Engine {

		bool Board::makeMove(char type, int orig_h, int orig_w, int h, int w, int player, bool enp) {
			Player* mover;
			if (player == RED) {
				mover = &Red;
			}
			else {
				mover = &Green;
			}
			bool first = main[orig_h][orig_w].isFirstMov();
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece(type, player);
			if (type == 'K') {
				mover->setKing(h, w);
				++halfMoves;
			}
			else if (type == 'P'){
				if (enp) {
					target = { h,w, true };
				}
				halfMoves = 0;
			}
			else {
				target.possible = false;
				++halfMoves;
			}
			main[h][w].checkPiecePoint()->firstMove();
			return true;
		}

		bool Board::makeFakeMove(char type, int orig_h, int orig_w, int h, int w, int player, bool& check) {
			Player* mover;
			if (player == RED) {
				mover = &Red;
			}
			else {
				mover = &Green;
			}
			bool first = main[orig_h][orig_w].isFirstMov();
			
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece(type, player);
			if (type == 'K') {
				mover->setKing(h, w);
			}
			int player_checked;
			int totChecked = whoChecked(player_checked);
			//rollback
			if (type == 'K') {
				mover->setKing(orig_h, orig_w);
			}
			main[h][w].removePiece();
			main[orig_h][orig_w].addPiece(type, player);
			if (not first) {
				main[orig_h][orig_w].checkPiecePoint()->firstMove();
			}
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
					check = true;
					return true;
				}
			}
			else if (totChecked == 2) {
				return false;
			}
			std::cout << "More than 2 players checked?" << std::endl;
			return false;
		}

		bool Board::makeFakeMovePro(int orig_h, int orig_w, int h, int w, int player, bool& check) {
			Player* mover;
			if (player == RED) {
				mover = &Red;
			}
			else {
				mover = &Green;
			}
			bool first = main[orig_h][orig_w].isFirstMov();
			std::vector<char> types = { 'Q', 'N', 'R', 'B' };
			int i = 0;
			while (i < 4 and not check) {
				main[h][w].addPiece(types[i], player);
				main[orig_h][orig_w].removePiece();
				int player_checked;
				int totChecked = whoChecked(player_checked);

				main[h][w].removePiece();
				main[orig_h][orig_w].addPiece('P', player);
				if (not first) {
					main[orig_h][orig_w].checkPiecePoint()->firstMove();
				}

				if (totChecked == 1) {
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
						check = true;
						return true;
					}
				}
				else if (totChecked == 2) {
					return false;
				}
				++i;
			}
			return true;
		}

		bool Board::pawnPromote(int h, int w, char type, int player) {
			Player* mover;
			int pawnConst, h_max;
			if (player == RED) {
				mover = &Red;
				pawnConst = 1;
				h_max = 0;
			}
			else {
				mover = &Green;
				pawnConst = -1;
				h_max = 7;
			}
			if (MODE == DEBUG) {
				std::cout << "[" << h << ", " << w << "]" << std::endl;
			}
			//Out of board
			if (w > 7 or w < 0 or h != h_max) {
				std::cout << "#1::Invalid position for a promotion" << std::endl;
				return false;
			}
			if (main[h][w].hasPiece()) {
				std::cout << "#2::The pawn is coliding with another piece (occupied tile)" << std::endl;
				return false;
			}
			if (type != 'Q' and
				type != 'R' and
				type != 'B' and
				type != 'N') {

				std::cout << "#3::The pawn can only promote to Queen (Q), Rook (R), Bishop (B) and Knight (N)" << std::endl;
				return false;
			}
			if (hasFriendly('P', h + pawnConst, w, player)) {
				//Make the move
				main[h + pawnConst][w].removePiece();
				main[h][w].addPiece(type, player);
				int player_checked;
				if (isChecked(player_checked) and player_checked == player) {
					if (MODE == DEBUG) {
						std::cout << "#10::The king is in check" << std::endl;
					}
					main[h][w].removePiece();
					main[h + pawnConst][w].addPiece('P', player);
					return false;
				}
				main[h][w].checkPiecePoint()->firstMove();
				target.possible = false;
				halfMoves = 0;
				return true;
			}
			std::cout << "#4::No pawn available to make that move" << std::endl;
			return false;
		}
	}
}