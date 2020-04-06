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

		std::map<char, int> Dummy::evaluationPoints = { {'P',10}, {'N', 30}, {'B',30}, {'R', 50}, {'Q',90}, {'K', 900} };

		void Dummy::move(Board& b) {
			moves.update(color, pieceCount, b);
			Board a = b;
			Move m;
			int depth = 3;
			/*int MM = minimax_r(a, depth, true);
			std::cout << "Minimax analysis for depth " << depth << " is " << MM << std::endl;*/
			std::cout << "Minimax analysis for depth " << depth << std::endl;

			//int eval = evaluateBoard(a);
			//captureMostPoints(m);
			//choseRandMove(m);
			m = minimax(a, depth);
			printMove(m);
			b.move(m, color);
		}

		bool Dummy::gameOver(Board& b) {
			return b.isEnded();
		}

		bool Dummy::gameOver2(Board& b, int& pen) {
			int checked;
			return b.isEnded(color, checked, pen);
		}

		//TODO: FIX TILE HAD ALREADY AN EXISTING PIECE

		Move Dummy::minimax(Board position, int depth) {
			int bestMove = -9999;
			std::vector<Move> equals(0);
			auto it = position.Green.moves.Set.begin();
			Move best = *it;
			for (; it != position.Green.moves.Set.end(); ++it) {
				Board aux = position;
				aux.move(*it, color);
				aux.update();
				int eval = minimax_r(aux, depth - 1, false);
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
			}
			if (equals.size() > 0) {
				int r = rand() % equals.size();
				return equals[r];
			}
			return best;
		}

		int Dummy::minimax_r(Board position, int depth, bool maximizingPlayer) {
			int pen = 0;
			if (depth == 0 or gameOver2(position, pen)) {
				return evaluateBoard(position) + pen;
			}
			if (maximizingPlayer) {
				int maxEval = -9999;
				auto it = position.Green.moves.Set.begin();
				for (; it != position.Green.moves.Set.end(); ++it) {
					Board aux = position;
					if (aux.main[it->source.h][it->source.w].hasPiece()) {
						aux.move(*it, color);
					}
					else {
						int a = 0;
					}
					aux.update();
					int eval = minimax_r(aux, depth - 1, not maximizingPlayer);
					maxEval = std::max(maxEval, eval);
				}
				return maxEval;
			}
			else {
				int minEval = 9999;
				//position.update();
				if (color == RED) {
					auto it = position.Green.moves.Set.begin();
					for (; it != position.Green.moves.Set.end(); ++it) {
						Board aux = position;
						aux.move(*it, enemyColor);
						aux.update();
						int eval = minimax_r(aux, depth - 1, not maximizingPlayer);
						minEval = std::min(minEval, eval);
					}
				}
				else {
					auto it = position.Red.moves.Set.begin();
					for (; it != position.Red.moves.Set.end(); ++it) {
						Board aux = position;
						aux.move(*it, enemyColor);
						aux.update();
						int eval = minimax_r(aux, depth - 1, not maximizingPlayer);
						minEval = std::min(minEval, eval);
					}
				}
				return minEval;
			}
			
		}


		int Dummy::evaluateBoard(const Board& b) const {
			int eval = 0;
			for (int i = 0; i < b.checkHeight(); ++i) {
				for (int j = 0; j < b.checkWidth(); ++j) {
					if (b.main[i][j].hasPiece()) {
						if (b.main[i][j].checkPlayer() == color) {
							eval += evaluationPoints[b.main[i][j].checkPieceType()];
						}
						else {
							eval -= evaluationPoints[b.main[i][j].checkPieceType()];
						}
					}
				}
			}
			return eval;
		}


		int Dummy::checkPoints(char type) const{
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
					std::cout << "WARNING::King has no numerical value" << std::endl;
					return -1;
				default:
					std::cout << "No known piece type" << std::endl;
					return -1;
			}
		}

		void Dummy::captureMostPoints(Move& m) {
			auto it = moves.Set.begin();
			int max = 0;
			for (; it != moves.Set.end(); ++it) {
				if (it->capture) {
					if (checkPoints(it->killed) > max) {
						max = checkPoints(it->killed);
						m = *it;
					}
				}
			}
			std::cout << max << " kills found\n";
			if (max == 0) {
				choseRandMove(m);
			}
			printMove(m);
		}

		void Dummy::printMove(const Move& m) const{
			std::cout << "Chosen move: " << char(m.source.w + 97) << char(8 - (m.source.h - 48));
			std::cout << " to " << char(m.destination.w + 97) << char(8 - (m.destination.h - 48)) << std::endl;
		}

		void Dummy::choseRandMove(Move& m) {
			int r = rand() % moves.Set.size();
			auto it = moves.Set.begin();
			for (int i = 0; i < r; ++i) {
				++it;
			}
			m = *it;
		}
	}
}