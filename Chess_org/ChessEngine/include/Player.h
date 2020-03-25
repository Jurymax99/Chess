#pragma once
#include <vector>
#include <set>
#include "Piece.h"

namespace Chess {
	namespace Engine {

		class Board;

		class Player {
		private:
			int color;
			std::vector <Pieces::Piece> Dead;
			struct PositionState {
				int h, w;
				bool empty = true;

				bool operator <(const PositionState& rhs) const;
			};
			std::set <PositionState, std::less<PositionState>> Threat;
			int score;
			struct Position {
				int h, w;
			} king;

		public:
			Player();
			Player(int color);
			void addDead(Pieces::Piece piece);
			bool findDead(int i, int j);
			bool findThreat(int i, int j, bool cond);
			bool findThreat(Position p, bool cond);
			Position checkKingPosition();
			void checkKing() const;
			void setKing(int h, int w);
			void addScore(int score);

			friend void updateThreats(Player& p, Board& b);

			void checkDeadRelease() const;
			void checkDeadDebug();
			int checkScore() const;
			void checkThreats() const;
		};
	}
}