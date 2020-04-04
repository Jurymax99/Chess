#include "Player.h"
#include "Board.h"
#include <windows.h>		//for SetConsoleTextAttribute

namespace Chess {
	namespace Engine {
		Player::Player() {
			Dead = std::vector <Pieces::Piece>();
			Threat = std::set <PositionState, std::less<PositionState>>();
			int score = 0;
			king = { 0,0 };
			color = 0;
			pieceCount = 16;
		}

		Player::Player(int color) {
			this->color = color;
			Dead = std::vector <Pieces::Piece>();
			Threat = std::set <PositionState, std::less<PositionState>>();
			int score = 0;
			pieceCount = 16;
			if (color == RED) {
				king = { 7, 4 };
			}
			else if (color == GREEN) {
				king = { 0, 4 };
			}
			else {
				std::cout << "No known player" << std::endl;
				king = { 0,0 };
			}
		}

		void Player::addDead(Pieces::Piece piece) {
			--pieceCount;
			Dead.push_back(piece);
			std::sort(Dead.begin(), Dead.end());
		}

		Position Player::findMove(char type, const Position& dest, const Board& b) const{
			return  moves.findMove(type, dest, b);
		}

		Position Player::findCapture(char type, const Position& dest, const Board& b) const {
			return  moves.findCapture(type, dest, b);
		}

		Position Player::findAmbRMove(char type, int source_h, const Position& dest, const Board& b) const {
			return  moves.findMoveR(type, source_h, dest, b);
		}

		Position Player::findAmbFMove(char type, int source_w, const Position& dest, const Board& b) const {
			return  moves.findMoveF(type, source_w, dest, b);
		}

		Position Player::findDAmbMove(char type, int source_h, int source_w, const Position& dest, const Board& b) const {
			return moves.findMoveDA(type, source_h, source_w, dest, b);
		}

		Position Player::findAmbRCapture(char type, int source_h, const Position& dest, const Board& b) const {
			return  moves.findCaptureR(type, source_h, dest, b);
		}

		Position Player::findAmbFCapture(char type, int source_w, const Position& dest, const Board& b) const {
			return  moves.findCaptureF(type, source_w, dest, b);
		}

		Position Player::findDAmbCapture(char type, int source_h, int source_w, const Position& dest, const Board& b) const {
			return moves.findCaptureDA(type, source_h, source_w, dest, b);
		}

		void Player::addKnight(const Board& b, const int& i, const int& j, const int& enemyColor) {
			if (b.inBound(i, j)) {
				if (not b.main[i][j].hasPiece()) {
					Threat.insert(  { i , j, true });
				}
				else if (b.main[i][j].checkPlayer() == enemyColor) {
					Threat.insert(  { i , j, false });
				}
			}
		}

		void Player::addRookLike(const Board& b, const int& i, const int& j, const int& enemyColor) {
			//Search below
			int it = i + 1;
			while (it <= 7 and not b.main[it][j].hasPiece()) {
				Threat.insert(  { it, j, true });
				++it;
			}
			if (it <= 7 and b.main[it][j].checkPlayer() == enemyColor) {
				Threat.insert(  { it, j, false });
			}
			//Search above
			it = i - 1;
			while (it >= 0 and not b.main[it][j].hasPiece()) {
				Threat.insert(  { it, j, true });
				--it;
			}
			if (it >= 0 and b.main[it][j].checkPlayer() == enemyColor) {
				Threat.insert(  { it, j, false });
			}
			//Search to the right
			it = j + 1;
			while (it <= 7 and not b.main[i][it].hasPiece()) {
				Threat.insert(  { i, it, true });
				++it;
			}
			if (it <= 7 and b.main[i][it].checkPlayer() == enemyColor) {
				Threat.insert(  { i, it, false });
			}
			//Search to the left
			it = j - 1;
			while (it >= 0 and not b.main[i][it].hasPiece()) {
				Threat.insert(  { i, it, true });
				--it;
			}
			if (it >= 0 and b.main[i][it].checkPlayer() == enemyColor) {
				Threat.insert(  { i, it, false });
			}
		}

		void Player::addBishopLike(const Board& b, const int& i, const int& j, const int& enemyColor) {
			//Search diagonal left-down
			int it_h = i + 1;
			int it_w = j - 1;
			while (it_h <= 7 and it_w >= 0 and not b.main[it_h][it_w].hasPiece()) {
				Threat.insert(  { it_h, it_w, true });
				++it_h;
				--it_w;
			}
			if (it_h <= 7 and it_w >= 0 and b.main[it_h][it_w].checkPlayer() == enemyColor) {
				Threat.insert(  { it_h, it_w, false });
			}
			//Search diagonal left-up
			it_h = i - 1;
			it_w = j - 1;
			while (it_h >= 0 and it_w >= 0 and not b.main[it_h][it_w].hasPiece()) {
				Threat.insert(  { it_h, it_w, true });
				--it_h;
				--it_w;
			}
			if (it_h >= 0 and it_w >= 0 and b.main[it_h][it_w].checkPlayer() == enemyColor) {
				Threat.insert(  { it_h, it_w, false });
			}
			//Search diagonal right-down
			it_h = i + 1;
			it_w = j + 1;
			while (it_h <= 7 and it_w <= 7 and not b.main[it_h][it_w].hasPiece()) {
				Threat.insert(  { it_h, it_w, true });
				++it_h;
				++it_w;
			}
			if (it_h <= 7 and it_w <= 7 and b.main[it_h][it_w].checkPlayer() == enemyColor) {
				Threat.insert(  { it_h, it_w, false });
			}
			//Search diagonal right-up
			it_h = i - 1;
			it_w = j + 1;
			while (it_h >= 0 and it_w <= 7 and not b.main[it_h][it_w].hasPiece()) {
				Threat.insert(  { it_h, it_w, true });
				--it_h;
				++it_w;
			}
			if (it_h >= 0 and it_w <= 7 and b.main[it_h][it_w].checkPlayer() == enemyColor) {
				Threat.insert(  { it_h, it_w, false });
			}
		}

		void Player::updateThreats(const Board& b) {
			Threat.clear();
			int enemyColor;
			int pawnConst;
			int i;
			if (color == RED) {
				enemyColor = GREEN;
				pawnConst = -1;
				i = b.height - 1;
			}
			else if (color == GREEN) {
				enemyColor = RED;
				pawnConst = 1;
				i = 0;
			}
			else {
				std::cout << "No such known color" << std::endl;
				enemyColor = 0;
				pawnConst = 0;
			}
			
			int auxCount = 0;
			while((color == RED ? i >= 0 : i < b.height) and auxCount <= pieceCount) {
				for (int j = 0; j < b.width and auxCount <= pieceCount; ++j) {
					//std::cout << char(j + 97) << char(8 - (i - 48)) << std::endl;
					//Pawn
					if (b.hasFriendly('P', i, j, color)) {
						++auxCount;
						if (b.inBound(i + pawnConst, j + 1)) {
							if (not b.main[i + pawnConst][j + 1].hasPiece()) {
								Threat.insert(  { i + pawnConst, j + 1, true });
							}
							else if (b.main[i + pawnConst][j + 1].checkPlayer() == enemyColor) {
								Threat.insert(  { i + pawnConst, j + 1, false });
							}
						}
						if (b.inBound(i + pawnConst, j - 1)) {
							if (not b.main[i + pawnConst][j - 1].hasPiece()) {
								Threat.insert(  { i + pawnConst, j - 1, true });
							}
							else if (b.main[i + pawnConst][j - 1].checkPlayer() == enemyColor) {
								Threat.insert(  { i + pawnConst, j - 1, false });
							}
						}
					}
					//Knight
					else if (b.hasFriendly('N', i, j, color)) {
						++auxCount;
						//Check -2, -1
						addKnight(b, i - 2, j - 1, enemyColor);
						//Check -2, 1
						addKnight(b, i - 2, j + 1, enemyColor);
						//Check -1, 2
						addKnight(b, i - 1, j + 2, enemyColor);
						//Check 1, 2
						addKnight(b, i + 1, j + 2, enemyColor);
						//Check 2, 1
						addKnight(b, i + 2, j + 1, enemyColor);
						//Check 2, -1
						addKnight(b, i + 2, j - 1, enemyColor);
						//Check 1,-2
						addKnight(b, i + 1, j - 2, enemyColor);
						//Check -1, -2
						addKnight(b, i - 1, j - 2, enemyColor);
					}
					//Rook
					else if (b.hasFriendly('R', i, j, color)) {
						++auxCount;
						addRookLike(b, i, j, enemyColor);
					}
					//Bishop
					else if (b.hasFriendly('B', i, j, color)) {
						++auxCount;
						addBishopLike(b, i, j, enemyColor);
					}
					//Queen
					else if (b.hasFriendly('Q', i, j, color)) {
						++auxCount;
						addRookLike(b, i, j, enemyColor);
						addBishopLike(b, i, j, enemyColor);
					}
					//King
					else if (b.hasFriendly('K', i, j, color)) {
						++auxCount;
						for (int ii = -1; ii < 2; ++ii) {
							for (int jj = -1; jj < 2; ++jj) {
								if (b.inBound(i + ii, j + jj)) {
									if (not b.main[i + ii][j + jj].hasPiece()) {
										Threat.insert(  { i + ii, j + jj, true });
									}
									else if (b.main[i + ii][j + jj].checkPlayer() == enemyColor) {
										Threat.insert(  { i + ii, j + jj, false });
									}
								}
							}
						}
					}
				}
				color == RED ? --i : ++i;
			}
		}
		void Player::checkDeadRelease() const {
			int k;
			if (color == RED) {
				std::cout << "Red: ";
				k = 12;
			}
			else if (color == GREEN) {
				std::cout << "Green: ";
				k = 10;
			}
			else {
				std::cout << "No known player" << std::endl;
				k = 7;
			}
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, k);
			for (int i = 0; i < Dead.size(); ++i) {
				std::cout << Dead[i].checkType() << " ";
				std::cout.flush();
			}
			SetConsoleTextAttribute(hConsole, 7);
		}

		void Player::checkDeadDebug() const{
			Color::Modifier col;
			if (color == RED) {
				std::cout << "Red: ";
				col = Color::Modifier (Color::FG_RED);
			}
			else if (color == GREEN) {
				std::cout << "Green: ";
				col = Color::Modifier(Color::FG_GREEN);
			}
			else {
				std::cout << "No known player" << std::endl;
			}
			Color::Modifier def(Color::FG_DEFAULT);
			for (int i = 0; i < Dead.size(); ++i) {
				std::cout << col << Dead[i].checkType() << def << " ";
				std::cout.flush();
			}
		}

		void Player::checkThreats() const{
			if (color == RED) {
				std::cout << "Red threatening positions: ";
			}
			else if (color == GREEN) {
				std::cout << "Green threatening positions: ";
			}
			else {
				std::cout << "No known player" << std::endl;
			}
			auto it = Threat.begin();
			for (; it != Threat.end(); ++it) {
				std::cout << "[" << char(it->checkW() + 97) << char(8 - char(it->checkH() - 48)) << ", " << it->isEmpty() << "] ";
			}
			std::cout << std::endl;
		}
	}
}


