#include "Board.h"
#include "Utilities.h"

namespace Chess {
	namespace Engine {

		bool Board::knightAmbiguousMove(char dis, int h, int w, int player) {
			//check if disambiguation comes from rank or file
			if (rank(dis)) {
				std::cout << "The ambiguity is at the file" << std::endl;
				return knightMoveRank((8 - (dis - 48)), h, w, player);
			}
			else if (file(dis)) {
				std::cout << "The ambiguity is at the rank" << std::endl;
				return knightMoveFile((dis - 97), h, w, player);
			}
			std::cout << "Couldn't convert instruction to tile" << std::endl;
			return false;
		}

		bool Board::knightMoveRank(int rank, int h, int w, int player) {
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
			else if (abs(rank - h) > 2) {
				std::cout << "#5::Your movement is out of bounds for a knight" << std::endl;
				return false;
			}
			//Search for player's knight 8 surrounding tiles
			int knight_count = 0;
			int orig_h, orig_w;
			//Check -2, -1
			if (hasFriendly('N', h - 2, w - 1, player) and
				(h - 2) == rank) {

				++knight_count;
				orig_h = h - 2;
				orig_w = w - 1;
			}
			//Check -2, 1
			if (hasFriendly('N', h - 2, w + 1, player) and
				(h - 2) == rank) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h - 2;
				orig_w = w + 1;
			}
			//Check -1, 2
			if (hasFriendly('N', h - 1, w + 2, player) and
				(h - 1) == rank) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h - 1;
				orig_w = w + 2;
			}
			//Check 1, 2
			if (hasFriendly('N', h + 1, w + 2, player) and
				(h + 1) == rank) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h + 1;
				orig_w = w + 2;
			}
			//Check 2, 1
			if (hasFriendly('N', h + 2, w + 1, player) and
				(h + 2) == rank) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h + 2;
				orig_w = w + 1;
			}
			//Check 2, -1
			if (hasFriendly('N', h + 2, w - 1, player) and
				(h + 2) == rank) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h + 2;
				orig_w = w - 1;
			}
			//Check 1,-2
			if (hasFriendly('N', h + 1, w - 2, player) and
				(h + 1) == rank) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h + 1;
				orig_w = w - 2;
			}
			//Check -1, -2
			if (hasFriendly('N', h - 1, w - 2, player) and
				(h - 1) == rank) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
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

		bool Board::knightMoveFile(int file, int h, int w, int player) {
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
			else if (abs(file - w) > 2) {
				std::cout << "#5::Your movement is out of bounds for a knight" << std::endl;
				return false;
			}
			//Search for player's knight 8 surrounding tiles
			int knight_count = 0;
			int orig_h, orig_w;
			//Check -2, -1
			if (hasFriendly('N', h - 2, w - 1, player) and
				(w - 1) == file) {
				++knight_count;
				orig_h = h - 2;
				orig_w = w - 1;
			}
			//Check -2, 1
			if (hasFriendly('N', h - 2, w + 1, player) and
				(w + 1) == file) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h - 2;
				orig_w = w + 1;
			}
			//Check -1, 2
			if (hasFriendly('N', h - 1, w + 2, player) and
				(w + 2) == file) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h - 1;
				orig_w = w + 2;
			}
			//Check 1, 2
			if (hasFriendly('N', h + 1, w + 2, player) and
				(w + 2) == file) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h + 1;
				orig_w = w + 2;
			}
			//Check 2, 1
			if (hasFriendly('N', h + 2, w + 1, player) and
				(w + 1) == file) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h + 2;
				orig_w = w + 1;
			}
			//Check 2, -1
			if (hasFriendly('N', h + 2, w - 1, player) and
				(w - 1) == file) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h + 2;
				orig_w = w - 1;
			}
			//Check 1,-2
			if (hasFriendly('N', h + 1, w - 2, player) and
				(w - 2) == file) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h + 1;
				orig_w = w - 2;
			}
			//Check -1, -2
			if (hasFriendly('N', h - 1, w - 2, player) and
				(w - 2) == file) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
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

		bool Board::rookAmbiguousMove(char dis, int h, int w, int player){
			//check if disambiguation comes from rank or file
			if (rank(dis)) {
				std::cout << "The ambiguity is at the file" << std::endl;
				return rookMoveRank((8 - (dis - 48)), h, w, player);
			}
			else if (file(dis)) {
				std::cout << "The ambiguity is at the rank" << std::endl;
				return rookMoveFile((dis - 97), h, w, player);
			}
			std::cout << "Couldn't convert instruction to tile" << std::endl;
			return false;
		}

		bool Board::rookMoveRank(int rank, int h, int w, int player) {
			//Nf3 h6 e3 g6 Be2 f6 d3 e6 Kd2 d6 c3 c6 Qc2 b6 b3 a6 Bb2 a5 Na3 b5  h3 c5 Rh2 d5 h4 e5 Rah1 f5 Rh3 g5 R3h2
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
			//No need to search left and right
			//Search above
			int it = h + 1;
			while (it <= 7 and not main[it][w].hasPiece()) {
				++it;
			}
			std::cout << "Found piece at [" << it << ", " << w << "]" << std::endl;
			if (hasFriendly('R', it, w, player) and
				it == rank) {
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
			if (hasFriendly('R', it, w, player) and
				it == rank) {
				++rook_count;
				orig_h = it;
				orig_w = w;
			}
			if (rook_count > 1) {
				std::cout << "#3::More than two rook than can make this move" << std::endl;
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

		bool Board::rookMoveFile(int file, int h, int w, int player) {
			//Nf3 h6 e3 g6 Be2 f6 d3 e6 Kd2 d6 c3 c6 Qc2 b6 b3 a6 Bb2 a5 Na3 b5  h3 c5 Rh2 d5 h4 e5 Rah1 f5 Rh3 g5 R3h2
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
			//No need to search up and down
			//Search to the right
			int it = w + 1;
			while (it <= 7 and not main[h][it].hasPiece()) {
				++it;
			}
			std::cout << "Found piece at [" << h << ", " << it << "]" << std::endl;
			if (hasFriendly('R', h, it, player) and
				it == file) {
				++rook_count;
				orig_h = h;
				orig_w = it;
			}
			if (rook_count > 1) {
				std::cout << "#3::More than two rook than can make this move" << std::endl;
				return false;
			}
			//Search to the left
			it = w - 1;
			while (it >= 0 and not main[h][it].hasPiece()) {
				--it;
			}
			std::cout << "Found piece at [" << h << ", " << it << "]" << std::endl;
			if (hasFriendly('R', h, it, player) and
				it == file) {
				++rook_count;
				orig_h = h;
				orig_w = it;
			}
			if (rook_count > 1) {
				std::cout << "#3::More than two rooks than can make this move" << std::endl;
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

		bool Board::bishopAmbiguousMove(char dis, int h, int w, int player) {
			//check if disambiguation comes from rank or file
			if (file(dis)) {
				std::cout << "The ambiguity is at the rank" << std::endl;
				return bishopMoveFile((dis - 97), h, w, player);
			}
			else if (rank(dis)) {
				std::cout << "The ambiguity is at the file" << std::endl;
				std::cout << "WARNING::It is better to express the disambiguation with the file" << std::endl;
				return bishopMoveRank((8 - (dis - 48)), h, w, player);
			}
			std::cout << "Couldn't convert instruction to tile" << std::endl;
			return false;
		}

		bool Board::bishopMoveRank(int rank, int h, int w, int player) {
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
			if (hasFriendly('B', it_h, it_w, player) and
				it_h == rank) {
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
			if (hasFriendly('B', it_h, it_w, player) and
				it_h == rank) {
				++bishop_count;
				orig_h = it_h;
				orig_w = it_w;
			}
			if (bishop_count > 1) {
				std::cout << "#3::More than two bishop than can make this move" << std::endl;
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
			if (hasFriendly('B', it_h, it_w, player) and
				it_h == rank) {
				++bishop_count;
				orig_h = it_h;
				orig_w = it_w;
			}
			if (bishop_count > 1) {
				std::cout << "#3::More than two bishop than can make this move" << std::endl;
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
			if (hasFriendly('B', it_h, it_w, player) and
				it_h == rank) {
				++bishop_count;
				orig_h = it_h;
				orig_w = it_w;
			}
			if (bishop_count > 1) {
				std::cout << "#3::More than two bishop than can make this move" << std::endl;
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

		bool Board::bishopMoveFile(int file, int h, int w, int player) {
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
			if (hasFriendly('B', it_h, it_w, player) and
				it_w == file) {
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
			if (hasFriendly('B', it_h, it_w, player) and
				it_w == file) {
				++bishop_count;
				orig_h = it_h;
				orig_w = it_w;
			}
			if (bishop_count > 1) {
				std::cout << "#3::More than two bishop than can make this move" << std::endl;
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
			if (hasFriendly('B', it_h, it_w, player) and
				it_w == file) {
				++bishop_count;
				orig_h = it_h;
				orig_w = it_w;
			}
			if (bishop_count > 1) {
				std::cout << "#3::More than two bishop than can make this move" << std::endl;
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
			if (hasFriendly('B', it_h, it_w, player) and
				it_w == file) {
				++bishop_count;
				orig_h = it_h;
				orig_w = it_w;
			}
			if (bishop_count > 1) {
				std::cout << "#3::More than two bishop than can make this move" << std::endl;
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

		bool Board::bishopDoubleAmbiguousMove(int h_s, int w_s, int h_d, int w_d, int player){
			std::cout << "Source: [" << h_s << ", " << w_s << "]" << std::endl;
			std::cout << "Destination: [" << h_d << ", " << w_d << "]" << std::endl;
			//Out of board
			if (not inBound(h_s, w_s) or not inBound(h_d, w_d)) {
				std::cout << "#1::Your movement is out of bounds for a bishop" << std::endl;
				return false;
			}
			//collision #1 there is already a piece in the tile
			else if (main[h_d][w_d].hasPiece()) {
				std::cout << "#2::The bishop is coliding with another piece (occupied tile)" << std::endl;
				return false;
			}
			//collision #2 there is no friendly bishop in source
			else if (not (main[h_s][w_s].hasPiece() and
					main[h_s][w_s].checkPieceType() == 'B' and
					main[h_s][w_s].checkPlayer() == player)) {
				std::cout << "#2::There is no friendly bishop in source" << std::endl;
				return false;
			}

			//Search for player's bishop 4 directions
			bool found = false;
			//Search diagonal left-up
			int it_h = h_d + 1;
			int it_w = w_d - 1;
			while (it_h <= 7 and it_w >= 0 and not main[it_h][it_w].hasPiece()) {
				++it_h;
				--it_w;
			}
			std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			if (hasFriendly('B', it_h, it_w, player)) {
				//found the specified bishop
				if (it_h == h_s and it_w == w_s) {
					found = true;
				}
			}
			//Search diagonal left-down
			it_h = h_d - 1;
			it_w = w_d - 1;
			while (it_h >= 0 and it_w >= 0 and not main[it_h][it_w].hasPiece()) {
				--it_h;
				--it_w;
			}
			std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			if (hasFriendly('B', it_h, it_w, player)) {
				//found the specified bishop
				if (it_h == h_s and it_w == w_s) {
					found = true;
				}
			}
			//Search diagonal right-up
			it_h = h_d + 1;
			it_w = w_d + 1;
			while (it_h <= 7 and it_w <= 7 and not main[it_h][it_w].hasPiece()) {
				++it_h;
				++it_w;
			}
			std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			if (hasFriendly('B', it_h, it_w, player)) {
				//found the specified bishop
				if (it_h == h_s and it_w == w_s) {
					found = true;
				}
			}
			//Search diagonal right-down
			it_h = h_d - 1;
			it_w = w_d + 1;
			while (it_h >= 0 and it_w <= 7 and not main[it_h][it_w].hasPiece()) {
				--it_h;
				++it_w;
			}
			std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			if (hasFriendly('B', it_h, it_w, player)) {
				//found the specified bishop
				if (it_h == h_s and it_w == w_s) {
					found = true;
				}
			}
			if (not found) {
				std::cout << "#4::No bishop found to make the move" << std::endl;
				return false;
			}
			std::cout << "Found the bishop in [" << h_s << ", " << h_s << "]" << std::endl;
			//Make the move
			main[h_s][w_s].removePiece();
			main[h_d][w_d].addPiece('B', player);
			return true;
		}

		bool Board::queenAmbiguousMove(char dis, int h, int w, int player) {
			//check if disambiguation comes from rank or file
			if (rank(dis)) {
				std::cout << "The ambiguity is at the file" << std::endl;
				return queenMoveRank((8 - (dis - 48)), h, w, player);
			}
			else if (file(dis)) {
				std::cout << "The ambiguity is at the rank" << std::endl;
				return queenMoveFile((dis - 97), h, w, player);
			}
			std::cout << "Couldn't convert instruction to tile" << std::endl;
			return false;
		}

		bool Board::queenMoveRank(int rank, int h, int w, int player) {
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
			if (hasFriendly('Q', it_h, it_w, player) and
				it_h == rank) {
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
			if (hasFriendly('Q', it_h, it_w, player) and
				it_h == rank) {
				++queen_count;
				orig_h = it_h;
				orig_w = it_w;
			}
			if (queen_count > 1) {
				std::cout << "#3::More than two queen than can make this move" << std::endl;
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
			if (hasFriendly('Q', it_h, it_w, player) and
				it_h == rank) {
				++queen_count;
				orig_h = it_h;
				orig_w = it_w;
			}
			if (queen_count > 1) {
				std::cout << "#3::More than two queen than can make this move" << std::endl;
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
			if (hasFriendly('Q', it_h, it_w, player) and
				it_h == rank) {
				++queen_count;
				orig_h = it_h;
				orig_w = it_w;
			}
			if (queen_count > 1) {
				std::cout << "#3::More than two queen than can make this move" << std::endl;
				return false;
			}
			//Search above
			int it = h + 1;
			while (it <= 7 and not main[it][w].hasPiece()) {
				++it;
			}
			std::cout << "Found piece at [" << it << ", " << w << "]" << std::endl;
			if (hasFriendly('Q', it, w, player) and
				it == rank) {
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
			if (hasFriendly('Q', it, w, player) and
				it == rank) {
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
			if (hasFriendly('Q', h, it, player) and
				h == rank) {
				++queen_count;
				orig_h = h;
				orig_w = it;
			}
			if (queen_count > 1) {
				std::cout << "#3::More than two queen than can make this move" << std::endl;
				return false;
			}
			//Search to the left
			it = w - 1;
			while (it >= 0 and not main[h][it].hasPiece()) {
				--it;
			}
			std::cout << "Found piece at [" << h << ", " << it << "]" << std::endl;
			if (hasFriendly('Q', h, it, player) and
				h == rank) {
				++queen_count;
				orig_h = h;
				orig_w = it;
			}
			if (queen_count > 1) {
				std::cout << "#3::More than two queen than can make this move" << std::endl;
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

		bool Board::queenMoveFile(int file, int h, int w, int player) {
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
			if (hasFriendly('Q', it_h, it_w, player) and
				it_w == file) {
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
			if (hasFriendly('Q', it_h, it_w, player) and
				it_w == file) {
				++queen_count;
				orig_h = it_h;
				orig_w = it_w;
			}
			if (queen_count > 1) {
				std::cout << "#3::More than two queen than can make this move" << std::endl;
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
			if (hasFriendly('Q', it_h, it_w, player) and
				it_w == file) {
				++queen_count;
				orig_h = it_h;
				orig_w = it_w;
			}
			if (queen_count > 1) {
				std::cout << "#3::More than two queen than can make this move" << std::endl;
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
			if (hasFriendly('Q', it_h, it_w, player) and
				it_w == file) {
				++queen_count;
				orig_h = it_h;
				orig_w = it_w;
			}
			if (queen_count > 1) {
				std::cout << "#3::More than two queen than can make this move" << std::endl;
				return false;
			}
			//Search above
			int it = h + 1;
			while (it <= 7 and not main[it][w].hasPiece()) {
				++it;
			}
			std::cout << "Found piece at [" << it << ", " << w << "]" << std::endl;
			if (hasFriendly('Q', it, w, player) and
				w == file) {
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
			if (hasFriendly('Q', it, w, player) and
				w == file) {
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
			if (hasFriendly('Q', h, it, player) and
				it == file) {
				++queen_count;
				orig_h = h;
				orig_w = it;
			}
			if (queen_count > 1) {
				std::cout << "#3::More than two queen than can make this move" << std::endl;
				return false;
			}
			//Search to the left
			it = w - 1;
			while (it >= 0 and not main[h][it].hasPiece()) {
				--it;
			}
			std::cout << "Found piece at [" << h << ", " << it << "]" << std::endl;
			if (hasFriendly('Q', h, it, player) and
				it == file) {
				++queen_count;
				orig_h = h;
				orig_w = it;
			}
			if (queen_count > 1) {
				std::cout << "#3::More than two queen than can make this move" << std::endl;
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

		bool Board::queenDoubleAmbiguousMove(int h_s, int w_s, int h_d, int w_d, int player) {
			std::cout << "Source: [" << h_s << ", " << w_s << "]" << std::endl;
			std::cout << "Destination: [" << h_d << ", " << w_d << "]" << std::endl;
			//Out of board
			if (not inBound(h_s, w_s) or not inBound(h_d, w_d)) {
				std::cout << "#1::Your movement is out of bounds for a queen" << std::endl;
				return false;
			}
			//collision #1 there is already a piece in the tile
			else if (main[h_d][w_d].hasPiece()) {
				std::cout << "#2::The queen is coliding with another piece (occupied tile)" << std::endl;
				return false;
			}
			//collision #2 there is no friendly bishop in source
			else if (not (main[h_s][w_s].hasPiece() and
				main[h_s][w_s].checkPieceType() == 'Q' and
				main[h_s][w_s].checkPlayer() == player)) {
				std::cout << "#2::There is no friendly queen in source" << std::endl;
				return false;
			}

			//Search for player's queen 8 directions
			bool found = false;
			//Search diagonal left-up
			int it_h = h_d + 1;
			int it_w = w_d - 1;
			while (it_h <= 7 and it_w >= 0 and not main[it_h][it_w].hasPiece()) {
				++it_h;
				--it_w;
			}
			std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			if (hasFriendly('Q', it_h, it_w, player)) {
				if (it_h == h_s and it_w == w_s) {
					found = true;
				}
			}
			//Search diagonal left-down
			it_h = h_d - 1;
			it_w = w_d - 1;
			while (it_h >= 0 and it_w >= 0 and not main[it_h][it_w].hasPiece()) {
				--it_h;
				--it_w;
			}
			std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			if (hasFriendly('Q', it_h, it_w, player)) {
				if (it_h == h_s and it_w == w_s) {
					found = true;
				}
			}
			//Search diagonal right-up
			it_h = h_d + 1;
			it_w = w_d + 1;
			while (it_h <= 7 and it_w <= 7 and not main[it_h][it_w].hasPiece()) {
				++it_h;
				++it_w;
			}
			std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			if (hasFriendly('Q', it_h, it_w, player)) {
				if (it_h == h_s and it_w == w_s) {
					found = true;
				}
			}
			//Search diagonal right-down
			it_h = h_d - 1;
			it_w = w_d + 1;
			while (it_h >= 0 and it_w <= 7 and not main[it_h][it_w].hasPiece()) {
				--it_h;
				++it_w;
			}
			std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			if (hasFriendly('Q', it_h, it_w, player)) {
				if (it_h == h_s and it_w == w_s) {
					found = true;
				}
			}
			//Search above
			int it = h_d + 1;
			while (it <= 7 and not main[it][w_d].hasPiece()) {
				++it;
			}
			std::cout << "Found piece at [" << it << ", " << w_d << "]" << std::endl;
			if (hasFriendly('Q', it, w_d, player)) {
				if (it_h == h_s and it_w == w_s) {
					found = true;
				}
			}
			//Search below
			it = h_d - 1;
			while (it >= 0 and not main[it][w_d].hasPiece()) {
				--it;
			}
			std::cout << "Found piece at [" << it << ", " << w_d << "]" << std::endl;
			if (hasFriendly('Q', it, w_d, player)) {
				if (it_h == h_s and it_w == w_s) {
					found = true;
				}
			}
			//Search to the right
			it = w_d + 1;
			while (it <= 7 and not main[h_d][it].hasPiece()) {
				++it;
			}
			std::cout << "Found piece at [" << h_d << ", " << it << "]" << std::endl;
			if (hasFriendly('Q', h_d, it, player)) {
				if (it_h == h_s and it_w == w_s) {
					found = true;
				}
			}
			//Search to the left
			it = w_d - 1;
			while (it >= 0 and not main[h_d][it].hasPiece()) {
				--it;
			}
			std::cout << "Found piece at [" << h_d << ", " << it << "]" << std::endl;
			if (hasFriendly('Q', h_d, it, player)) {
				if (it_h == h_s and it_w == w_s) {
					found = true;
				}
			}
			if (not found) {
				std::cout << "#4::No queen found to make the move" << std::endl;
				return false;
			}
			std::cout << "Found a queen in [" << h_d << ", " << w_d << "]" << std::endl;

			//Make the move
			main[h_s][w_s].removePiece();
			main[h_d][w_d].addPiece('Q', player);
			return true;
		}

		bool Board::kingAmbiguousMove(char dis, int h, int w, int player) {
			//check if disambiguation comes from rank or file
			if (rank(dis)) {
				std::cout << "The ambiguity is at the file" << std::endl;
				return kingMoveRank((8 - (dis - 48)), h, w, player);
			}
			else if (file(dis)) {
				std::cout << "The ambiguity is at the rank" << std::endl;
				return kingMoveFile((dis - 97), h, w, player);
			}
			std::cout << "Couldn't convert instruction to tile" << std::endl;
			return false;
		}

		bool Board::kingMoveRank(int rank, int h, int w, int player) {
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
			else if (abs(rank - h) > 1) {
				std::cout << "#5::Your movement is out of bounds for a king" << std::endl;
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
					if (hasFriendly('K', it_h, it_w, player) and
						it_h == rank) {
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
			else if (king_count > 2) {
				std::cout << "#4::More than two king can take the move" << std::endl;
				return false;
			}
			std::cout << "Found a king in [" << orig_h << ", " << orig_w << "]" << std::endl;
			//Make the move
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece('K', player);
			main[h][w].checkPiecePoint()->firstMove();
			return true;
		}

		bool Board::kingMoveFile(int file, int h, int w, int player) {
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
			else if (abs(file - w) > 1) {
				std::cout << "#5::Your movement is out of bounds for a king" << std::endl;
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
					if (hasFriendly('K', it_h, it_w, player) and
						it_w == file) {
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
			else if (king_count > 2) {
				std::cout << "#4::More than two king can take the move" << std::endl;
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