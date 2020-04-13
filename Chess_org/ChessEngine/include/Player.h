#pragma once
#include "MoveSet.h"
#include <vector>
#include <set>
#include <algorithm>

namespace Chess {
	namespace Engine {

		class Board;
		class MoveSet;

		class Player {
		protected:
			int color, score, pieceCount;
			std::vector <char> Dead;
			Position king;
			bool castleKing, castleQueen;

		private:
			void addKnight(Board& b, const int& i, const int& j);
			void addRookLike(Board& b, const int& i, const int& j);
			void addBishopLike(Board& b, const int& i, const int& j);

		public:
			MoveSet moves;
			Player();
			Player(int color);

			void addDead(const char& piece);
			void updateThreats(Board& b, const bool& clean);

			inline Position findMove(char type, const Position& dest, const Board& b) const { return  moves.findMove(type, dest, b); }
			inline Position findAmbRMove(char type, int source_h, const Position& dest, const Board& b) const { return  moves.findMoveR(type, source_h, dest, b); }
			inline Position findAmbFMove(char type, int source_w, const Position& dest, const Board& b) const { return  moves.findMoveF(type, source_w, dest, b); }
			inline Position findDAmbMove(char type, const Position& source, const Position& dest, const Board& b) const { return moves.findMoveDA(type, source, dest, b); }
			inline Position findCapture(char type, const Position& dest, const Board& b) const { return  moves.findCapture(type, dest, b); }
			inline Position findAmbRCapture(char type, int source_h, const Position& dest, const Board& b) const { return  moves.findCaptureR(type, source_h, dest, b); }
			inline Position findAmbFCapture(char type, int source_w, const Position& dest, const Board& b) const { return  moves.findCaptureF(type, source_w, dest, b); }
			inline Position findDAmbCapture(char type, const Position& source, const Position& dest, const Board& b) const{ return moves.findCaptureDA(type, source, dest, b); }
			inline bool findKingsideCastling(const Board& b) const {return moves.findKingsideCastling(b);}
			inline bool findQueensideCastling(const Board& b) const {return moves.findQueensideCastling(b);}
			
			void checkDeadRelease() const;
			void checkDeadDebug() const;

			inline int checkPieceCount() const { return pieceCount; };

			inline void setPieceCount(const int& count) { pieceCount = count; };

			inline void setCastleKing(const bool& cond) { castleKing = cond; }

			inline void setCastleQueen(const bool& cond) { castleQueen = cond; }

			inline bool checkCastleKing() const { return castleKing; }

			inline bool checkCastleQueen() const { return castleQueen; }
			
			inline void setKing(int h, int w) { king = { h,w }; }
			
			inline Position checkKingPosition() const{return king;}
			
			inline void checkKing() const { std::cout << "king is at [" << char(king.checkW() + 97) << char(8 - char(king.checkH() - 48)) << "]" << std::endl; }
			
			inline void checkMoves() const { if (MODE == DEBUG) moves.checkDebug(color); };

			inline bool hasMoves() const { return not moves.empty(); }
			
			inline void addScore(int score){this->score += score;}
			
			inline int checkScore() const { return score; }

			inline int checkColor() const { return color; }
			
			inline void updateMoveSet(Board& b) {moves.update(color, pieceCount, b);}

		};
	}
}