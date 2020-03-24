#include "Board.h"
#include "Utilities.h"

namespace Chess {
	namespace Engine {

		bool Board::knightAmbiguousCapture(char dis, int h, int w, int player) {
			//check if disambiguation comes from rank or file
			if (rank(dis)) {
				std::cout << "The ambiguity is at the file" << std::endl;
				return knightCaptureRank((8 - (dis - 48)), h, w, player);
			}
			else if (file(dis)) {
				std::cout << "The ambiguity is at the rank" << std::endl;
				return knightCaptureFile((dis - 97), h, w, player);
			}
			std::cout << "Couldn't convert instruction to tile" << std::endl;
			return false;
		}

		bool Board::knightCaptureRank(int rank, int h, int w, int player) {
			std::cout << "[" << h << ", " << w << "]" << std::endl;
			//Out of board
			if (not inBound(h, w)) {
				std::cout << "#1::Your movement is out of bounds for a knight" << std::endl;
				return false;
			}
			//collision #1 there is already a piece in the tile
			else if (not main[h][w].hasPiece()) {
				std::cout << "#2::No piece can be killed in this tile" << std::endl;
				return false;
			}
			else if (abs(rank - h) > 2) {
				std::cout << "#5::Your movement is out of bounds for a knight" << std::endl;
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
			return makeCapture('N', orig_h, orig_w, h, w, player);
		}

		bool Board::knightCaptureFile(int file, int h, int w, int player) {
			std::cout << "[" << h << ", " << w << "]" << std::endl;
			//Out of board
			if (not inBound(h, w)) {
				std::cout << "#1::Your movement is out of bounds for a knight" << std::endl;
				return false;
			}
			//collision #1 there is already a piece in the tile
			else if (not main[h][w].hasPiece()) {
				std::cout << "#2::No piece can be killed in this tile" << std::endl;
				return false;
			}
			else if (abs(file - w) > 2) {
				std::cout << "#5::Your movement is out of bounds for a knight" << std::endl;
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
			return makeCapture('N', orig_h, orig_w, h, w, player);
		}

		bool Board::rookAmbiguousCapture(char dis, int h, int w, int player) {
			//check if disambiguation comes from rank or file
			if (rank(dis)) {
				std::cout << "The ambiguity is at the file" << std::endl;
				return rookCaptureRank((8 - (dis - 48)), h, w, player);
			}
			else if (file(dis)) {
				std::cout << "The ambiguity is at the rank" << std::endl;
				return rookCaptureFile((dis - 97), h, w, player);
			}
			std::cout << "Couldn't convert instruction to tile" << std::endl;
			return false;
		}

		bool Board::rookCaptureRank(int rank, int h, int w, int player) {
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
			//Search to the right
			int it = w + 1;
			while (it <= 7 and not main[rank][it].hasPiece()) {
				++it;
			}
			std::cout << "Found piece at [" << rank << ", " << it << "]" << std::endl;
			if (hasFriendly('R', h, it, player)) {
				++rook_count;
				orig_h = rank;
				orig_w = it;
			}
			//Search to the left
			it = w - 1;
			while (it >= 0 and not main[rank][it].hasPiece()) {
				--it;
			}
			std::cout << "Found piece at [" << rank << ", " << it << "]" << std::endl;
			if (hasFriendly('R', rank, it, player)) {
				++rook_count;
				orig_h = rank;
				orig_w = it;
			}
			if (rook_count > 1) {
				std::cout << "#3::More than two rooks than can make this move" << std::endl;
				return false;
			}
			//Search above
			it = h + 1;
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
			if (rook_count > 1) {
				std::cout << "#3::More than two rook than can make this move" << std::endl;
				return false;
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
			return makeCapture('R', orig_h, orig_w, h, w, player);
		}

		bool Board::rookCaptureFile(int file, int h, int w, int player) {
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
			while (it <= 7 and not main[it][file].hasPiece()) {
				++it;
			}
			std::cout << "Found piece at [" << it << ", " << file << "]" << std::endl;
			if (hasFriendly('R', it, file, player)) {
				++rook_count;
				orig_h = it;
				orig_w = file;
			}
			//Search below
			it = h - 1;
			while (it >= 0 and not main[it][file].hasPiece()) {
				--it;
			}
			std::cout << "Found piece at [" << it << ", " << w << "]" << std::endl;
			if (hasFriendly('R', it, file, player)) {
				++rook_count;
				orig_h = it;
				orig_w = file;
			}
			if (rook_count > 1) {
				std::cout << "#3::More than two rook than can make this move" << std::endl;
				return false;
			}
			//Search to the right
			it = w + 1;
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
			return makeCapture('R', orig_h, orig_w, h, w, player);
		}

		bool Board::bishopAmbiguousCapture(char dis, int h, int w, int player) {
			//check if disambiguation comes from rank or file
			if (file(dis)) {
				std::cout << "The ambiguity is at the rank" << std::endl;
				return bishopCaptureFile((dis - 97), h, w, player);
			}
			else if (rank(dis)) {
				std::cout << "The ambiguity is at the file" << std::endl;
				std::cout << "WARNING::It is better to express the disambiguation with the file" << std::endl;
				return bishopCaptureRank((8 - (dis - 48)), h, w, player);
			}
			std::cout << "Couldn't convert instruction to tile" << std::endl;
			return false;
		}

		bool Board::bishopCaptureRank(int rank, int h, int w, int player) {
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
			return makeCapture('B', orig_h, orig_w, h, w, player);
		}

		bool Board::bishopCaptureFile(int file, int h, int w, int player) {
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
			return makeCapture('B', orig_h, orig_w, h, w, player);
		}

		bool Board::bishopDoubleAmbiguousCapture(int h_s, int w_s, int h_d, int w_d, int player) {
			std::cout << "Source: [" << h_s << ", " << w_s << "]" << std::endl;
			std::cout << "Destination: [" << h_d << ", " << w_d << "]" << std::endl;
			//Out of board
			if (not inBound(h_s, w_s) or not inBound(h_d, w_d)) {
				std::cout << "#1::Your movement is out of bounds for a bishop" << std::endl;
				return false;
			}
			//collision #1 there is already a piece in the tile
			else if (not main[h_d][w_d].hasPiece()) {
				std::cout << "#2::No piece can be killed in this tile" << std::endl;
				return false;
			}
			//collision #2 there is no friendly bishop in source
			else if (not hasFriendly('B', h_s, w_s, player)) {
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
			//Make move
			return makeCapture('B', h_s, w_s, h_d, w_d, player);
		}

		bool Board::queenAmbiguousCapture(char dis, int h, int w, int player) {
			//check if disambiguation comes from rank or file
			if (rank(dis)) {
				std::cout << "The ambiguity is at the file" << std::endl;
				return queenCaptureRank((8 - (dis - 48)), h, w, player);
			}
			else if (file(dis)) {
				std::cout << "The ambiguity is at the rank" << std::endl;
				return queenCaptureFile((dis - 97), h, w, player);
			}
			std::cout << "Couldn't convert instruction to tile" << std::endl;
			return false;
		}

		bool Board::queenCaptureRank(int rank, int h, int w, int player) {
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
			return makeCapture('Q', orig_h, orig_w, h, w, player);
		}

		bool Board::queenCaptureFile(int file, int h, int w, int player) {
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
			return makeCapture('Q', orig_h, orig_w, h, w, player);
		}

		bool Board::queenDoubleAmbiguousCapture(int h_s, int w_s, int h_d, int w_d, int player)
		{
			std::cout << "Source: [" << h_s << ", " << w_s << "]" << std::endl;
			std::cout << "Destination: [" << h_d << ", " << w_d << "]" << std::endl;
			//Out of board
			if (not inBound(h_s, w_s) or not inBound(h_d, w_d)) {
				std::cout << "#1::Your movement is out of bounds for a queen" << std::endl;
				return false;
			}
			//collision #1 there is already a piece in the tile
			else if (not main[h_d][w_d].hasPiece()) {
				std::cout << "#2::No piece can be killed in this tile" << std::endl;
				return false;
			}
			//collision #2 there is no friendly bishop in source
			else if (not hasFriendly('Q', h_s, w_s, player)) {
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

			//Make move
			return makeCapture('Q', h_s, w_s, h_d, w_d, player);
		}
	}
}
