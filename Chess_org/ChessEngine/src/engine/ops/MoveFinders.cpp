#include "MoveSet.h"

namespace Chess {
	namespace Engine {
		struct MoveSet::find_move_by_piece {
			find_move_by_piece(const char& type, const Position& dest) noexcept
				: type(type), dest(dest) {}

			inline bool operator()(const Move& m) const {
				return not m.isCapture() and
					not m.isCastleKingside() and
					not m.isCastleQueenside() and
					m.getType() == type and
					m.getDestination() == dest;
			}

		private:
			char type;
			Position dest;
		};

		struct MoveSet::find_moveDA_by_piece {
			find_moveDA_by_piece(const char& type, const Position& source, const Position& dest) noexcept
				: type(type), dest(dest), source(source) {}

			inline bool operator()(const Move& m) const {
				return not m.isCapture() and
					m.getType() == type and
					m.getSource() == source and
					m.getDestination() == dest;
			}
		private:
			char type;
			Position dest;
			Position source;
		};

		struct MoveSet::find_moveR_by_piece {
			find_moveR_by_piece(const char& type, const int& source_h, const Position& dest) noexcept
				: type(type), source_h(source_h), dest(dest) {}

			inline bool operator()(const Move& m) const {
				return not m.isCapture() and
					not m.isCastleKingside() and
					not m.isCastleQueenside() and
					m.getType() == type and
					m.getSource().checkH()== source_h and
					m.getDestination() == dest;
			}
		private:
			char type;
			int source_h;
			Position dest;
		};

		struct MoveSet::find_moveF_by_piece {
			find_moveF_by_piece(const char& type, const int& source_w, const Position& dest) noexcept
				: type(type), source_w(source_w), dest(dest) {}

			inline bool operator()(const Move& m) const {
				return not m.isCapture() and
					not m.isCastleKingside() and
					not m.isCastleQueenside() and
					m.getType() == type and
					m.getSource().checkW() == source_w and
					m.getDestination() == dest;
			}
		private:
			char type;
			Position dest;
			int source_w;
		};

		struct MoveSet::find_capture_by_piece {
			find_capture_by_piece(const char& type, const Position& dest) noexcept
				: type(type), dest(dest) {}

			inline bool operator()(const Move& m) const {
				return m.isCapture() and
					m.getType() == type and
					m.getDestination() == dest;
			}
		private:
			char type;
			Position dest;
		};

		struct MoveSet::find_captureDA_by_piece {
			find_captureDA_by_piece(const char& type, const Position& source, const Position& dest) noexcept
				: type(type), dest(dest), source(source)  {}

			inline bool operator()(const Move& m) const {
				return m.isCapture() and
					m.getType() == type and
					m.getSource() == source and
					m.getDestination() == dest;
			}
		private:
			char type;
			Position dest;
			Position source;
		};

		struct MoveSet::find_captureR_by_piece {
			find_captureR_by_piece(const char& type, const int& source_h, const Position& dest) noexcept
				: type(type), source_h(source_h), dest(dest) {}

			inline bool operator()(const Move& m) const {
				return m.isCapture() and
					m.getType() == type and
					m.getSource().checkH()== source_h and
					m.getDestination() == dest;
			}
		private:
			char type;
			int source_h;
			Position dest;
		};

		struct MoveSet::find_captureF_by_piece {
			find_captureF_by_piece(const char& type, const int& source_w, const Position& dest) noexcept
				: type(type), source_w(source_w), dest(dest) {}

			inline bool operator()(const Move& m) const {
				return m.isCapture() and
					m.getType() == type and
					m.getSource().checkW() == source_w and
					m.getDestination() == dest;
			}
		private:
			char type;
			Position dest;
			int source_w;
		};

		struct MoveSet::find_kingside {
			inline bool operator()(const Move& m) const {return m.isCastleKingside();}
		};

		struct MoveSet::find_queenside {
			inline bool operator()(const Move& m) const {return m.isCastleQueenside();}
		};

		struct MoveSet::find_promote {
			find_promote(const int& w)
				: w(w) {}
			inline bool operator()(const Move& m) const { return m.isPromotion() and m.getDestination().checkW() == w; }
		private:
			int w;
		};

		Position MoveSet::findMove(const char& type, const Position& dest, const Board& b) const {
			int available = std::count_if(Set.begin(),
				Set.begin() + size,
				find_move_by_piece(type, dest));
			if (available != 1) {
				if (available > 1 and MODE == DEBUG) {
					std::cout << "More than 1 piece can make this move" << std::endl;
				}
				return { -1,-1 };
			}
			auto it = std::find_if(Set.begin(),
				Set.begin() + size,
				find_move_by_piece(type, dest));
			return it->getSource();
		}
		

		Position MoveSet::findMoveDA(const char& type, const Position& source, const Position& dest, const Board& b) const {
			if (MODE == DEBUG) {
				std::cout << "From " << source.checkH()<< " " << source.checkW() << " to " << dest.checkH()<< " " << dest.checkW() << std::endl;
			}
			int available = std::count_if(Set.begin(),
				Set.begin() + size,
				find_moveDA_by_piece(type, source, dest));
			if (available != 1) {
				if (available > 1 and MODE == DEBUG) {
					std::cout << "More than 2 pieces can make this move" << std::endl;
				}
				return { -1,-1 };
			}
			auto it = std::find_if(Set.begin(),
				Set.begin() + size,
				find_moveDA_by_piece(type, source, dest));
			return it->getSource();
		}

		Position MoveSet::findMoveR(const char& type, const int& source_h, const Position& dest, const Board& b) const {
			int available = std::count_if(Set.begin(),
				Set.begin() + size,
				find_moveR_by_piece(type, source_h, dest));
			if (available != 1) {
				if (MODE == DEBUG) {
					std::cout << "More than 2 pieces can make this move" << std::endl;
				}
				return { -1,-1 };
			}
			auto it = std::find_if(Set.begin(),
				Set.begin() + size,
				find_moveR_by_piece(type, source_h, dest));
			return it->getSource();
		}

		Position MoveSet::findMoveF(const char& type, const int& source_w, const Position& dest, const Board& b) const {
			int available = std::count_if(Set.begin(),
				Set.begin() + size,
				find_moveF_by_piece(type, source_w, dest));
			if (available != 1) {
				if (MODE == DEBUG) {
					std::cout << "More than 2 pieces can make this move" << std::endl;
				}
				return { -1,-1 };
			}
			auto it = std::find_if(Set.begin(),
				Set.begin() + size,
				find_moveF_by_piece(type, source_w, dest));
			return it->getSource();
		}

		Position MoveSet::findCapture(const char& type, const Position& dest, const Board& b) const {
			int available = std::count_if(Set.begin(),
				Set.begin() + size,
				find_capture_by_piece(type, dest));
			if (available != 1) {
				if (MODE == DEBUG) {
					std::cout << "More than 1 piece can make this move" << std::endl;
				}
				return { -1,-1 };
			}
			auto it = std::find_if(Set.begin(),
				Set.begin() + size,
				find_capture_by_piece(type, dest));
			return it->getSource();
		}

		Position MoveSet::findCaptureDA(const char& type, const Position& source, const Position& dest, const Board& b) const {
			int available = std::count_if(Set.begin(),
				Set.begin() + size,
				find_captureDA_by_piece(type, source, dest));
			if (available != 1) {
				if (MODE == DEBUG) {
					std::cout << "More than 2 pieces can make this move" << std::endl;
				}
				return { -1,-1 };
			}
			auto it = std::find_if(Set.begin(),
				Set.begin() + size,
				find_captureDA_by_piece(type, source, dest));
			return it->getSource();
		}

		Position MoveSet::findCaptureR(const char& type, const int& source_h, const Position& dest, const Board& b) const {
			int available = std::count_if(Set.begin(),
				Set.begin() + size,
				find_captureR_by_piece(type, source_h, dest));
			if (available != 1) {
				if (MODE == DEBUG) {
					std::cout << "More than 2 pieces can make this move" << std::endl;
				}
				return { -1,-1 };
			}
			auto it = std::find_if(Set.begin(),
				Set.begin() + size,
				find_captureR_by_piece(type, source_h, dest));
			return it->getSource();
		}

		Position MoveSet::findCaptureF(const char& type, const int& source_w, const Position& dest, const Board& b) const {
			int available = std::count_if(Set.begin(),
				Set.begin() + size,
				find_captureF_by_piece(type, source_w, dest));
			if (available != 1) {
				if (MODE == DEBUG) {
					std::cout << "More than 2 pieces can make this move" << std::endl;
				}
				return { -1,-1 };
			}
			auto it = std::find_if(Set.begin(),
				Set.begin() + size,
				find_captureF_by_piece(type, source_w, dest));
			return it->getSource();
		}

		bool MoveSet::findKingsideCastling(const Board& b) const {
			auto it = std::find_if(Set.begin(),
				Set.begin() + size,
				find_kingside());
			return it != Set.begin() + size;
		}

		bool MoveSet::findQueensideCastling(const Board& b) const {
			auto it = std::find_if(Set.begin(),
				Set.begin() + size,
				find_queenside());
			return it != Set.begin() + size;
		}

		Position MoveSet::findPromote(const Position& dest, const Board& b) const {
			auto it = std::find_if(Set.begin(),
				Set.begin() + size,
				find_promote(dest.checkW()));
			if (it != Set.end()) {
				return it->getSource();
			}
			return { -1, -1 };
		}
	}
}