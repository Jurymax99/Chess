#pragma once
#include "Player.h"
#include <algorithm>
#include <map>

namespace Chess {
	namespace Engine {

		class Dummy : public Player {

		private:
			int enemyColor;
			static std::map<char, int> evaluationPoints;

			int checkPoints(char type) const;

			int evaluateBoard(const Board& b) const;
			void choseRandMove(Move& m);
			void captureMostPoints(Move& m);
			int minimax_r(Board position, int depth, bool maximizingPlayer);
			Move minimax(Board position, int depth);
			bool gameOver(Board& b);
			bool gameOver2(Board& b, int& pen);
			void printMove(const Move& m) const;
		public:
			Dummy();
			Dummy(int color);

			void move(Board& b);
		};
	}
}
		