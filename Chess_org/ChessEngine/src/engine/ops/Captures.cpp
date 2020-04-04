#include "Board.h"
#include "Utilities.h"

namespace Chess {
	namespace Engine {

		bool Board::makeCapture(char type, int orig_h, int orig_w, int h, int w, int player) {
			Player *killed, *killer;
			if (player == RED) {
				killer = &Red;
				killed = &Green;
			}
			else {
				killed = &Red;
				killer = &Green;
			}
			char type_killed = main[h][w].checkPieceType();
			//int player_killed = main[h][w].checkPlayer();
			bool first_mov_killed = main[h][w].isFirstMov();
			bool first_mov_killer = main[orig_h][orig_w].isFirstMov();
			Pieces::Piece tempPiece = main[h][w].checkPiece();
			
			int tempScore = main[h][w].killPiece();
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece(type, player);
			if (type == 'K') {
				killer->setKing(orig_h, orig_w);
			}
			killed->addDead(tempPiece);
			killer->addScore(tempScore);
			main[h][w].checkPiecePoint()->firstMove();
			return true;
		}

		bool Board::makeCapture(char type, char typepro, int orig_h, int orig_w, int h, int w, int player) {
			//e4 f5 exf5 e5 fxe6 d5 e7 Qd6 exf8=Q
			Player* killed, * killer;
			if (player == RED) {
				killer = &Red;
				killed = &Green;
			}
			else {
				killed = &Red;
				killer = &Green;
			}
			char type_killed = main[h][w].checkPieceType();
			//int player_killed = main[h][w].checkPlayer();
			bool first_mov_killed = main[h][w].isFirstMov();
			bool first_mov_killer = main[orig_h][orig_w].isFirstMov();
			Pieces::Piece tempPiece = main[h][w].checkPiece();
			int tempScore = main[h][w].killPiece();
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece(typepro, player);
			killed->addDead(tempPiece);
			killer->addScore(tempScore);
			target.possible = false;
			main[h][w].checkPiecePoint()->firstMove();
			return true;
		}

		bool Board::makeFakeCapture(char type, int orig_h, int orig_w, int h, int w, int player, bool& check) {
			Player* killed, * killer;
			if (player == RED) {
				killer = &Red;
				killed = &Green;
			}
			else {
				killed = &Red;
				killer = &Green;
			}
			char type_killed = main[h][w].checkPieceType();
			bool first_mov_killed = main[h][w].isFirstMov();
			bool first_mov_killer = main[orig_h][orig_w].isFirstMov();
			main[orig_h][orig_w].removePiece();
			main[h][w].removePiece();
			main[h][w].addPiece(type, player);
			if (type == 'K') {
				killer->setKing(h, w);
			}
			int player_checked;
			int totChecked = whoChecked(player_checked);
			//rollback
			if (type == 'K') {
				killer->setKing(orig_h, orig_w);
			}
			main[h][w].removePiece();
			main[orig_h][orig_w].addPiece(type, player);
			main[h][w].addPiece(type_killed, killed->checkColor());
			if (not first_mov_killed) {
				main[h][w].checkPiecePoint()->firstMove();
			}
			if (not first_mov_killer) {
				main[orig_h][orig_w].checkPiecePoint()->firstMove();
			}
			
			if (totChecked == 0) {
				return true;
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
			std::cout << "More than 2 players checked?" << std::endl;
			return false;
		}
				
		bool Board::makeFakeCapturePro(int orig_h, int orig_w, int h, int w, int player, bool& check) {
			Player* killed, * killer;
			if (player == RED) {
				killer = &Red;
				killed = &Green;
			}
			else {
				killed = &Red;
				killer = &Green;
			}
			char type_killed = main[h][w].checkPieceType();
			bool first_mov_killed = main[h][w].isFirstMov();
			bool first_mov_killer = main[orig_h][orig_w].isFirstMov();
			
			std::vector<char> types = { 'Q', 'N', 'R', 'B' };

			int i = 0;
			while (i < 4 and not check) {
				main[orig_h][orig_w].removePiece();
				main[h][w].removePiece();
				main[h][w].addPiece(types[i], player);
				int player_checked;
				int totChecked = whoChecked(player_checked);
				main[h][w].removePiece();
				main[orig_h][orig_w].addPiece('P', player);
				main[h][w].addPiece(type_killed, killed->checkColor());
				if (not first_mov_killed) {
					main[h][w].checkPiecePoint()->firstMove();
				}
				if (not first_mov_killer) {
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

		bool Board::makeFakeEnPassant(int orig_h, int orig_w, int dest_h, int dest_w, int killed_h, int killed_w, int player, bool& check) {
			Player* killed, * killer;
			if (player == RED) {
				killer = &Red;
				killed = &Green;
			}
			else {
				killed = &Red;
				killer = &Green;
			}
			bool first_mov_killed = main[killed_h][killed_w].isFirstMov();
			bool first_mov_killer = main[orig_h][orig_w].isFirstMov();
			main[orig_h][orig_w].removePiece();
			main[killed_h][killed_w].removePiece();
			main[dest_h][dest_w].addPiece('P', player);

			int player_checked;
			int totChecked = whoChecked(player_checked);

			main[dest_h][dest_w].removePiece();
			main[orig_h][orig_w].addPiece('P', player);
			main[killed_h][killed_w].addPiece('P', killed->checkColor());
			if (not first_mov_killed) {
				main[killed_h][killed_w].checkPiecePoint()->firstMove();
			}
			if (not first_mov_killer) {
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

		bool Board::pawnCapture(int w_s, int h_d, int w_d, int player, bool enpassant) {
			int h_s = h_d;
			int pawnConst;
			if (player == RED) {
				pawnConst = 1;
			}
			else if (player == GREEN) {
				pawnConst = -1;
			}
			else {
				std::cout << "No such known player" << std::endl;
				return false;
			}

			if (MODE == DEBUG) {
				std::cout << "From rank " << w_s << " to [" << h_d << ", " << w_d << "]" << std::endl;
			}
			if (not inBound(h_d, w_d)) {
				std::cout << "#1::Your movement is out of bounds for a pawn" << std::endl;
				return false;
			}
			if ((player == RED and h_d == 0) or (player == GREEN and h_d == 7)) {
				std::cout << "6#::The pawn can promote to another piece" << std::endl;
				return false;
			}
			bool correct_enp = false;
			if (not main[h_d][w_d].hasPiece()) {
				if (not enpassant) {
					std::cout << "#2::No piece can be killed in this tile" << std::endl;
					return false;
				}
				h_s = h_d + pawnConst;
				if (not main[h_s][w_d].hasPiece()) {
					std::cout << "#6::There is no piece in this tile that can be killed en passant" << std::endl;
					return false;
				}
				if (not (target.h == (h_s) and target.w == w_d)) {
					std::cout << "#7::The pawn you want to kill is not the one that can be killed en passant" << std::endl;
					return false;
				}
				correct_enp = true;
			}
			if (w_s == w_d) {
				std::cout << "#3::Pawns can only capture in diagonal" << std::endl;
				return false;
			}
			if (abs(w_s - w_d) > 1) {
				std::cout << "#4::Pawns can only capture at 1 tile of distance" << std::endl;
				return false;
			}
			//look for pawn below the given position 
			if (hasFriendly('P', h_d + pawnConst, w_s, player)) {
				Player* killer, * killed;
				if (player == RED) {
					killer = &Red;
					killed = &Green;
				}
				else {
					killer = &Green;
					killed = &Red;
				}
				//Make the move
				int killer_h, killer_w;
				int killed_h, killed_w;
				if (correct_enp) {
					killer_h = h_d + pawnConst;
					killer_w = w_s;
					killed_h = h_d + pawnConst;
					killed_w = w_d;
				}
				else {
					killer_h = h_d + pawnConst;
					killer_w = w_s;
					killed_h = h_d;
					killed_w = w_d;
				}
				bool first_mov_killer = main[killer_h][killer_w].isFirstMov();
				bool first_mov_killed = main[killed_h][killed_w].isFirstMov();
				Pieces::Piece tempPiece = main[killed_h][killed_w].checkPiece();
				int tempScore = tempPiece.checkPoints();
				char type = tempPiece.checkType();


				
				main[killer_h][killer_w].removePiece();
				main[killed_h][killed_w].removePiece();
				main[h_d][w_d].addPiece('P', player);

				int player_checked;
				if (isChecked(player_checked) and player_checked == player) {
					if (MODE == DEBUG) {
						std::cout << "#10::The king is in check" << std::endl;
					}
					//Rollback
					main[h_d][w_d].removePiece();
					//Killer
					main[killer_h][killer_w].addPiece('P', player);
					//Killed
					main[killed_h][killer_h].addPiece(type, killed->checkColor());
					if (not first_mov_killer) {
						main[killer_h][killer_w].checkPiecePoint()->firstMove();
					}
					if (not first_mov_killed) {
						main[killed_h][killed_w].checkPiecePoint()->firstMove();
					}
					return false;
				}
				//Commit
				killed->addDead(tempPiece);
				killer->addScore(tempScore);
				target.possible = false;
				main[h_d][w_d].checkPiecePoint()->firstMove();
				return true;
			}
			else {
				std::cout << "#5::You can't kill a friendly pawn" << std::endl;
				return false;
			}
		}

		bool Board::pawnPromoteCapture(int w_s, int h_d, int w_d, char type, int player) {
			int pawnConst, h_max;
			if (player == RED) {
				pawnConst = 1;
				h_max = 0;
			}
			else if (player == GREEN) {
				pawnConst = -1;
				h_max = 7;
			}
			else {
				std::cout << "No such known player" << std::endl;
				return false;
			}
			if (MODE == DEBUG) {
				std::cout << "From rank " << w_s << " to [" << h_d << ", " << w_d << "]" << std::endl;
			}
			//Out of board
			if (w_d > 7 or w_d < 0 or h_d != h_max) {
				std::cout << "#1::Invalid position for a promotion" << std::endl;
				return false;
			}
			if (not main[h_d][w_d].hasPiece()) {
				std::cout << "#2::No piece can be killed in this tile" << std::endl;
				return false;
			}
			if (w_s == w_d) {
				std::cout << "#3::Pawns can only capture in diagonal" << std::endl;
				return false;
			}
			if (abs(w_s - w_d) > 1) {
				std::cout << "#4::Pawns can only capture at 1 tile of distance" << std::endl;
				return false;
			}
			if (type != 'Q' and
				type != 'R' and
				type != 'B' and
				type != 'N') {

				std::cout << "#3::The pawn can only promote to Queen (Q), Rook (R), Bishop (B) and Knight (N)" << std::endl;
				return false;
			}

			//Look for the pawn
			if (hasFriendly('P', h_d + pawnConst, w_s, player)) {

				//Make the move
				return makeCapture('P', type, h_d + pawnConst, w_s, h_d, w_d, player);
			}
			std::cout << "#4::No pawn available to make that move" << std::endl;
			return false;
		}
	}
}