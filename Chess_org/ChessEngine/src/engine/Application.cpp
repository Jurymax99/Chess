#include "Application.h"
#include "Board.h"
#include <stack>
#include <fstream>
#include <windows.h>
#include <shellapi.h>		//For browser search

namespace Chess {
	namespace Engine {
		Application::Application()
		{
			std::cout << "Chess started ... " << std::endl;
		}

		Application::~Application()
		{
			std::cout << "Chess ended ... " << std::endl;
		}

		int Application::gameCount = 0;

		void Application::printHelpDebug(){
			std::cout << "You can: P / F / M / C / q" << std::endl;
			std::cout << "    (P)lay" << std::endl;
			std::cout << "    Read a (F)ile with a PGN formatted game" << std::endl;
			std::cout << "    Input (M)anually a PGN formatted game" << std::endl;
			std::cout << "    Roll the (C)redits" << std::endl;
			std::cout << "    (q)uit" << std::endl;
		}

		void Application::printHelp(){
			std::cout << "You can: P / F / M / C / q" << std::endl;
			std::cout << "    (P)lay" << std::endl;
			std::cout << "    Read a (F)ile with a PGN formatted game" << std::endl;
			std::cout << "    Input (M)anually a PGN formatted game" << std::endl;
			std::cout << "    Roll the (C)redits" << std::endl;
			std::cout << "    (q)uit" << std::endl;
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
							//Read a manual PGN game
						case 'F':
							++gameCount;
							ended = false;
							fileRead_pgn();
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
							std::cout << "Goodbye :)" << std::endl;
							exit(1);
							break;
						default:
							printHelp();
							break;
						}
					}
				}
				else {
					std::cout << "Cannot start another game while there is one active" << std::endl;
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
							//Read a manual PGN game
						case 'F':
							++gameCount;
							ended = false;
							fileRead_pgn();
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
							std::cout << "Goodbye :)" << std::endl;
							exit(1);
							break;
						default:
							printHelpDebug();
							break;
						}
					}
				}
				else {
					std::cout << "Cannot start another game while there is one active" << std::endl;
				}
			}
			else {
				std::cout << "No known app mode" << std::endl;
			}
		}

		void Application::play() {
			std::cout << "PLAY MODE" << std::endl;
			std::cout << "Game #" << gameCount << " started" << std::endl;
			Board* mainBoard = new Board;
			mainBoard->isChecked();
			mainBoard -> printBoard();
			int currentPlayer;
			std::string mov;
			while (not ended) {
				//Red's turn
				currentPlayer = RED;
				std::cout << "Red's turn" << std::endl;
				mainBoard->isChecked();
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
					mainBoard->printBoard();
					mainBoard->isChecked();
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
				//mainBoard->isChecked();
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
				//Check if movement is valid
				while (not ended and not mainBoard->move(mov, currentPlayer, enp)) {
					std::cout << "Green's turn" << std::endl;
					mainBoard->printBoard();
					mainBoard->isChecked();
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
				mainBoard->printBoard();
				mainBoard->isChecked();
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
			mainBoard->isChecked();
			mainBoard->printBoard();
			int currentPlayer;
			std::string mov;
			while (not ended) {
				//Red's turn
				currentPlayer = RED;
				std::cout << "Red's turn" << std::endl;
				//mainBoard->isChecked();
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
					//mainBoard->isChecked();
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
				mainBoard->isChecked();
				//mainBoard->isChecked();
				mainBoard->printBoard();

				//Green's turn
				currentPlayer = GREEN;
				std::cout << "Green's turn" << std::endl;
				//mainBoard->isChecked();
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
					mainBoard->isChecked();
					//mainBoard->isChecked();
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
				mainBoard->isChecked();
				//mainBoard->isChecked();
				mainBoard->printBoard();
			}
			delete mainBoard;
			if (MODE == DEBUG) {
				printHelpDebug();
			}
			else {
				std::cout << "Do you want to (P)lay, (R)ead a game or (q)uit? P/R/q" << std::endl;
			}
		}

		void Application::fileRead_pgn() {
			std::cout << "READ FILE MODE" << std::endl;
			std::cout << "Game #" << gameCount << " started" << std::endl;
			Board* mainBoard = new Board;
			int currentPlayer;
			std::ifstream inFile;
			if (MODE == DEBUG) {
				mainBoard->isChecked();
				mainBoard->printBoard();
			}
			system("dir ChessEngine\\examples\\");
			std::cout << "You have these files available, type the one you'd like to read" << std::endl;
			std::cout << "Format: E.g. if you want to read file named 3.txt, type 3" << std::endl;
			std::string ans;
			std::cin >> ans;
			inFile.open("ChessEngine\\examples\\" + ans + ".txt");
			if (not inFile) {
				std::cout << "Could not open file" << std::endl;
				ended = true;
			}
			std::string playcount;
			while (inFile >> playcount and playcount != "[PlyCount");
			inFile >> playcount;
			int i = 1;
			while (i < playcount.length() and playcount[i] != '"') {
				++i;
			}
			int Plycount = stoi(playcount.substr(1, i - 1));
			int temp = Plycount;
			std::cout << Plycount << std::endl;
			std::string mov;
			while (Plycount > 0) {
				//Red's turn
				currentPlayer = RED;
				if (MODE == DEBUG) {
					std::cout << "Red's turn" << std::endl;
					mainBoard->isChecked();
					std::cout << "Insert your movement: " << std::endl;
				}
				char ppp;
				while (inFile >> ppp and ppp != '.');
				inFile >> mov;
				//Play number
				--Plycount;
				if (mov.back() == '+' or mov.back() == '#') {
					mov = mov.substr(0, mov.length() - 1);
				}
				bool enp = false;
				//Check if movement is valid
				if (not ended and not mainBoard->move(mov, currentPlayer, enp)) {
					if (MODE == DEBUG) {
						std::cout << "Red's turn" << std::endl;
						mainBoard->isChecked();
						mainBoard->printBoard();
					}
					std::cout << "Cannot perform movement number " << ((temp - Plycount) / 2) + 1 << " for player red" << std::endl;
					if (mov == "quit") {
						ended = true;
						break;
					}
				}
				if (ended) {
					break;
				}
				enp = false;
				if (MODE == DEBUG) {
					std::cout << "Piece successfully moved" << std::endl;
					mainBoard->isChecked();
					mainBoard->printBoard();
				}

				if (Plycount == 0) {
					break;
				}

				//Green's turn
				currentPlayer = GREEN;
				if (MODE == DEBUG) {
					std::cout << "Green's turn" << std::endl;
					std::cout << "Insert your movement: " << std::endl;
				}
				inFile >> mov;
				--Plycount;
				if (mov.back() == '+') {
					mov = mov.substr(0, mov.length() - 1);
				}
				//Check if movement is valid
				if (not ended and not mainBoard->move(mov, currentPlayer, enp)) {
					if (MODE == DEBUG) {
						std::cout << "Green's turn" << std::endl;
						mainBoard->isChecked();
						mainBoard->printBoard();
					}
					std::cout << "Cannot perform movement number " << ((temp - Plycount) / 2) + 1 << " for player green" << std::endl;
					if (mov == "quit") {
						ended = true;
						break;
					}
				}
				if (ended) {
					break;
				}
				if (MODE == DEBUG) {
					std::cout << "Piece successfully moved" << std::endl;
					mainBoard->isChecked();
					mainBoard->printBoard();
				}
			}
			mainBoard->printBoard();
			std::cout << "Do you want to open the match in your default browser? Y / n" << std::endl;
			while (std::cin >> ans and ans != "Y" and ans != "n");
			std::string aux;
			inFile >> aux;
			inFile >> aux;
			if (ans == "Y") {
				open_browser(aux.c_str());
			}
			inFile.close();
			delete mainBoard;
			if (MODE == DEBUG) {
				printHelpDebug();
			}
			else {
				printHelp();
			}
		}

		bool Application::open_browser(const char* URL) {
			HWND parent = NULL;
			// Try normally, with the default verb (which will typically be "open")
			HINSTANCE result = ShellExecuteA(parent, NULL, URL, NULL, NULL, SW_SHOWNORMAL);

			// If that fails due to privileges, let's ask for more and try again
			if ((int)result == SE_ERR_ACCESSDENIED)
				result = ShellExecuteA(parent, "runas", URL, NULL, NULL, SW_SHOWNORMAL);

			// Return whether or not we were successful.
			return ((int)result > 32);
		}

		void Application::credits() {
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