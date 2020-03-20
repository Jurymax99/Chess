#pragma once

namespace Chess {
	namespace Pieces {
		class Piece {
		protected:
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
			void firstMove();
		};
	}
}
