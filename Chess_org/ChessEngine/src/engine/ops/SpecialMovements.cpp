#include "Board.h"
#include "Utilities.h"

namespace Chess {
	namespace Engine {

		bool Board::castleKingside(int player) {
			int h;
			int w_r = 7;	//rook file
			int w_k = 4;	//king file

			if (player == RED) {
				h = 7;
			}
			else if (player == GREEN) {
				h = 0;
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			//collision #2 Pieces in beetween
			for (int i = w_k + 1; i < w_r; ++i) {
				if (main[h][i].hasPiece()) {
					std::cout << "There is a piece between the rook and the king" << std::endl;
					return false;
				}
			}
			//collision #2 rook not in position or not first movement
			if (not (hasFriendly('R', h, w_r, player) and
				main[h][w_r].checkPiecePoint()->isFirst())) {

				std::cout << "There is no friendly rook in position or can't take the move" << std::endl;
				return false;
			}
			//collision #3 king not in position or not first movement
			if (not (hasFriendly('K', h, w_k, player) and
				main[h][w_k].checkPiecePoint()->isFirst())) {

				std::cout << "There is no friendly king in position or can't take the move" << std::endl;
				return false;
			}
			if (player == RED) {
				for (int i = w_k + 1; i < w_r; ++i) {
					if (Green.findThreat(h,i)) {
						std::cout << "There is a threat in between" << std::endl;
						return false;
					}
				}
			}
			else if (player == GREEN) {
				for (int i = w_k + 1; i < w_r; ++i) {
					if (Red.findThreat(h, i)) {
						std::cout << "There is a threat in between" << std::endl;
						return false;
					}
				}
			}
			else {
				std::cout << "No such known player" << std::endl;
			}
			if (MODE == DEBUG) {
				std::cout << "Kingside castling can be done" << std::endl;
			}
			//Make the move
			main[h][w_r].removePiece();
			main[h][w_k].removePiece();
			w_r = 5;	//rook destination file
			w_k = 6;	//king destination file
			main[h][w_r].addPiece('R', player);
			main[h][w_k].addPiece('K', player);
			if (player == RED) {
				Red.setKing(h, w_k);
			}
			else if (player == GREEN) {
				Green.setKing(h, w_k);
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			int player_checked;
			if (isChecked(player_checked) and player_checked == player) {
				if (player == RED) {
					if (MODE == DEBUG) {
						std::cout << "#10::The red king is in check" << std::endl;
					}
					Red.setKing(h, w_k);
				}
				else if (player == GREEN) {
					if (MODE == DEBUG) {
						std::cout << "#10::The green king is in check" << std::endl;
					}
					Green.setKing(h, w_k);
				}
				else {
					std::cout << "#10::No known player" << std::endl;
					return false;
				}
				main[h][w_k].removePiece();
				main[h][w_r].removePiece();
				w_r = 7;
				w_k = 4;
				main[h][w_k].addPiece('K', player);
				main[h][w_r].addPiece('R', player);
				return false;
			}
			main[h][w_r].checkPiecePoint()->firstMove();
			main[h][w_k].checkPiecePoint()->firstMove();
			if (player == RED) {
				Red.setKing(h, w_k);
				return true;
			}
			else if (player == GREEN) {
				Green.setKing(h, w_k);
				return true;
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
		}

		bool Board::castleQueenside(int player) {
			int h;
			int w_r = 0;	//rook file
			int w_k = 4;	//king file

			if (player == RED) {
				h = 7;
			}
			else if (player == GREEN) {
				h = 0;
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			//collision #2 Pieces in beetween
			for (int i = w_r + 1; i < w_k; ++i) {
				if (main[h][i].hasPiece()) {
					std::cout << "There is a piece between the rook and the king" << std::endl;
					return false;
				}
			}
			//collision #2 rook not in position or not first movement
			if (not (hasFriendly('R', h, w_r, player) and
				main[h][w_r].checkPiecePoint()->isFirst())) {

				std::cout << "There is no friendly rook in position or can't take the move" << std::endl;
				return false;
			}
			//collision #3 king not in position or not first movement
			if (not (hasFriendly('K', h, w_k, player) and
				main[h][w_k].checkPiecePoint()->isFirst())) {

				std::cout << "There is no friendly king in position or can't take the move" << std::endl;
				return false;
			}
			if (player == RED) {
				for (int i = w_r + 2; i < w_k; ++i) {
					if (Green.findThreat(h, i)) {
						std::cout << "There is a threat in between" << std::endl;
						return false;
					}
				}
			}
			else if (player == GREEN) {
				for (int i = w_r + 2; i < w_k; ++i) {
					if (Red.findThreat(h, i)) {
						std::cout << "There is a threat in between" << std::endl;
						return false;
					}
				}
			}
			if (MODE == DEBUG) {
				std::cout << "Queenside castling can be done" << std::endl;
			}
			//Make the move
			main[h][w_r].removePiece();
			main[h][w_k].removePiece();
			w_r = 3;	//rook destination file
			w_k = 2;	//king destination file
			main[h][w_r].addPiece('R', player);
			main[h][w_k].addPiece('K', player);
			if (player == RED) {
				Red.setKing(h, w_k);
			}
			else if (player == GREEN) {
				Green.setKing(h, w_k);
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			int player_checked;
			if (isChecked(player_checked) and player_checked == player) {
				if (player == RED) {
					if (MODE == DEBUG) {
						std::cout << "#10::The red king is in check" << std::endl;
					}
					Red.setKing(h, w_k);
				}
				else if (player == GREEN) {
					if (MODE == DEBUG) {
						std::cout << "#10::The green king is in check" << std::endl;
					}
					Green.setKing(h, w_k);
				}
				else {
					std::cout << "#10::No known player" << std::endl;
					return false;
				}
				main[h][w_k].removePiece();
				main[h][w_r].removePiece();
				w_r = 0;
				w_k = 4;
				main[h][w_k].addPiece('K', player);
				main[h][w_r].addPiece('R', player);
				return false;
			}
			main[h][w_r].checkPiecePoint()->firstMove();
			main[h][w_k].checkPiecePoint()->firstMove();
			if (player == RED) {
				Red.setKing(h, w_k);
				return true;
			}
			else if (player == GREEN) {
				Green.setKing(h, w_k);
				return true;
			}
			std::cout << "No such known player " << player << std::endl;
			return false;
		}

		bool Board::castleFakeKingside(int player, bool& check) {
			int h;
			int w_r = 7;	//rook file
			int w_k = 4;	//king file

			if (player == RED) {
				h = 7;
			}
			else if (player == GREEN) {
				h = 0;
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			//collision #2 Pieces in beetween
			for (int i = w_k + 1; i < w_r; ++i) {
				if (main[h][i].hasPiece()) {
					return false;
				}
			}
			//collision #2 rook not in position or not first movement
			if (not (hasFriendly('R', h, w_r, player) and
				main[h][w_r].checkPiecePoint()->isFirst())) {
				return false;
			}
			//collision #3 king not in position or not first movement
			if (not (hasFriendly('K', h, w_k, player) and
				main[h][w_k].checkPiecePoint()->isFirst())) {
				return false;
			}
			if (player == RED) {
				for (int i = w_k + 1; i < w_r; ++i) {
					if (Green.findThreat(h, i)) {
						if (MODE == DEBUG) {
							std::cout << "There is a threat in between" << std::endl;
						}
						return false;
					}
				}
			}
			else if (player == GREEN) {
				for (int i = w_k + 1; i < w_r; ++i) {
					if (Red.findThreat(h, i)) {
						if (MODE == DEBUG) {
							std::cout << "There is a threat in between" << std::endl;
						}
						return false;
					}
				}
			}
			if (MODE == DEBUG) {
				std::cout << "Kingside castling can be done" << std::endl;
			}
			//Make the move
			main[h][w_r].removePiece();
			main[h][w_k].removePiece();
			w_r = 5;	//rook destination file
			w_k = 6;	//king destination file
			main[h][w_r].addPiece('R', player);
			main[h][w_k].addPiece('K', player);
			if (player == RED) {
				Red.setKing(h, w_k);
			}
			else if (player == GREEN) {
				Green.setKing(h, w_k);
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			int player_checked;
			if (isChecked(player_checked)) {
				if(player_checked == player){
					if (player == RED) {
						if (MODE == DEBUG) {
							std::cout << "#10::The red king is in check" << std::endl;
						}
						Red.setKing(h, w_k);
					}
					else if (player == GREEN) {
						if (MODE == DEBUG) {
							std::cout << "#10::The green king is in check" << std::endl;
						}
						Green.setKing(h, w_k);
					}
					else {
						std::cout << "#10::No known player" << std::endl;
						return false;
					}
					main[h][w_k].removePiece();
					main[h][w_r].removePiece();
					w_r = 7;
					w_k = 4;
					main[h][w_k].addPiece('K', player);
					main[h][w_r].addPiece('R', player);
					return false;
				}
				else {
					check = true;
				}
			}
			if (player == RED) {
				Red.setKing(h, w_k);
			}
			else if (player == GREEN) {
				Green.setKing(h, w_k);
			}
			else {
				std::cout << "#10::No known player" << std::endl;
				return false;
			}
			main[h][w_k].removePiece();
			main[h][w_r].removePiece();
			w_r = 7;
			w_k = 4;
			main[h][w_k].addPiece('K', player);
			main[h][w_r].addPiece('R', player);
			return true;
		}
		
		bool Board::castleFakeQueenside(int player, bool& check) {
			int h;
			int w_r = 0;	//rook file
			int w_k = 4;	//king file

			if (player == RED) {
				h = 7;
			}
			else if (player == GREEN) {
				h = 0;
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			//collision #2 Pieces in beetween
			for (int i = w_r + 1; i < w_k; ++i) {
				if (main[h][i].hasPiece()) {
					return false;
				}
			}
			//collision #2 rook not in position or not first movement
			if (not (hasFriendly('R', h, w_r, player) and
				main[h][w_r].checkPiecePoint()->isFirst())) {
				return false;
			}
			//collision #3 king not in position or not first movement
			if (not (hasFriendly('K', h, w_k, player) and
				main[h][w_k].checkPiecePoint()->isFirst())) {
				return false;
			}
			if (player == RED) {
				for (int i = w_r + 2; i < w_k; ++i) {
					if (Green.findThreat(h, i)) {
						if (MODE == DEBUG) {
							std::cout << "There is a threat in between" << std::endl;
						}
						return false;
					}
				}
			}
			else if (player == GREEN) {
				for (int i = w_r + 2; i < w_k; ++i) {
					if (Red.findThreat(h, i)) {
						if (MODE == DEBUG) {
							std::cout << "There is a threat in between" << std::endl;
						}
						return false;
					}
				}
			}
			if (MODE == DEBUG) {
				std::cout << "Queenside castling can be done" << std::endl;
			}
			//Make the move
			main[h][w_r].removePiece();
			main[h][w_k].removePiece();
			w_r = 3;	//rook destination file
			w_k = 2;	//king destination file
			main[h][w_r].addPiece('R', player);
			main[h][w_k].addPiece('K', player);
			if (player == RED) {
				Red.setKing(h, w_k);
			}
			else if (player == GREEN) {
				Green.setKing(h, w_k);
			}
			else {
				std::cout << "No such known player " << player << std::endl;
				return false;
			}
			int player_checked;
			if (isChecked(player_checked)){
				if (player_checked == player) {
					if (player == RED) {
						if (MODE == DEBUG) {
							std::cout << "#10::The red king is in check" << std::endl;
						}
						Red.setKing(h, w_k);
					}
					else if (player == GREEN) {
						if (MODE == DEBUG) {
							std::cout << "#10::The green king is in check" << std::endl;
						}
						Green.setKing(h, w_k);
					}
					else {
						std::cout << "#10::No known player" << std::endl;
						return false;
					}
					main[h][w_k].removePiece();
					main[h][w_r].removePiece();
					w_r = 0;
					w_k = 4;
					main[h][w_k].addPiece('K', player);
					main[h][w_r].addPiece('R', player);
					return false;
				}
				else {
					check = true;
				}
			}
			if (player == RED) {
				Red.setKing(h, w_k);
			}
			else if (player == GREEN) {
				Green.setKing(h, w_k);
			}
			else {
				std::cout << "#10::No known player" << std::endl;
				return false;
			}
			main[h][w_k].removePiece();
			main[h][w_r].removePiece();
			w_r = 0;
			w_k = 4;
			main[h][w_k].addPiece('K', player);
			main[h][w_r].addPiece('R', player);
			return true;
		}

		bool Board::isChecked() {
			//See if any king is in the positions threatened by other player
			Red.updateThreats(*this);
			Green.updateThreats(*this);
			if (Green.findThreat(Red.checkKingPosition(), true)) {
				if (MODE == DEBUG) {
					std::cout << "Red king is in check" << std::endl;
				}
				return true;
			}
			if (Red.findThreat(Green.checkKingPosition(), true)) {
				if (MODE == DEBUG) {
					std::cout << "Green king is in check" << std::endl;
				}
				return true;
			}
			return false;
		}

		bool Board::isChecked(int& player) {
			//See if any king is in the positions threatened by other player
			Red.updateThreats(*this);
			Green.updateThreats(*this);
			if (Green.findThreat(Red.checkKingPosition(), true)) {
				if (MODE == DEBUG) {
					std::cout << "Red king is in check" << std::endl;
				}
				player = RED;
				return true;
			}
			if (Red.findThreat(Green.checkKingPosition(), true)) {
				if (MODE == DEBUG) {
					std::cout << "Green king is in check" << std::endl;
				}
				player = GREEN;
				return true;
			}
			player = 0;
			return false;
		}

		bool Board::areBothChecked() {
			//See if any king is in the positions threatened by other player
			Red.updateThreats(*this);
			Green.updateThreats(*this);
			int count = 0;
			if (Green.findThreat(Red.checkKingPosition(), true)) {
				if (MODE == DEBUG) {
					std::cout << "Red king is in check" << std::endl;
				}
				++count;
			}
			if (Red.findThreat(Green.checkKingPosition(), true)) {
				if (MODE == DEBUG) {
					std::cout << "Green king is in check" << std::endl;
				}
				++count;
			}
			return count == 2;
		}
	}
}