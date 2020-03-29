#include "Board.h"
#include "Utilities.h"

namespace Chess {
	namespace Engine {
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
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			}
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
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			}
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
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			}
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
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			}
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
			return makeMove('B', h_s, w_s, h_d, w_d, player);
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
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			}
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
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			}
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
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			}
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
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it_h << ", " << it_w << "]" << std::endl;
			}
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
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it << ", " << w_d << "]" << std::endl;
			}
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
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << it << ", " << w_d << "]" << std::endl;
			}
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
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << h_d << ", " << it << "]" << std::endl;
			}
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
			if (MODE == DEBUG) {
				std::cout << "Found piece at [" << h_d << ", " << it << "]" << std::endl;
			}
			if (hasFriendly('Q', h_d, it, player)) {
				if (it_h == h_s and it_w == w_s) {
					found = true;
				}
			}
			if (not found) {
				std::cout << "#4::No queen found to make the move" << std::endl;
				return false;
			}
			if (MODE == DEBUG) {
				std::cout << "Found a queen in [" << h_d << ", " << w_d << "]" << std::endl;
			}
			//Make the move
			return makeMove('Q', h_s, w_s, h_d, w_d, player);
		}
	}
}