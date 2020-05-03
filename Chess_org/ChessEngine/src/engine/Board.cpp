#include "Board.h"
#include "Color.h"
#include <windows.h>		// for SetConsoleTextAttribute
#include <string>			// for various std::string operations (isalpha, stoi, tolower, ...)
#include "Utilities.h"

namespace Chess {
	namespace Engine {
		Board::Board() {
			Red = Player(RED);
			Green = Player(GREEN);
			target = { -1,-1, false };
			halfMoves = 0;
			turn = 0;
			pieces = 32;
			if (OUTPUT == NORMAL) {
				std::cout << "Standard 8 x 8 board created with 32 pieces" << std::endl;
			}
			//Green pieces
			main(0, 0).addPiece('R', GREEN);
			main(0, 1).addPiece('N', GREEN);
			main(0, 2).addPiece('B', GREEN);
			main(0, 3).addPiece('Q', GREEN);
			main(0, 4).addPiece('K', GREEN);
			main(0, 5).addPiece('B', GREEN);
			main(0, 6).addPiece('N', GREEN);
			main(0, 7).addPiece('R', GREEN);
			main(1, 0).addPiece('P', GREEN);
			main(1, 1).addPiece('P', GREEN);
			main(1, 2).addPiece('P', GREEN);
			main(1, 3).addPiece('P', GREEN);
			main(1, 4).addPiece('P', GREEN);
			main(1, 5).addPiece('P', GREEN);
			main(1, 6).addPiece('P', GREEN);
			main(1, 7).addPiece('P', GREEN);

			//Red pieces
			main(6, 0).addPiece('P', RED);
			main(6, 1).addPiece('P', RED);
			main(6, 2).addPiece('P', RED);
			main(6, 3).addPiece('P', RED);
			main(6, 4).addPiece('P', RED);
			main(6, 5).addPiece('P', RED);
			main(6, 6).addPiece('P', RED);
			main(6, 7).addPiece('P', RED);
			main(7, 0).addPiece('R', RED);
			main(7, 1).addPiece('N', RED);
			main(7, 2).addPiece('B', RED);
			main(7, 3).addPiece('Q', RED);
			main(7, 4).addPiece('K', RED);
			main(7, 5).addPiece('B', RED);
			main(7, 6).addPiece('N', RED);
			main(7, 7).addPiece('R', RED);
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

		Board::Board(const std::string& FEN) {
			//largest rnbqkbnr/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/PPPPPPPP/RNBQKBNR w KQkq pp 49 200
			//shortest 1/1/1/1/1/1/1/1 w - - 0 1
			Red = Player(RED);
			Green = Player(GREEN);
			if (FEN.length() > 88 or FEN.length() < 25) {
				std::cout << "Invalid FEN format\n";
				*this = Board();
				return;
			}
			int it, pieceCount;
			it = pieceCount = 0;
			for (int i = 0; i < 8; ++i) {
				for (int j = 0; j < 8; ++j) {
					if (std::isalpha(FEN[it])) {
						if (std::islower(FEN[it])) {
							main(i,j).addPiece(std::toupper(FEN[it]), GREEN);
							if (FEN[it] == 'k') {
								Green.setKing(i, j);
							}
							++pieceCount;
						}
						else {
							main(i,j).addPiece(FEN[it], RED);
							if (FEN[it] == 'K') {
								Red.setKing(i, j);
							}
							++pieceCount;
						}
					}
					else if(FEN[it] != '/'){
						j += FEN[it] - '0' - 1;
					}
					++it;
				}
				++it;
			}

			if (OUTPUT == NORMAL) {
				std::cout << "Standard " << 8 << "x" << 8 << " board created with " << pieceCount << " pieces" << std::endl;
			}

			pieces = pieceCount;

			//turn
			int playerToMove = FEN[it] == 'w' ? RED : GREEN;
			it += 2;

			//castleability
			Red.setCastleKing(false);
			Red.setCastleQueen(false);
			Green.setCastleKing(false);
			Green.setCastleQueen(false);
			if (FEN[it] != '-') {
				while (FEN[it] != ' ') {
					if (FEN[it] == 'K' and
						hasFriendly('R', 7, 7, RED) and
						hasFriendly('K', 7, 4, RED)) {
						Red.setCastleKing(true);
					}
					else if (FEN[it] == 'Q' and
						hasFriendly('R', 7, 0, RED) and
						hasFriendly('K', 7, 4, RED)) {
						Red.setCastleQueen(true);
					}
					else if (FEN[it] == 'k' and
						hasFriendly('R', 0, 7, GREEN) and
						hasFriendly('K', 0, 4, GREEN)) {
						Green.setCastleKing(true);
					}
					else if (FEN[it] == 'q' and
						hasFriendly('R', 0, 0, GREEN) and
						hasFriendly('K', 0, 4, GREEN)) {
						Green.setCastleQueen(true);
					}
					++it;
				}
				++it;
			}
			else {
				it += 2;
			}

			//enpassant
			if (FEN[it] != '-') {
				int tempW = FEN[it++] - 'a';
				int tempH = 8 - ((FEN[it] - '0') - playerToMove);
				if (hasFriendly('P', tempH, tempW, -playerToMove)) {
					target = { tempH, tempW, true };
				}
				else {
					target = { -1, -1, false };
				}
			}
			else {
				target.possible = false;
			}
			it += 2;

			if (it >= FEN.length()) {
				turn = playerToMove == RED ? 0 : 1;
				halfMoves = 0;
				return;
			}

			//halfMoves
			std::string acum;
			while (FEN[it] != ' ') {
				acum += FEN[it];
				++it;
			}
			halfMoves = std::stoi(acum);


			//turn number
			++it;
			acum = std::string();
			while (FEN[it] >= '0' and FEN[it] <= '9') {
				acum += FEN[it];
				++it;
			}
			turn = std::stoi(acum);

			if (turn == 1 and playerToMove == RED) {
				--turn;
			}


			if (playerToMove == RED ? turn % 2 != 0 : turn % 2 == 0) {
				std::cout << "WARNING::The FEN indicated is not possible, adjusting turn number to make it possible\n";
				turn != 0 ? --turn : ++turn;
			}

			if (MODE == DEBUG) {
				std::cout << "FEN succesfully created\n";
			}
		}

		void Board::createFEN() const{
			std::string FEN;
			for (int i = 0; i < 8; ++i) {
				int empty = 0;
				for (int j = 0; j < 8; ++j) {
					if (main(i,j).hasPiece()) {
						if (empty != 0) {
							FEN += std::to_string(empty);
						}
						FEN += main(i, j).checkPlayer() == RED ? main(i, j).checkPieceType() : std::tolower(main(i, j).checkPieceType());
						empty = 0;
					}
					else {
						++empty;
					}
				}
				if (empty != 0) {
					FEN += std::to_string(empty);
				}
				if (i != 7) {
					FEN += '/';
				}
			}
			FEN += " ";
			FEN += turn % 2 == 0 ? 'w' : 'b';
			FEN += " ";
			int count = 0;
			if (Red.checkCastleKing()) {
				FEN += 'K';
				++count;
			}
			if (Red.checkCastleQueen()){
				FEN += 'Q';
				++count;
			}
			if (Green.checkCastleKing()) {
				FEN += 'k';
				++count;
			}
			if (Green.checkCastleQueen()) {
				FEN += 'q';
				++count;
			}
			if (count == 0) {
				FEN += '-';
			}
			FEN += " ";
			if (target.possible) {
				int pawnConst = (turn % 2 == 0) ? 1 : -1;
				FEN += char(target.w + 97);
				FEN += std::to_string(8 - target.h + pawnConst);
			}
			else {
				FEN += '-';
			}
			FEN += " ";
			FEN += std::to_string(halfMoves);
			FEN += " ";
			FEN += turn == 0 ? "1" : std::to_string(turn);
			std::cout << "Board's FEN is " << FEN << std::endl;
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
					if (main(i,j).hasPiece()) {
						if (abs(i - j) % 2 == 0) {
							if (main(i,j).checkPlayer() == RED) {
								SetConsoleTextAttribute(hConsole, 252);
							}
							else if (main(i,j).checkPlayer() == GREEN) {
								SetConsoleTextAttribute(hConsole, 242);
							}
							else {
								std::cout << std::endl << "ERROR::Pieces created with no player" << std::endl;
							}
							std::cout << "   " << main(i,j).checkPieceType() << "   ";
						}
						else {
							if (main(i,j).checkPlayer() == RED) {
								SetConsoleTextAttribute(hConsole, 12);
							}
							else if (main(i,j).checkPlayer() == GREEN) {
								SetConsoleTextAttribute(hConsole, 10);
							}
							else {
								std::cout << std::endl << "ERROR::Pieces created with no player" << std::endl;
							}
							std::cout << "   " << main(i,j).checkPieceType() << "   ";
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

		void Board::printBoardDebug(){
			std::cout << "__________________________________________\n";
			std::cout << "Halfmoves: " << halfMoves << std::endl;
			std::cout << "__________________________________________\n";
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
			std::cout << "__________________________________________\n";
			std::cout << "__________________________________________\n";
			Red.updateThreats(*this, true);
			Green.updateThreats(*this, false);
			printThreats();
			std::cout << "__________________________________________\n";
			std::cout << "__________________________________________\n";
			Red.checkMoves();
			Green.checkMoves();
			std::cout << "__________________________________________\n";
			std::cout << "__________________________________________\n";
			std::cout << "Red ";
			std::cout.flush();
			Red.checkKing();
			std::cout << "Green ";
			std::cout.flush();
			Green.checkKing();
			std::cout << "__________________________________________\n";
			std::cout << "__________________________________________\n";
			std::cout << "   A    B    C    D    E    F    G    H\n";
			const Color::Modifier red(Color::FG_RED);
			const Color::Modifier green(Color::FG_GREEN);
			const Color::Modifier blue(Color::FG_BLUE);
			const Color::Modifier yellow(Color::FG_YELLOW);
			const Color::Modifier def(Color::FG_DEFAULT);
			for (int i = 0; i < 8; ++i) {
				std::cout << -i + 8 << "  ";
				for (int j = 0; j < 8; ++j) {
					//Print piece name if it has piece
					if (main(i,j).hasPiece()) {
						if (main(i,j).checkPlayer() == RED) {
							std::cout << red << main(i,j).checkPieceType() << def << "    ";
						}
						else if (main(i,j).checkPlayer() == GREEN) {
							std::cout << green << main(i, j).checkPieceType() << def << "    ";
						}
						else {
							std::cout << std::endl << "ERROR::Pieces created with no player\n";
						}
					}
					else {
						int it = main(i,j).isThreatened();
						if (it == RED) {
							std::cout << blue << ".    " << def;
						}
						else if (it == GREEN) {
							std::cout << yellow << ".    " << def;
						}
						else {
							std::cout << ".    ";
						}
					}
				}
				std::cout << '\b' << -i + 8 << std::endl << std::endl;
			}
			std::cout << "   A    B    C    D    E    F    G    H\n";
		}

		inline bool Board::contains(char c, std::string word) const noexcept {
			for (int i = 0; i < word.size(); ++i) {
				if (c == word[i]) {
					return true;
				}
			}
			return false;
		}

		bool Board::findMove(char type, const Position& dest, int player){
			Position source = player == RED ? Red.findMove(type, dest, *this)
				: Green.findMove(type, dest, *this);
			if (not source.isNull()) {
				bool enp = type == 'P' and abs(source.checkH() - dest.checkH()) == 2;
				return makeMove(type, source, dest, player, enp);
			}
			return false;
		}

		bool Board::findCapture(char type, const Position& dest, int player) {
			Position source = player == RED ? Red.findCapture(type, dest, *this)
				: Green.findCapture(type, dest, *this);
			if (not source.isNull()) {
				return makeCapture(type, source.checkH(), source.checkW(), dest.checkH(), dest.checkW(), player);
			}
			return false;
		}

		bool Board::findPromotion(const Position& dest, char typePro, int player) {
			Position source = player == RED ? Red.findPromotion(dest, *this)
				: Green.findPromotion(dest, *this);
			if (not source.isNull()) {
				return pawnPromote(source, dest, typePro, player);
			}
			return false;
		}

		bool Board::findAmbiguousMove(char type, char dis, const Position& dest, int player) {
			Position source;
			if (rank(dis)) {
				if (MODE == DEBUG) {
					std::cout << "The ambiguity is at the file" << std::endl;
				}
				source = player == RED ? Red.findAmbRMove(type, (8 - (dis - 48)), dest, *this)
					: Green.findAmbRMove(type, (8 - (dis - 48)), dest, *this);
			}
			else if (file(dis)) {
				if (MODE == DEBUG) {
					std::cout << "The ambiguity is at the rank" << std::endl;
				}
				source = player == RED ? Red.findAmbFMove(type, (dis - 97), dest, *this)
					: Green.findAmbFMove(type, (dis - 97), dest, *this);
			}
			else {
				std::cout << "Couldn't convert instruction to tile" << std::endl;
				return false;
			}
			if (not source.isNull()) {
				return makeMove(type, source, dest, player, false);
			}
			return false;
		}
	
		bool Board::findAmbiguousCapture(char type, char dis, const Position& dest, int player) {
			Position source;
			if (rank(dis)) {
				if (MODE == DEBUG) {
					std::cout << "The ambiguity is at the file" << std::endl;
				}
				source = player == RED ? Red.findAmbRCapture(type, (8 - (dis - 48)), dest, *this)
					: Green.findAmbRCapture(type, (8 - (dis - 48)), dest, *this);
			}
			else if (file(dis)) {
				if (MODE == DEBUG) {
					std::cout << "The ambiguity is at the rank" << std::endl;
				}
				source = player == RED ? Red.findAmbFCapture(type, (dis - 97), dest, *this)
					: Green.findAmbFCapture(type, (dis - 97), dest, *this);
			}
			else {
				std::cout << "Couldn't convert instruction to tile" << std::endl;
				return false;
			}
			if (not source.isNull()) {
				return makeCapture(type, source.checkH(), source.checkW(), dest.checkH(), dest.checkW(), player);
			}
			return false;
		}

		bool Board::findDoubleAmbiguousMove(char type, const Position& source, const Position& dest, int player) {
			Position found_source = player == RED ? Red.findDAmbMove(type, source, dest, *this)
				: Green.findDAmbMove(type, source, dest, *this);
			if (not found_source.isNull()) {
				return makeMove(type, source, dest, player, false);
			}
			return false;
		}

		bool Board::findDoubleAmbiguousCapture(char type, const Position& source, const Position& dest, int player) {
			Position found_source = player == RED ? Red.findDAmbCapture(type, source, dest, *this) 
				: Green.findDAmbCapture(type, source, dest, *this);
			if (not found_source.isNull()) {
				return makeCapture(type, source.checkH(), source.checkW(), dest.checkH(), dest.checkW(), player);
			}
			return false;
		}

		bool Board::findKingsideCastling(int player) {
			if (player == RED ? Red.findKingsideCastling(*this) : Green.findKingsideCastling(*this)) {
				return castleKingside(player);
			} 
			return false;
		}

		bool Board::findQueensideCastling(int player) {
			if (player == RED ? Red.findQueensideCastling(*this) : Green.findQueensideCastling(*this)) {
				return castleQueenside(player);
			}
			return false;
		}

		bool Board::move(std::string movement, bool& enp) {
			const int player = checkPlayer();
			int rank_d, file_d;
			if (OUTPUT == NORMAL) {
				std::cout << "Your movement was " << movement << std::endl;
			}
			bool temp = target.possible or enp;
			if (temp) {
				target.possible = true;
				enp = true;
			}
			Position dest, source;
			switch (movement.length()) {
			case 2:
				//normal pawn move
				dest = { 8 - (movement[1] - 48) , movement[0] - 97 };
				return (player == RED ? dest.checkH() != 0 : dest.checkH() != 7) and findMove('P', dest, player);
				break;
			case 3:
				//non-ambiguous other moves
				if (movement == "O-O" or movement == "0-0") {
					if (MODE == DEBUG) {
						std::cout << "Kingside castling detected!" << std::endl;
					}
					return findKingsideCastling(player);
				}
				dest = { 8 - (movement[2] - 48) , movement[1] - 97 };
				if (movement[0] != 'N' and
					movement[0] != 'B' and
					movement[0] != 'Q' and
					movement[0] != 'K' and
					movement[0] != 'R') {
					std::cout << "Wrong type for this kind of move" << std::endl;
					return false;
				}
				return findMove(movement[0], dest, player);
				break;
			case 4:
				//captures
				if (contains('x', movement)) {
					if (MODE == DEBUG) {
						std::cout << "Capture detected!" << std::endl;
					}
					//if first letter is lowercase it is a pawn capture
					dest = { 8 - (movement[3] - 48) , movement[2] - 97 };
					if (islower(movement[0])) {
						//p.e: exf5
						int file_s = movement[0] - 97;
						return pawnCapture(file_s, dest.checkH(), dest.checkW(), player, temp);
					}

					if (movement[0] != 'N' and
						movement[0] != 'B' and
						movement[0] != 'Q' and
						movement[0] != 'K' and
						movement[0] != 'R') {
						std::cout << "Wrong type for this kind of move" << std::endl;
						return false;
					}
					return findCapture(movement[0], dest, player);
				}
				else if (contains('=', movement)) {
					if (MODE == DEBUG) {
						std::cout << "Promotion detected!" << std::endl;
					}
					Position dest = Position(8 - (movement[1] - 48), movement[0] - 97);
					char type = movement[3];
					if (movement[3] != 'N' and
						movement[3] != 'B' and
						movement[3] != 'Q' and
						movement[3] != 'R') {
						std::cout << "Wrong type to promote" << std::endl;
						return false;
					}
					return findPromotion(dest, type, player);
				}
				//ambiguous moves
				else {
					dest = { 8 - (movement[3] - 48) , movement[2] - 97 };
					char dis = movement[1];
					if (movement[0] != 'N' and
						movement[0] != 'B' and
						movement[0] != 'Q' and
						movement[0] != 'R') {
						std::cout << "Wrong type for this kind of move" << std::endl;
						return false;
					}
					return findAmbiguousMove(movement[0], dis, dest, player);
				}
				break;
			case 5:
				//ambiguous captures
				if (contains('x', movement)) {
					if (MODE == DEBUG) {
						std::cout << "Capture detected!" << std::endl;
					}
					dest = { 8 - (movement[4] - 48) , movement[3] - 97 };
					char dis = movement[1];

					if (movement[0] != 'N' and
						movement[0] != 'B' and
						movement[0] != 'Q' and
						movement[0] != 'R') {
						std::cout << "Wrong type for this kind of move" << std::endl;
						return false;
					}
					return findAmbiguousCapture(movement[0], dis, dest, player);
				}
				if (movement == "O-O-O" or movement == "0-0-0") {
					if (MODE == DEBUG) {
						std::cout << "Queenside castling detected!" << std::endl;
					}
					return findQueensideCastling(player);
				}
				//double ambiguous move
				else {
					if (MODE == DEBUG) {
						std::cout << "Double ambiguous detected!" << std::endl;
					}
					dest = { 8 - (movement[4] - 48) , movement[3] - 97 };
					source = { 8 - (movement[2] - 48) , movement[1] - 97 };

					if (movement[0] != 'B' and
						movement[0] != 'Q') {
						std::cout << "Wrong type for this kind of move" << std::endl;
						return false;
					}
					return findDoubleAmbiguousMove(movement[0], source, dest, player);
				}
				break;
			case 6:
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
						dest = { 8 - (movement[5] - 48) , movement[4] - 97 };
						source = { 8 - (movement[2] - 48), movement[1] - 97 };
						if (movement[0] != 'B' and
							movement[0] != 'Q') {
							std::cout << "Wrong type for this kind of move" << std::endl;
							return false;
						}
						return findDoubleAmbiguousCapture(movement[0], source, dest, player);
					}
				}
				break;
			}
			return false;
		}

		bool Board::move(const Move& m) {
			const int player = checkPlayer();
			char type = m.getType();
			Position source = m.getSource();
			Position dest = m.getDestination();
			bool correct_captenp, act_enp;
			correct_captenp = act_enp = false;

			if (type == 'P') {
				switch (source.checkH()) {
				case 1:
					act_enp = player == RED and dest.checkH() == 4;
					break;
				case 3:
					correct_captenp = target.possible and player == RED and Position(target.h, target.w) == dest;
					break;
				case 4:
					correct_captenp = target.possible and player == GREEN and Position(target.h, target.w) == dest;
					break;
				case 6:
					act_enp = player == GREEN and dest.checkH() == 3;
					break;
				default:
					break;
				}
			}

			if (not m.isCapture()) {
				if (m.isCastleKingside()) {
					return castleKingside(player);
				}
				else if (m.isCastleQueenside()) {
					return castleQueenside(player);
				}
				else if (m.isPromotion()) {
					return pawnPromote(source, dest, m.getPromotedType(), player);
				}
				else {
					return makeMove(type, source, dest, player, act_enp);
				}
			}
			else{
				if (m.isPromotion()) {
					return pawnPromoteCapture(source, dest, 'Q', player);
				}
				else if (type == 'P') {
					return pawnCapture(source, dest, player, correct_captenp);
				}
				return makeCapture(type, source.checkH(), source.checkW(), dest.checkH(), dest.checkW(), player);
			}

		}

		bool Board::isEnded(int player, Ending& status) {
			if (halfMoves == 50) {
				status = Ending::FIFTYRULE;
				return true;
			}
			else if (player == RED) {
				int player_checked = player;
				//checkmate
				if (not Red.hasMoves()){
					if (whoChecked(player_checked) and player_checked == RED) {
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
					if (whoChecked(player_checked) and player_checked == GREEN) {
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

		bool Board::isEnded() const{
			return halfMoves == 50 or not Red.hasMoves() or not Green.hasMoves();
		}

		bool Board::isEnded(int player, int& checked, float& pen, bool& mate) {
			if (halfMoves == 50) {
				pen = 100;
				return true;
			}
			else if (player == RED) {
				//checkmate
				checked = player;
				if (not Red.hasMoves()) {
					if (whoChecked(checked) and checked == RED) {
						pen = -900;
						mate = true;
						return true;
					}
					//stalemate
					else {
						pen = 100;
						checked = -1;
						return true;
					}
				}
				else if(not Green.hasMoves()){
					if (whoChecked(checked) and checked == GREEN) {
						pen = 900;
						mate = true;
						return true;
					}
				}
			}
			else if (player == GREEN) {
				//checkmate
				if (not Green.hasMoves()) {
					if (whoChecked(checked) and checked == GREEN) {
						pen = -900;
						mate = true;
						return true;
					}
					//stalemate
					else {
						pen = 100;
						checked = -1;
						return true;
					}
				}
				else if (not Red.hasMoves() and whoChecked(checked) and checked == RED) {
					pen = 900;
					mate = true;
					return true;
				}
			}
			else {
				std::cout << "No such known player" << std::endl;
				return false;
			}
			return false;
		}

		int Board::queenCount() const{
			int auxCount = 0;
			for (int i = 0; i < 64; ++i) {
				if (main(i).checkPieceType() == 'Q') {
					++auxCount;
				}
			}
			return auxCount;
		}

		bool Board::hasQueen() const {
			for (int i = 0; i < 64; ++i) {
				if (main(i).checkPieceType() == 'Q') {
					return true;
				}
			}
			return false;
		}

		Board::Board(const Board& b){
			Red = b.Red;
			Green = b.Green;
			target = b.target;
			halfMoves = b.halfMoves;
			turn = b.turn;
			main = b.main;
		}

		void Board::update() {
			//Green.moves.update(*this);
			//Red.moves.update(*this);
			turn % 2 ? Green.moves.update(*this) : Red.moves.update(*this);
		}

		void Board::printThreats() const {
			std::vector<Position> pRed(0);
			std::vector<Position> pGreen(0);

			for (int i = 0; i < 8; ++i) {
				for (int j = 0; j < 8; ++j) {
					int player_threatened;
					if (player_threatened = main(i,j).isThreatened()) {
						player_threatened == RED ? pRed.push_back(Position(i,j)) : pGreen.push_back(Position(i, j));
					}
				}
			}
			std::cout << "Red threatening positions: ";

			for (auto& d : pRed) {
				std::cout << "[" << char(d.checkW() + 97) << char(8 - char(d.checkH()- 48)) << "] ";
			}
			std::cout << std::endl;

			std::cout << "Green threatening positions: ";
			for (auto& d : pGreen) {
				std::cout << "[" << char(d.checkW() + 97) << char(8 - char(d.checkH()- 48)) << "] ";
			}
			std::cout << std::endl;
		}
	}
}