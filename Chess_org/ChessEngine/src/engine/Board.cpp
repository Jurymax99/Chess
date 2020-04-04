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
			if (OUTPUT == NORMAL) {
				std::cout << "Standard " << height << "x" << width << " board created with " << pieces << " pieces" << std::endl;
			}

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
			if (MODE == DEBUG) {
				std::cout << "Board destroyed" << std::endl;
			}
		}

		void Board::printBoard() const{
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

		void Board::print_blank(int par) const{
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

		void Board::printBoardRelease() const{
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

		void Board::printBoardDebug() const{
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
			Red.checkMoves();
			Green.checkMoves();
			std::cout << "__________________________________________" << std::endl;
			std::cout << "__________________________________________" << std::endl;
			std::cout << "Red ";
			std::cout.flush();
			Red.checkKing();
			std::cout << "Green ";
			std::cout.flush();
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
						bool it_b = Red.findThreat(i, j); 
						bool it_g = Green.findThreat(i, j);
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

		bool Board::hasFriendly(int h, int w, int player) const {
			//std::cout << "Checking [" << h << ", " << w << "]" << std::endl;
			return inBound(h, w) and
				main[h][w].hasPiece() and
				main[h][w].checkPlayer() == player;
		}

		bool Board::hasEnemy(char type, int h, int w, int player) const {
			if (player == RED) {
				return hasFriendly(type, h, w, GREEN);
			}
			else if (player == GREEN) {
				return hasFriendly(type, h, w, RED);
			}
			std::cout << "No known player" << std::endl;
			return false;
		}

		bool Board::hasEnemy(int h, int w, int player) const {
			if (player == RED) {
				return hasFriendly(h, w, GREEN);
			}
			else if (player == GREEN) {
				return hasFriendly(h, w, RED);
			}
			std::cout << "No known player" << std::endl;
			return false;
		}

		bool Board::findMove(char type, const Position& dest, int player){
			Position source;
			if (player == RED) {
				source = Red.findMove(type, dest, *this);
			}
			else if (player == GREEN) {
				source = Green.findMove(type, dest, *this);
			}
			else {
				std::cout << "No such known player" << std::endl;
			}
			if (not source.isNull()) {
				bool enp = type == 'P' and abs(source.h - dest.h) == 2;
				return makeMove(type, source.h, source.w, dest.h, dest.w, player, enp);
			}
			return false;
		}

		bool Board::findCapture(char type, const Position& dest, int player) {
			Position source;
			if (player == RED) {
				source = Red.findCapture(type, dest, *this);

			}
			else if (player == GREEN) {
				source = Green.findCapture(type, dest, *this);
			}
			else {
				std::cout << "No such known player" << std::endl;
			}
			if (not source.isNull()) {
				return makeCapture(type, source.h, source.w, dest.h, dest.w, player);
			}
			return false;
		}

		bool Board::findAmbiguousMove(char type, char dis, const Position& dest, int player) {
			Position source;
			if (rank(dis)) {
				if (MODE == DEBUG) {
					std::cout << "The ambiguity is at the file" << std::endl;
				}
				if (player == RED) {
					source = Red.findAmbRMove(type, (8 - (dis - 48)), dest, *this);
				}
				else if (player == GREEN) {
					source = Green.findAmbRMove(type, (8 - (dis - 48)), dest, *this);
				}
				else {
					std::cout << "No such known player" << std::endl;
				}
			}
			else if (file(dis)) {
				if (MODE == DEBUG) {
					std::cout << "The ambiguity is at the rank" << std::endl;
				}
				if (player == RED) {
					source = Red.findAmbFMove(type, (dis - 97), dest, *this);
				}
				else if (player == GREEN) {
					source = Green.findAmbFMove(type, (dis - 97), dest, *this);
				}
				else {
					std::cout << "No such known player" << std::endl;
				}
			}
			else {
				std::cout << "Couldn't convert instruction to tile" << std::endl;
				return false;
			}
			if (not source.isNull()) {
				return makeMove(type, source.h, source.w, dest.h, dest.w, player, false);
			}
			return false;
		}
	
		bool Board::findAmbiguousCapture(char type, char dis, const Position& dest, int player) {
			Position source;
			if (rank(dis)) {
				if (MODE == DEBUG) {
					std::cout << "The ambiguity is at the file" << std::endl;
				}
				if (player == RED) {
					source = Red.findAmbRCapture(type, (8 - (dis - 48)), dest, *this);
				}
				else if (player == GREEN) {
					source = Green.findAmbRCapture(type, (8 - (dis - 48)), dest, *this);
				}
				else {
					std::cout << "No such known player" << std::endl;
				}
			}
			else if (file(dis)) {
				if (MODE == DEBUG) {
					std::cout << "The ambiguity is at the rank" << std::endl;
				}
				if (player == RED) {
					source = Red.findAmbFCapture(type, (dis - 97), dest, *this);
				}
				else if (player == GREEN) {
					source = Green.findAmbFCapture(type, (dis - 97), dest, *this);
				}
				else {
					std::cout << "No such known player" << std::endl;
				}
			}
			else {
				std::cout << "Couldn't convert instruction to tile" << std::endl;
				return false;
			}
			if (not source.isNull()) {
				return makeCapture(type, source.h, source.w, dest.h, dest.w, player);
			}
			return false;
		}

		bool Board::findDoubleAmbiguousMove(char type, int source_h, int source_w, const Position& dest, int player) {
			Position source;
			
			if (player == RED) {
				source = Red.findDAmbMove(type, source_h, source_w, dest, *this);
			}
			else if (player == GREEN) {
				source = Green.findDAmbMove(type, source_h, source_w, dest, *this);
			}
			else {
				std::cout << "No such known player" << std::endl;
			}
			if (not source.isNull()) {
				return makeMove(type, source.h, source.w, dest.h, dest.w, player, false);
			}
			return false;
		}

		bool Board::findDoubleAmbiguousCapture(char type, int source_h, int source_w, const Position& dest, int player) {
			Position source;

			if (player == RED) {
				source = Red.findDAmbCapture(type, source_h, source_w, dest, *this);
			}
			else if (player == GREEN) {
				source = Green.findDAmbCapture(type, source_h, source_w, dest, *this);
			}
			else {
				std::cout << "No such known player" << std::endl;
			}
			if (not source.isNull()) {
				return makeCapture(type, source.h, source.w, dest.h, dest.w, player);
			}
			return false;
		}

		bool Board::move(std::string movement, int player, bool& enp) {
			int rank_d, file_d;
			if (OUTPUT == NORMAL) {
				std::cout << "Your movement was " << movement << std::endl;
			}
			bool temp = target.possible or enp;
			if (temp) {
				target.possible = true;
				enp = true;
			}

			if (movement.length() < 2) {
				return false;
			}

			//normal pawn move
			else if (movement.length() == 2) {
				Position dest = { 8 - (movement[1] - 48) , movement[0] - 97 };
				return findMove('P', dest, player);
			}

			//non-ambiguous other moves
			else if (movement.length() == 3) {
				Position dest = { 8 - (movement[2] - 48) , movement[1] - 97 };
				//normal knight move
				if (movement[0] == 'N') {
					return findMove('N', dest, player);
				}
				//normal rook move
				if (movement[0] == 'R') {
					return findMove('R', dest, player);
				}
				//normal bishop move
				if (movement[0] == 'B') {
					return findMove('B', dest, player);
				}
				//normal queen move
				if (movement[0] == 'Q') {
					return findMove('Q', dest, player);
				}
				//normal king move
				if (movement[0] == 'K') {
					return findMove('K', dest, player);
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
					Position dest = { 8 - (movement[3] - 48) , movement[2] - 97 };
					if (islower(movement[0])) {
						//p.e: exf5
						int file_s = movement[0] - 97;
						return pawnCapture(file_s, dest.h, dest.w, player, temp);
					}
					//normal knight capture
					if (movement[0] == 'N') {
						return findCapture('N', dest, player);
					}
					//normal rook capture
					if (movement[0] == 'R') {
						return findCapture('R', dest, player);
					}
					//normal bishop capture
					if (movement[0] == 'B') {
						return findCapture('B', dest, player);
					}
					//normal queen capture
					if (movement[0] == 'Q') {
						return findCapture('Q', dest, player);
					}
					//normal king capture
					if (movement[0] == 'K') {
						return findCapture('K', dest, player);
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
					Position dest = { 8 - (movement[3] - 48) , movement[2] - 97 };
					char dis = movement[1];
					//knight
					if (movement[0] == 'N') {
						return findAmbiguousMove('N', dis, dest, player);
					}
					//rook
					if (movement[0] == 'R') {
						return findAmbiguousMove('R', dis, dest, player);
					}
					//bishop
					if (movement[0] == 'B') {
						return findAmbiguousMove('B', dis, dest, player);
					}
					//queen
					if (movement[0] == 'Q') {
						return findAmbiguousMove('Q', dis, dest, player);
					}
				}
			}
			//ambiguous captures
			else if (movement.length() == 5) {
				if (contains('x', movement)) {
					if (MODE == DEBUG) {
						std::cout << "Capture detected!" << std::endl;
					}
					Position dest = { 8 - (movement[4] - 48) , movement[3] - 97 };
					char dis = movement[1];
					//knight
					if (movement[0] == 'N') {
						return findAmbiguousCapture('N', dis, dest, player);
					}
					//rook
					if (movement[0] == 'R') {
						return findAmbiguousCapture('R', dis, dest, player);
					}
					//bishop
					if (movement[0] == 'B') {
						return findAmbiguousCapture('B', dis, dest, player);
					}
					//queen
					if (movement[0] == 'Q') {
						return findAmbiguousCapture('Q', dis, dest, player);
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
					Position dest = { 8 - (movement[4] - 48) , movement[3] - 97 };
					int rank_s = 8 - (movement[2] - 48);
					int file_s = movement[1] - 97;
					//bishop
					if (movement[0] == 'B') {
						return findDoubleAmbiguousMove('B', rank_s, file_s, dest, player);
					}
					//queen
					if (movement[0] == 'Q') {
						return findDoubleAmbiguousMove('Q', rank_s, file_s, dest, player);
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
						Position dest = { 8 - (movement[5] - 48) , movement[4] - 97 };
						int rank_s = 8 - (movement[2] - 48);
						int file_s = movement[1] - 97;
						//bishop
						if (movement[0] == 'B') {
							return findDoubleAmbiguousCapture('B', rank_s, file_s, dest, player);
						}
						//queen
						if (movement[0] == 'Q') {
							return findDoubleAmbiguousCapture('Q', rank_s, file_s, dest, player);
						}
					}
				}
			}
			return false;
		}

		bool Board::isCheckmate(int player, Ending& status) {
			if (player == RED) {
				int player_checked;
				//checkmate
				if (not Red.hasMoves()){
					if (isChecked(player_checked) and player_checked == RED) {
						status = Ending::CHECKMATE;
						return true;
					}
				//stalemate
					else {
						status = Ending::STALEMATE;
						return true;
					}
				}
			}
			else if (player == GREEN) {
				int player_checked;
				//checkmate
				if (not Green.hasMoves()) {
					if (isChecked(player_checked) and player_checked == GREEN) {
						status = Ending::CHECKMATE;
						return true;
					}
					//stalemate
					else {
						status = Ending::STALEMATE;
						return true;
					}
				}
			}
			else {
				status = Ending::UNDEFINED;
				std::cout << "No such known player" << std::endl;
				return false;
			}
			status = Ending::UNDEFINED;
			return false;
		}

		void Board::update() {
			Red.updateMoveSet(*this);
			Green.updateMoveSet(*this);
		}
	}
}