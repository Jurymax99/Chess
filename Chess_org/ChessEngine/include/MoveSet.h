#pragma once
#include <set>
#include "Utilities.h"

namespace Chess {
	namespace Engine {

		class Board;

		class MoveSet {
		private:
			friend class Dummy;
			std::set<Move> Set;

			void addKnight(Board& b, int orig_h, int orig_w, int i, int j, int color, int enemyColor);

			struct find_move_by_piece;
			struct find_moveDA_by_piece;
			struct find_moveR_by_piece;
			struct find_moveF_by_piece;
			struct find_capture_by_piece;
			struct find_captureDA_by_piece;
			struct find_captureR_by_piece;
			struct find_captureF_by_piece;

		public:
			void update(int color, int pieceCount, Board& b);
			void checkDebug(int color) const;
			bool empty() const;
			Position findMove(char type, const Position& dest, const Board& b) const;
			Position findMoveDA(char type, int source_h, int source_w, const Position& dest, const Board& b) const;
			Position findMoveR(char type, int source_h, const Position& dest, const Board& b) const;
			Position findMoveF(char type, int source_w, const Position& dest, const Board& b) const;
			Position findCapture(char type, const Position& dest, const Board& b) const;
			Position findCaptureDA(char type, int source_h, int source_w, const Position& dest, const Board& b) const;
			Position findCaptureR(char type, int source_h, const Position& dest, const Board& b) const;
			Position findCaptureF(char type, int source_w, const Position& dest, const Board& b) const;

		};
	}
}