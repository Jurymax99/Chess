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
					std::cout << "There is a piece between the rook and the king" << player << std::endl;
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
			if (isChecked()) {
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
					std::cout << "There is a piece between the rook and the king" << player << std::endl;
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
			if (isChecked()) {
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

		bool Board::isChecked() {
			//See if any king is in the positions threatened by other player
			updateThreats(Red, *this);
			updateThreats(Green, *this);
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
			updateThreats(Red, *this);
			updateThreats(Green, *this);
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

		/*void Board::updateThreats() {
			updateRedThreats();
			updateGreenThreats();
		}

		void Board::updateRedThreats() {
			RedThreat.clear();
			for (int i = 0; i < height; ++i) {
				for (int j = 0; j < width; ++j) {
					//Pawn
					if (hasFriendly('P', i, j, RED)) {
						if (inBound(i - 1, j + 1)) {
							if (not main[i - 1][j + 1].hasPiece()) {
								RedThreat.insert({ i - 1, j + 1, true });
							}
							else if(main[i - 1][j + 1].checkPlayer() == GREEN){
								RedThreat.insert({ i - 1, j + 1, false });
							}
						}
						if (inBound(i - 1, j - 1)) {
							if (not main[i - 1][j - 1].hasPiece()) {
								RedThreat.insert({ i - 1, j - 1, true });
							}
							else if (main[i - 1][j - 1].checkPlayer() == GREEN) {
								RedThreat.insert({ i - 1, j - 1, false });
							}
						}
					}
						
					//Knight
					else if (hasFriendly('N', i, j, RED)) {
						//Check -2, -1
						if (inBound(i - 2, j - 1)) {
							if (not main[i - 2][j - 1].hasPiece()) {
								RedThreat.insert({ i - 2, j - 1, true });
							}
							else if (main[i - 2][j - 1].checkPlayer() == GREEN) {
								RedThreat.insert({ i - 2, j - 1, false });
							}
						}
						//Check -2, 1
						if (inBound(i - 2, j + 1)) {
							if (not main[i - 2][j + 1].hasPiece()) {
								RedThreat.insert({ i - 2, j + 1, true });
							}
							else if (main[i - 2][j + 1].checkPlayer() == GREEN) {
								RedThreat.insert({ i - 2, j + 1, false });
							}
						}
						//Check -1, 2
						if (inBound(i - 1, j + 2)) {
							if (not main[i - 1][j + 2].hasPiece()) {
								RedThreat.insert({ i - 1, j + 2, true });
							}
							else if (main[i - 1][j + 2].checkPlayer() == GREEN) {
								RedThreat.insert({ i - 1, j + 2, false });
							}
						}
						//Check 1, 2
						if (inBound(i + 1, j + 2)) {
							if (not main[i + 1][j + 2].hasPiece()) {
								RedThreat.insert({ i + 1, j + 2, true });
							}
							else if (main[i + 1][j + 2].checkPlayer() == GREEN) {
								RedThreat.insert({ i + 1, j + 2, false });
							}
						}
						//Check 2, 1
						if (inBound(i + 2, j + 1)) {
							if (not main[i + 2][j + 1].hasPiece()) {
								RedThreat.insert({ i + 2, j + 1, true });
							}
							else if (main[i + 2][j + 1].checkPlayer() == GREEN) {
								RedThreat.insert({ i + 2, j + 1, false });
							}
						}
						//Check 2, -1
						if (inBound(i + 2, j - 1)) {
							if (not main[i + 2][j - 1].hasPiece()) {
								RedThreat.insert({ i + 2, j - 1, true });
							}
							else if (main[i + 2][j - 1].checkPlayer() == GREEN) {
								RedThreat.insert({ i + 2, j - 1, false });
							}
						}
						//Check 1,-2
						if (inBound(i + 1, j - 2)) {
							if (not main[i + 1][j - 2].hasPiece()) {
								RedThreat.insert({ i + 1, j - 2, true });
							}
							else if (main[i + 1][j - 2].checkPlayer() == GREEN) {
								RedThreat.insert({ i + 1, j - 2, false });
							}
						}
						//Check -1, -2
						if (inBound(i - 1, j - 2)) {
							if (not main[i - 1][j - 2].hasPiece()) {
								RedThreat.insert({ i - 1, j - 2, true });
							}
							else if (main[i - 1][j - 2].checkPlayer() == GREEN) {
								RedThreat.insert({ i - 1, j - 2, false });
							}
						}
					}
					//Rook
					else if (hasFriendly('R', i, j, RED)) {
						//Search above
						int it = i + 1;
						while (it <= 7 and not main[it][j].hasPiece()) {
							RedThreat.insert({ it, j, true });
							++it;
						}
						if (it <= 7 and main[it][j].checkPlayer() == GREEN) {
							RedThreat.insert({ it, j, false });
						}
						//Search below
						it = i - 1;
						while (it >= 0 and not main[it][j].hasPiece()) {
							RedThreat.insert({ it, j, true });
							--it;
						}
						if (it >= 0 and main[it][j].checkPlayer() == GREEN) {
							RedThreat.insert({ it, j, false });
						}
						//Search to the right
						it = j + 1;
						while (it <= 7 and not main[i][it].hasPiece()) {
							RedThreat.insert({ i, it, true });
							++it;
						}
						if (it <= 7 and main[i][it].checkPlayer() == GREEN) {
							RedThreat.insert({ i, it, false });
						}
						//Search to the left
						it = j - 1;
						while (it >= 0 and not main[i][it].hasPiece()) {
							RedThreat.insert({ i, it });
							--it;
						}
						if (it >= 0 and main[i][it].checkPlayer() == GREEN) {
							RedThreat.insert({ i, it, false });
						}
					}
					//Bishop
					else if (hasFriendly('B', i, j, RED)) {
						//Search diagonal left-up
						int it_h = i + 1;
						int it_w = j - 1;
						while (it_h <= 7 and it_w >= 0 and not main[it_h][it_w].hasPiece()) {
							RedThreat.insert({ it_h, it_w, true });
							++it_h;
							--it_w;
						}
						if (it_h <= 7 and it_w >= 0 and main[it_h][it_w].checkPlayer() == GREEN) {
							RedThreat.insert({ it_h, it_w, false });
						}
						//Search diagonal left-down
						it_h = i - 1;
						it_w = j - 1;
						while (it_h >= 0 and it_w >= 0 and not main[it_h][it_w].hasPiece()) {
							RedThreat.insert({ it_h, it_w, true });
							--it_h;
							--it_w;
						}
						if (it_h >= 0 and it_w >= 0 and main[it_h][it_w].checkPlayer() == GREEN) {
							RedThreat.insert({ it_h, it_w, false });
						}
						//Search diagonal right-up
						it_h = i + 1;
						it_w = j + 1;
						while (it_h <= 7 and it_w <= 7 and not main[it_h][it_w].hasPiece()) {
							RedThreat.insert({ it_h, it_w, true });
							++it_h;
							++it_w;
						}
						if (it_h <= 7 and it_w <= 7 and main[it_h][it_w].checkPlayer() == GREEN) {
							RedThreat.insert({ it_h, it_w, false });
						}
						//Search diagonal right-down
						it_h = i - 1;
						it_w = j + 1;
						while (it_h >= 0 and it_w <= 7 and not main[it_h][it_w].hasPiece()) {
							RedThreat.insert({ it_h, it_w, true });
							--it_h;
							++it_w;
						}
						if (it_h >= 0 and it_w <= 7 and main[it_h][it_w].checkPlayer() == GREEN) {
							RedThreat.insert({ it_h, it_w, false });
						}
					}
					//Queen
					else if (hasFriendly('Q', i, j, RED)) {
						//Search above
						int it = i + 1;
						while (it <= 7 and not main[it][j].hasPiece()) {
							RedThreat.insert({ it, j, true });
							++it;
						}
						if (it <= 7 and main[it][j].checkPlayer() == GREEN) {
							RedThreat.insert({ it, j, false });
						}
						//Search below
						it = i - 1;
						while (it >= 0 and not main[it][j].hasPiece()) {
							RedThreat.insert({ it, j, true });
							--it;
						}
						if (it >= 0 and main[it][j].checkPlayer() == GREEN) {
							RedThreat.insert({ it, j, false });
						}
						//Search to the right
						it = j + 1;
						while (it <= 7 and not main[i][it].hasPiece()) {
							RedThreat.insert({ i, it, true });
							++it;
						}
						if (it <= 7 and main[i][it].checkPlayer() == GREEN) {
							RedThreat.insert({ i, it, false });
						}
						//Search to the left
						it = j - 1;
						while (it >= 0 and not main[i][it].hasPiece()) {
							RedThreat.insert({ i, it, false });
							--it;
						}
						if (it >= 0 and main[i][it].checkPlayer() == GREEN) {
							RedThreat.insert({ i, it, false });
						}
						//Search diagonal left-up
						int it_h = i + 1;
						int it_w = j - 1;
						while (it_h <= 7 and it_w >= 0 and not main[it_h][it_w].hasPiece()) {
							RedThreat.insert({ it_h, it_w, true });
							++it_h;
							--it_w;
						}
						if (it_h <= 7 and it_w >= 0 and main[it_h][it_w].checkPlayer() == GREEN) {
							RedThreat.insert({ it_h, it_w, false });
						}
						//Search diagonal left-down
						it_h = i - 1;
						it_w = j - 1;
						while (it_h >= 0 and it_w >= 0 and not main[it_h][it_w].hasPiece()) {
							RedThreat.insert({ it_h, it_w, true });
							--it_h;
							--it_w;
						}
						if (it_h >= 0 and it_w >= 0 and main[it_h][it_w].checkPlayer() == GREEN) {
							RedThreat.insert({ it_h, it_w, false });
						}
						//Search diagonal right-up
						it_h = i + 1;
						it_w = j + 1;
						while (it_h <= 7 and it_w <= 7 and not main[it_h][it_w].hasPiece()) {
							RedThreat.insert({ it_h, it_w, true });
							++it_h;
							++it_w;
						}
						if (it_h <= 7 and it_w <= 7 and main[it_h][it_w].checkPlayer() == GREEN) {
							RedThreat.insert({ it_h, it_w, false });
						}
						//Search diagonal right-down
						it_h = i - 1;
						it_w = j + 1;
						while (it_h >= 0 and it_w <= 7 and not main[it_h][it_w].hasPiece()) {
							RedThreat.insert({ it_h, it_w, true });
							--it_h;
							++it_w;
						}
						if (it_h >= 0 and it_w <= 7 and main[it_h][it_w].checkPlayer() == GREEN) {
							RedThreat.insert({ it_h, it_w, false });
						}
					}
					//King
					else if (hasFriendly('K', i, j, RED)) {
						for (int ii = -1; ii < 2; ++ii) {
							for (int jj = -1; jj < 2; ++jj) {
								if (inBound(i + ii, j + jj)) {
									if (not main[i + ii][j + jj].hasPiece()) {
										RedThreat.insert({ i + ii, j + jj, true });
									}
									else if (main[i + ii][j + jj].checkPlayer() == GREEN) {
										RedThreat.insert({ i + ii, j + jj, false });
									}
								}
							}
						}
					}
				}
			}
		}

		void Board::updateGreenThreats() {
			GreenThreat.clear();
			for (int i = 0; i < height; ++i) {
				for (int j = 0; j < width; ++j) {
					//Pawn
					if (hasFriendly('P', i, j, GREEN)) {
						if (inBound(i + 1, j + 1)) {
							if (not main[i + 1][j + 1].hasPiece()) {
								GreenThreat.insert({ i + 1, j + 1, true });
							}
							else if (main[i + 1][j + 1].checkPlayer() == RED) {
								GreenThreat.insert({ i + 1, j + 1, false });
							}
						}
						if (inBound(i + 1, j - 1)) {
							if (not main[i + 1][j - 1].hasPiece()) {
								GreenThreat.insert({ i + 1, j - 1, true });
							}
							else if (main[i + 1][j - 1].checkPlayer() == RED) {
								GreenThreat.insert({ i + 1, j - 1, false });
							}
						}
					}

					//Knight
					else if (hasFriendly('N', i, j, GREEN)) {
						//Check -2, -1
						if (inBound(i - 2, j - 1)) {
							if (not main[i - 2][j - 1].hasPiece()) {
								GreenThreat.insert({ i - 2, j - 1, true });
							}
							else if (main[i - 2][j - 1].checkPlayer() == RED) {
								GreenThreat.insert({ i - 2, j - 1, false });
							}
						}
						//Check -2, 1
						if (inBound(i - 2, j + 1)) {
							if (not main[i - 2][j + 1].hasPiece()) {
								GreenThreat.insert({ i - 2, j + 1, true });
							}
							else if (main[i - 2][j + 1].checkPlayer() == RED) {
								GreenThreat.insert({ i - 2, j + 1, false });
							}
						}
						//Check -1, 2
						if (inBound(i - 1, j + 2)) {
							if (not main[i - 1][j + 2].hasPiece()) {
								GreenThreat.insert({ i - 1, j + 2, true });
							}
							else if (main[i - 1][j + 2].checkPlayer() == RED) {
								GreenThreat.insert({ i - 1, j + 2, false });
							}
						}
						//Check 1, 2
						if (inBound(i + 1, j + 2)) {
							if (not main[i + 1][j + 2].hasPiece()) {
								GreenThreat.insert({ i + 1, j + 2, true });
							}
							else if (main[i + 1][j + 2].checkPlayer() == RED) {
								GreenThreat.insert({ i + 1, j + 2, false });
							}
						}
						//Check 2, 1
						if (inBound(i + 2, j + 1)) {
							if (not main[i + 2][j + 1].hasPiece()) {
								GreenThreat.insert({ i + 2, j + 1, true });
							}
							else if (main[i + 2][j + 1].checkPlayer() == RED) {
								GreenThreat.insert({ i + 2, j + 1, false });
							}
						}
						//Check 2, -1
						if (inBound(i + 2, j - 1)) {
							if (not main[i + 2][j - 1].hasPiece()) {
								GreenThreat.insert({ i + 2, j - 1, true });
							}
							else if (main[i + 2][j - 1].checkPlayer() == RED) {
								GreenThreat.insert({ i + 2, j - 1, false });
							}
						}
						//Check 1,-2
						if (inBound(i + 1, j - 2)) {
							if (not main[i + 1][j - 2].hasPiece()) {
								GreenThreat.insert({ i + 1, j - 2, true });
							}
							else if (main[i + 1][j - 2].checkPlayer() == RED) {
								GreenThreat.insert({ i + 1, j - 2, false });
							}
						}
						//Check -1, -2
						if (inBound(i - 1, j - 2)) {
							if (not main[i - 1][j - 2].hasPiece()) {
								GreenThreat.insert({ i - 1, j - 2, true });
							}
							else if (main[i - 1][j - 2].checkPlayer() == RED) {
								GreenThreat.insert({ i - 1, j - 2, false });
							}
						}
					}
					//Rook
					else if (hasFriendly('R', i, j, GREEN)) {
						//Search above
						int it = i + 1;
						while (it <= 7 and not main[it][j].hasPiece()) {
							GreenThreat.insert({ it, j, true });
							++it;
						}
						if (it <= 7 and main[it][j].checkPlayer() == RED) {
							GreenThreat.insert({ it, j, false });
						}
						//Search below
						it = i - 1;
						while (it >= 0 and not main[it][j].hasPiece()) {
							GreenThreat.insert({ it, j, true });
							--it;
						}
						if (it >= 0 and main[it][j].checkPlayer() == RED) {
							GreenThreat.insert({ it, j, false });
						}
						//Search to the right
						it = j + 1;
						while (it <= 7 and not main[i][it].hasPiece()) {
							GreenThreat.insert({ i, it, true });
							++it;
						}
						if (it <= 7 and main[i][it].checkPlayer() == RED) {
							GreenThreat.insert({ i, it, false });
						}
						//Search to the left
						it = j - 1;
						while (it >= 0 and not main[i][it].hasPiece()) {
							GreenThreat.insert({ i, it });
							--it;
						}
						if (it >= 0 and main[i][it].checkPlayer() == RED) {
							GreenThreat.insert({ i, it, false });
						}
					}
					//Bishop
					else if (hasFriendly('B', i, j, GREEN)) {
						//Search diagonal left-up
						int it_h = i + 1;
						int it_w = j - 1;
						while (it_h <= 7 and it_w >= 0 and not main[it_h][it_w].hasPiece()) {
							GreenThreat.insert({ it_h, it_w, true });
							++it_h;
							--it_w;
						}
						if (it_h <= 7 and it_w >= 0 and main[it_h][it_w].checkPlayer() == RED) {
							GreenThreat.insert({ it_h, it_w, false });
						}
						//Search diagonal left-down
						it_h = i - 1;
						it_w = j - 1;
						while (it_h >= 0 and it_w >= 0 and not main[it_h][it_w].hasPiece()) {
							GreenThreat.insert({ it_h, it_w, true });
							--it_h;
							--it_w;
						}
						if (it_h >= 0 and it_w >= 0 and main[it_h][it_w].checkPlayer() == RED) {
							GreenThreat.insert({ it_h, it_w, false });
						}
						//Search diagonal right-up
						it_h = i + 1;
						it_w = j + 1;
						while (it_h <= 7 and it_w <= 7 and not main[it_h][it_w].hasPiece()) {
							GreenThreat.insert({ it_h, it_w, true });
							++it_h;
							++it_w;
						}
						if (it_h <= 7 and it_w <= 7 and main[it_h][it_w].checkPlayer() == RED) {
							GreenThreat.insert({ it_h, it_w, false });
						}
						//Search diagonal right-down
						it_h = i - 1;
						it_w = j + 1;
						while (it_h >= 0 and it_w <= 7 and not main[it_h][it_w].hasPiece()) {
							GreenThreat.insert({ it_h, it_w, true });
							--it_h;
							++it_w;
						}
						if (it_h >= 0 and it_w <= 7 and main[it_h][it_w].checkPlayer() == RED) {
							GreenThreat.insert({ it_h, it_w, false });
						}
					}
					//Queen
					else if (hasFriendly('Q', i, j, GREEN)) {
						//Search above
						int it = i + 1;
						while (it <= 7 and not main[it][j].hasPiece()) {
							GreenThreat.insert({ it, j, true });
							++it;
						}
						if (it <= 7 and main[it][j].checkPlayer() == RED) {
							GreenThreat.insert({ it, j, false });
						}
						//Search below
						it = i - 1;
						while (it >= 0 and not main[it][j].hasPiece()) {
							GreenThreat.insert({ it, j, true });
							--it;
						}
						if (it >= 0 and main[it][j].checkPlayer() == RED) {
							GreenThreat.insert({ it, j, false });
						}
						//Search to the right
						it = j + 1;
						while (it <= 7 and not main[i][it].hasPiece()) {
							GreenThreat.insert({ i, it, true });
							++it;
						}
						if (it <= 7 and main[i][it].checkPlayer() == RED) {
							GreenThreat.insert({ i, it, false });
						}
						//Search to the left
						it = j - 1;
						while (it >= 0 and not main[i][it].hasPiece()) {
							GreenThreat.insert({ i, it, true });
							--it;
						}
						if (it >= 0 and main[i][it].checkPlayer() == RED) {
							GreenThreat.insert({ i, it, false });
						}
						//Search diagonal left-up
						int it_h = i + 1;
						int it_w = j - 1;
						while (it_h <= 7 and it_w >= 0 and not main[it_h][it_w].hasPiece()) {
							GreenThreat.insert({ it_h, it_w, true });
							++it_h;
							--it_w;
						}
						if (it_h <= 7 and it_w >= 0 and main[it_h][it_w].checkPlayer() == RED) {
							GreenThreat.insert({ it_h, it_w, false });
						}
						//Search diagonal left-down
						it_h = i - 1;
						it_w = j - 1;
						while (it_h >= 0 and it_w >= 0 and not main[it_h][it_w].hasPiece()) {
							GreenThreat.insert({ it_h, it_w, true });
							--it_h;
							--it_w;
						}
						if (it_h >= 0 and it_w >= 0 and main[it_h][it_w].checkPlayer() == RED) {
							GreenThreat.insert({ it_h, it_w, false });
						}
						//Search diagonal right-up
						it_h = i + 1;
						it_w = j + 1;
						while (it_h <= 7 and it_w <= 7 and not main[it_h][it_w].hasPiece()) {
							GreenThreat.insert({ it_h, it_w, true });
							++it_h;
							++it_w;
						}
						if (it_h <= 7 and it_w <= 7 and main[it_h][it_w].checkPlayer() == RED) {
							GreenThreat.insert({ it_h, it_w, false });
						}
						//Search diagonal right-down
						it_h = i - 1;
						it_w = j + 1;
						while (it_h >= 0 and it_w <= 7 and not main[it_h][it_w].hasPiece()) {
							GreenThreat.insert({ it_h, it_w, true });
							--it_h;
							++it_w;
						}
						if (it_h >= 0 and it_w <= 7 and main[it_h][it_w].checkPlayer() == RED) {
							GreenThreat.insert({ it_h, it_w, false });
						}
					}
					//King
					else if (hasFriendly('K', i, j, GREEN)) {
						for (int ii = -1; ii < 2; ++ii) {
							for (int jj = -1; jj < 2; ++jj) {
								if (inBound(i + ii, j + jj)) {
									if (not main[i + ii][j + jj].hasPiece()) {
										GreenThreat.insert({ i + ii, j + jj, true });
									}
									else if (main[i + ii][j + jj].checkPlayer() == RED) {
										GreenThreat.insert({ i + ii, j + jj, false });
									}
								}
							}
						}
					}
				}
			}
		}*/
	}
}