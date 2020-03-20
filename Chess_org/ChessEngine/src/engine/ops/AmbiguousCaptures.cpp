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
			if (inBound(h - 2, w - 1) and
				(h - 2) == rank and
				main[h - 2][w - 1].hasPiece() and
				main[h - 2][w - 1].checkPieceType() == 'N' and
				main[h - 2][w - 1].checkPlayer() == player) {

				++knight_count;
				orig_h = h - 2;
				orig_w = w - 1;
			}
			//Check -2, 1
			if (inBound(h - 2, w + 1) and
				(h - 2) == rank and
				main[h - 2][w + 1].hasPiece() and
				main[h - 2][w + 1].checkPieceType() == 'N' and
				main[h - 2][w + 1].checkPlayer() == player) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h - 2;
				orig_w = w + 1;
			}
			//Check -1, 2
			if (inBound(h - 1, w + 2) and
				(h - 1) == rank and
				main[h - 1][w + 2].hasPiece() and
				main[h - 1][w + 2].checkPieceType() == 'N' and
				main[h - 1][w + 2].checkPlayer() == player) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h - 1;
				orig_w = w + 2;
			}
			//Check 1, 2
			if (inBound(h + 1, w + 2) and
				(h + 1) == rank and
				main[h + 1][w + 2].hasPiece() and
				main[h + 1][w + 2].checkPieceType() == 'N' and
				main[h + 1][w + 2].checkPlayer() == player) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h + 1;
				orig_w = w + 2;
			}
			//Check 2, 1
			if (inBound(h + 2, w + 1) and
				(h + 2) == rank and
				main[h + 2][w + 1].hasPiece() and
				main[h + 2][w + 1].checkPieceType() == 'N' and
				main[h + 2][w + 1].checkPlayer() == player) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h + 2;
				orig_w = w + 1;
			}
			//Check 2, -1
			if (inBound(h + 2, w - 1) and
				(h + 2) == rank and
				main[h + 2][w - 1].hasPiece() and
				main[h + 2][w - 1].checkPieceType() == 'N' and
				main[h + 2][w - 1].checkPlayer() == player) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h + 2;
				orig_w = w - 1;
			}
			//Check 1,-2
			if (inBound(h + 1, w - 2) and
				(h + 1) == rank and
				main[h + 1][w - 2].hasPiece() and
				main[h + 1][w - 2].checkPieceType() == 'N' and
				main[h + 1][w - 2].checkPlayer() == player) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h + 1;
				orig_w = w - 2;
			}
			//Check -1, -2
			if (inBound(h - 1, w - 2) and
				(h - 1) == rank and
				main[h - 1][w - 2].hasPiece() and
				main[h - 1][w - 2].checkPieceType() == 'N' and
				main[h - 1][w - 2].checkPlayer() == player) {
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
			if (player == BLUE) {
				addGreenDead(main[h][w].checkPieceType());
			}
			else if (player == GREEN) {
				addBlueDead(main[h][w].checkPieceType());
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			main[h][w].removePiece();
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece('N', player);
			main[h][w].checkPiecePoint()->firstMove();
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
			if (inBound(h - 2, w - 1) and
				(w - 1) == file and
				main[h - 2][w - 1].hasPiece() and
				main[h - 2][w - 1].checkPieceType() == 'N' and
				main[h - 2][w - 1].checkPlayer() == player) {

				++knight_count;
				orig_h = h - 2;
				orig_w = w - 1;
			}
			//Check -2, 1
			if (inBound(h - 2, w + 1) and
				(w + 1) == file and
				main[h - 2][w + 1].hasPiece() and
				main[h - 2][w + 1].checkPieceType() == 'N' and
				main[h - 2][w + 1].checkPlayer() == player) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h - 2;
				orig_w = w + 1;
			}
			//Check -1, 2
			if (inBound(h - 1, w + 2) and
				(w + 2) == file and
				main[h - 1][w + 2].hasPiece() and
				main[h - 1][w + 2].checkPieceType() == 'N' and
				main[h - 1][w + 2].checkPlayer() == player) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h - 1;
				orig_w = w + 2;
			}
			//Check 1, 2
			if (inBound(h + 1, w + 2) and
				(w + 2) == file and
				main[h + 1][w + 2].hasPiece() and
				main[h + 1][w + 2].checkPieceType() == 'N' and
				main[h + 1][w + 2].checkPlayer() == player) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h + 1;
				orig_w = w + 2;
			}
			//Check 2, 1
			if (inBound(h + 2, w + 1) and
				(w + 1) == file and
				main[h + 2][w + 1].hasPiece() and
				main[h + 2][w + 1].checkPieceType() == 'N' and
				main[h + 2][w + 1].checkPlayer() == player) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h + 2;
				orig_w = w + 1;
			}
			//Check 2, -1
			if (inBound(h + 2, w - 1) and
				(w - 1) == file and
				main[h + 2][w - 1].hasPiece() and
				main[h + 2][w - 1].checkPieceType() == 'N' and
				main[h + 2][w - 1].checkPlayer() == player) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h + 2;
				orig_w = w - 1;
			}
			//Check 1,-2
			if (inBound(h + 1, w - 2) and
				(w - 2) == file and
				main[h + 1][w - 2].hasPiece() and
				main[h + 1][w - 2].checkPieceType() == 'N' and
				main[h + 1][w - 2].checkPlayer() == player) {
				if (knight_count == 1) {
					std::cout << "#3::More than two knight than can make this move" << std::endl;
					return false;
				}
				++knight_count;
				orig_h = h + 1;
				orig_w = w - 2;
			}
			//Check -1, -2
			if (inBound(h - 1, w - 2) and
				(w - 2) == file and
				main[h - 1][w - 2].hasPiece() and
				main[h - 1][w - 2].checkPieceType() == 'N' and
				main[h - 1][w - 2].checkPlayer() == player) {
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
			if (player == BLUE) {
				addGreenDead(main[h][w].checkPieceType());
			}
			else if (player == GREEN) {
				addBlueDead(main[h][w].checkPieceType());
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			main[h][w].removePiece();
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece('N', player);
			main[h][w].checkPiecePoint()->firstMove();
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
			//No need to search left and right
			//Search above
			int it = h + 1;
			while (it <= 7 and not main[it][w].hasPiece()) {
				++it;
			}
			std::cout << "Found piece at [" << it << ", " << w << "]" << std::endl;
			if (inBound(it, w) and
				it == rank and
				main[it][w].checkPieceType() == 'R' and
				main[it][w].checkPlayer() == player) {
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
			if (inBound(it, w) and
				it == rank and
				main[it][w].checkPieceType() == 'R' and
				main[it][w].checkPlayer() == player) {
				++rook_count;
				orig_h = it;
				orig_w = w;
			}
			if (rook_count > 1) {
				std::cout << "#3::More than two rook than can make this move" << std::endl;
				return false;
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
			if (player == BLUE) {
				addGreenDead(main[h][w].checkPieceType());
			}
			else if (player == GREEN) {
				addBlueDead(main[h][w].checkPieceType());
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			main[h][w].removePiece();
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece('R', player);
			main[h][w].checkPiecePoint()->firstMove();
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
			//No need to search up and down
			//Search to the right
			int it = w + 1;
			while (it <= 7 and not main[h][it].hasPiece()) {
				++it;
			}
			std::cout << "Found piece at [" << h << ", " << it << "]" << std::endl;
			if (inBound(h, it) and
				it == file and
				main[h][it].checkPieceType() == 'R' and
				main[h][it].checkPlayer() == player) {
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
			if (inBound(h, it) and
				it == file and
				main[h][it].checkPieceType() == 'R' and
				main[h][it].checkPlayer() == player) {
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
			if (player == BLUE) {
				addGreenDead(main[h][w].checkPieceType());
			}
			else if (player == GREEN) {
				addBlueDead(main[h][w].checkPieceType());
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			main[h][w].removePiece();
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece('R', player);
			main[h][w].checkPiecePoint()->firstMove();
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
			if (inBound(it_h, it_w) and
				it_h == rank and
				main[it_h][it_w].checkPieceType() == 'B' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (inBound(it_h, it_w) and
				it_h == rank and
				main[it_h][it_w].checkPieceType() == 'B' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (inBound(it_h, it_w) and
				it_h == rank and
				main[it_h][it_w].checkPieceType() == 'B' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (inBound(it_h, it_w) and
				it_h == rank and
				main[it_h][it_w].checkPieceType() == 'B' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (player == BLUE) {
				addGreenDead(main[h][w].checkPieceType());
			}
			else if (player == GREEN) {
				addBlueDead(main[h][w].checkPieceType());
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			main[h][w].removePiece();
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece('B', player);
			main[h][w].checkPiecePoint()->firstMove();
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
			if (inBound(it_h, it_w) and
				it_w == file and
				main[it_h][it_w].checkPieceType() == 'B' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (inBound(it_h, it_w) and
				it_w == file and
				main[it_h][it_w].checkPieceType() == 'B' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (inBound(it_h, it_w) and
				it_w == file and
				main[it_h][it_w].checkPieceType() == 'B' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (inBound(it_h, it_w) and
				it_w == file and
				main[it_h][it_w].checkPieceType() == 'B' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (player == BLUE) {
				addGreenDead(main[h][w].checkPieceType());
			}
			else if (player == GREEN) {
				addBlueDead(main[h][w].checkPieceType());
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			main[h][w].removePiece();
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece('B', player);
			main[h][w].checkPiecePoint()->firstMove();
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
			if (inBound(it_h, it_w) and
				main[it_h][it_w].checkPieceType() == 'B' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (inBound(it_h, it_w) and
				main[it_h][it_w].checkPieceType() == 'B' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (inBound(it_h, it_w) and
				main[it_h][it_w].checkPieceType() == 'B' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (inBound(it_h, it_w) and
				main[it_h][it_w].checkPieceType() == 'B' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (player == BLUE) {
				addGreenDead(main[h_d][w_d].checkPieceType());
			}
			else if (player == GREEN) {
				addBlueDead(main[h_d][w_d].checkPieceType());
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			main[h_d][w_d].removePiece();
			main[h_s][w_s].removePiece();
			main[h_d][w_d].addPiece('B', player);
			main[h_d][w_d].checkPiecePoint()->firstMove();
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
			if (inBound(it_h, it_w) and
				it_h == rank and
				main[it_h][it_w].checkPieceType() == 'Q' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (inBound(it_h, it_w) and
				it_h == rank and
				main[it_h][it_w].checkPieceType() == 'Q' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (inBound(it_h, it_w) and
				it_h == rank and
				main[it_h][it_w].checkPieceType() == 'Q' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (inBound(it_h, it_w) and
				it_h == rank and
				main[it_h][it_w].checkPieceType() == 'Q' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (inBound(it, w) and
				it == rank and
				main[it][w].checkPieceType() == 'Q' and
				main[it][w].checkPlayer() == player) {
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
			if (inBound(it, w) and
				it == rank and
				main[it][w].checkPieceType() == 'Q' and
				main[it][w].checkPlayer() == player) {
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
			if (inBound(h, it) and
				h == rank and
				main[h][it].checkPieceType() == 'Q' and
				main[h][it].checkPlayer() == player) {
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
			if (inBound(h, it) and
				h == rank and
				main[h][it].checkPieceType() == 'Q' and
				main[h][it].checkPlayer() == player) {
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
			if (player == BLUE) {
				addGreenDead(main[h][w].checkPieceType());
			}
			else if (player == GREEN) {
				addBlueDead(main[h][w].checkPieceType());
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			main[h][w].removePiece();
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece('Q', player);
			main[h][w].checkPiecePoint()->firstMove();
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
			if (inBound(it_h, it_w) and
				it_w == file and
				main[it_h][it_w].checkPieceType() == 'Q' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (inBound(it_h, it_w) and
				it_w == file and
				main[it_h][it_w].checkPieceType() == 'Q' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (inBound(it_h, it_w) and
				it_w == file and
				main[it_h][it_w].checkPieceType() == 'Q' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (inBound(it_h, it_w) and
				it_w == file and
				main[it_h][it_w].checkPieceType() == 'Q' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (inBound(it, w) and
				w == file and
				main[it][w].checkPieceType() == 'Q' and
				main[it][w].checkPlayer() == player) {
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
			if (inBound(it, w) and
				w == file and
				main[it][w].checkPieceType() == 'Q' and
				main[it][w].checkPlayer() == player) {
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
			if (inBound(h, it) and
				it == file and
				main[h][it].checkPieceType() == 'Q' and
				main[h][it].checkPlayer() == player) {
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
			if (inBound(h, it) and
				it == file and
				main[h][it].checkPieceType() == 'Q' and
				main[h][it].checkPlayer() == player) {
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
			if (player == BLUE) {
				addGreenDead(main[h][w].checkPieceType());
			}
			else if (player == GREEN) {
				addBlueDead(main[h][w].checkPieceType());
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			main[h][w].removePiece();
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece('Q', player);
			main[h][w].checkPiecePoint()->firstMove();
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
			if (inBound(it_h, it_w) and
				main[it_h][it_w].checkPieceType() == 'Q' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (inBound(it_h, it_w) and
				main[it_h][it_w].checkPieceType() == 'Q' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (inBound(it_h, it_w) and
				main[it_h][it_w].checkPieceType() == 'Q' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (inBound(it_h, it_w) and
				main[it_h][it_w].checkPieceType() == 'Q' and
				main[it_h][it_w].checkPlayer() == player) {
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
			if (inBound(it, w_d) and
				main[it][w_d].checkPieceType() == 'Q' and
				main[it][w_d].checkPlayer() == player) {
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
			if (inBound(it, w_d) and
				main[it][w_d].checkPieceType() == 'Q' and
				main[it][w_d].checkPlayer() == player) {
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
			if (inBound(h_d, it) and
				main[h_d][it].checkPieceType() == 'Q' and
				main[h_d][it].checkPlayer() == player) {
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
			if (inBound(h_d, it) and
				main[h_d][it].checkPieceType() == 'Q' and
				main[h_d][it].checkPlayer() == player) {
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
			if (player == BLUE) {
				addGreenDead(main[h_d][w_d].checkPieceType());
			}
			else if (player == GREEN) {
				addBlueDead(main[h_d][w_d].checkPieceType());
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			main[h_d][w_d].removePiece();
			main[h_s][w_s].removePiece();
			main[h_d][w_d].addPiece('Q', player);
			main[h_d][w_d].checkPiecePoint()->firstMove();
		}

		bool Board::kingAmbiguousCapture(char dis, int h, int w, int player) {
			//check if disambiguation comes from rank or file
			if (rank(dis)) {
				std::cout << "The ambiguity is at the file" << std::endl;
				return kingCaptureRank((8 - (dis - 48)), h, w, player);
			}
			else if (file(dis)) {
				std::cout << "The ambiguity is at the rank" << std::endl;
				return kingCaptureFile((dis - 97), h, w, player);
			}
			std::cout << "Couldn't convert instruction to tile" << std::endl;
			return false;
		}

		bool Board::kingCaptureRank(int rank, int h, int w, int player) {
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
					if (inBound(it_h, it_w) and
						it_h == rank and
						main[it_h][it_w].checkPieceType() == 'K' and
						main[it_h][it_w].checkPlayer() == player) {
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
			if (player == BLUE) {
				addGreenDead(main[h][w].checkPieceType());
			}
			else if (player == GREEN) {
				addBlueDead(main[h][w].checkPieceType());
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			main[h][w].removePiece();
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece('K', player);
			main[h][w].checkPiecePoint()->firstMove();
		}

		bool Board::kingCaptureFile(int file, int h, int w, int player) {
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
					if (inBound(it_h, it_w) and
						it_w == file and
						main[it_h][it_w].checkPieceType() == 'K' and
						main[it_h][it_w].checkPlayer() == player) {
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
			if (player == BLUE) {
				addGreenDead(main[h][w].checkPieceType());
			}
			else if (player == GREEN) {
				addBlueDead(main[h][w].checkPieceType());
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			main[h][w].removePiece();
			main[orig_h][orig_w].removePiece();
			main[h][w].addPiece('K', player);
			main[h][w].checkPiecePoint()->firstMove();
		}
	}
}
