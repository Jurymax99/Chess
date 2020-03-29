#pragma once
#include <vector>
#include <set>
#include "Piece.h"
#include "Utilities.h"
#include "MoveSet.h"

namespace Chess {
	namespace Engine {

		class Board;
		class MoveSet;

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
			Position king;
			MoveSet moves;

		public:
			Player();
			Player(int color);
			void addDead(Pieces::Piece piece);
			bool findThreat(int i, int j);
			bool findThreat(int i, int j, bool cond);
			bool findThreat(Position p, bool cond);
			Position checkKingPosition();
			void checkKing() const;
			void setKing(int h, int w);
			void addScore(int score);

			Position findMove(char type, Position dest, Board& b);
			Position findCapture(char type, Position dest, Board& b);
			Position findAmbRMove(char type, int source_h, Position dest, Board& b);
			Position findAmbFMove(char type, int souce_w, Position dest, Board& b);

			void updateThreats(Board& b);
			void updateMoveSet(Board& b);

			bool hasMoves() const;
			void checkMoves() const;
			void checkDeadRelease() const;
			void checkDeadDebug() const;
			int checkScore() const;
			void checkThreats() const;
		};
	}
}