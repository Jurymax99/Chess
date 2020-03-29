#pragma once
#include <vector>
#include <set>
#include "Tile.h"
#include "Player.h"
#include "MoveSet.h"

namespace Chess {
	namespace Engine {

		class Player;
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
			
			bool inBound					(int h, int w)	const;
			bool contains					(char c, std::string word) const;
			bool hasFriendly				(char type, int h, int w, int player) const;
			bool hasFriendly				(int h, int w, int player) const;
			bool hasEnemy					(char type, int h, int w, int player) const;
			bool hasEnemy					(int h, int w, int player) const;
			bool rank						(char a) const;
			bool file						(char a) const;
			bool isChecked					(int& player);
			bool isChecked					();
			bool areBothChecked				();

			bool findMove					(char type, Position dest, int player);
			bool findCapture				(char type, Position dest, int player);
			bool findAmbiguousMove			(char type, char dis, Position dest, int player);

			bool makeMove					(char type, int orig_h, int orig_w, int h, int w, int player);
			bool makeCapture				(char type, int orig_h, int orig_w, int h, int w, int player);
			bool makeCapture				(char type, char typepro, int orig_h, int orig_w, int h, int w, int player);

			bool makeFakeMove				(char type, int orig_h, int orig_w, int h, int w, int player, bool& check);
			bool makeFakeCapture			(char type, int orig_h, int orig_w, int h, int w, int player, bool& check);
			bool makeFakeMovePro			(int orig_h, int orig_w, int h, int w, int player, bool& check);
			bool makeFakeCapturePro			(int orig_h, int orig_w, int h, int w, int player, bool& check);
			bool makeFakeEnPassant			(int orig_h, int orig_w, int dest_h, int dest_w, int killed_h, int killed_w, int player, bool& check);

			//Pawn
			bool pawnMove					(int h, int w, int player);
			bool pawnRedMove				(int h, int w);
			bool pawnGreenMove				(int h, int w);
			bool pawnPromote				(int h, int w, char type, int player);
			bool pawnRedPromote				(int h, int w, char type);
			bool pawnGreenPromote			(int h, int w, char type);
			bool pawnCapture				(int w_s, int h_d, int w_d, int player, bool enpassant);
			bool pawnRedCapture				(int w_s, int h_d, int w_d, bool enpassant);
			bool pawnGreenCapture			(int w_s, int h_d, int w_d, bool enpassant);
			bool pawnPromoteCapture			(int w_s, int h_d, int w_d, char type, int player);
			bool pawnRedPromoteCapture		(int w_s, int h_d, int w_d, char type);
			bool pawnGreenPromoteCapture	(int w_s, int h_d, int w_d, char type);
			
			//Knight
			bool knightAmbiguousCapture		(char dis, int h, int w, int player);
			bool knightCaptureRank			(int rank, int h, int w, int player);
			bool knightCaptureFile			(int file, int h, int w, int player);

			//Rook
			bool rookAmbiguousCapture		(char dis, int h, int w, int player);
			bool rookCaptureRank			(int rank, int h, int w, int player);
			bool rookCaptureFile			(int file, int h, int w, int player);

			//Bishop
			bool bishopDoubleAmbiguousMove	(int h_s, int w_s, int h_d, int w_d, int player);
			bool bishopAmbiguousCapture		(char dis, int h, int w, int player);
			bool bishopCaptureRank			(int rank, int h, int w, int player);
			bool bishopCaptureFile			(int file, int h, int w, int player);
			bool bishopDoubleAmbiguousCapture(int h_s, int w_s, int h_d, int w_d, int player);

			//Queen
			bool queenDoubleAmbiguousMove	(int h_s, int w_s, int h_d, int w_d, int player);
			bool queenAmbiguousCapture		(char dis, int h, int w, int player);
			bool queenCaptureRank			(int rank, int h, int w, int player);
			bool queenCaptureFile			(int file, int h, int w, int player);
			bool queenDoubleAmbiguousCapture(int h_s, int w_s, int h_d, int w_d, int player);

			//Castling
			bool castleKingside				(int player);
			bool castleQueenside			(int player);
			bool castleFakeKingside			(int player, bool& check);
			bool castleFakeQueenside		(int player, bool& check);

			void print_blank(int par);
			void printBoardRelease();
			void printBoardDebug();
		public:
			friend class Player;
			friend class MoveSet;

			Board();
			~Board();

			void printBoard();
			bool move(std::string movement, int player, bool& enp);
			void update();
			bool isCheckmate				(int player) const;
		};
	}
}