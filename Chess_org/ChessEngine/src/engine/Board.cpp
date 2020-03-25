#include "Board.h"
#include <windows.h>

namespace Chess {
	namespace Engine {
		Board::Board() {
			height = 8;
			width = 8;
			pieces = 32;
			main = Matrix(8, Row(8));
			Red = Player(RED);
			Green = Player(GREEN);
			target = { -1, -1, false };
			std::cout << "Standard " << height << "x" << width << " board created with " << pieces << " pieces" << std::endl;

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

			//Red pieces
			main[6][0].addPiece('P', RED);
			main[6][1].addPiece('P', RED);
			main[6][2].addPiece('P', RED);
			main[6][3].addPiece('P', RED);
			main[6][4].addPiece('P', RED);
			main[6][5].addPiece('P', RED);
			main[6][6].addPiece('P', RED);
			main[6][7].addPiece('P', RED);
			main[7][0].addPiece('R', RED);
			main[7][1].addPiece('N', RED);
			main[7][2].addPiece('B', RED);
			main[7][3].addPiece('Q', RED);
			main[7][4].addPiece('K', RED);
			main[7][5].addPiece('B', RED);
			main[7][6].addPiece('N', RED);
			main[7][7].addPiece('R', RED);
		}

		Board::~Board() {
			std::cout << "Board destroyed" << std::endl;
		}

		void Board::printBoard(){
			if (MODE == RELEASE) {
				printBoardRelease();
			}
			else if (MODE == DEBUG) {
				printBoardDebug();
			}
			else {
				std::cout << "No known app mode" << std::endl;
			}
		}

		void Board::print_blank(int par) {
			HANDLE  hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			std::cout << "   ";
			for (int it = 0; it < 8; ++it) {
				if (it % 2 == par) {
					SetConsoleTextAttribute(hConsole, 255);
				}
				else {
					SetConsoleTextAttribute(hConsole, 0);
				}
				std::cout << "_______";
			}
			SetConsoleTextAttribute(hConsole, 0);
			std::cout << "_" << std::endl;
		}

		void Board::printBoardRelease() {
			std::cout << "_______________________________________________________________" << std::endl;
			Red.checkDeadRelease();
			if (Red.checkScore() < Green.checkScore()) {
				std::cout << "+" << Green.checkScore() - Red.checkScore();
			}
			std::cout << std::endl;
			Green.checkDeadRelease();
			if (Green.checkScore() < Red.checkScore()) {
				std::cout << "+" << Red.checkScore() - Green.checkScore();
			}
			std::cout << std::endl;
			std::cout << "_______________________________________________________________" << std::endl;
			std::cout << "      A      B      C      D      E      F      G      H" << std::endl;
			HANDLE  hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			for (int i = 0; i < 8; ++i) {
				print_blank(i % 2);
				SetConsoleTextAttribute(hConsole, 7);
				std::cout << -i + 8 << "  ";
				for (int j = 0; j < 8; ++j) {
					//Print piece name if it has piece
					if (main[i][j].hasPiece()) {
						if (abs(i - j) % 2 == 0) {
							if (main[i][j].checkPlayer() == RED) {
								SetConsoleTextAttribute(hConsole, 252);
							}
							else if (main[i][j].checkPlayer() == GREEN) {
								SetConsoleTextAttribute(hConsole, 242);
							}
							else {
								std::cout << std::endl << "ERROR::Pieces created with no player" << std::endl;
							}
							std::cout << "   " << main[i][j].checkPieceType() << "   ";
						}
						else {
							if (main[i][j].checkPlayer() == RED) {
								SetConsoleTextAttribute(hConsole, 12);
							}
							else if (main[i][j].checkPlayer() == GREEN) {
								SetConsoleTextAttribute(hConsole, 10);
							}
							else {
								std::cout << std::endl << "ERROR::Pieces created with no player" << std::endl;
							}
							std::cout << "   " << main[i][j].checkPieceType() << "   ";
						}
						SetConsoleTextAttribute(hConsole, 7);
					}
					else {
						if (abs(i - j) % 2 == 0) {
							SetConsoleTextAttribute(hConsole, 240);
						}
						else {
							SetConsoleTextAttribute(hConsole, 7);
						}
						std::cout << "       ";
						SetConsoleTextAttribute(hConsole, 7);
					}
				}
				SetConsoleTextAttribute(hConsole, 7);
				std::cout << "  " << -i + 8 << std::endl;
				print_blank(i % 2);
				SetConsoleTextAttribute(hConsole, 7);
			}
			std::cout << "      A      B      C      D      E      F      G      H" << std::endl;
		}

		void Board::printBoardDebug() {
			std::cout << "__________________________________________" << std::endl;
			Red.checkDeadDebug();
			if (Red.checkScore() < Green.checkScore()) {
				std::cout << "+" << Green.checkScore() - Red.checkScore();
			}
			std::cout << std::endl;
			Green.checkDeadDebug();
			if (Green.checkScore() < Red.checkScore()) {
				std::cout << "+" << Red.checkScore() - Green.checkScore();
			}
			std::cout << std::endl;
			std::cout << "__________________________________________" << std::endl;
			std::cout << "__________________________________________" << std::endl;
			Red.checkThreats();
			Green.checkThreats();
			std::cout << "__________________________________________" << std::endl;
			std::cout << "__________________________________________" << std::endl;
			Red.checkKing();
			Green.checkKing();
			std::cout << "__________________________________________" << std::endl;
			std::cout << "   A    B    C    D    E    F    G    H" << std::endl;
			Color::Modifier red(Color::FG_RED);
			Color::Modifier green(Color::FG_GREEN);
			Color::Modifier blue(Color::FG_BLUE);
			Color::Modifier yellow(Color::FG_YELLOW);
			Color::Modifier def(Color::FG_DEFAULT);
			for (int i = 0; i < 8; ++i) {
				std::cout << -i + 8 << "  ";
				for (int j = 0; j < 8; ++j) {
					//Print piece name if it has piece
					if (main[i][j].hasPiece()) {
						if (main[i][j].checkPlayer() == RED) {
							std::cout << red << main[i][j].checkPieceType() << def << "    ";
						}
						else if (main[i][j].checkPlayer() == GREEN) {
							std::cout << green << main[i][j].checkPieceType() << def << "    ";
						}
						else {
							std::cout << std::endl << "ERROR::Pieces created with no player" << std::endl;
						}
					}
					else {
						bool it_b = Red.findDead(i, j); 
						bool it_g = Green.findDead(i, j);
						if (it_b) {
							std::cout << blue << ".    " << def;
						}
						else if (it_g) {
							std::cout << yellow << ".    " << def;
						}
						else {
							std::cout << ".    ";
						}
					}
				}
				std::cout << '\b' << -i + 8 << std::endl << std::endl;
			}
			std::cout << "   A    B    C    D    E    F    G    H" << std::endl;
		}

		inline bool Board::inBound(int h, int w) const {
			//std::cout << "Checking [" << h << ", " << w << "]" << std::endl;
			return w >= 0 and w <= 7 and h >= 0 and h <= 7;
		}

		inline bool Board::contains(char c, std::string word) const {
			for (int i = 0; i < word.size(); ++i) {
				if (c == word[i]) {
					return true;
				}
			}
			return false;
		}

		bool Board::hasFriendly(char type, int h, int w, int player) const {
			//std::cout << "Checking [" << h << ", " << w << "]" << std::endl;
			return inBound(h, w) and
				main[h][w].hasPiece() and
				main[h][w].checkPieceType() == type and
				main[h][w].checkPlayer() == player;
		}

		bool Board::hasEnemy(char type, int h, int w, int player) const {
			if (player == RED) {
				return hasFriendly(type, h, w, GREEN);
			}
			else if(player == GREEN){
				return hasFriendly(type, h, w, RED);
			}
			std::cout << "No known player" << std::endl;
			return false;
		}

		bool Board::rank(char a) const {
			return a >= '1' and a <= '8';
		}

		bool Board::file(char a) const {
			return a >= 'a' and a <= 'h';
		}

		//TODO: 
		//		-checkmate detection
		//		-flip board
		//		-count pieces
		//			-left
		//			-per player
		//			-warnings at start if dif than 32
		//		-go back funtionality
		//		-FEN encoding
		//		-interactive GUI

		//CHANGELOG:
		//	-Added ambiguous moves :
		//		-knight e.g.Nfg5
		//		- rook
		//		- bishop
		//		- queen
		//		- king(possible ? )
		//_____________________________________________________________________________________
		//	- Added single ambiguous captures :
		//		-knight e.g.Nfxg5
		//		- rook
		//		- bishop
		//		- queen
		//		- king(possible ? )
		//		- Added double ambiguity moves and captures
		//		- bishop e.g.Bd5xe4
		//		- queen e.g.Qd5xe4
		//_____________________________________________________________________________________
		//		- Added pawn promotion :
		//			- by moving e.g.b8 = Q
		//			- by moving e.g.axb7 = Q
		//_____________________________________________________________________________________
		//		- Added castling e.g. O-O or 0-0-0
		//		- Added read mode, to directly read pgn formatted matches
		//_____________________________________________________________________________________
		//		- Added scoreboard
		//_____________________________________________________________________________________
		//		- Added en passant
		//_____________________________________________________________________________________
		//		- Added a system to know threatened tiles by each player
		//		- Added check detection
		//_____________________________________________________________________________________
		//		- Added move restriction when board is in check
		//_____________________________________________________________________________________
		//		- Fixed en passant minor bug:
		//			- If a move failed, you couldn't capture en passant even if it was valid
		//		- Fixed ambiguous rook moves and captures
		//		- Added RELEASE and DEBUG modes
		//		- Added new colorisation method (Windows API)
		//_____________________________________________________________________________________
		//		- RELEASE mode now just shows the board without control messages
		//		- Rearranged some classes
		//		- Added new functionality that allows you to read for a file
		//		- Added functionality to browse online the match read in the file if URL is in 
		//		  the bottom of file
		//		- Improved performance
		//		- Fixed minor bugs

		bool Board::move(std::string movement, int player, bool &enp) {
			int rank_d, file_d;
			std::cout << "Your movement was " << movement << std::endl;
			bool temp = target.possible or enp;
			if (temp) {
				target.possible = false;
				enp = true;
			}
						
			if (movement.length() < 2) {
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
					if (MODE == DEBUG) {
						std::cout << "Kingside castling detected!" << std::endl;
					}
					return castleKingside(player);
				}
			}

			//longer instructions
			else if (movement.length() == 4) {
				//captures
				if (contains('x', movement)) {
					if (MODE == DEBUG) {
						std::cout << "Capture detected!" << std::endl;
					}
					//if first letter is lowercase it is a pawn capture
					rank_d = 8 - (movement[3] - 48);
					file_d = movement[2] - 97;
					if (islower(movement[0])) {
						//p.e: exf5
						int file_s = movement[0] - 97;
						return pawnCapture(file_s, rank_d, file_d, player, temp);
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
					if (MODE == DEBUG) {
						std::cout << "Promotion detected!" << std::endl;
					}
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
				}
			}
			//ambiguous captures
			else if (movement.length() == 5) {
				if (contains('x', movement)) {
					if (MODE == DEBUG) {
						std::cout << "Capture detected!" << std::endl;
					}
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
				}
				if (movement == "O-O-O" or movement == "0-0-0") {
					if (MODE == DEBUG) {
						std::cout << "Queenside castling detected!" << std::endl;
					}
					return castleQueenside(player);
				}
				//double ambiguous move
				else {
					if (MODE == DEBUG) {
						std::cout << "Double ambiguous detected!" << std::endl;
					}
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
						if (MODE == DEBUG) {
							std::cout << "Promotion detected!" << std::endl;
						}
						rank_d = 8 - (movement[3] - 48);
						file_d = movement[2] - 97;
						char type = movement[5];
						int file_s = movement[0] - 97;
						return pawnPromoteCapture(file_s, rank_d, file_d, type, player);
					}
					//double ambiguous capture
					else {
						if (MODE == DEBUG) {
							std::cout << "Capture detected!" << std::endl;
						}
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