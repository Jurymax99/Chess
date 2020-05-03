#pragma once
#include <vector>
#include "Utilities.h"

namespace Chess {
	namespace Engine {

		class Board;

		class MoveSet {
		private:
			friend class Dummy;
			int color, size;
			std::vector<Move> Set = std::vector<Move>(300);
			void addKnight(Board& b, const int& orig_h, const int& orig_w, const int& i, const int& j, int& k);
			void addRookLike(Board& b, const int& i, const int& j, const char& type, int& k);
			void addBishopLike(Board& b, const int& i, const int& j, const char& type, int& k);

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
			struct find_promote;

		public:
			MoveSet();
			MoveSet(const int& color);

			void update(Board& b);
			void checkDebug() const;
			Position findMove(const char& type, const Position& dest, const Board& b) const;
			Position findMoveDA(const char& type, const Position& source, const Position& dest, const Board& b) const;
			Position findMoveR(const char& type, const int& source_h, const Position& dest, const Board& b) const;
			Position findMoveF(const char& type, const int& source_w, const Position& dest, const Board& b) const;
			Position findCapture(const char& type, const Position& dest, const Board& b) const;
			Position findCaptureDA(const char& type, const Position& source, const Position& dest, const Board& b) const;
			Position findCaptureR(const char& type, const int& source_h, const Position& dest, const Board& b) const;
			Position findCaptureF(const char& type, const int& source_w, const Position& dest, const Board& b) const;
			bool findKingsideCastling(const Board& b) const;
			bool findQueensideCastling(const Board& b) const;
			Position findPromote(const Position& p, const Board& b) const;


			inline bool empty() const noexcept { return Set.empty(); }

			inline int SetSize() const noexcept { return size; }

			void sortMoves();

		};
	}
}