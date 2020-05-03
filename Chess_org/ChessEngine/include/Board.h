#pragma once
#include <vector>
#include "Tile.h"
#include "Player.h"

namespace Chess {
	namespace Engine {

		class Player;
		class MoveSet;

		class Board {
			
		private:
			int halfMoves, turn, pieces;
			Player Red, Green;

			struct ChessBoard {
				std::vector<Tile> main = std::vector<Tile>(64);
				inline Tile& operator()(const int& i, const int& j) noexcept{ return main[8 * i + j]; }
				inline const Tile& operator()(const int& i, const int& j) const noexcept { return main[8 * i + j]; }
				inline Tile& operator()(const Position& p) noexcept{ return main[8 * p.checkH() + p.checkW()]; }
				inline const Tile& operator()(const Position& p) const noexcept { return main[8 * p.checkH() + p.checkW()]; }
				inline Tile& operator()(const int& i) noexcept { return main[i]; }
				inline const Tile& operator()(const int& i) const noexcept { return main[i]; }
			} main;

			struct EnPassant {
				int h, w;
				bool possible = false;
			} target;
			
			bool contains					(char c, std::string word) const noexcept;
			bool whoChecked					(int& player);

			bool findMove					(char type, const Position& dest, int player);
			bool findCapture				(char type, const Position& dest, int player);
			bool findPromotion				(const Position& dest, char typePro, int player);
			bool findAmbiguousMove			(char type, char dis, const Position& dest, int player);
			bool findDoubleAmbiguousMove	(char type, const Position& source, const Position& dest, int player);
			bool findAmbiguousCapture		(char type, char dis, const Position& dest, int player);
			bool findDoubleAmbiguousCapture	(char type, const Position& source, const Position& dest, int player);
			bool findKingsideCastling		(int player);
			bool findQueensideCastling		(int player);

			bool makeMove					(const char& type, const Position& source, const Position& dest, const int& player, const bool& enp);
			bool makeFakeMove				(const char& type, const Position& source, const Position& dest, const int& player);
			bool makeFakeMovePro			(const Position& source, const Position& dest, const int& player);
			bool makeCapture				(char type, int orig_h, int orig_w, int h, int w, int player);
			bool makeCapture				(char type, char typepro, int orig_h, int orig_w, int h, int w, int player);

			bool makeFakeCapture			(char type, int orig_h, int orig_w, int h, int w, int player);
			bool makeFakeCapturePro			(int orig_h, int orig_w, int h, int w, int player);
			bool makeFakeEnPassant			(int orig_h, int orig_w, int dest_h, int dest_w, int killed_h, int killed_w, int player);

			//Pawn
			bool pawnCapture				(int w_s, int h_d, int w_d, int player, bool enpassant);
			bool pawnCapture				(const Position& source, const Position& dest, int player, bool enpassant);
			bool pawnPromote				(const Position& source, const Position& dest, const char& type, const int& player);
			bool pawnPromoteCapture			(int w_s, int h_d, int w_d, char type, int player);
			bool pawnPromoteCapture			(const Position& source, const Position& dest, char type, int player);

			//Castling
			bool castleKingside				(int player);
			bool castleQueenside			(int player);
			bool castleFakeKingside			(int player);
			bool castleFakeQueenside		(int player);

			void print_blank(int par) const;
			void printBoardRelease() const;
			void printBoardDebug();
			void printThreats() const;

			inline bool inBound(int h, int w) const noexcept { return w >= 0 and w <= 7 and h >= 0 and h <= 7; };
			
			inline bool rank(char a) const noexcept { return a >= '1' and a <= '8'; }

			inline bool file(char a) const noexcept { return a >= 'a' and a <= 'h'; }
			
			inline bool hasFriendly(char type, int h, int w, int player) const noexcept {
				return inBound(h, w) and
					main(h,w).hasPiece() and
					main(h, w).checkPieceType() == type and
					main(h, w).checkPlayer() == player;
			}

			inline bool hasFriendly(int h, int w, int player) const noexcept {
				return inBound(h, w) and
					main(h, w).hasPiece() and
					main(h, w).checkPlayer() == player;
			}

			inline bool hasEnemy(char type, int h, int w, int player) const {
					return hasFriendly(type, h, w, -player);
			}

			inline bool hasEnemy(int h, int w, int player) const {
				return hasFriendly(h, w, -player);
			}

		public:
			friend class Player;
			friend class Dummy;
			friend class MoveSet;

			Board();
			Board(const std::string& FEN);

			void printBoard();
			void createFEN() const;
			bool move						(std::string movement, bool& enp);
			bool move						(const Move& m);
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
			
			bool isEnded(int player, Ending& status);

			bool isEnded() const;

			bool isEnded(int player, int& checked, float& pen, bool& mate);

			int queenCount() const;

			bool hasQueen() const;

			inline int checkTurn() const noexcept { return turn; }

			inline int checkPlayer() const noexcept { return turn % 2 == 0 ? RED : GREEN; }

			inline int checkPieces() const noexcept { return pieces; }

			/*Board operator=(const Board& b); */

			Board(const Board& b);
		};
	}
}