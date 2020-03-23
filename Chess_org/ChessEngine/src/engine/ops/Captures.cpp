#include "Board.h"
#include "Utilities.h"

namespace Chess {
	namespace Engine {

		bool Board::pawnCapture(int w_s, int h_d, int w_d, int player, bool enpassant) {
			if (player == BLUE) {
				return pawnBlueCapture(w_s, h_d, w_d, enpassant);
			}
			else if (player == GREEN) {
				return pawnGreenCapture(w_s, h_d, w_d, enpassant);
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
		}

		bool Board::pawnBlueCapture(int w_s, int h_d, int w_d, bool enpassant) {
			int h_s = h_d;
			std::cout << "From rank " << w_s << " to [" << h_d << ", " << w_d << "]" << std::endl;
			if (not inBound(h_d, w_d)) {
				std::cout << "#1::Your movement is out of bounds for a pawn" << std::endl;
				return false;
			}
			if (h_d == 0) {
				std::cout << "6#::The pawn can promote to another piece" << std::endl;
				return false;
			}
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
			if (hasFriendly('P', h_d + 1, w_s, BLUE)) {
				//Make the move
				addGreenDead(main[h_s][w_d].checkPiece());
				blueScore += main[h_s][w_d].killPiece();
				main[h_d + 1][w_s].removePiece();
				main[h_d][w_d].addPiece('P', BLUE);
				main[h_d][w_d].checkPiecePoint()->firstMove();
				return true;
			}
			else {
				std::cout << "#5::You can't kill a friendly pawn" << std::endl;
				return false;
			}
		}

		bool Board::pawnGreenCapture(int w_s, int h_d, int w_d, bool enpassant) {
			std::cout << "From rank " << w_s << " to [" << h_d << ", " << w_d << "]" << std::endl;
			int h_s = h_d;
			if (not inBound(h_d, w_d)) {
				std::cout << "#1::Your movement is out of bounds for a pawn" << std::endl;
				return false;
			}
			if (h_d == 7) {
				std::cout << "6#::The pawn can promote to another piece" << std::endl;
				return false;
			}
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
				addBlueDead(main[h_s][w_d].checkPiece());
				greenScore += main[h_s][w_d].killPiece();
				main[h_d - 1][w_s].removePiece();
				main[h_d][w_d].addPiece('P', GREEN);
				main[h_d][w_d].checkPiecePoint()->firstMove();
				return true;
			}
			else {
				std::cout << "#5::You can't kill a friendly pawn" << std::endl;
				return false;
			}
		}

		bool Board::pawnPromoteCapture(int w_s, int h_d, int w_d, char type, int player) {
			if (player == BLUE) {
				return pawnBluePromoteCapture(w_s, h_d, w_d, type);
			}
			else if (player == GREEN) {
				return pawnGreenPromoteCapture(w_s, h_d, w_d, type);
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
		}

		bool Board::pawnBluePromoteCapture(int w_s, int h_d, int w_d, char type) {
			std::cout << "From rank " << w_s << " to [" << h_d << ", " << w_d << "]" << std::endl;
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
			if (hasFriendly('P', h_d + 1, w_s, BLUE)) {

				//Make the move
				addGreenDead(main[h_d][w_d].checkPiece());
				blueScore += main[h_d][w_d].killPiece();
				main[h_d + 1][w_s].removePiece();
				main[h_d][w_d].addPiece(type, BLUE);
				main[h_d][w_d].checkPiecePoint()->firstMove();
				return true;
			}
			std::cout << "#4::No pawn available to make that move" << std::endl;
			return false;
		}

		bool Board::pawnGreenPromoteCapture(int w_s, int h_d, int w_d, char type) {
			std::cout << "From rank " << w_s << " to [" << h_d << ", " << w_d << "]" << std::endl;
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
				addBlueDead(main[h_d][w_d].checkPiece());
				greenScore += main[h_d][w_d].killPiece();
				main[h_d - 1][w_s].removePiece();
				main[h_d][w_d].addPiece(type, GREEN);
				main[h_d][w_d].checkPiecePoint()->firstMove();
				return true;
			}
			std::cout << "#4::No pawn available to make that move" << std::endl;
			return false;
		}

		bool Board::knightCapture(int h, int w, int player) {
			std::cout << "[" << h << ", " << w << "]" << std::endl;
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
			std::cout << "Found a knight in [" << orig_h << ", " << orig_w << "]" << std::endl;
			//Make the move
			if (player == BLUE) {
				addGreenDead(main[h][w].checkPiece());
				blueScore += main[h][w].killPiece();
			}
			else if (player == GREEN) {
				addBlueDead(main[h][w].checkPiece());
				greenScore += main[h][w].killPiece();
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece('N', player);
			main[h][w].checkPiecePoint()->firstMove();
			return true;
		}

		bool Board::rookCapture(int h, int w, int player) {
			std::cout << "[" << h << ", " << w << "]" << std::endl;
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
			std::cout << "Found piece at [" << it << ", " << w << "]" << std::endl;
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
			std::cout << "Found piece at [" << it << ", " << w << "]" << std::endl;
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
			std::cout << "Found piece at [" << h << ", " << it << "]" << std::endl;
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
			std::cout << "Found piece at [" << h << ", " << it << "]" << std::endl;
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
			std::cout << "Found a rook in [" << orig_h << ", " << orig_w << "]" << std::endl;

			//Make the move
			if (player == BLUE) {
				addGreenDead(main[h][w].checkPiece());
				blueScore += main[h][w].killPiece();
			}
			else if (player == GREEN) {
				addBlueDead(main[h][w].checkPiece());
				greenScore += main[h][w].killPiece();
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece('R', player);
			main[h][w].checkPiecePoint()->firstMove();
			return true;
		}

		bool Board::bishopCapture(int h, int w, int player) {
			std::cout << "[" << h << ", " << w << "]" << std::endl;
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
			std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
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
			std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
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
			std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
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
			std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
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
			std::cout << "Found a bishop in [" << orig_h << ", " << orig_w << "]" << std::endl;
			//Make the move
			if (player == BLUE) {
				addGreenDead(main[h][w].checkPiece());
				blueScore += main[h][w].killPiece();
			}
			else if (player == GREEN) {
				addBlueDead(main[h][w].checkPiece());
				greenScore += main[h][w].killPiece();
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece('B', player);
			main[h][w].checkPiecePoint()->firstMove();
			return true;
		}

		bool Board::queenCapture(int h, int w, int player) {
			std::cout << "[" << h << ", " << w << "]" << std::endl;
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
			std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
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
			std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
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
			std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
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
			std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
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
			std::cout << "Found piece at [" << it << ", " << w << "]" << std::endl;
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
			std::cout << "Found piece at [" << it << ", " << w << "]" << std::endl;
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
			std::cout << "Found piece at [" << h << ", " << it << "]" << std::endl;
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
			std::cout << "Found piece at [" << h << ", " << it << "]" << std::endl;
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
			std::cout << "Found a queen in [" << orig_h << ", " << orig_w << "]" << std::endl;
			//Make the move
			if (player == BLUE) {
				addGreenDead(main[h][w].checkPiece());
				blueScore += main[h][w].killPiece();
			}
			else if (player == GREEN) {
				addBlueDead(main[h][w].checkPiece());
				greenScore += main[h][w].killPiece();
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece('Q', player);
			main[h][w].checkPiecePoint()->firstMove();
			return true;
		}

		bool Board::kingCapture(int h, int w, int player) {
			std::cout << "[" << h << ", " << w << "]" << std::endl;
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
			std::cout << "Found a king in [" << orig_h << ", " << orig_w << "]" << std::endl;
			//Make the move
			if (player == BLUE) {
				addGreenDead(main[h][w].checkPiece());
				blueScore += main[h][w].killPiece();
				blueKing = { h,w };
			}
			else if (player == GREEN) {
				addBlueDead(main[h][w].checkPiece());
				greenScore += main[h][w].killPiece();
				greenKing = { h,w };
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece('K', player);
			main[h][w].checkPiecePoint()->firstMove();
			return true;
		}
	}
}