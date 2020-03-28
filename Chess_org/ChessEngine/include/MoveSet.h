#pragma once
#include <set>
#include "Utilities.h"
//#include "Board.h"

namespace Chess {
	namespace Engine {

		class Board;

		class MoveSet {
		private:
			struct Move {
				Position source, destination;
				bool capture, move, castleKing, castleQueen, promote, check;

				bool operator <(const Move& rhs) const;
			};
			std::set<Move> Set;

			void addKnight(Board& b, int orig_h, int orig_w, int i, int j, int color, int enemyColor);

		public:
			void update(int color, Board& b);
			void checkDebug(int color) const;
			bool empty() const;
		};
	}
}