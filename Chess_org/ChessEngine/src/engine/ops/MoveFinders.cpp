#include "MoveSet.h"

namespace Chess {
	namespace Engine {
		struct MoveSet::find_move_by_piece {
			find_move_by_piece(const char& type, const Position& dest)
				: type(type), dest(dest) {}

			bool operator()(const Move& m) const {
				return m.move and
					not m.castleKing and
					not m.castleQueen and
					m.type == type and
					m.destination == dest;
			}

		private:
			char type;
			Position dest;
		};

		struct MoveSet::find_moveDA_by_piece {
			find_moveDA_by_piece(const char& type, const int& source_h, const int& source_w, const Position& dest)
				: type(type), dest(dest), source_h(source_h), source_w(source_w) {}

			bool operator()(const Move& m) const {
				return m.move and
					m.type == type and
					m.source.h == source_h and
					m.source.w == source_w and
					m.destination == dest;
			}
		private:
			char type;
			Position dest;
			int source_h, source_w;
		};

		struct MoveSet::find_moveR_by_piece {
			find_moveR_by_piece(const char& type, const int& source_h, const Position& dest)
				: type(type), source_h(source_h), dest(dest) {}

			bool operator()(const Move& m) const {
				return m.move and
					not m.castleKing and
					not m.castleQueen and
					m.type == type and
					m.source.h == source_h and
					m.destination == dest;
			}
		private:
			char type;
			int source_h;
			Position dest;
		};

		struct MoveSet::find_moveF_by_piece {
			find_moveF_by_piece(const char& type, const int& source_w, const Position& dest)
				: type(type), source_w(source_w), dest(dest) {}

			bool operator()(const Move& m) const {
				return m.move and
					not m.castleKing and
					not m.castleQueen and
					m.type == type and
					m.source.w == source_w and
					m.destination == dest;
			}
		private:
			char type;
			Position dest;
			int source_w;
		};

		struct MoveSet::find_capture_by_piece {
			find_capture_by_piece(const char& type, const Position& dest)
				: type(type), dest(dest) {}

			bool operator()(const Move& m) const {
				return m.capture and
					m.type == type and
					m.destination == dest;
			}
		private:
			char type;
			Position dest;
		};

		struct MoveSet::find_captureDA_by_piece {
			find_captureDA_by_piece(const char& type, const int& source_h, const int& source_w, const Position& dest)
				: type(type), dest(dest), source_h(source_h), source_w(source_w)  {}

			bool operator()(const Move& m) const {
				return m.capture and
					m.type == type and
					m.source.h == source_h and
					m.source.w == source_w and
					m.destination == dest;
			}
		private:
			char type;
			Position dest;
			int source_h, source_w;
		};

		struct MoveSet::find_captureR_by_piece {
			find_captureR_by_piece(const char& type, const int& source_h, const Position& dest)
				: type(type), source_h(source_h), dest(dest) {}

			bool operator()(const Move& m) const {
				return m.capture and
					m.type == type and
					m.source.h == source_h and
					m.destination == dest;
			}
		private:
			char type;
			int source_h;
			Position dest;
		};

		struct MoveSet::find_captureF_by_piece {
			find_captureF_by_piece(const char& type, const int& source_w, const Position& dest)
				: type(type), source_w(source_w), dest(dest) {}

			bool operator()(const Move& m) const {
				return m.capture and
					m.type == type and
					m.source.w == source_w and
					m.destination == dest;
			}
		private:
			char type;
			Position dest;
			int source_w;
		};

		Position MoveSet::findMove(char type, const Position& dest, const Board& b) const {
			int available = std::count_if(Set.begin(),
				Set.end(),
				find_move_by_piece(type, dest));
			if (available != 1) {
				if (available > 1 and MODE == DEBUG) {
					std::cout << "More than 1 piece can make this move" << std::endl;
				}
				return { -1,-1 };
			}
			auto it = std::find_if(Set.begin(),
				Set.end(),
				find_move_by_piece(type, dest));
			return it->source;
		}

		Position MoveSet::findMoveDA(char type, int source_h, int source_w, const Position& dest, const Board& b) const {
			std::cout << "From " << source_h << " " << source_w << " to " << dest.h << " " << dest.w << std::endl;
			int available = std::count_if(Set.begin(),
				Set.end(),
				find_moveDA_by_piece(type, source_h, source_w, dest));
			if (available != 1) {
				if (available > 1 and MODE == DEBUG) {
					std::cout << "More than 2 pieces can make this move" << std::endl;
				}
				return { -1,-1 };
			}
			auto it = std::find_if(Set.begin(),
				Set.end(),
				find_moveDA_by_piece(type, source_h, source_w, dest));
			return it->source;
		}

		Position MoveSet::findMoveR(char type, int source_h, const Position& dest, const Board& b) const {
			int available = std::count_if(Set.begin(),
				Set.end(),
				find_moveR_by_piece(type, source_h, dest));
			if (available != 1) {
				if (MODE == DEBUG) {
					std::cout << "More than 2 pieces can make this move" << std::endl;
				}
				return { -1,-1 };
			}
			auto it = std::find_if(Set.begin(),
				Set.end(),
				find_moveR_by_piece(type, source_h, dest));
			return it->source;
		}

		Position MoveSet::findMoveF(char type, int source_w, const Position& dest, const Board& b) const {
			int available = std::count_if(Set.begin(),
				Set.end(),
				find_moveF_by_piece(type, source_w, dest));
			if (available != 1) {
				if (MODE == DEBUG) {
					std::cout << "More than 2 pieces can make this move" << std::endl;
				}
				return { -1,-1 };
			}
			auto it = std::find_if(Set.begin(),
				Set.end(),
				find_moveF_by_piece(type, source_w, dest));
			return it->source;
		}

		Position MoveSet::findCapture(char type, const Position& dest, const Board& b) const {
			int available = std::count_if(Set.begin(),
				Set.end(),
				find_capture_by_piece(type, dest));
			if (available != 1) {
				if (MODE == DEBUG) {
					std::cout << "More than 1 piece can make this move" << std::endl;
				}
				return { -1,-1 };
			}
			auto it = std::find_if(Set.begin(),
				Set.end(),
				find_capture_by_piece(type, dest));
			return it->source;
		}

		Position MoveSet::findCaptureDA(char type, int source_h, int source_w, const Position& dest, const Board& b) const {
			int available = std::count_if(Set.begin(),
				Set.end(),
				find_captureDA_by_piece(type, source_h, source_w, dest));
			if (available != 1) {
				if (MODE == DEBUG) {
					std::cout << "More than 2 pieces can make this move" << std::endl;
				}
				return { -1,-1 };
			}
			auto it = std::find_if(Set.begin(),
				Set.end(),
				find_captureDA_by_piece(type, source_h, source_w, dest));
			return it->source;
		}

		Position MoveSet::findCaptureR(char type, int source_h, const Position& dest, const Board& b) const {
			int available = std::count_if(Set.begin(),
				Set.end(),
				find_captureR_by_piece(type, source_h, dest));
			if (available != 1) {
				if (MODE == DEBUG) {
					std::cout << "More than 2 pieces can make this move" << std::endl;
				}
				return { -1,-1 };
			}
			auto it = std::find_if(Set.begin(),
				Set.end(),
				find_captureR_by_piece(type, source_h, dest));
			return it->source;
		}

		Position MoveSet::findCaptureF(char type, int source_w, const Position& dest, const Board& b) const {
			int available = std::count_if(Set.begin(),
				Set.end(),
				find_captureF_by_piece(type, source_w, dest));
			if (available != 1) {
				if (MODE == DEBUG) {
					std::cout << "More than 2 pieces can make this move" << std::endl;
				}
				return { -1,-1 };
			}
			auto it = std::find_if(Set.begin(),
				Set.end(),
				find_captureF_by_piece(type, source_w, dest));
			return it->source;
		}
	}
}