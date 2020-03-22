#include "Board.h"
#include "Utilities.h"

namespace Chess {
	namespace Engine {

		bool Board::pawnMove(int h, int w, int player) {
			if (player == BLUE) {
				return pawnBlueMove(h, w);
			}
			else if (player == GREEN) {
				return pawnGreenMove(h, w);
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
		}

		bool Board::pawnBlueMove(int h, int w) {
			std::cout << "[" << h << ", " << w << "]" << std::endl;
			//Out of board
			if (w > 7 or w < 0 or h > 5 or h < 0) {
				std::cout << "#1::Your movement is out of bounds for a pawn" << std::endl;
				return false;
			}
			else if (h == 0) {
				std::cout << "10#::The pawn can promote to another piece" << std::endl;
				return false;
			}
			if (main[h + 1][w].hasPiece()) {
				//collision #1 pawn has another piece in between
				if (main[h + 1][w].checkPieceType() != 'P') {
					std::cout << "#2::The pawn is coliding with another piece (piece in between)" << std::endl;
					return false;
				}
				//collision #2 pawn wants to move to occupied tile
				else if (main[h][w].hasPiece()) {
					std::cout << "#3::The pawn is coliding with another piece (occupied tile)" << std::endl;
					return false;
				}
				//collision #3 pawn is from another player
				else if (main[h + 1][w].checkPlayer() != BLUE) {
					std::cout << "#4::No available blue pawns to make the move" << std::endl;
					return false;
				}
				//remove and add the piece to new position
				main[h + 1][w].removePiece();
				main[h][w].addPiece('P', BLUE);
				main[h][w].checkPiecePoint()->firstMove();
				return true;
			}
			else if (main[h + 2][w].hasPiece()) {
				//collision #1 pawn has another piece in between
				if (main[h + 2][w].checkPieceType() != 'P') {
					std::cout << "#5::No pawn available to make that move" << std::endl;
					return false;
				}
				//collision #2 pawn wants to move to occupied tile
				else if (main[h][w].hasPiece()) {
					std::cout << "#6::The pawn is coliding with another piece (occupied tile)" << std::endl;
					return false;
				}
				//pawns can only move two tiles on first move
				else if (not main[h + 2][w].checkPiece().isFirst()) {
					std::cout << "#7::The pawn cannot move two tiles anymore" << std::endl;
					return false;
				}
				//collision #3 pawn is from another player
				else if (main[h + 2][w].checkPlayer() != BLUE) {
					std::cout << "#8::No available blue pawns to make the move" << std::endl;
					return false;
				}
				main[h + 2][w].removePiece();
				main[h][w].addPiece('P', BLUE);
				main[h][w].checkPiecePoint()->firstMove();
				target = { h, w, true };
				std::cout << "Pawn at [" << h << ", " << w << "] is enpassantable" << std::endl;
				return true;
			}
			else {
				std::cout << "#9::No pawn available to make that move" << std::endl;
				return false;
			}
		}

		bool Board::pawnGreenMove(int h, int w) {
			std::cout << "[" << h << ", " << w << "]" << std::endl;
			//Out of board
			if (w > 7 or w < 0 or h > 7 or h < 2) {
				std::cout << "#1::Your movement is out of bounds for a pawn" << std::endl;
				return false;
			}
			else if (h == 7) {
				std::cout << "10#::The pawn can promote to another piece" << std::endl;
				return false;
			}
			if (main[h - 1][w].hasPiece()) {
				//collision #1 pawn has another piece in between
				if (main[h - 1][w].checkPieceType() != 'P') {
					std::cout << "#2::The pawn is coliding with another piece (piece in between)" << std::endl;
					return false;
				}
				//collision #2 pawn wants to move to occupied tile
				else if (main[h][w].hasPiece()) {
					std::cout << "#3::The pawn is coliding with another piece (occupied tile)" << std::endl;
					return false;
				}
				//collision #3 pawn is from another player
				else if (main[h - 1][w].checkPlayer() != GREEN) {
					std::cout << "#4::No available green pawns to make the move" << std::endl;
					return false;
				}
				//remove and add the piece to new position
				main[h - 1][w].removePiece();
				main[h][w].addPiece('P', GREEN);
				main[h][w].checkPiecePoint()->firstMove();
				return true;
			}
			else if (main[h - 2][w].hasPiece()) {
				//collision #1 pawn has another piece in between
				if (main[h - 2][w].checkPieceType() != 'P') {
					std::cout << "#5::No pawn available to make that move" << std::endl;
					return false;
				}
				//collision #2 pawn wants to move to occupied tile
				else if (main[h][w].hasPiece()) {
					std::cout << "#6::The pawn is coliding with another piece (occupied tile)" << std::endl;
					return false;
				}
				//pawns can only move two tiles on first move
				else if (not main[h - 2][w].checkPiece().isFirst()) {
					std::cout << "#7::The pawn cannot move two tiles anymore" << std::endl;
					return false;
				}
				//collision #3 pawn is from another player
				else if (main[h - 2][w].checkPlayer() != GREEN) {
					std::cout << "#8::No available green pawns to make the move" << std::endl;
					return false;
				}
				main[h - 2][w].removePiece();
				main[h][w].addPiece('P', GREEN);
				main[h][w].checkPiecePoint()->firstMove(); 
				target = { h, w, true };
				std::cout << "Pawn at [" << h << ", " << w << "] is enpassantable" << std::endl;
				return true;
			}
			else {
				std::cout << "#8::No pawn available to make that move" << std::endl;
				return false;
			}
		}

		bool Board::pawnPromote(int h, int w, char type, int player) {
			if (player == BLUE) {
				return pawnBluePromote(h, w, type);
			}
			else if (player == GREEN) {
				return pawnGreenPromote(h, w, type);
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
		}

		bool Board::pawnBluePromote(int h, int w, char type) {
			std::cout << "[" << h << ", " << w << "]" << std::endl;
			//Out of board
			if (w > 7 or w < 0 or h != 0) {
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
			if (hasFriendly('P', h + 1, w, BLUE)) {

				//Make the move
				main[h + 1][w].removePiece();
				main[h][w].addPiece(type, BLUE);
				main[h][w].checkPiecePoint()->firstMove();
				return true;
			}
			std::cout << "#4::No pawn available to make that move" << std::endl;
			return false;
		}

		bool Board::pawnGreenPromote(int h, int w, char type) {
			std::cout << "[" << h << ", " << w << "]" << std::endl;
			//Out of board
			if (w > 7 or w < 0 or h != 7) {
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
			if (hasFriendly('P', h - 1, w, GREEN)) {

				//Make the move
				main[h - 1][w].removePiece();
				main[h][w].addPiece(type, GREEN);
				main[h][w].checkPiecePoint()->firstMove();
				return true;
			}
			std::cout << "#4::No pawn available to make that move" << std::endl;
			return false;
		}

		bool Board::knightMove(int h, int w, int player) {
			std::cout << "[" << h << ", " << w << "]" << std::endl;
			//Out of board
			if (not inBound(h, w)) {
				std::cout << "#1::Your movement is out of bounds for a knight" << std::endl;
				return false;
			}
			//collision #1 there is already a piece in the tile
			else if (main[h][w].hasPiece()) {
				std::cout << "#2::The knight is coliding with another piece (occupied tile)" << std::endl;
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
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece('N', player);
			return true;
		}

		bool Board::rookMove(int h, int w, int player) {
			std::cout << "[" << h << ", " << w << "]" << std::endl;
			//Out of board
			if (not inBound(h, w)) {
				std::cout << "#1::Your movement is out of bounds for a rook" << std::endl;
				return false;
			}
			//collision #1 there is already a piece in the tile
			else if (main[h][w].hasPiece()) {
				std::cout << "#2::The rook is coliding with another piece (occupied tile)" << std::endl;
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
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece('R', player);
			main[h][w].checkPiecePoint()->firstMove();
			return true;
		}

		bool Board::bishopMove(int h, int w, int player) {
			std::cout << "[" << h << ", " << w << "]" << std::endl;
			//Out of board
			if (not inBound(h, w)) {
				std::cout << "#1::Your movement is out of bounds for a bishop" << std::endl;
				return false;
			}
			//collision #1 there is already a piece in the tile
			else if (main[h][w].hasPiece()) {
				std::cout << "#2::The bishop is coliding with another piece (occupied tile)" << std::endl;
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
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece('B', player);
			return true;
		}

		bool Board::queenMove(int h, int w, int player) {
			std::cout << "[" << h << ", " << w << "]" << std::endl;
			//Out of board
			if (not inBound(h, w)) {
				std::cout << "#1::Your movement is out of bounds for a queen" << std::endl;
				return false;
			}
			//collision #1 there is already a piece in the tile
			else if (main[h][w].hasPiece()) {
				std::cout << "#2::The queen is coliding with another piece (occupied tile)" << std::endl;
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
			if (queen_count > 1) {
				std::cout << "#3::More than one queen than can make this move" << std::endl;
				return false;
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
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece('Q', player);
			return true;
		}

		bool Board::kingMove(int h, int w, int player) {
			std::cout << "[" << h << ", " << w << "]" << std::endl;
			//Out of board
			if (not inBound(h, w)) {
				std::cout << "#1::Your movement is out of bounds for a king" << std::endl;
				return false;
			}
			//collision #1 there is already a piece in the tile
			else if (main[h][w].hasPiece()) {
				std::cout << "#2::The king is coliding with another piece (occupied tile)" << std::endl;
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
					if (king_count > 1) {
						std::cout << "#3::More than one king than can make this move" << std::endl;
						return false;
					}
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
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece('K', player);
			main[h][w].checkPiecePoint()->firstMove();
			return true;
		}

	}
}