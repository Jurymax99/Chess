#include "Board.h"
#include "Utilities.h"

namespace Chess {
	namespace Engine {

		bool Board::makeCapture(char type, int orig_h, int orig_w, int h, int w, int player) {
			char type_killed = main[h][w].checkPieceType();
			int player_killed = main[h][w].checkPlayer();
			bool first_mov_killed = main[h][w].isFirstMov();
			bool first_mov_killer = main[orig_h][orig_w].isFirstMov();
			Pieces::Piece tempPiece = main[h][w].checkPiece();
			int tempScore = main[h][w].killPiece();
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece(type, player);
			if (type == 'K') {
				if (player == RED) {
					Red.setKing(h, w);
				}
				else if (player == GREEN) {
					Green.setKing(h, w);
				}
			}
			int player_checked;
			if (isChecked(player_checked) and player_checked == player) {
				if (player == RED) {
					if (type == 'K') {
						Red.setKing(orig_h, orig_w);
					}
					if (MODE == DEBUG) {
						std::cout << "#10::The red king is in check" << std::endl;
					}
				}
				else if (player == GREEN) {
					if (type == 'K') {
						Green.setKing(orig_h, orig_w);
					}
					if (MODE == DEBUG) {
						std::cout << "#10::The green king is in check" << std::endl;
					}
				}
				else {
					std::cout << "#10::No known player" << std::endl;
					return false;
				}
				main[h][w].removePiece();
				main[orig_h][orig_w].addPiece(type, player);
				main[h][w].addPiece(type_killed, player_killed);
				if (not first_mov_killed) {
					main[h][w].checkPiecePoint()->firstMove();
				}
				if (not first_mov_killer) {
					main[orig_h][orig_w].checkPiecePoint()->firstMove();
				}
				return false;
			}
			if (player == RED) {
				Green.addDead(tempPiece);
				Red.addScore(tempScore);
			}
			else if (player == GREEN) {
				Red.addDead(tempPiece);
				Green.addScore(tempScore);
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			main[h][w].checkPiecePoint()->firstMove();
			return true;
		}

		bool Board::makeCapture(char type, char typepro, int orig_h, int orig_w, int h, int w, int player) {
			//e4 f5 exf5 e5 fxe6 d5 e7 Qd6 exf8=Q
			char type_killed = main[h][w].checkPieceType();
			int player_killed = main[h][w].checkPlayer();
			bool first_mov_killed = main[h][w].isFirstMov();
			bool first_mov_killer = main[orig_h][orig_w].isFirstMov();
			Pieces::Piece tempPiece = main[h][w].checkPiece();
			int tempScore = main[h][w].killPiece();
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece(typepro, player);
			int player_checked;
			if (isChecked(player_checked) and player_checked == player) {
				if (player == RED) {
					if (MODE == DEBUG) {
						std::cout << "#10::The red king is in check" << std::endl;
					}
				}
				else if (player == GREEN) {
					if (MODE == DEBUG) {
						std::cout << "#10::The green king is in check" << std::endl;
					}
				}
				else {
					std::cout << "#10::No known player" << std::endl;
					return false;
				}
				main[h][w].removePiece();
				main[orig_h][orig_w].addPiece(type, player);
				main[h][w].addPiece(type_killed, player_killed);
				if (not first_mov_killed) {
					main[h][w].checkPiecePoint()->firstMove();
				}
				if (not first_mov_killer) {
					main[orig_h][orig_w].checkPiecePoint()->firstMove();
				}
				return false;
			}
			if (player == RED) {
				Green.addDead(tempPiece);
				Red.addScore(tempScore);
			}
			else if (player == GREEN) {
				Red.addDead(tempPiece);
				Green.addScore(tempScore);
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			main[h][w].checkPiecePoint()->firstMove();
			return true;
		}

		bool Board::makeFakeCapture(char type, int orig_h, int orig_w, int h, int w, int player, bool& check) {
			char type_killed = main[h][w].checkPieceType();
			int player_killed = main[h][w].checkPlayer();
			bool first_mov_killed = main[h][w].isFirstMov();
			bool first_mov_killer = main[orig_h][orig_w].isFirstMov();
			main[orig_h][orig_w].removePiece();
			main[h][w].removePiece();
			main[h][w].addPiece(type, player);
			if (type == 'K') {
				if (player == RED) {
					Red.setKing(h, w);
				}
				else if (player == GREEN) {
					Green.setKing(h, w);
				}
			}
			int player_checked;
			if (isChecked(player_checked)) {
				if (areBothChecked() or player_checked == player) {
					if (player == RED) {
						if (type == 'K') {
							Red.setKing(orig_h, orig_w);
						}
						if (MODE == DEBUG) {
							std::cout << "#10::The red king is in check" << std::endl;
						}
					}
					else if (player == GREEN) {
						if (type == 'K') {
							Green.setKing(orig_h, orig_w);
						}
						if (MODE == DEBUG) {
							std::cout << "#10::The green king is in check" << std::endl;
						}
					}
					else {
						std::cout << "#10::No known player" << std::endl;
						return false;
					}
					main[h][w].removePiece();
					main[orig_h][orig_w].addPiece(type, player);
					main[h][w].addPiece(type_killed, player_killed);
					if (not first_mov_killed) {
						main[h][w].checkPiecePoint()->firstMove();
					}
					if (not first_mov_killer) {
						main[orig_h][orig_w].checkPiecePoint()->firstMove();
					}
					return false;
				}
				else {
					check = true;
				}
			}
			if (type == 'K') {
				if (player == RED) {
					Red.setKing(orig_h, orig_w);
				}
				else if (player == GREEN) {
					Green.setKing(orig_h, orig_w);
				}
			}
			main[h][w].removePiece();
			main[orig_h][orig_w].addPiece(type, player);
			main[h][w].addPiece(type_killed, player_killed);
			if (not first_mov_killed) {
				main[h][w].checkPiecePoint()->firstMove();
			}
			if (not first_mov_killer) {
				main[orig_h][orig_w].checkPiecePoint()->firstMove();
			}
			return true;
		}
				
		bool Board::makeFakeCapturePro(int orig_h, int orig_w, int h, int w, int player, bool& check) {
			char type_killed = main[h][w].checkPieceType();
			int player_killed = main[h][w].checkPlayer();
			bool first_mov_killed = main[h][w].isFirstMov();
			bool first_mov_killer = main[orig_h][orig_w].isFirstMov();
			main[orig_h][orig_w].removePiece();
			main[h][w].removePiece(); 
			std::vector<char> types = { 'Q', 'N', 'R', 'B' };
			int i = 0;
			while (i < 4 and not check) {
				main[h][w].addPiece(types[i], player);
				int player_checked;
				if (isChecked(player_checked)) {
					if (areBothChecked() or player_checked == player) {
						if (player == RED) {
							if (MODE == DEBUG) {
								std::cout << "#10::The red king is in check" << std::endl;
							}
						}
						else if (player == GREEN) {
							if (MODE == DEBUG) {
								std::cout << "#10::The green king is in check" << std::endl;
							}
						}
						else {
							std::cout << "#10::No known player" << std::endl;
							return false;
						}
						main[h][w].removePiece();
						main[orig_h][orig_w].addPiece('P', player);
						main[h][w].addPiece(type_killed, player_killed);
						if (not first_mov_killed) {
							main[h][w].checkPiecePoint()->firstMove();
						}
						if (not first_mov_killer) {
							main[orig_h][orig_w].checkPiecePoint()->firstMove();
						}
						return false;
					}
					else {
						check = true;
					}
				}
				if (not check) {
					main[h][w].removePiece();
				}
				++i;
			}
			if (main[h][w].hasPiece()) {
				main[h][w].removePiece();
			}
			main[orig_h][orig_w].addPiece('P', player);
			main[h][w].addPiece(type_killed, player_killed);
			if (not first_mov_killed) {
				main[h][w].checkPiecePoint()->firstMove();
			}
			if (not first_mov_killer) {
				main[orig_h][orig_w].checkPiecePoint()->firstMove();
			}
			return true;
		}

		bool Board::makeFakeEnPassant(int orig_h, int orig_w, int dest_h, int dest_w, int killed_h, int killed_w, int player, bool& check) {
			int player_killed = main[killed_h][killed_w].checkPlayer();
			bool first_mov_killed = main[killed_h][killed_w].isFirstMov();
			bool first_mov_killer = main[orig_h][orig_w].isFirstMov();
			main[orig_h][orig_w].removePiece();
			main[killed_h][killed_w].removePiece();
			main[dest_h][dest_w].addPiece('P', player);
			int player_checked;
			if (isChecked(player_checked)){
				if (player_checked == player) {
					if (player == RED) {
						if (MODE == DEBUG) {
							std::cout << "#10::The red king is in check" << std::endl;
						}
					}
					else if (player == GREEN) {
						if (MODE == DEBUG) {
							std::cout << "#10::The green king is in check" << std::endl;
						}
					}
					else {
						std::cout << "#10::No known player" << std::endl;
						return false;
					}
					main[dest_h][dest_w].removePiece();
					main[orig_h][orig_w].addPiece('P', player);
					main[killed_h][killed_w].addPiece('P', player_killed);
					if (not first_mov_killed) {
						main[killed_h][killed_w].checkPiecePoint()->firstMove();
					}
					if (not first_mov_killer) {
						main[orig_h][orig_w].checkPiecePoint()->firstMove();
					}
					return false;
				}
				else {
					check = true;
				}
			}
			main[dest_h][dest_w].removePiece();
			main[orig_h][orig_w].addPiece('P', player);
			main[killed_h][killed_w].addPiece('P', player_killed);
			if (not first_mov_killed) {
				main[killed_h][killed_w].checkPiecePoint()->firstMove();
			}
			if (not first_mov_killer) {
				main[orig_h][orig_w].checkPiecePoint()->firstMove();
			}
			return true;
		}

		bool Board::pawnCapture(int w_s, int h_d, int w_d, int player, bool enpassant) {
			if (player == RED) {
				return pawnRedCapture(w_s, h_d, w_d, enpassant);
			}
			else if (player == GREEN) {
				return pawnGreenCapture(w_s, h_d, w_d, enpassant);
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
		}

		bool Board::pawnRedCapture(int w_s, int h_d, int w_d, bool enpassant) {
			int h_s = h_d;
			if (MODE == DEBUG) {
				std::cout << "From rank " << w_s << " to [" << h_d << ", " << w_d << "]" << std::endl;
			}
			if (not inBound(h_d, w_d)) {
				std::cout << "#1::Your movement is out of bounds for a pawn" << std::endl;
				return false;
			}
			if (h_d == 0) {
				std::cout << "6#::The pawn can promote to another piece" << std::endl;
				return false;
			}
			bool correct_enp = false;
			if (not main[h_d][w_d].hasPiece()) {
				if (not enpassant) {
					std::cout << "#2::No piece can be killed in this tile" << std::endl;
					return false;
				}
				h_s = h_d + 1;
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
			if (hasFriendly('P', h_d + 1, w_s, RED)) {
				//Make the move
				int killer_h, killer_w;
				int killed_h, killed_w;
				int tempScore;
				char type;
				Pieces::Piece tempPiece;
				bool first_mov_killer;
				bool first_mov_killed;
				if (correct_enp) {
					killer_h = h_d + 1;
					killer_w = w_s;
					killed_h = h_d + 1;
					killed_w = w_d;
				}
				else {
					killer_h = h_d + 1;
					killer_w = w_s;
					killed_h = h_d;
					killed_w = w_d;
				}
				first_mov_killer = main[killer_h][killer_w].isFirstMov();
				first_mov_killed = main[killed_h][killed_w].isFirstMov();
				tempPiece = main[killed_h][killed_w].checkPiece();
				tempScore = tempPiece.checkPoints();
				type = tempPiece.checkType();
				main[killer_h][killer_w].removePiece();
				main[killed_h][killed_w].removePiece();
				main[h_d][w_d].addPiece('P', RED);
				int player_checked;
				if (isChecked(player_checked) and player_checked == RED) {
					if (MODE == DEBUG) {
						std::cout << "#10::The red king is in check" << std::endl;
					}
					//Rollback
					main[h_d][w_d].removePiece();
					//Killer
					main[killer_h][killer_w].addPiece('P', RED);
					//Killed
					main[killed_h][killer_h].addPiece(type, GREEN);
					if (not first_mov_killer) {
						main[killer_h][killer_w].checkPiecePoint()->firstMove();
					}
					if (not first_mov_killed) {
						main[killed_h][killed_w].checkPiecePoint()->firstMove();
					}
					return false;
				}
				//Commit
				Green.addDead(tempPiece);
				Red.addScore(tempScore);
				main[h_d][w_d].checkPiecePoint()->firstMove();
				return true;
			}
			else {
				std::cout << "#5::You can't kill a friendly pawn" << std::endl;
				return false;
			}
		}

		bool Board::pawnGreenCapture(int w_s, int h_d, int w_d, bool enpassant) {
			if (MODE == DEBUG) {
				std::cout << "From rank " << w_s << " to [" << h_d << ", " << w_d << "]" << std::endl;
			}
			int h_s = h_d;
			if (not inBound(h_d, w_d)) {
				std::cout << "#1::Your movement is out of bounds for a pawn" << std::endl;
				return false;
			}
			if (h_d == 7) {
				std::cout << "6#::The pawn can promote to another piece" << std::endl;
				return false;
			}
			bool correct_enp = false;
			if (not main[h_d][w_d].hasPiece()) {
				if (not enpassant) {
					std::cout << "#2::No piece can be killed in this tile" << std::endl;
					return false;
				}
				h_s = h_d - 1;
				if (not main[h_s][w_d].hasPiece()){
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
			if (hasFriendly('P', h_d - 1, w_s, GREEN)) {
				//Make the move
				int killer_h, killer_w;
				int killed_h, killed_w;
				int tempScore;
				char type;
				Pieces::Piece tempPiece;
				bool first_mov_killer;
				bool first_mov_killed;
				if (correct_enp) {
					killer_h = h_d - 1;
					killer_w = w_s;
					killed_h = h_d - 1;
					killed_w = w_d;
				}
				else {
					killer_h = h_d - 1;
					killer_w = w_s;
					killed_h = h_d;
					killed_w = w_d;
				}
				first_mov_killer = main[killer_h][killer_w].isFirstMov();
				first_mov_killed = main[killed_h][killed_w].isFirstMov();
				tempPiece = main[killed_h][killed_w].checkPiece();
				tempScore = tempPiece.checkPoints();
				type = tempPiece.checkType();
				main[killer_h][killer_w].removePiece();
				main[killed_h][killed_w].removePiece();
				main[h_d][w_d].addPiece('P', GREEN);
				int player_checked;
				if (isChecked(player_checked) and player_checked == GREEN) {
					if (MODE == DEBUG) {
						std::cout << "#10::The green king is in check" << std::endl;
					}
					//Rollback
					main[h_d][w_d].removePiece();
					//Killer
					main[killer_h][killer_w].addPiece('P', GREEN);
					//Killed
					main[killed_h][killed_w].addPiece(type, RED);
					if (not first_mov_killer) {
						main[killer_h][killer_w].checkPiecePoint()->firstMove();
					}
					if (not first_mov_killed) {
						main[killed_h][killed_w].checkPiecePoint()->firstMove();
					}
					return false;
				}
				//Commit
				Red.addDead(tempPiece);
				Green.addScore(tempScore);
				main[h_d][w_d].checkPiecePoint()->firstMove();
				return true;
			}
			else {
				std::cout << "#5::You can't kill a friendly pawn" << std::endl;
				return false;
			}
		}

		bool Board::pawnPromoteCapture(int w_s, int h_d, int w_d, char type, int player) {
			if (player == RED) {
				return pawnRedPromoteCapture(w_s, h_d, w_d, type);
			}
			else if (player == GREEN) {
				return pawnGreenPromoteCapture(w_s, h_d, w_d, type);
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
		}

		bool Board::pawnRedPromoteCapture(int w_s, int h_d, int w_d, char type) {
			if (MODE == DEBUG) {
				std::cout << "From rank " << w_s << " to [" << h_d << ", " << w_d << "]" << std::endl;
			}
			//Out of board
			if (w_d > 7 or w_d < 0 or h_d != 0) {
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
			if (hasFriendly('P', h_d + 1, w_s, RED)) {

				//Make the move
				return makeCapture('P', type, h_d + 1, w_s, h_d, w_d, RED);
			}
			std::cout << "#4::No pawn available to make that move" << std::endl;
			return false;
		}

		bool Board::pawnGreenPromoteCapture(int w_s, int h_d, int w_d, char type) {
			if (MODE == DEBUG) {
				std::cout << "From rank " << w_s << " to [" << h_d << ", " << w_d << "]" << std::endl;
			}
			//Out of board
			if (w_d > 7 or w_d < 0 or h_d != 7) {
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
			if (hasFriendly('P', h_d - 1, w_s, GREEN)) {

				//Make the move
				return makeCapture('P', type, h_d - 1, w_s, h_d, w_d, GREEN);
			}
			std::cout << "#4::No pawn available to make that move" << std::endl;
			return false;
		}
	}
}