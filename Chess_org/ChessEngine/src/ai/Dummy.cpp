#include "Dummy.h"
#include "Board.h"

namespace Chess {
	namespace Engine {
		Dummy::Dummy() {
			color = 0;
			enemyColor = 0;
		}

		Dummy::Dummy(int color) {
			this->color = color;
			if (color == RED) {
				enemyColor = GREEN;
			}
			else {
				enemyColor = RED;
			}
		}

		std::unordered_map<char, float> Dummy::evaluationPoints = { {'P',10}, {'N', 30}, {'B',30.3}, {'R', 50}, {'Q',90}, {'K', 900} };

		void Dummy::move(Board& b) {
			Board a = b;
			Move m;
			std::cout << "Minimax analysis for depth " << DEPTH << std::endl;

			float delta;
			m = minimax(a, DEPTH, delta);
			std::cout << "Delta of " << delta << std::endl;
			printMove(m);
			b.move(m, color);
		}

		bool Dummy::gameOver(Board& b) {
			return b.isEnded();
		}

		bool Dummy::gameOver2(Board& b, float& pen, const int& depth, bool& ended) {
			int checked;
			if (b.isEnded(color, checked, pen)) {
				//std::cout << "MATE IN " << DEPTH - depth << std::endl;
				if (DEPTH - depth <= 2) {
					ended = checked == enemyColor;
				}
				return true;
			}
			return false;
		}

		//TODO: WARNING KING HAS NO NUMERICAL VALUE
		//FEN: r2r2k1/pppb1ppp/3b4/3pp2P/4q3/2P1P3/PP1B1PP1/R2QKB1R b KQ - 0 17

		Move Dummy::minimax(Board& position, int depth, float& delta) {
			float bestMove = -9999;
			std::vector<Move> equals(0);
			auto it = position.Green.moves.Set.begin();
			int count = 1;
			Move best = *it;
			bool ended = false;
			for (; it != position.Green.moves.Set.end() and not ended; ++it) {
				Board aux = position;
				aux.move(*it, color);
				//aux.Red.moves.update(RED, aux.Red.checkPieceCount(), aux);
				aux.update();
				float eval = minimax_r(aux, -10000, 10000, depth - 1, false, ended);
				if (eval > bestMove) {
					bestMove = eval;
					best = *it;
					if (equals.size() != 0) {
						equals.clear();
					}
				}
				else if (eval == bestMove) {
					bestMove = eval;
					best = *it;
					equals.push_back(best);
				}
				std::cout << "Analised " << count << " out of " << position.Green.moves.Set.size() << " movements (last eval = " << eval << ")\n";
				++count;
			}
			if (equals.size() > 0) {
				int r = rand() % equals.size();
				delta = bestMove;
				return equals[r];
			}
			delta = bestMove;
			return best;
		}

		/*float Dummy::minimaxStd_r(Board position, int depth, bool maximizingPlayer) {
			float pen = 0;
			if (depth == 0 or gameOver2(position, pen, depth)) {
				return evaluateBoard(position) + pen;
			}
			if (maximizingPlayer) {
				float maxEval = -9999;
				auto it = position.Green.moves.Set.begin();
				for (; it != position.Green.moves.Set.end(); ++it) {
					Board aux = position;
					if (aux.main(it->source.h,it->source.w).hasPiece()) {
						aux.move(*it, color);
					}
					else {
						int a = 0;
					}
					aux.Red.moves.update(RED, aux.Red.checkPieceCount(), aux);
					//aux.update();
					float eval = minimaxStd_r(aux, depth - 1, not maximizingPlayer);
					maxEval = std::max(maxEval, eval);
				}
				return maxEval;
			}
			else {
				float minEval = 9999;
				//position.update();
				if (color == RED) {
					auto it = position.Green.moves.Set.begin();
					for (; it != position.Green.moves.Set.end(); ++it) {
						Board aux = position;
						aux.move(*it, enemyColor);
						aux.Red.moves.update(RED, aux.Red.checkPieceCount(), aux);
						//aux.update();
						float eval = minimaxStd_r(aux, depth - 1, not maximizingPlayer);
						minEval = std::min(minEval, eval);
					}
				}
				else {
					auto it = position.Red.moves.Set.begin();
					for (; it != position.Red.moves.Set.end(); ++it) {
						Board aux = position;
						aux.move(*it, enemyColor);
						aux.Green.moves.update(GREEN, aux.Green.checkPieceCount(), aux);
						//aux.update();
						float eval = minimaxStd_r(aux, depth - 1, not maximizingPlayer);
						minEval = std::min(minEval, eval);
					}
				}
				return minEval;
			}
			
		}*/

		float Dummy::minimax_r(Board& position, float alpha, float beta, int depth, bool maximizingPlayer, bool& ended) {
			if (not ended) {
				float pen = 0;
				if (depth == 0 or gameOver2(position, pen, depth, ended)) {
					return evaluateBoard(position) + pen;
				}
				if (maximizingPlayer) {
					float maxEval = -9999;
					auto it = position.Green.moves.Set.begin();
					Board aux;
					for (; it != position.Green.moves.Set.end(); ++it) {
						aux = position;
						if (aux.main(it->getSource().checkH(),it->getSource().checkW()).hasPiece()) {
							aux.move(*it, color);
						}
						//aux.Red.moves.update(RED, aux.Red.checkPieceCount(), aux);
						aux.update();
						float eval = minimax_r(aux, alpha, beta, depth - 1, not maximizingPlayer, ended);
						maxEval = std::max(maxEval, eval);
						alpha = std::max(alpha, maxEval);
						if (beta <= alpha) {
							return maxEval;
						}
					}
					return maxEval;
				}
				else {
					float minEval = 9999;
					//position.update();
					/*if (color == RED) {
						auto it = position.Green.moves.Set.begin();
						Board aux;
						for (; it != position.Green.moves.Set.end(); ++it) {
							aux = position;
							aux.move(*it, enemyColor);
							aux.Red.moves.update(RED, aux.Red.checkPieceCount(), aux);
							//aux.update();
							float eval = minimax_r(aux, alpha, beta, depth - 1, not maximizingPlayer);
							minEval = std::min(minEval, eval);
							beta = std::min(beta, minEval);
							if (beta <= alpha) {
								return minEval;
							}
						}
					}
					else {*/
					auto it = position.Red.moves.Set.begin();
					Board aux;
					for (; it != position.Red.moves.Set.end(); ++it) {
						aux = position;
						aux.move(*it, enemyColor);
						//aux.Green.moves.update(GREEN, aux.Green.checkPieceCount(), aux);
						aux.update();
						float eval = minimax_r(aux, alpha, beta, depth - 1, not maximizingPlayer, ended);
						minEval = std::min(minEval, eval);
						beta = std::min(beta, minEval);
						if (beta <= alpha) {
							return minEval;
						}
					}
					//}
					return minEval;
				}
			}
			return 9999;
		}

		float Dummy::evaluateByPos(char type, const int& i, const int& j, const int& player, const int& pieceCount) const{
			switch (type) {
				case 'P':
					return 10 + (player == GREEN ? GreenPawnPos[i][j] : RedPawnPos[i][j]);
				case 'N':
					return 30 + (player == GREEN ? GreenKnightPos[i][j] : RedKnightPos[i][j]);
				case 'B':
					return 30 + (player == GREEN ? GreenBishopPos[i][j] : RedBishopPos[i][j]);
				case 'R':
					return 50 + (player == GREEN ? GreenRookPos[i][j] : RedRookPos[i][j]);
				case 'Q':
					return 90 + (player == GREEN ? GreenQueenPos[i][j] : RedQueenPos[i][j]);
				case 'K':
					//std::cout << "WARNING::King has no numerical value" << std::endl;
					//evaluate endgame king
					return 900 + (pieceCount < 15 ? EndKing[i][j] : (player == GREEN ? GreenKingPos[i][j] : RedKingPos[i][j]));
				default:
					std::cout << "No known piece type" << std::endl;
					return -1;
			}
		}


		float Dummy::evaluateBoard(const Board& b) const {
			float eval = 0;
			for (int i = 0; i < 8; ++i) {
				for (int j = 0; j < 8; ++j) {
					if (b.main(i,j).hasPiece()) {
						if (b.main(i,j).checkPlayer() == color) {
							//eval += evaluationPoints[b.main(i,j).checkPieceType()];
							eval += evaluateByPos(b.main(i,j).checkPieceType(), i, j, color, b.checkPieces());
							if (b.checkTurn() < 20 and not b.main(i,j).isFirstMov()) {
								eval -= 0.5;
							}
						}
						else {
							//eval -= evaluationPoints[b.main(i,j).checkPieceType()];
							eval -= evaluateByPos(b.main(i,j).checkPieceType(), i, j, enemyColor, b.checkPieces());
							if (b.checkTurn() < 20 and not b.main(i,j).isFirstMov()) {
								eval += 0.5;
							}
						}
					}
				}
			}
			return eval;
		}


		float Dummy::checkPoints(char type) const{
			switch (type) {
				case 'P':
					return 1;
				case 'N':
				case 'B':
					return 3;
				case 'R':
					return 5;
				case 'Q':
					return 9;
				case 'K':
					//std::cout << "WARNING::King has no numerical value" << std::endl;
					return 900;
				default:
					std::cout << "No known piece type" << std::endl;
					return -1;
			}
		}

		void Dummy::printMove(const Move& m) const{
			std::cout << "Chosen move: " << char(m.getSource().checkW() + 97) << char(8 - (m.getSource().checkH()- 48));
			std::cout << " to " << char(m.getDestination().checkW() + 97) << char(8 - (m.getDestination().checkH()- 48)) << std::endl;
		}

		void Dummy::choseRandMove(Move& m) {
			int r = rand() % moves.Set.size();
			auto it = moves.Set.begin();
			for (int i = 0; i < r; ++i) {
				++it;
			}
			m = *it;
		}

		const std::vector<std::vector<float>> Dummy::RedPawnPos = {
			{0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
			{5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0},
			{1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0},
			{0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5},
			{0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0},
			{0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5},
			{0.5,  1.0, 1.0,  -2.0, -2.0,  1.0,  1.0,  0.5},
			{0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0}
		};

		const std::vector<std::vector<float>> Dummy::RedKnightPos = {
			{-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
			{-4.0, -2.0,  0.0,  0.0,  0.0,  0.0, -2.0, -4.0},
			{-3.0,  0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0},
			{-3.0,  0.5,  1.5,  2.0,  2.0,  1.5,  0.5, -3.0},
			{-3.0,  0.0,  1.5,  2.0,  2.0,  1.5,  0.0, -3.0},
			{-3.0,  0.5,  1.0,  1.5,  1.5,  1.0,  0.5, -3.0},
			{-4.0, -2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0},
			{-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0}
		};

		const std::vector<std::vector<float>> Dummy::RedBishopPos = {
			{-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
			{-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0},
			{-1.0,  0.0,  0.5,  1.0,  1.0,  0.5,  0.0, -1.0},
			{-1.0,  0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -1.0},
			{-1.0,  0.0,  1.0,  1.0,  1.0,  1.0,  0.0, -1.0},
			{-1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0},
			{-1.0,  0.5,  0.0,  0.0,  0.0,  0.0,  0.5, -1.0},
			{-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0}
		};

		const std::vector<std::vector<float>> Dummy::RedRookPos = {
			{0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
			{0.5,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  0.5},
			{-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
			{-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
			{-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
			{-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
			{-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
			{0.0,   0.0, 0.0,  0.5,  0.5,  0.0,  0.0,  0.0}
		};

		const std::vector<std::vector<float>> Dummy::RedQueenPos = {
			{-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0},
			{-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0},
			{-1.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0},
			{-0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5},
			{0.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5},
			{-1.0,  0.5,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0},
			{-1.0,  0.0,  0.5,  0.0,  0.0,  0.0,  0.0, -1.0},
			{-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0}
		};

		const std::vector<std::vector<float>> Dummy::RedKingPos = {
			{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
			{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
			{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
			{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
			{-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
			{-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
			{2.0,  2.0,  0.0,  0.0,  0.0,  0.0,  2.0,  2.0},
			{2.0,  3.0,  1.0,  0.0,  0.0,  1.0,  3.0,  2.0}
		};

		const std::vector<std::vector<float>> Dummy::EndKing = {
			{-5.0, -3.0,  -0.5,  2.0,  2.0, -0.5, -3.0,  -5.0},
			{-3.0, -0.5,   2.0,  3.5,  3.5,  2.0, -0.5,  -3.0},
			{-0.5,  2.0,   3.5,  5.0,  5.0,  3.5,  2.0,  -0.5},
			{2.0,   3.5,   5.0,  6.5,  6.5,  5.0,  3.5,   2.0},
			{2.0,   3.5,   5.0,  6.5,  6.5,  5.0,  3.5,   2.0},
			{-0.5,  2.0,   3.5,  5.0,  5.0,  3.5,  2.0,  -0.5},
			{-3.0, -0.5,   2.0,  3.5,  3.5,  2.0,  -0.5, -3.0},
			{-5.0, -3.0,  -0.5,  2.0,  2.0,  -0.5, -3.0, -5.0}
		};

		const std::vector<std::vector<float>> Dummy::GreenPawnPos = {
			{0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
			{0.5,  1.0, 1.0,  -2.0, -2.0,  1.0,  1.0,  0.5},
			{0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5},
			{0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0},
			{0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5},
			{1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0},
			{5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0},
			{0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0}
		};
		const std::vector<std::vector<float>> Dummy::GreenKnightPos = {
			{-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
			{-4.0, -2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0},
			{-3.0,  0.5,  1.0,  1.5,  1.5,  1.0,  0.5, -3.0},
			{-3.0,  0.0,  1.5,  2.0,  2.0,  1.5,  0.0, -3.0},
			{-3.0,  0.5,  1.5,  2.0,  2.0,  1.5,  0.5, -3.0},
			{-3.0,  0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0},
			{-4.0, -2.0,  0.0,  0.0,  0.0,  0.0, -2.0, -4.0},
			{-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0}
		};

		const std::vector<std::vector<float>> Dummy::GreenBishopPos = {
			{-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
			{-1.0,  0.5,  0.0,  0.0,  0.0,  0.0,  0.5, -1.0},
			{-1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0},
			{-1.0,  0.0,  1.0,  1.0,  1.0,  1.0,  0.0, -1.0},
			{-1.0,  0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -1.0},
			{-1.0,  0.0,  0.5,  1.0,  1.0,  0.5,  0.0, -1.0},
			{-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0},
			{-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0}
		};

		const std::vector<std::vector<float>> Dummy::GreenRookPos = {
			{0.0,   0.0, 0.0,  0.5,  0.5,  0.0,  0.0,  0.0},
			{-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
			{-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
			{-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
			{-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
			{-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
			{0.5,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  0.5},
			{0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
		};
		const std::vector<std::vector<float>> Dummy::GreenQueenPos = {
			{-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0},
			{-1.0,  0.0,  0.5,  0.0,  0.0,  0.0,  0.0, -1.0},
			{-1.0,  0.5,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0},
			{0.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5},
			{-0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5},
			{-1.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0},
			{-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0},
			{-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0},
		};

		const std::vector<std::vector<float>> Dummy::GreenKingPos = {
			{2.0,  3.0,  1.0,  0.0,  0.0,  1.0,  3.0,  2.0},
			{2.0,  2.0,  0.0,  0.0,  0.0,  0.0,  2.0,  2.0},
			{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
			{-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
			{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
			{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
			{-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
			{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
		};
	}
}