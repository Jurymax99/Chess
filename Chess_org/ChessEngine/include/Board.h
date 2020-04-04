#pragma once
#include <vector>
#include <set>
#include "Tile.h"
#include "Player.h"
#include "MoveSet.h"

namespace Chess {
	namespace Engine {

		class Player;
		class Dummy;
		class MoveSet;

		class Board {

			typedef std::vector <Tile> Row;
			typedef std::vector <Row> Matrix;
			
		private:
			int height, width, pieces;
			Matrix main;
			Player Red, Green;
			struct EnPassant {
				int h, w;
				bool possible = false;
			} target;
			
			bool contains					(char c, std::string word) const;
			bool hasFriendly				(char type, int h, int w, int player) const;
			bool hasFriendly				(int h, int w, int player) const;
			bool hasEnemy					(char type, int h, int w, int player) const;
			bool hasEnemy					(int h, int w, int player) const;
			bool isChecked					();
			bool isChecked					(int& player);
			int	whoChecked					(int& player);
			bool areBothChecked				();

			bool findMove					(char type, const Position& dest, int player);
			bool findCapture				(char type, const Position& dest, int player);
			bool findAmbiguousMove			(char type, char dis, const Position& dest, int player);
			bool findDoubleAmbiguousMove	(char type, int source_h, int source_w, const Position& dest, int player);
			bool findAmbiguousCapture		(char type, char dis, const Position& dest, int player);
			bool findDoubleAmbiguousCapture	(char type, int source_h, int source_w, const Position& dest, int player);

			bool makeMove					(char type, int orig_h, int orig_w, int h, int w, int player, bool enp);
			bool makeCapture				(char type, int orig_h, int orig_w, int h, int w, int player);
			bool makeCapture				(char type, char typepro, int orig_h, int orig_w, int h, int w, int player);

			bool makeFakeMove				(char type, int orig_h, int orig_w, int h, int w, int player, bool& check);
			bool makeFakeCapture			(char type, int orig_h, int orig_w, int h, int w, int player, bool& check);
			bool makeFakeMovePro			(int orig_h, int orig_w, int h, int w, int player, bool& check);
			bool makeFakeCapturePro			(int orig_h, int orig_w, int h, int w, int player, bool& check);
			bool makeFakeEnPassant			(int orig_h, int orig_w, int dest_h, int dest_w, int killed_h, int killed_w, int player, bool& check);

			//Pawn
			bool pawnPromote				(int h, int w, char type, int player);
			bool pawnCapture				(int w_s, int h_d, int w_d, int player, bool enpassant);
			bool pawnPromoteCapture			(int w_s, int h_d, int w_d, char type, int player);

			//Castling
			bool castleKingside				(int player);
			bool castleQueenside			(int player);
			bool castleFakeKingside			(int player, bool& check);
			bool castleFakeQueenside		(int player, bool& check);

			void print_blank(int par) const;
			void printBoardRelease() const;
			void printBoardDebug() const;

			inline bool inBound(int h, int w) const { return w >= 0 and w <= 7 and h >= 0 and h <= 7; };
			
			inline bool rank(char a) const{ return a >= '1' and a <= '8'; }

			inline bool file(char a) const{ return a >= 'a' and a <= 'h'; }
			
		public:
			friend class Player;
			friend class MoveSet;

			Board();
			~Board();

			void printBoard() const;
			bool move						(std::string movement, int player, bool& enp);
			void update();

			enum class Ending : int {
				UNDEFINED = -1,
				STALEMATE,
				CHECKMATE,
				DRAW,
				FIFTYRULE,
				VICTORY,
				DEFEAT,
				RESIGN
			};
			
			bool isCheckmate				(int player, Ending& status);
		};
	}
}