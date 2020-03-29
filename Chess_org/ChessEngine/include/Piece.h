#pragma once
#include <iostream>

namespace Chess {
	namespace Pieces {
		class Piece {
		private:
			int color;
			bool first = true;
			char type;
		public:
			Piece();
			void newPlayer(int newPlayer);
			void newType(char newType);
			int checkColor() const;
			char checkType() const;
			bool isFirst() const;
			int checkPoints() const;
			bool operator <(const Piece& rhs) const;
			void firstMove();
		};
	}
}
