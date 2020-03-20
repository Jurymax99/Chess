#include "Board.h"
#include "Utilities.h"

namespace Chess {
	namespace Engine {

		bool Board::castleKingside(int player) {
			int h;
			int w_r = 7;	//rook file
			int w_k = 4;	//king file

			if (player == BLUE) {
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
					std::cout << "There is a piece between the rook and the king" << player << std::endl;
					return false;
				}
			}
			//collision #2 rook not in position or not first movement
			if (not (main[h][w_r].hasPiece() and
				main[h][w_r].checkPieceType() == 'R' and
				main[h][w_r].checkPlayer() == player and
				main[h][w_r].checkPiecePoint()->isFirst())) {

				std::cout << "There is no friendly rook in position or can't take the move" << std::endl;
				return false;
			}
			//collision #3 king not in position or not first movement
			if (not (main[h][w_k].hasPiece() and
				main[h][w_k].checkPieceType() == 'K' and
				main[h][w_k].checkPlayer() == player and
				main[h][w_k].checkPiecePoint()->isFirst())) {

				std::cout << "There is no friendly king in position or can't take the move" << std::endl;
				return false;
			}
			std::cout << "Kingside castling can be done" << std::endl;
			//Make the move
			main[h][w_r].removePiece();
			main[h][w_k].removePiece();
			w_r = 5;	//rook destination file
			w_k = 6;	//king destination file
			main[h][w_r].addPiece('R', player);
			main[h][w_k].addPiece('K', player);
			main[h][w_r].checkPiecePoint()->firstMove();
			main[h][w_k].checkPiecePoint()->firstMove();
			return true;
		}

		bool Board::castleQueenside(int player) {
			int h;
			int w_r = 0;	//rook file
			int w_k = 4;	//king file

			if (player == BLUE) {
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
					std::cout << "There is a piece between the rook and the king" << player << std::endl;
					return false;
				}
			}
			//collision #2 rook not in position or not first movement
			if (not (main[h][w_r].hasPiece() and
				main[h][w_r].checkPieceType() == 'R' and
				main[h][w_r].checkPlayer() == player and
				main[h][w_r].checkPiecePoint()->isFirst())) {

				std::cout << "There is no friendly rook in position or can't take the move" << std::endl;
				return false;
			}
			//collision #3 king not in position or not first movement
			if (not (main[h][w_k].hasPiece() and
				main[h][w_k].checkPieceType() == 'K' and
				main[h][w_k].checkPlayer() == player and
				main[h][w_k].checkPiecePoint()->isFirst())) {

				std::cout << "There is no friendly king in position or can't take the move" << std::endl;
				return false;
			}
			std::cout << "Queenside castling can be done" << std::endl;
			//Make the move
			main[h][w_r].removePiece();
			main[h][w_k].removePiece();
			w_r = 3;	//rook destination file
			w_k = 2;	//king destination file
			main[h][w_r].addPiece('R', player);
			main[h][w_k].addPiece('K', player);
			main[h][w_r].checkPiecePoint()->firstMove();
			main[h][w_k].checkPiecePoint()->firstMove();
			return true;
		}

	}
}