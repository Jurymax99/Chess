#include "Dummy.h"
#include "Board.h"

namespace Chess {
	namespace Engine {
		Dummy::Dummy() noexcept {
			color = 0;
			phase = Phase::UNDEFINED;
		}

		Dummy::Dummy(int color) noexcept{
			this->color = color;
			phase = Phase::OPENING;
		}

		void Dummy::move(Board& b) {
			Board a = b;
			Move m;

			float delta;
			std::cout << "Negamax analysis for depth " << DEPTH << std::endl;
			m = negamax(a, DEPTH, delta);
			std::cout << "Delta of " << delta << std::endl;
			std::cout << "Chosen move: ";
			printMove(m);
			b.move(m);
		}

		bool Dummy::gameOver(const Board& b) {
			return b.isEnded();
		}

		bool Dummy::gameOver2(Board& b, float& pen, const int& depth, bool& ended, const int& player) {
			int checked;
			return b.isEnded(player, checked, pen, ended);
		}

		Move Dummy::negamax(Board& position, int depth, float& delta) {
			float bestMove = -10000;
			std::vector<Move> equals(0);
			auto mover = color == GREEN ? &position.Green : &position.Red;
			mover->moves.sortMoves();
			int k = 0;
			auto it = mover->moves.Set.begin();
			int count = 1;
			Move best = *it;
			bool ended = false;
			while (k < mover->moves.SetSize()) {
				Board aux = position;
				aux.move(*it);
				aux.update();
				const float eval = -negamax(aux, -10000, 10000, depth - 1, ended, -color);
				if (eval > bestMove) {
					bestMove = eval;
					best = *it;
					if (equals.size() != 0) {
						equals.clear();
						equals.push_back(best);
					}
				}
				else if (eval == bestMove) {
					bestMove = eval;
					best = *it;
					equals.push_back(best);
				}
				//if (OUTPUT != MINIMAL) {
					std::cout << "Analised " << count << " out of " << mover->moves.SetSize() << " movements (last eval = " << eval << ") for ";
					printMove(*it);
				//}
				++count;
				++k;
				++it;
			}
			if (equals.size() > 1) {
				const int r = rand() % equals.size();
				delta = bestMove;
				return equals[r];
			}
			delta = bestMove;
			return best;
		}

		float Dummy::negamax(Board& position, float alpha, float beta, int depth, bool& ended, const int& player) {
				float pen = 0;
				if (depth == 0 or gameOver2(position, pen, depth, ended, player)) {
					if (abs(pen) == 900) {
						if (depth != 0) {
							pen -= depth * 90;
						}
					}
					return evaluateBoard(position, player) + pen;
				}
				float value = -10000;
				Player* mover = player == GREEN ? &position.Green : &position.Red;
				mover->moves.sortMoves();
				auto it = mover->moves.Set.begin();
				Board aux;
				int k = 0;
				while (k < mover->moves.SetSize()) {
					aux = position;
					aux.move(*it);
					aux.update();
					value = std::max(value, -negamax(aux, -beta, -alpha, depth - 1, ended, -player));
					alpha = std::max(alpha, value);
					if (alpha >= beta) {
						return value;
					}
					++k;
					++it;
				}
				return value;
		}

		float Dummy::evaluateByPos(char type, const int& i, const int& player, const int& pieceCount) const{
			switch (type) {
				case 'P':
					return 10 + (player == GREEN ? GreenPawnPos[i] : RedPawnPos[i]);
				case 'N':
					return 32 + (player == GREEN ? GreenKnightPos[i] : RedKnightPos[i]);
				case 'B':
					return 33 + (player == GREEN ? GreenBishopPos[i] : RedBishopPos[i]);
				case 'R':
					return 50 + (player == GREEN ? GreenRookPos[i] : RedRookPos[i]);
				case 'Q':
					return 90 + (player == GREEN ? GreenQueenPos[i] : RedQueenPos[i]);
				case 'K':
					//evaluate endgame king
					return 20000 + (pieceCount < 6 ? EndKing[i] : (player == GREEN ? GreenKingPos[i] : RedKingPos[i]));
				default:
					std::cout << "No known piece type" << std::endl;
					return -1;
			}
		}

		float Dummy::evaluateByPos(char type, const int& i, const int& player, const int& pieceCount, const int& turn) const {
			switch (type) {
			case 'P':
				return 10 + (player == GREEN ? GreenPawnPos[i] : RedPawnPos[i]);
			case 'N':
				return 32 + (player == GREEN ? GreenKnightPos[i] : RedKnightPos[i]);
			case 'B':
				return 33 + (player == GREEN ? GreenBishopPos[i] : RedBishopPos[i]);
			case 'R':
				return 50 + (player == GREEN ? GreenRookPos[i] : RedRookPos[i]);
			case 'Q':
				return 90 + (player == GREEN ? GreenQueenPos[i] : RedQueenPos[i]);
			case 'K':
				//evaluate endgame king
				return 20000 + (phase == Phase::END ? EndKing[i] : (player == GREEN ? GreenKingPos[i] : RedKingPos[i]));
			default:
				std::cout << "No known piece type" << std::endl;
				return -1;
			}
		}

		float Dummy::evaluateBoard(const Board& b, const int& player) {
			phase = not b.hasQueen() and b.checkPieces() < 10 ? Phase::END : Phase::OPENING;
			float eval = 0;
			for (int i = 0; i < 64; ++i) {
				if (b.main(i).checkPlayer() == player) {
					eval += evaluateByPos(b.main(i).checkPieceType(), i, player, b.checkPieces(), b.checkTurn());
					if (b.checkTurn() < 16 and not b.main(i).isFirstMov()) {
						eval -= 2.5;
					}
				}
				else if(b.main(i).checkPlayer() == -player){
					eval -= evaluateByPos(b.main(i).checkPieceType(), i, -player, b.checkPieces(), b.checkTurn());
					if (b.checkTurn() < 16 and not b.main(i).isFirstMov()) {
						eval += 2.5;
					}
				}
			}
			return eval;
		}

		void Dummy::printMove(const Move& m) const{
			std::cout << char(m.getSource().checkW() + 97) << char(8 - (m.getSource().checkH()- 48));
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

		const std::vector<float> Dummy::RedPawnPos = {
			0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
			5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,
			1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0,
			0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5,
			0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0,
			0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5,
			0.5,  1.0, 1.0,  -2.0, -2.0,  1.0,  1.0,  0.5,
			0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0
		};

		const std::vector<float> Dummy::RedKnightPos = {
			-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0,
			-4.0, -2.0,  0.0,  0.0,  0.0,  0.0, -2.0, -4.0,
			-3.0,  0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0,
			-3.0,  0.5,  1.5,  2.0,  2.0,  1.5,  0.5, -3.0,
			-3.0,  0.0,  1.5,  2.0,  2.0,  1.5,  0.0, -3.0,
			-3.0,  0.5,  1.0,  1.5,  1.5,  1.0,  0.5, -3.0,
			-4.0, -2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0,
			-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0
		};

		const std::vector<float> Dummy::RedBishopPos = {
			-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0,
			-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
			-1.0,  0.0,  0.5,  1.0,  1.0,  0.5,  0.0, -1.0,
			-1.0,  0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -1.0,
			-1.0,  0.0,  1.0,  1.0,  1.0,  1.0,  0.0, -1.0,
			-1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0,
			-1.0,  0.5,  0.0,  0.0,  0.0,  0.0,  0.5, -1.0,
			-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0
		};

		const std::vector<float> Dummy::RedRookPos = {
			0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
			0.5,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  0.5,
			-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
			-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
			-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
			-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
			-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
			0.0,   0.0, 0.0,  0.5,  0.5,  0.0,  0.0,  0.0
		};

		const std::vector<float> Dummy::RedQueenPos = {
			-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0,
			-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
			-1.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0,
			-0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5,
			0.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5,
			-1.0,  0.5,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0,
			-1.0,  0.0,  0.5,  0.0,  0.0,  0.0,  0.0, -1.0,
			-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0
		};

		const std::vector<float> Dummy::RedKingPos = {
			-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
			-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
			-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
			-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
			-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0,
			-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0,
			2.0,  2.0,  0.0,  0.0,  0.0,  0.0,  2.0,  2.0,
			2.0,  3.0,  1.0,  0.0,  0.0,  1.0,  3.0,  2.0
		};

		const std::vector<float> Dummy::EndKing = {
			-5.0, -4.0, -3.0, -2.0, -2.0, -3.0, -4.0, -5.0,
			-3.0, -2.0, -1.0,  0.0,  0.0, -1.0, -2.0, -3.0,
			-3.0, -1.0,  2.0,  3.0,  3.0,  2.0, -1.0, -3.0,
			-3.0, -1.0,  3.0,  4.0,  4.0,  3.0, -1.0, -3.0,
			-3.0, -1.0,  3.0,  4.0,  4.0,  3.0, -1.0, -3.0,
			-3.0, -1.0,  2.0,  3.0,  3.0,  2.0, -1.0, -3.0,
			-3.0, -3.0,  0.0,  0.0,  0.0,  0.0, -3.0, -3.0,
			-5.0, -3.0, -3.0, -3.0, -3.0, -3.0, -3.0, -5.0
		};

		const std::vector<float> Dummy::GreenPawnPos = {
			0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
			0.5,  1.0, 1.0,  -2.0, -2.0,  1.0,  1.0,  0.5,
			0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5,
			0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0,
			0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5,
			1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0,
			5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,
			0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0
		};
		const std::vector<float> Dummy::GreenKnightPos = {
			-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0,
			-4.0, -2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0,
			-3.0,  0.5,  1.0,  1.5,  1.5,  1.0,  0.5, -3.0,
			-3.0,  0.0,  1.5,  2.0,  2.0,  1.5,  0.0, -3.0,
			-3.0,  0.5,  1.5,  2.0,  2.0,  1.5,  0.5, -3.0,
			-3.0,  0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0,
			-4.0, -2.0,  0.0,  0.0,  0.0,  0.0, -2.0, -4.0,
			-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0
		};

		const std::vector<float> Dummy::GreenBishopPos = {
			-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0,
			-1.0,  0.5,  0.0,  0.0,  0.0,  0.0,  0.5, -1.0,
			-1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0,
			-1.0,  0.0,  1.0,  1.0,  1.0,  1.0,  0.0, -1.0,
			-1.0,  0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -1.0,
			-1.0,  0.0,  0.5,  1.0,  1.0,  0.5,  0.0, -1.0,
			-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
			-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0
		};

		const std::vector<float> Dummy::GreenRookPos = {
			0.0,   0.0, 0.0,  0.5,  0.5,  0.0,  0.0,  0.0,
			-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
			-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
			-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
			-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
			-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
			0.5,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  0.5,
			0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0
		};
		const std::vector<float> Dummy::GreenQueenPos = {
			-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0,
			-1.0,  0.0,  0.0,  0.0,  0.0,  0.5,  0.0, -1.0,
			-1.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.5, -1.0,
			-0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0,  0.0,
			-0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5,
			-1.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0,
			-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
			-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0
		};

		const std::vector<float> Dummy::GreenKingPos = {
			2.0,  3.0,  1.0,  0.0,  0.0,  1.0,  3.0,  2.0,
			2.0,  2.0,  0.0,  0.0,  0.0,  0.0,  2.0,  2.0,
			-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
			-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0,
			-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
			-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
			-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0,
			-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0
		};
	}
}