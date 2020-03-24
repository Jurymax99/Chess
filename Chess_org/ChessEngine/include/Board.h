#pragma once
#include <vector>
#include <set>
#include "Tile.h"


namespace Chess {
	namespace Engine {
		class Board {

			typedef std::vector <Tile> Row;
			typedef std::vector <Row> Matrix;
			
		private:
			int height, width, pieces;
			Matrix main;
			std::vector <Pieces::Piece> GreenDead;
			std::vector <Pieces::Piece> RedDead;
			struct PositionState {
				int h, w;
				bool empty = true;

				bool operator <(const PositionState& rhs) const;
			};
			std::set <PositionState, std::less<PositionState>> RedThreat;
			std::set <PositionState, std::less<PositionState>> GreenThreat;
			int redScore, greenScore;
			struct Position {
				int h, w;
			} redKing, greenKing;

			struct EnPassant {
				int h, w;
				bool possible = false;
			} target;
			
			bool inBound					(int h, int w)	const;
			bool contains					(char c, std::string word) const;
			bool hasFriendly				(char type, int h, int w, int player) const;
			bool hasEnemy					(char type, int h, int w, int player) const;
			bool rank						(char a) const;
			bool file						(char a) const;
			bool isChecked					(int& player);

			bool makeMove					(char type, int orig_h, int orig_w, int h, int w, int player);
			bool makeCapture				(char type, int orig_h, int orig_w, int h, int w, int player);
			bool makeCapture				(char type, char typepro, int orig_h, int orig_w, int h, int w, int player);

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
			bool knightMove					(int h, int w, int player);
			bool knightAmbiguousMove		(char dis, int h, int w, int player);
			bool knightMoveRank				(int rank, int h, int w, int player);
			bool knightMoveFile				(int file, int h, int w, int player);
			bool knightCapture				(int h, int w, int player);
			bool knightAmbiguousCapture		(char dis, int h, int w, int player);
			bool knightCaptureRank			(int rank, int h, int w, int player);
			bool knightCaptureFile			(int file, int h, int w, int player);

			//Rook
			bool rookMove					(int h, int w, int player);
			bool rookAmbiguousMove			(char dis, int h, int w, int player);
			bool rookMoveRank				(int rank, int h, int w, int player);
			bool rookMoveFile				(int file, int h, int w, int player);
			bool rookCapture				(int h, int w, int player);
			bool rookAmbiguousCapture		(char dis, int h, int w, int player);
			bool rookCaptureRank			(int rank, int h, int w, int player);
			bool rookCaptureFile			(int file, int h, int w, int player);

			//Bishop
			bool bishopMove					(int h, int w, int player);
			bool bishopAmbiguousMove		(char dis, int h, int w, int player);
			bool bishopMoveRank				(int rank, int h, int w, int player);
			bool bishopMoveFile				(int file, int h, int w, int player);
			bool bishopDoubleAmbiguousMove	(int h_s, int w_s, int h_d, int w_d, int player);
			bool bishopCapture				(int h, int w, int player);
			bool bishopAmbiguousCapture		(char dis, int h, int w, int player);
			bool bishopCaptureRank			(int rank, int h, int w, int player);
			bool bishopCaptureFile			(int file, int h, int w, int player);
			bool bishopDoubleAmbiguousCapture(int h_s, int w_s, int h_d, int w_d, int player);

			//Queen
			bool queenMove					(int h, int w, int player);
			bool queenAmbiguousMove			(char dis, int h, int w, int player);
			bool queenMoveRank				(int rank, int h, int w, int player);
			bool queenMoveFile				(int file, int h, int w, int player);
			bool queenDoubleAmbiguousMove	(int h_s, int w_s, int h_d, int w_d, int player);
			bool queenCapture				(int h, int w, int player);
			bool queenAmbiguousCapture		(char dis, int h, int w, int player);
			bool queenCaptureRank			(int rank, int h, int w, int player);
			bool queenCaptureFile			(int file, int h, int w, int player);
			bool queenDoubleAmbiguousCapture(int h_s, int w_s, int h_d, int w_d, int player);

			//King
			bool kingMove					(int h, int w, int player);
			bool kingCapture				(int h, int w, int player);

			//Castling
			bool castleKingside				(int player);
			bool castleQueenside			(int player);

			void addGreenDead				(Pieces::Piece);
			void addRedDead					(Pieces::Piece);

			void checkGreenDeadDebug() const;
			void checkRedDeadDebug() const;
			void checkGreenDeadRelease() const;
			void checkRedDeadRelease() const;

			void checkRedThreats() const;
			void checkGreenThreats() const;

			void checkRedKing() const;
			void checkGreenKing() const;

			void updateRedThreats();
			void updateGreenThreats();

			void print_blank(int par);
			void printBoardRelease();
			void printBoardDebug();
		public:
			Board();
			~Board();

			void printBoard(int mode);
			bool move(std::string movement, int player, bool& enp);
			bool isChecked					();
			void updateThreats();
		};
	}
}