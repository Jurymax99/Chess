#pragma once
//#include <set>
//#include <unordered_set>
#include <vector>
#include "Utilities.h"

namespace Chess {
	namespace Engine {

		class Board;

		class MoveSet {
		private:
			friend class Dummy;
			//std::unordered_set<Move, MyHashFunction> Set;
			std::vector<Move> Set;
			//std::set<Move> Set;
			void addKnight(Board& b, int orig_h, int orig_w, int i, int j, int color);
			void addRookLike(Board& b, int i, int j, char type, int color);
			void addBishopLike(Board& b, int i, int j, char type, int color);

			struct find_move_by_piece;
			struct find_moveDA_by_piece;
			struct find_moveR_by_piece;
			struct find_moveF_by_piece;
			struct find_capture_by_piece;
			struct find_captureDA_by_piece;
			struct find_captureR_by_piece;
			struct find_captureF_by_piece;
			struct find_kingside;
			struct find_queenside;

		public:
			void update(int color, int pieceCount, Board& b);
			void checkDebug(int color) const;
			bool empty() const;
			Position findMove(char type, const Position& dest, const Board& b) const;
			Position findMoveDA(char type, const Position& source, const Position& dest, const Board& b) const;
			Position findMoveR(char type, int source_h, const Position& dest, const Board& b) const;
			Position findMoveF(char type, int source_w, const Position& dest, const Board& b) const;
			Position findCapture(char type, const Position& dest, const Board& b) const;
			Position findCaptureDA(char type, const Position& source, const Position& dest, const Board& b) const;
			Position findCaptureR(char type, int source_h, const Position& dest, const Board& b) const;
			Position findCaptureF(char type, int source_w, const Position& dest, const Board& b) const;
			bool findKingsideCastling(const Board& b) const;
			bool findQueensideCastling(const Board& b) const;
		};
	}
}