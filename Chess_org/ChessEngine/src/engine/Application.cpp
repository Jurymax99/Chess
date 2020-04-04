#include "Application.h"
#include "Utilities.h"
#include <stack>
#include <fstream>
#include <windows.h>
#include <shellapi.h>		//For browser search
#include "Timer.h"
#include "Dummy.h"

namespace Chess {
	namespace Engine {
		Application::Application() {
			std::cout << "Chess started ...\n";
		}

		Application::~Application() {
			std::cout << "Chess ended ...\n";
		}

		int Application::gameCount = 0;

		inline void Application::printHelpDebug() const{
			std::cout << "You can: P / F / L / M / C / q\n";
			std::cout << "    (P)lay\n";
			std::cout << "    Play (V)s the computer\n";
			std::cout << "    Read a (F)ile with a PGN formatted game\n";
			std::cout << "    Read a (L)arge file with multiple PGN formatted games\n";
			std::cout << "    Input (M)anually a PGN formatted game\n";
			std::cout << "    Roll the (C)redits\n";
			std::cout << "    (q)uit\n";
		}

		inline void Application::printHelp() const{
			std::cout << "You can: P / F / L / M / C / q\n";
			std::cout << "    (P)lay\n";
			std::cout << "    Play (V)s the computer\n";
			std::cout << "    Read a (F)ile with a PGN formatted game\n";
			std::cout << "    Read a (L)arge file with multiple PGN formatted games\n";
			std::cout << "    Input (M)anually a PGN formatted game\n";
			std::cout << "    Roll the (C)redits\n";
			std::cout << "    (q)uit\n";
		}

		void Application::start() {
			if (MODE == RELEASE) {
				if (ended) {
					printHelp();
					char ans;
					while (std::cin >> ans) {
						switch (ans) {
							//Play a game
						case 'P':
							++gameCount;
							ended = false;
							play();
							break;
							//Play against AI
						case 'V':
							++gameCount;
							ended = false;
							playComputer();
							break;
							//Read a file PGN game
						case 'F':
							++gameCount;
							ended = false;
							fileRead_pgn();
							break;
							//Read a file with multiple PGN games
						case 'L':
							++gameCount;
							ended = false;
							largeFileRead_pgn();
							break;
							//Read a manual PGN game
						case 'M':
							++gameCount;
							ended = false;
							manRead_pgn();
							break;
						case 'C':
							credits();
							break;
							//Exit the program
						case 'q':
							std::cout << "Goodbye :)\n";
							exit(1);
							break;
						default:
							printHelp();
							break;
						}
					}
				}
				else {
					std::cout << "Cannot start another game while there is one active\n";
				}
			}
			else if (MODE == DEBUG) {
				if (ended) {
					printHelpDebug();
					char ans;
					while (std::cin >> ans) {
						switch (ans) {
							//Play a game
						case 'P':
							++gameCount;
							ended = false;
							play();
							break;
							//Play against AI
						case 'V':
							++gameCount;
							ended = false;
							playComputer();
							break;
							//Read a file PGN game
						case 'F':
							++gameCount;
							ended = false;
							fileRead_pgn();
							break;
							//Read a file with multiple PGN games
						case 'L':
							++gameCount;
							ended = false;
							largeFileRead_pgn();
							break;
							//Read a manual PGN game
						case 'M':
							++gameCount;
							ended = false;
							manRead_pgn();
							break; 
						case 'C':
							credits();
							break;
							//Exit the program
						case 'q':
							std::cout << "Goodbye :)\n";
							exit(1);
							break;
						default:
							printHelpDebug();
							break;
						}
					}
				}
				else {
					std::cout << "Cannot start another game while there is one active\n";
				}
			}
			else {
				std::cout << "No known app mode\n";
			}
		}

		void Application::play() {
			std::cout << "PLAY MODE" << std::endl;
			std::cout << "Game #" << gameCount << " started" << std::endl;
			Board* mainBoard = new Board;
			mainBoard->update();
			mainBoard -> printBoard();
			int currentPlayer;
			std::string mov;
			while (not ended) {
				//Red's turn
				currentPlayer = RED;
				Board::Ending ending;
				if (mainBoard->isCheckmate(currentPlayer, ending)) {
					print_end(ending);
					break;
				}
				std::cout << "Red's turn" << std::endl;
				std::cout << "Insert your movement: " << std::endl;
				std::cin >> mov;
				if (mov == "quit") {
					ended = true;
					break;
				}
				bool enp = false;
				//Check if movement is valid
				while (not ended and not mainBoard -> move(mov, currentPlayer, enp)) {
					std::cout << "Red's turn" << std::endl;
					mainBoard->update();
					mainBoard->printBoard();
					std::cout << "Cannot perform movement, please try again:" << std::endl;
					std::cin >> mov;
					if (mov == "quit") {
						ended = true;
						break;
					}
				}
				if (ended) {
					break;
				}
				enp = false;
				std::cout << "Piece successfully moved" << std::endl;
				mainBoard->update();
				mainBoard->printBoard();
				//Green's turn
				currentPlayer = GREEN;
				if (mainBoard->isCheckmate(currentPlayer, ending)) {
					print_end(ending);
					break;
				}
				std::cout << "Green's turn" << std::endl;
				std::cout << "Insert your movement: " << std::endl;
				std::cin >> mov;
				if (mov == "quit") {
					ended = true;
					break;
				}
				//Check if movement is valid
				while (not ended and not mainBoard->move(mov, currentPlayer, enp)) {
					std::cout << "Green's turn" << std::endl;
					mainBoard->update();
					mainBoard->printBoard();
					std::cout << "Cannot perform movement, please try again:" << std::endl;
					std::cin >> mov;
					if (mov == "quit") {
						ended = true;
						break;
					}
				}
				if (ended) {
					break;
				}
				enp = false;
				std::cout << "Piece successfully moved" << std::endl;
				mainBoard->update();
				mainBoard->printBoard();
			}
			delete mainBoard;
			if (MODE == DEBUG) {
				printHelpDebug();
			}
			else {
				printHelp();
			}
		}

		void Application::playComputer() {
			std::cout << "PLAY AGAINST COMPUTER MODE" << std::endl;
			std::cout << "Game #" << gameCount << " started" << std::endl;
			Board* mainBoard = new Board;
			mainBoard->update();
			mainBoard->printBoard();
			int currentPlayer;
			Dummy player2(GREEN);
			std::string mov;
			while (not ended) {
				//Red's turn
				currentPlayer = RED;
				Board::Ending ending;
				if (mainBoard->isCheckmate(currentPlayer, ending)) {
					print_end(ending);
					break;
				}
				std::cout << "Red's turn" << std::endl;
				std::cout << "Insert your movement: " << std::endl;
				std::cin >> mov;
				if (mov == "quit") {
					ended = true;
					break;
				}
				bool enp = false;
				//Check if movement is valid
				while (not ended and not mainBoard->move(mov, currentPlayer, enp)) {
					std::cout << "Red's turn" << std::endl;
					mainBoard->update();
					mainBoard->printBoard();
					std::cout << "Cannot perform movement, please try again:" << std::endl;
					std::cin >> mov;
					if (mov == "quit") {
						ended = true;
						break;
					}
				}
				if (ended) {
					break;
				}
				enp = false;
				std::cout << "Piece successfully moved" << std::endl;
				mainBoard->update();
				mainBoard->printBoard();
				//Green's turn
				currentPlayer = GREEN;
				if (mainBoard->isCheckmate(currentPlayer, ending)) {
					print_end(ending);
					break;
				}
				std::cout << "Green's turn" << std::endl;
				
				std::cin >> mov;
				if (mov == "quit") {
					ended = true;
					break;
				}
				//Check if movement is valid
				while (not ended and not mainBoard->move(mov, currentPlayer, enp)) {
					std::cout << "Green's turn" << std::endl;
					mainBoard->update();
					mainBoard->printBoard();
					std::cout << "Cannot perform movement, please try again:" << std::endl;
					std::cin >> mov;
					if (mov == "quit") {
						ended = true;
						break;
					}
				}
				if (ended) {
					break;
				}
				enp = false;
				std::cout << "Piece successfully moved" << std::endl;
				mainBoard->update();
				mainBoard->printBoard();
			}
			delete mainBoard;
			if (MODE == DEBUG) {
				printHelpDebug();
			}
			else {
				printHelp();
			}
		}

		void Application::manRead_pgn() {
			std::cout << "READ MODE" << std::endl;
			std::cout << "Game #" << gameCount << " started" << std::endl;
			Board* mainBoard = new Board;
			mainBoard->update();
			mainBoard->printBoard();
			int currentPlayer;
			std::string mov;
			while (not ended) {
				//Red's turn
				currentPlayer = RED;
				std::cout << "Red's turn" << std::endl;
				std::cout << "Insert your movement: " << std::endl;
				char ppp;
				while (std::cin >> ppp and ppp != '.');
				std::cin >> mov;
				if (mov == "quit") {
					ended = true;
					break;
				}
				if (mov.back() == '+') {
					mov = mov.substr(0, mov.length() - 1);
				}
				bool enp = false;
				//Check if movement is valid
				while (not ended and not mainBoard->move(mov, currentPlayer, enp)) {
					std::cout << "Red's turn" << std::endl;
					mainBoard->update();
					mainBoard->printBoard();
					std::cout << "Cannot perform movement, please try again:" << std::endl;
					std::cin >> mov;
					if (mov == "quit") {
						ended = true;
						break;
					}
				}
				if (ended) {
					break;
				}
				enp = false;
				std::cout << "Piece successfully moved" << std::endl;
				mainBoard->update();
				mainBoard->printBoard();

				//Green's turn
				currentPlayer = GREEN;
				std::cout << "Green's turn" << std::endl;
				std::cout << "Insert your movement: " << std::endl;
				std::cin >> mov;
				if (mov == "quit") {
					ended = true;
					break;
				}
				if (mov.back() == '+') {
					mov = mov.substr(0, mov.length() - 1);
				}
				//Check if movement is valid
				while (not ended and not mainBoard->move(mov, currentPlayer, enp)) {
					std::cout << "Green's turn" << std::endl;
					mainBoard->update();
					mainBoard->printBoard();
					std::cout << "Cannot perform movement, please try again:" << std::endl;
					std::cin >> mov;
					if (mov == "quit") {
						ended = true;
						break;
					}
				}
				if (ended) {
					break;
				}
				std::cout << "Piece successfully moved" << std::endl;
				mainBoard->update();
				mainBoard->printBoard();
			}
			delete mainBoard;
			if (MODE == DEBUG) {
				printHelpDebug();
			}
			else {
				printHelp();
			}
		}

		void Application::fileRead_pgn() {
			if (OUTPUT != MINIMAL) {
				std::cout << "READ FILE MODE" << std::endl;
				std::cout << "Game #" << gameCount << " started" << std::endl;
			}
			Board* mainBoard = new Board;
			int currentPlayer;
			std::ifstream inFile;
			mainBoard->update();
			if (MODE == DEBUG) {
				mainBoard->printBoard();
			}
			//system("dir");
			std::string directory;
			if (ENVIRONMENT == VISUAL) {
				directory = "ChessEngine\\examples\\";
			}
			else {
				directory = "..\\..\\Chess_org\\ChessEngine\\examples\\";
			}
			std::string full = "dir " + directory;
			if (OUTPUT != MINIMAL) {
				system(full.c_str());
			std::cout << "You have these files available, type the one you'd like to read" << std::endl;
			std::cout << "Format: E.g. if you want to read file named 3.txt, type 3" << std::endl;
			}
			std::string ans;
			std::cin >> ans;
			inFile.open(directory + ans + ".txt");
			std::cout << ans << std::endl;
			if (not inFile) {
				std::cout << "Could not open file " << directory + ans + ".txt" << std::endl;
				delete mainBoard;
				if (MODE == DEBUG) {
					printHelpDebug();
				}
				else {
					printHelp();
				}
				return;
			}
			std::string result;
			while (inFile >> result and result != "[Result");
			inFile >> result;
			int i = 1;
			while (i < result.length() and result[i] != '"') {
				++i;
			}
			std::string end = result.substr(1, i - 1);
			if (MODE == DEBUG) {
				std::cout << end << std::endl;
			}
			std::string mov;
			inFile >> mov;
			while (std::getline(inFile, mov) and not mov.empty());
			Board::Ending ending;
			int count = 0;
			while (mov != end) {
				//F 11c n F 12c n F 13c n F 14c n F 15c n F 16c n F 17c n F 18c n F 3 n F 19l n F 20l n F 21l n F 22l n
				//F 11c n F 12c n F 13c n F 14c n F 15c n F 16c n F 17c n F 18c n F 3 n F 1 n F 4 n F 5 n F 6 n F 7 n F 8 n F 9 n F 10 n
				//Red's turn
				currentPlayer = RED;
				if (OUTPUT == NORMAL) {
					std::cout << (count / 2) + 1 << "." << std::endl;
				}
				++count;
				if (MODE == DEBUG) {
					std::cout << "Red's turn" << std::endl;
					std::cout << "Insert your movement: " << std::endl;
				}
				std::string acum;
				char ppp;
				while (inFile >> ppp and ppp != '.') {
					acum += ppp;
					if (acum == end) {
						mov = end;
						break;
					}
				}
				if (mainBoard->isCheckmate(currentPlayer, ending)) {
					break;
				}
				if (mov == end) {
					if (end == "1-0") {
						ending = Board::Ending::VICTORY;
					}
					else if (end == "0-1") {
						ending = Board::Ending::DEFEAT;
					}
					else if (end == "1/2-1/2") {
						ending = Board::Ending::DRAW;
					}
					break;
				}
				inFile >> mov;
				//Play number
				if (mov.back() == '+' or mov.back() == '#') {
					mov = mov.substr(0, mov.length() - 1);
				}
				bool enp = false;
				//Check if movement is valid
				if (not mainBoard->move(mov, currentPlayer, enp)) {
					if (MODE == DEBUG) {
						mainBoard->printBoard();
					}
					std::cout << "Cannot perform movement number " << ((count) / 2) + 1 << " for player red" << std::endl;
				}
				enp = false;
				mainBoard->update();
				if (MODE == DEBUG) {
					std::cout << "Piece successfully moved" << std::endl;
					mainBoard->printBoard();
				}
				//Green's turn
				currentPlayer = GREEN;
				if (MODE == DEBUG) {
					std::cout << "Green's turn" << std::endl;
					std::cout << "Insert your movement: " << std::endl;
				}
				inFile >> mov;
				if (mainBoard->isCheckmate(currentPlayer, ending)) {
					break;
				}
				if (mov == end) {
					if (end == "1-0") {
						ending = Board::Ending::VICTORY;
					}
					else if (end == "0-1") {
						ending = Board::Ending::DEFEAT;
					}
					else if (end == "1/2-1/2") {
						ending = Board::Ending::DRAW;
					}
					break;
				}
				if (mov.back() == '+' or mov.back() == '#') {
					mov = mov.substr(0, mov.length() - 1);
				}
				//Check if movement is valid
				if (not mainBoard->move(mov, currentPlayer, enp)) {
					if (MODE == DEBUG) {
						mainBoard->printBoard();
					}
					std::cout << "Cannot perform movement number " << ((count) / 2) + 1 << " for player green" << std::endl;
				}
				mainBoard->update();
				if (MODE == DEBUG) {
					std::cout << "Piece successfully moved" << std::endl;
					mainBoard->printBoard();
				}
				++count;
			}
			if (OUTPUT != MINIMAL) {
				mainBoard->printBoard();
				print_end(ending);
				std::cout << "Do you want to open the match in your default browser? Y / n" << std::endl;
				while (std::cin >> ans and ans != "Y" and ans != "n");
				std::string aux;
				inFile >> aux;
				inFile >> aux;
				if (ans == "Y") {
					open_browser(aux.c_str());
				}
			}
			inFile.close();
			delete mainBoard;
			if (OUTPUT != MINIMAL) {
				if (MODE == DEBUG) {
					printHelpDebug();
				}
				else {
					printHelp();
				}
			}
			else {
				std::cout << "GAME READ" << std::endl;
			}
		}

		void Application::largeFileRead_pgn() {
			if (OUTPUT != MINIMAL) {
				std::cout << "READ LARGE FILE MODE" << std::endl;
			}
			int currentPlayer;
			std::ifstream inFile;
			//system("dir");
			std::string directory;
			if (ENVIRONMENT == VISUAL) {
				directory = "ChessEngine\\examples\\";
			}
			else {
				directory = "..\\..\\Chess_org\\ChessEngine\\examples\\";
			}
			std::string full = "dir " + directory;
			//if (OUTPUT != MINIMAL) {
				system(full.c_str());
				std::cout << "You have these files available, type the one you'd like to read" << std::endl;
				std::cout << "Format: E.g. if you want to read file named 3.txt, type 3" << std::endl;
			//}
			std::string ans;
			std::cin >> ans;
			inFile.open(directory + ans + ".pgn");
			std::cout << ans << std::endl;
			if (not inFile) {
				std::cout << "Could not open file " << directory + ans + ".pgn" << std::endl;
				if (MODE == DEBUG) {
					printHelpDebug();
				}
				else {
					printHelp();
				}
				return;
			}
			int gameNum = 0;

			int victories, defeats, draws, checkmates, stalemates;
			victories = defeats = draws = checkmates = stalemates = 0;

			std::string mov;
			Timer tmr;
			while (inFile >> mov) {
				++gameNum;
				std::unique_ptr<Board> mainBoard(new Board);
				mainBoard->update();
				std::string result;
				while (inFile >> result and result != "[Result");
				inFile >> result;
				int i = 1;
				while (i < result.length() and result[i] != '"') {
					++i;
				}
				std::string end = result.substr(1, i - 1);
				if (MODE == DEBUG) {
					std::cout << end << std::endl;
				}
				inFile >> mov;
				std::string bullshit;
				while (std::getline(inFile, mov) and not mov.empty()) bullshit += mov;
				int count = 0;
				Board::Ending ending = Board::Ending::UNDEFINED;
				while (mov != end) {
					//Red's turn
					currentPlayer = RED;
					if (OUTPUT == NORMAL) {
						std::cout << (count / 2) + 1 << "." << std::endl;
					}
					++count;
					if (MODE == DEBUG) {
						std::cout << "Red's turn" << std::endl;
					}
					std::string acum;
					char ppp;
					while (inFile >> ppp and ppp != '.') {
						acum += ppp;
						if (acum == end) {
							mov = end;
							break;
						}
					}
					if (mainBoard->isCheckmate(currentPlayer, ending)) {
						if (ending == Board::Ending::CHECKMATE) {
							++checkmates;
						}
						else if (ending == Board::Ending::STALEMATE) {
							++stalemates;
						}
						break;
					}
					if (mov == end) {
						if (end == "1-0") {
							ending = Board::Ending::VICTORY;
							++victories;
						}
						else if (end == "0-1") {
							ending = Board::Ending::DEFEAT;
							++defeats;
						}
						else if (end == "1/2-1/2") {
							ending = Board::Ending::DRAW;
							++draws;
						}
						break;
					}
					inFile >> mov;
					//Play number
					if (mov.back() == '+' or mov.back() == '#') {
						mov = mov.substr(0, mov.length() - 1);
					}
					bool enp = false;
					//Check if movement is valid
					if (not mainBoard->move(mov, currentPlayer, enp)) {
						if (MODE == DEBUG) {
							std::cout << "Red's turn" << std::endl;
							mainBoard->update();
						}
						//mainBoard->printBoard();
						std::cout << "Cannot perform movement " << mov << " number " << ((count) / 2) + 1 << " for player red" << std::endl;
						std::cout << bullshit << std::endl;
					}
					enp = false;
					mainBoard->update();
					if (MODE == DEBUG) {
						std::cout << "Piece successfully moved" << std::endl;
					}
					//Green's turn
					currentPlayer = GREEN;
					if (MODE == DEBUG) {
						std::cout << "Green's turn" << std::endl;
					}
					if (mainBoard->isCheckmate(currentPlayer, ending)) {
						if (ending == Board::Ending::CHECKMATE) {
							++checkmates;
						}
						else if (ending == Board::Ending::STALEMATE) {
							++stalemates;
						}
						break;
					}
					inFile >> mov;

					if (mov == end) {
						if (end == "1-0") {
							ending = Board::Ending::VICTORY;
							++victories;
						}
						else if (end == "0-1") {
							ending = Board::Ending::DEFEAT;
							++defeats;
						}
						else if (end == "1/2-1/2") {
							ending = Board::Ending::DRAW;
							++draws;
						}
						break;
					}
					//std::cout << mov << std::endl;
					if (mov.back() == '+' or mov.back() == '#') {
						mov = mov.substr(0, mov.length() - 1);
					}
					//Check if movement is valid
					if (not mainBoard->move(mov, currentPlayer, enp)) {
						mainBoard->update();
						if (MODE == DEBUG) {
							std::cout << "Green's turn" << std::endl;
						}
						//mainBoard->printBoard();
						std::cout << "Cannot perform movement " << mov << " number " << ((count) / 2) + 1 << " for player green" << std::endl;
						std::cout << bullshit << std::endl;
					}
					mainBoard->update();
					if (MODE == DEBUG) {
						std::cout << "Piece successfully moved" << std::endl;
					}
					++count;
				}
				std::cout << "Game number " << gameNum << " succsessfuly read\n";
				if (OUTPUT != MINIMAL) {
					std::cout << "Ending: ";
					print_end(ending);
				}
			}
			double t = tmr.elapsed();
			inFile.close();
			std::cout << "Time elapsed: " << t << " (" << double(gameNum)/t << " games/sec)\n";
			std::cout << "READ " << gameNum << " game(s)\n";
			std::cout << "Total victories: " << victories << std::endl;
			std::cout << "Total defeats: " << defeats << std::endl;
			std::cout << "Total draws: " << draws << std::endl;
			std::cout << "Total checkmates: " << checkmates << std::endl;
			std::cout << "Total stalemates: " << stalemates << std::endl;
			if (OUTPUT != MINIMAL) {
				if (MODE == DEBUG) {
					printHelpDebug();
				}
				else {
					printHelp();
				}
			}
		}

		bool Application::open_browser(const char* URL) const{
			HWND parent = NULL;
			// Try normally, with the default verb (which will typically be "open")
			HINSTANCE result = ShellExecuteA(parent, NULL, URL, NULL, NULL, SW_SHOWNORMAL);

			// If that fails due to privileges, let's ask for more and try again
			if ((int)result == SE_ERR_ACCESSDENIED) {
				result = ShellExecuteA(parent, "runas", URL, NULL, NULL, SW_SHOWNORMAL);
			}

			// Return whether or not we were successful.
			return ((int)result > 32);
		}

		void Application::print_end(Board::Ending status) const{
			switch (status) {
				case Board::Ending::STALEMATE:
					std::cout << "STALEMATE\n";
					break;
				case Board::Ending::CHECKMATE:
					std::cout << "CHECKMATE\n";
					break;
				case Board::Ending::DRAW:
					std::cout << "DRAW\n";
					break;
				case Board::Ending::FIFTYRULE:
					std::cout << "FIFTYRULE\n";
					break;
				case Board::Ending::VICTORY:
					std::cout << "VICTORY\n";
					break;
				case Board::Ending::DEFEAT:
					std::cout << "DEFEAT\n";
					break;
				case Board::Ending::RESIGN:
					std::cout << "RESIGN\n";
					break;
				default:
					std::cout << "No such ending type\n";
					break;
			}
		}

		void Application::credits() const{
			std::cout << "Game developed by Jurymax99" << std::endl;
			if (MODE == DEBUG) {
				printHelpDebug();
			}
			else {
				printHelp();
			}
		}
	}
}