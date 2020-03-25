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
				Red.addDead(tempPiece);
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

		bool Board::knightCapture(int h, int w, int player) {
			if (MODE == DEBUG) {
				std::cout << "[" << h << ", " << w << "]" << std::endl;
			}
			//Out of board
			if (not inBound(h, w)) {
				std::cout << "#1::Your movement is out of bounds for a knight" << std::endl;
				return false;
			}
			//collision #1 no piece in the tile
			else if (not main[h][w].hasPiece()) {
				std::cout << "#2::No piece can be killed in this tile" << std::endl;
				return false;
			}
			else if (main[h][w].checkPlayer() == player) {
				std::cout << "#5::You can't kill a friendly piece" << std::endl;
				return false;
			}
			//Search for player's knight 8 surrounding tiles
			int knight_count = 0;
			int orig_h, orig_w;
			//Check -2, -1
			if (hasFriendly('N', h - 2, w - 1, player)) {
				++knight_count;
				orig_h = h - 2;
				orig_w = w - 1;
			}
			//Check -2, 1
			if (hasFriendly('N', h - 2, w + 1, player)) {
				if (knight_count == 1) {
					std::cout << "#3::More than one knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h - 2;
				orig_w = w + 1;
			}
			//Check -1, 2
			if (hasFriendly('N', h - 1, w + 2, player)) {
				if (knight_count == 1) {
					std::cout << "#3::More than one knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h - 1;
				orig_w = w + 2;
			}
			//Check 1, 2
			if (hasFriendly('N', h + 1, w + 2, player)) {
				if (knight_count == 1) {
					std::cout << "#3::More than one knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h + 1;
				orig_w = w + 2;
			}
			//Check 2, 1
			if (hasFriendly('N', h + 2, w + 1, player)) {
				if (knight_count == 1) {
					std::cout << "#3::More than one knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h + 2;
				orig_w = w + 1;
			}
			//Check 2, -1
			if (hasFriendly('N', h + 2, w - 1, player)) {
				if (knight_count == 1) {
					std::cout << "#3::More than one knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h + 2;
				orig_w = w - 1;
			}
			//Check 1,-2
			if (hasFriendly('N', h + 1, w - 2, player)) {
				if (knight_count == 1) {
					std::cout << "#3::More than one knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h + 1;
				orig_w = w - 2;
			}
			//Check -1, -2
			if (hasFriendly('N', h - 1, w - 2, player)) {
				if (knight_count == 1) {
					std::cout << "#3::More than one knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h - 1;
				orig_w = w - 2;
			}
			if (knight_count == 0) {
				std::cout << "#4::No knight found to make the move" << std::endl;
				return false;
			}
			if (MODE == DEBUG) {
				std::cout << "Found a knight in [" << orig_h << ", " << orig_w << "]" << std::endl;
			}
			//Make the move
			return makeCapture('N', orig_h, orig_w, h, w, player);
		}

		bool Board::rookCapture(int h, int w, int player) {
			if (MODE == DEBUG) {
				std::cout << "[" << h << ", " << w << "]" << std::endl;
			}
			//Out of board
			if (not inBound(h, w)) {
				std::cout << "#1::Your movement is out of bounds for a rook" << std::endl;
				return false;
			}
			//collision #1 there is already a piece in the tile
			else if (not main[h][w].hasPiece()) {
				std::cout << "#2::No piece can be killed in this tile" << std::endl;
				return false;
			}
			else if (main[h][w].checkPlayer() == player) {
				std::cout << "#5::You can't kill a friendly piece" << std::endl;
				return false;
			}
			//Search for player's rook 4 directions
			int rook_count = 0;
			int orig_h, orig_w;
			//Search above
			int it = h + 1;
			while (it <= 7 and not main[it][w].hasPiece()) {
				++it;
			}
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it << ", " << w << "]" << std::endl;
			}
			if (hasFriendly('R', it, w, player)) {
				++rook_count;
				orig_h = it;
				orig_w = w;
			}
			//Search below
			it = h - 1;
			while (it >= 0 and not main[it][w].hasPiece()) {
				--it;
			}
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it << ", " << w << "]" << std::endl;
			}
			if (hasFriendly('R', it, w, player)) {
				++rook_count;
				orig_h = it;
				orig_w = w;
			}
			if (rook_count > 1) {
				std::cout << "#3::More than one rook than can make this move" << std::endl;
				return false;
			}
			//Search to the right
			it = w + 1;
			while (it <= 7 and not main[h][it].hasPiece()) {
				++it;
			}
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << h << ", " << it << "]" << std::endl;
			}
			if (hasFriendly('R', h, it, player)) {
				++rook_count;
				orig_h = h;
				orig_w = it;
			}
			if (rook_count > 1) {
				std::cout << "#3::More than one rook than can make this move" << std::endl;
				return false;
			}
			//Search to the left
			it = w - 1;
			while (it >= 0 and not main[h][it].hasPiece()) {
				--it;
			}
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << h << ", " << it << "]" << std::endl;
			}
			if (hasFriendly('R', h, it, player)) {
				++rook_count;
				orig_h = h;
				orig_w = it;
			}
			if (rook_count > 1) {
				std::cout << "#3::More than one rook than can make this move" << std::endl;
				return false;
			}
			if (rook_count == 0) {
				std::cout << "#4::No rook found to make the move" << std::endl;
				return false;
			}
			if (MODE == DEBUG) {
				std::cout << "Found a rook in [" << orig_h << ", " << orig_w << "]" << std::endl;
			}
			//Make the move
			return makeCapture('R', orig_h, orig_w, h, w, player);
		}

		bool Board::bishopCapture(int h, int w, int player) {
			if (MODE == DEBUG) {
				std::cout << "[" << h << ", " << w << "]" << std::endl;
			}
			//Out of board
			if (not inBound(h, w)) {
				std::cout << "#1::Your movement is out of bounds for a bishop" << std::endl;
				return false;
			}
			//collision #1 there is already a piece in the tile
			else if (not main[h][w].hasPiece()) {
				std::cout << "#2::No piece can be killed in this tile" << std::endl;
				return false;
			}
			else if (main[h][w].checkPlayer() == player) {
				std::cout << "#5::You can't kill a friendly piece" << std::endl;
				return false;
			}

			//Search for player's bishop 4 directions
			int bishop_count = 0;
			int orig_h, orig_w;
			//Search diagonal left-up
			int it_h = h + 1;
			int it_w = w - 1;
			while (it_h <= 7 and it_w >= 0 and not main[it_h][it_w].hasPiece()) {
				++it_h;
				--it_w;
			}
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			}
			if (hasFriendly('B', it_h, it_w, player)) {
				++bishop_count;
				orig_h = it_h;
				orig_w = it_w;
			}
			//Search diagonal left-down
			it_h = h - 1;
			it_w = w - 1;
			while (it_h >= 0 and it_w >= 0 and not main[it_h][it_w].hasPiece()) {
				--it_h;
				--it_w;
			}
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			}
			if (hasFriendly('B', it_h, it_w, player)) {
				++bishop_count;
				orig_h = it_h;
				orig_w = it_w;
			}
			if (bishop_count > 1) {
				std::cout << "#3::More than one bishop than can make this move" << std::endl;
				return false;
			}
			//Search diagonal right-up
			it_h = h + 1;
			it_w = w + 1;
			while (it_h <= 7 and it_w <= 7 and not main[it_h][it_w].hasPiece()) {
				++it_h;
				++it_w;
			}
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			}
			if (hasFriendly('B', it_h, it_w, player)) {
				++bishop_count;
				orig_h = it_h;
				orig_w = it_w;
			}
			if (bishop_count > 1) {
				std::cout << "#3::More than one bishop than can make this move" << std::endl;
				return false;
			}
			//Search diagonal right-down
			it_h = h - 1;
			it_w = w + 1;
			while (it_h >= 0 and it_w <= 7 and not main[it_h][it_w].hasPiece()) {
				--it_h;
				++it_w;
			}
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			}
			if (hasFriendly('B', it_h, it_w, player)) {
				++bishop_count;
				orig_h = it_h;
				orig_w = it_w;
			}
			if (bishop_count > 1) {
				std::cout << "#3::More than one bishop than can make this move" << std::endl;
				return false;
			}
			if (bishop_count == 0) {
				std::cout << "#4::No bishop found to make the move" << std::endl;
				return false;
			}
			if (MODE == DEBUG) {
				std::cout << "Found a bishop in [" << orig_h << ", " << orig_w << "]" << std::endl;
			}
			//Make the move
			return makeCapture('B', orig_h, orig_w, h, w, player);
		}

		bool Board::queenCapture(int h, int w, int player) {
			if (MODE == DEBUG) {
				std::cout << "[" << h << ", " << w << "]" << std::endl;
			}
			//Out of board
			if (not inBound(h, w)) {
				std::cout << "#1::Your movement is out of bounds for a queen" << std::endl;
				return false;
			}
			//collision #1 there is already a piece in the tile
			else if (not main[h][w].hasPiece()) {
				std::cout << "#2::No piece can be killed in this tile" << std::endl;
				return false;
			}
			else if (main[h][w].checkPlayer() == player) {
				std::cout << "#5::You can't kill a friendly piece" << std::endl;
				return false;
			}

			//Search for player's queen 8 directions
			int queen_count = 0;
			int orig_h, orig_w;
			//Search diagonal left-up
			int it_h = h + 1;
			int it_w = w - 1;
			while (it_h <= 7 and it_w >= 0 and not main[it_h][it_w].hasPiece()) {
				++it_h;
				--it_w;
			}
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			}
			if (hasFriendly('Q', it_h, it_w, player)) {
				++queen_count;
				orig_h = it_h;
				orig_w = it_w;
			}
			//Search diagonal left-down
			it_h = h - 1;
			it_w = w - 1;
			while (it_h >= 0 and it_w >= 0 and not main[it_h][it_w].hasPiece()) {
				--it_h;
				--it_w;
			}
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			}
			if (hasFriendly('Q', it_h, it_w, player)) {
				++queen_count;
				orig_h = it_h;
				orig_w = it_w;
			}
			if (queen_count > 1) {
				std::cout << "#3::More than one queen than can make this move" << std::endl;
				return false;
			}
			//Search diagonal right-up
			it_h = h + 1;
			it_w = w + 1;
			while (it_h <= 7 and it_w <= 7 and not main[it_h][it_w].hasPiece()) {
				++it_h;
				++it_w;
			}
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			}
			if (hasFriendly('Q', it_h, it_w, player)) {
				++queen_count;
				orig_h = it_h;
				orig_w = it_w;
			}
			if (queen_count > 1) {
				std::cout << "#3::More than one queen than can make this move" << std::endl;
				return false;
			}
			//Search diagonal right-down
			it_h = h - 1;
			it_w = w + 1;
			while (it_h >= 0 and it_w <= 7 and not main[it_h][it_w].hasPiece()) {
				--it_h;
				++it_w;
			}
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			}
			if (hasFriendly('Q', it_h, it_w, player)) {
				++queen_count;
				orig_h = it_h;
				orig_w = it_w;
			}
			if (queen_count > 1) {
				std::cout << "#3::More than one queen than can make this move" << std::endl;
				return false;
			}
			//Search above
			int it = h + 1;
			while (it <= 7 and not main[it][w].hasPiece()) {
				++it;
			}
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it << ", " << w << "]" << std::endl;
			}
			if (hasFriendly('Q', it, w, player)) {
				++queen_count;
				orig_h = it;
				orig_w = w;
			}
			//Search below
			it = h - 1;
			while (it >= 0 and not main[it][w].hasPiece()) {
				--it;
			}
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it << ", " << w << "]" << std::endl;
			}
			if (hasFriendly('Q', it, w, player)) {
				++queen_count;
				orig_h = it;
				orig_w = w;
			}
			//Search to the right
			it = w + 1;
			while (it <= 7 and not main[h][it].hasPiece()) {
				++it;
			}
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << h << ", " << it << "]" << std::endl;
			}
			if (hasFriendly('Q', h, it, player)) {
				++queen_count;
				orig_h = h;
				orig_w = it;
			}
			if (queen_count > 1) {
				std::cout << "#3::More than one queen than can make this move" << std::endl;
				return false;
			}
			//Search to the left
			it = w - 1;
			while (it >= 0 and not main[h][it].hasPiece()) {
				--it;
			}
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << h << ", " << it << "]" << std::endl;
			}
			if (hasFriendly('Q', h, it, player)) {
				++queen_count;
				orig_h = h;
				orig_w = it;
			}
			if (queen_count > 1) {
				std::cout << "#3::More than one queen than can make this move" << std::endl;
				return false;
			}
			if (queen_count == 0) {
				std::cout << "#4::No queen found to make the move" << std::endl;
				return false;
			}
			if (MODE == DEBUG) {
				std::cout << "Found a queen in [" << orig_h << ", " << orig_w << "]" << std::endl;
			}
			//Make the move
			return makeCapture('Q', orig_h, orig_w, h, w, player);
		}

		bool Board::kingCapture(int h, int w, int player) {
			if (MODE == DEBUG) {
				std::cout << "[" << h << ", " << w << "]" << std::endl;
			}
			//Out of board
			if (not inBound(h, w)) {
				std::cout << "#1::Your movement is out of bounds for a king" << std::endl;
				return false;
			}
			//collision #1 there is already a piece in the tile
			else if (not main[h][w].hasPiece()) {
				std::cout << "#2::No piece can be killed in this tile" << std::endl;
				return false;
			}
			else if (main[h][w].checkPlayer() == player) {
				std::cout << "#5::You can't kill a friendly piece" << std::endl;
				return false;
			}

			//Search for player's king 4 surrounding tiles
			int king_count = 0;
			int orig_h, orig_w;
			int it_h = h - 1;
			int it_w = w - 1;
			while (it_h <= (h + 1)) {
				it_w = w - 1;
				while (it_w <= (w + 1)) {
					if (hasFriendly('K', it_h, it_w, player)) {
						++king_count;
						orig_h = it_h;
						orig_w = it_w;
					}
					++it_w;
				}
				++it_h;
			}
			if (king_count == 0) {
				std::cout << "#4::No king found to make the move" << std::endl;
				return false;
			}
			if (MODE == DEBUG) {
				std::cout << "Found a king in [" << orig_h << ", " << orig_w << "]" << std::endl;
			}
			//Make the move
			if (makeCapture('K', orig_h, orig_w, h, w, player)) {
				if (player == RED) {
					Red.setKing(h, w);
					return true;
				}
				else if (player == GREEN) {
					Green.setKing(h, w);
					return true;
				}
				else {
					std::cout << "No such known player " << player << std::endl;
					return false;
				}
			}
			return false;
		}
	}
}