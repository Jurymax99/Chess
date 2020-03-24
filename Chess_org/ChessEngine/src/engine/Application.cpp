#include "Application.h"
#include "Board.h"
#include <stack>

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

		void Application::start(int mode) {
			if (ended) {
				std::cout << "Do you want to (P)lay, (R)ead a game or (q)uit? P/R/q" << std::endl;
				char ans;
				while (std::cin >> ans) {
					switch (ans) {
						//Play a game
					case 'P':
						++gameCount;
						ended = false;
						play(mode);
						break;
						//Read a game
					case 'R':
						++gameCount;
						ended = false;
						read_pgn(mode);
						break;
						//Exit the program
					case 'q':
						std::cout << "Goodbye :)" << std::endl;
						exit(1);
						break;
					default:
						std::cout << "Do you want to (P)lay, (R)ead a game or (q)uit? P/R/q" << std::endl;
						break;
					}
				}
			}
			else {
				std::cout << "Cannot start another game while there is one active" << std::endl;
			}
		}

		void Application::play(int mode) {
			std::cout << "PLAY MODE" << std::endl;
			std::cout << "Game #" << gameCount << " started" << std::endl;
			Board* mainBoard = new Board;
			mainBoard->isChecked();
			mainBoard -> printBoard(mode);
			int currentPlayer;
			std::string mov;
			while (not ended) {
				//Red's turn
				currentPlayer = RED;
				std::cout << "Red's turn" << std::endl;
				//mainBoard->isChecked();
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
					//mainBoard->isChecked();
					mainBoard->printBoard(mode);
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
				mainBoard->printBoard(mode);

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
					//mainBoard->isChecked();
					mainBoard->printBoard(mode);
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
				mainBoard->printBoard(mode);
			}
			delete mainBoard;
			std::cout << "Do you want to (P)lay, (R)ead a game or (q)uit? P/R/q" << std::endl;
		}

		void Application::read_pgn(int mode) {
			std::cout << "READ MODE" << std::endl;
			std::cout << "Game #" << gameCount << " started" << std::endl;
			Board* mainBoard = new Board;
			mainBoard->updateThreats();
			mainBoard->printBoard(mode);
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
					mainBoard->printBoard(mode);
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
				mainBoard->updateThreats();
				//mainBoard->isChecked();
				mainBoard->printBoard(mode);

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
					mainBoard->updateThreats();
					//mainBoard->isChecked();
					mainBoard->printBoard(mode);
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
				mainBoard->updateThreats();
				//mainBoard->isChecked();
				mainBoard->printBoard(mode);
			}
			delete mainBoard;
			std::cout << "Do you want to (P)lay, (R)ead a game or (q)uit? P/R/q" << std::endl;
		}
	}
}