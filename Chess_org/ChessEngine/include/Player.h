#pragma once
#include <vector>
#include <set>
#include "Piece.h"
#include "Utilities.h"
#include "MoveSet.h"
#include "PositionState.h"

namespace Chess {
	namespace Engine {

		class Board;
		class MoveSet;

		class Player {
		protected:
			int color, score, pieceCount;
			std::vector <Pieces::Piece> Dead;
			std::set <PositionState> Threat;
			Position king;
			MoveSet moves;

		public:
			Player();
			Player(int color);

			void addDead(Pieces::Piece piece);

			Position findMove(char type, const Position& dest, const Board& b) const;
			Position findAmbRMove(char type, int source_h, const Position& dest, const Board& b) const;
			Position findAmbFMove(char type, int souce_w, const Position& dest, const Board& b) const;
			Position findDAmbMove(char type, int source_h, int source_w, const Position& dest, const Board& b) const;
			Position findCapture(char type, const Position& dest, const Board& b) const;
			Position findAmbRCapture(char type, int source_h, const Position& dest, const Board& b) const;
			Position findAmbFCapture(char type, int souce_w, const Position& dest, const Board& b) const;
			Position findDAmbCapture(char type, int source_h, int source_w, const Position& dest, const Board& b) const;

			void updateThreats(const Board& b);
			void addKnight(const Board& b, const int& i, const int& j, const int& enemyColor);
			void addRookLike(const Board& b, const int& i, const int& j, const int& enemyColor);
			void addBishopLike(const Board& b, const int& i, const int& j, const int& enemyColor);
			
			void checkDeadRelease() const;
			void checkDeadDebug() const;
			void checkThreats() const;
			
			inline void setKing(int h, int w) { king = { h,w }; }
			
			inline Position checkKingPosition() const{return king;}
			
			inline void checkKing() const { std::cout << "king is at [" << char(king.w + 97) << char(8 - char(king.h - 48)) << "]" << std::endl; }

			
			inline void checkMoves() const { if (MODE == DEBUG) moves.checkDebug(color); };

			inline bool hasMoves() const { return not moves.empty(); }
			
			
			inline void addScore(int score){this->score += score;}
			
			inline int checkScore() const { return score; }

			inline int checkColor() const { return color; }

			inline int chackPiecesLeft() const { return pieceCount; }
			
			inline void updateMoveSet(Board& b) {moves.update(color, pieceCount, b);}

			

			inline bool findThreat(int i, int j) const{return Threat.find({ i,j,false }) != Threat.end();}

			inline bool findThreat(int i, int j, bool cond) const{return Threat.find({ i,j, cond }) != Threat.end();}

			inline bool findThreat(const Position& p, bool cond) const{return Threat.find({ p.h,p.w, cond }) != Threat.end();}

		};
	}
}