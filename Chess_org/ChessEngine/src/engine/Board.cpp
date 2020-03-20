#include "Board.h"

namespace Chess {
	namespace Engine {
		Board::Board()
		{
			height = 8;
			width = 8;
			pieces = 32;
			main = Matrix(8, Row(8));
			GreenDead = std::vector <char>();
			BlueDead = std::vector <char>();
			std::cout << "Standard 8x8 board created with 32 pieces" << std::endl;

			//Green pieces
			main[0][0].addPiece('R', GREEN);
			main[0][1].addPiece('N', GREEN);
			main[0][2].addPiece('B', GREEN);
			main[0][3].addPiece('Q', GREEN);
			main[0][4].addPiece('K', GREEN);
			main[0][5].addPiece('B', GREEN);
			main[0][6].addPiece('N', GREEN);
			main[0][7].addPiece('R', GREEN);
			main[1][0].addPiece('P', GREEN);
			main[1][1].addPiece('P', GREEN);
			main[1][2].addPiece('P', GREEN);
			main[1][3].addPiece('P', GREEN);
			main[1][4].addPiece('P', GREEN);
			main[1][5].addPiece('P', GREEN);
			main[1][6].addPiece('P', GREEN);
			main[1][7].addPiece('P', GREEN);

			//Blue pieces
			main[6][0].addPiece('P', BLUE);
			main[6][1].addPiece('P', BLUE);
			main[6][2].addPiece('P', BLUE);
			main[6][3].addPiece('P', BLUE);
			main[6][4].addPiece('P', BLUE);
			main[6][5].addPiece('P', BLUE);
			main[6][6].addPiece('P', BLUE);
			main[6][7].addPiece('P', BLUE);
			main[7][0].addPiece('R', BLUE);
			main[7][1].addPiece('N', BLUE);
			main[7][2].addPiece('B', BLUE);
			main[7][3].addPiece('Q', BLUE);
			main[7][4].addPiece('K', BLUE);
			main[7][5].addPiece('B', BLUE);
			main[7][6].addPiece('N', BLUE);
			main[7][7].addPiece('R', BLUE);

			//DEBUG

			/*main[2][4].addPiece('Q', BLUE);
			main[4][4].addPiece('Q', BLUE);
			main[2][6].addPiece('Q', BLUE);
			main[3][5].addPiece('P', GREEN);*/

			//Blue pieces
			/*main[6][0].addPiece('P', BLUE);
			main[6][1].addPiece('P', BLUE);
			main[6][2].addPiece('P', BLUE);
			main[6][3].addPiece('P', BLUE);
			main[6][4].addPiece('P', BLUE);
			main[6][5].addPiece('P', BLUE);
			main[6][6].addPiece('P', BLUE);
			main[6][7].addPiece('P', BLUE);
			main[7][5].addPiece('K', BLUE);
			main[7][1].addPiece('N', BLUE);
			main[7][2].addPiece('B', BLUE);
			main[7][3].addPiece('Q', BLUE);
			main[7][4].addPiece('K', BLUE);
			main[7][5].addPiece('B', BLUE);
			main[7][6].addPiece('N', GREEN);
			main[6][5].addPiece('N', GREEN);
			main[7][7].addPiece('K', BLUE);*/

		}

		Board::~Board() {
			std::cout << "Board destroyed: " << std::endl;
		}

		void Board::printBoard() {
			std::cout << "__________________________________________" << std::endl;
			checkBlueDead();
			checkGreenDead();
			std::cout << "__________________________________________" << std::endl;
			std::cout << "   A    B    C    D    E    F    G    H" << std::endl;
			Color::Modifier blue(Color::FG_BLUE);
			Color::Modifier green(Color::FG_GREEN);
			Color::Modifier def(Color::FG_DEFAULT);
			for (int i = 0; i < 8; ++i) {
				std::cout << -i + 8 << "  ";
				for (int j = 0; j < 8; ++j) {
					//Print piece name if it has piece
					if (main[i][j].hasPiece()) {
						if (main[i][j].checkPlayer() == BLUE) {
							std::cout << blue << main[i][j].checkPieceType() << def << "    ";
						}
						else if (main[i][j].checkPlayer() == GREEN) {
							std::cout << green << main[i][j].checkPieceType() << def << "    ";
						}
						else {
							std::cout << std::endl << "ERROR::Pieces created with no player" << std::endl;
						}
					}
					else {
						std::cout << ".    ";
					}
				}
				std::cout << '\b' << -i + 8 << std::endl << std::endl;
			}
			std::cout << "   A    B    C    D    E    F    G    H" << std::endl;
		}

		bool Board::inBound(int h, int w) const {
			std::cout << "Checking [" << h << ", " << w << "]" << std::endl;
			return w >= 0 and w <= 7 and h >= 0 and h <= 7;
		}

		bool Board::contains(char c, std::string word) const {
			for (int i = 0; i < word.size(); ++i) {
				if (c == word[i]) {
					return true;
				}
			}
			return false;
		}

		bool Board::rank(char a) const {
			return a >= '1' and a <= '8';
		}

		bool Board::file(char a) const {
			return a >= 'a' and a <= 'h';
		}

		void Board::addGreenDead(char piece)
		{
			GreenDead.push_back(piece);
			std::sort(GreenDead.begin(), GreenDead.end());
		}

		void Board::addBlueDead(char piece)
		{
			BlueDead.push_back(piece);
			std::sort(BlueDead.begin(), BlueDead.end());
		}

		void Board::checkGreenDead() const {
			std::cout << "Dead green pieces: ";
			for (int i = 0; i < GreenDead.size(); ++i) {
				std::cout << GreenDead[i] << " ";
			}
			std::cout << std::endl;
		}

		void Board::checkBlueDead() const {
			std::cout << "Dead blue pieces: ";
			for (int i = 0; i < BlueDead.size(); ++i) {
				std::cout << BlueDead[i] << " ";
			}
			std::cout << std::endl;
		}

		//TODO: 
		//		-en passant?
		//		-check detection
		//		-checkmate detection
		//		-go back funtionality
		//		-flip board
		//		-count pieces
		//			-left
		//			-per player
		//			-warnings at start if dif than 32
		//		-read instructions from file
		//		-interactive GUI

		//CHANGELOG:
		//		-Added ambiguous moves:
		//			-knight 
		//			-rook 
		//			-bishop 
		//			-queen 
		//			-king (possible?) 
		//		-Added single ambiguous captures:
		//			-knight 
		//			-rook 
		//			-bishop 
		//			-queen 
		//			-king (possible?) 
		//		-Added double ambiguity moves and captures
		//			-bishop
		//			-queen
		//		-Added pawn promotion:
		//			-by moving e.g. b8=Q X
		//			-by moving e.g. axb7=Q
		//		-Added castling
		//		-Added read mode, to directly read pgn formatted matches

		bool Board::move(std::string movement, int player) {
			int rank_d, file_d;
			std::cout << "Your movement was " << movement << std::endl;
			if (movement.length() == 0) {
				return false;
			}

			//normal pawn move
			else if (movement.length() == 2) {
				rank_d = 8 - (movement[1] - 48);
				file_d = movement[0] - 97;
				return pawnMove(rank_d, file_d, player);
			}

			//non-ambiguous other moves
			else if (movement.length() == 3) {
				rank_d = 8 - (movement[2] - 48);
				file_d = movement[1] - 97;
				//normal knight move
				if (movement[0] == 'N') {
					return knightMove(rank_d, file_d, player);
				}
				//normal rook move
				if (movement[0] == 'R') {
					return rookMove(rank_d, file_d, player);
				}
				//normal bishop move
				if (movement[0] == 'B') {
					return bishopMove(rank_d, file_d, player);
				}
				//normal queen move
				if (movement[0] == 'Q') {
					return queenMove(rank_d, file_d, player);
				}
				//normal king move
				if (movement[0] == 'K') {
					return kingMove(rank_d, file_d, player);
				}
				if (movement == "O-O" or movement == "0-0") {
					std::cout << "Kingside castling detected!" << std::endl;
					return castleKingside(player);
				}
			}

			//longer instructions
			else if (movement.length() == 4) {
				//captures
				if (contains('x', movement)) {
					std::cout << "Capture detected!" << std::endl;
					//if first letter is lowercase it is a pawn capture
					rank_d = 8 - (movement[3] - 48);
					file_d = movement[2] - 97;
					if (islower(movement[0])) {
						//p.e: exf5
						int file_s = movement[0] - 97;
						return pawnCapture(file_s, rank_d, file_d, player);
					}
					//normal knight capture
					if (movement[0] == 'N') {
						return knightCapture(rank_d, file_d, player);
					}
					//normal rook capture
					if (movement[0] == 'R') {
						return rookCapture(rank_d, file_d, player);
					}
					//normal bishop capture
					if (movement[0] == 'B') {
						return bishopCapture(rank_d, file_d, player);
					}
					//normal queen capture
					if (movement[0] == 'Q') {
						return queenCapture(rank_d, file_d, player);
					}
					//normal king capture
					if (movement[0] == 'K') {
						return kingCapture(rank_d, file_d, player);
					}
				}
				else if (contains('=', movement)) {
					std::cout << "Promotion detected!" << std::endl;
					rank_d = 8 - (movement[1] - 48);
					file_d = movement[0] - 97;
					char type = movement[3];
					return pawnPromote(rank_d, file_d, type, player);
				}
				//ambiguous moves
				else {
					rank_d = 8 - (movement[3] - 48);
					file_d = movement[2] - 97;
					char dis = movement[1];
					//knight
					if (movement[0] == 'N') {
						return knightAmbiguousMove(dis, rank_d, file_d, player);
					}
					//rook
					if (movement[0] == 'R') {
						return rookAmbiguousMove(dis, rank_d, file_d, player);
					}
					//bishop
					if (movement[0] == 'B') {
						return bishopAmbiguousMove(dis, rank_d, file_d, player);
					}
					//queen
					if (movement[0] == 'Q') {
						return queenAmbiguousMove(dis, rank_d, file_d, player);
					}
					//king?
					if (movement[0] == 'K') {
						return kingAmbiguousMove(dis, rank_d, file_d, player);
					}
				}
			}
			//ambiguous captures
			else if (movement.length() == 5) {
				if (contains('x', movement)) {
					std::cout << "Capture detected!" << std::endl;
					rank_d = 8 - (movement[4] - 48);
					file_d = movement[3] - 97;
					char dis = movement[1];
					//knight
					if (movement[0] == 'N') {
						return knightAmbiguousCapture(dis, rank_d, file_d, player);
					}
					//rook
					if (movement[0] == 'R') {
						return rookAmbiguousCapture(dis, rank_d, file_d, player);
					}
					//bishop
					if (movement[0] == 'B') {
						return bishopAmbiguousCapture(dis, rank_d, file_d, player);
					}
					//queen
					if (movement[0] == 'Q') {
						return queenAmbiguousCapture(dis, rank_d, file_d, player);
					}
					//king?
					if (movement[0] == 'K') {
						return kingAmbiguousCapture(dis, rank_d, file_d, player);
					}
				}
				if (movement == "O-O-O" or movement == "0-0-0") {
					std::cout << "Queenside castling detected!" << std::endl;
					return castleQueenside(player);
				}
				//double ambiguous move
				else {
					std::cout << "Double ambiguous detected!" << std::endl;
					rank_d = 8 - (movement[4] - 48);
					file_d = movement[3] - 97;
					int rank_s = 8 - (movement[2] - 48);
					int file_s = movement[1] - 97;
					//bishop
					if (movement[0] == 'B') {
						return bishopDoubleAmbiguousMove(rank_s, file_s, rank_d, file_d, player);
					}
					//queen
					if (movement[0] == 'Q') {
						return queenDoubleAmbiguousMove(rank_s, file_s, rank_d, file_d, player);
					}
				}
			}

			//longer instructions
			else if (movement.length() == 6) {
				if (contains('x', movement)) {
					//pawn promotion capture
					if (contains('=', movement)) {
						std::cout << "Promotion detected!" << std::endl;
						rank_d = 8 - (movement[3] - 48);
						file_d = movement[2] - 97;
						char type = movement[5];
						int file_s = movement[0] - 97;
						return pawnPromoteCapture(file_s, rank_d, file_d, type, player);
					}
					//double ambiguous capture
					else {
						std::cout << "Capture detected!" << std::endl;
						rank_d = 8 - (movement[5] - 48);
						file_d = movement[4] - 97;
						int rank_s = 8 - (movement[2] - 48);
						int file_s = movement[1] - 97;
						//bishop
						if (movement[0] == 'B') {
							return bishopDoubleAmbiguousCapture(rank_s, file_s, rank_d, file_d, player);
						}
						//queen
						if (movement[0] == 'Q') {
							return queenDoubleAmbiguousCapture(rank_s, file_s, rank_d, file_d, player);
						}
					}
				}
			}
			return false;
		}
	}
}