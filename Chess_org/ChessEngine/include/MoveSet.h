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
				char type;
				Position source, destination;
				bool capture, move, castleKing, castleQueen, promote, check;

				bool operator <(const Move& rhs) const;
			};
			std::set<Move> Set;

			void addKnight(Board& b, int orig_h, int orig_w, int i, int j, int color, int enemyColor);

			struct find_move_by_piece;
			struct find_moveR_by_piece;
			struct find_moveF_by_piece;
			struct find_capture_by_piece;

		public:
			void update(int color, Board& b);
			void checkDebug(int color) const;
			bool empty() const;
			Position findMove(char type, Position dest, Board& b) const;
			Position findMoveR(char type, int source_h, Position dest, Board& b) const;
			Position findMoveF(char type, int source_w, Position dest, Board& b) const;
			Position findCapture(char type, Position dest, Board& b) const;
		};
	}
}