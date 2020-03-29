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
		}

		Player::Player(int color) {
			this->color = color;
			Dead = std::vector <Pieces::Piece>();
			Threat = std::set <PositionState, std::less<PositionState>>();
			int score = 0;
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

		bool Player::PositionState::operator<(const PositionState& rhs) const {
			if (h == rhs.h) {
				return w < rhs.w;
			}
			return h < rhs.h;
		}

		void Player::addDead(Pieces::Piece piece) {
			Dead.push_back(piece);
			std::sort(Dead.begin(), Dead.end());
		}

		bool Player::findThreat(int i, int j) {
			return Threat.find({ i,j, false }) != Threat.end();
		}

		bool Player::findThreat(int i, int j, bool cond) {
			return Threat.find({ i,j, cond }) != Threat.end();
		}

		bool Player::findThreat(Position p, bool cond) {
			return Threat.find({ p.h,p.w, cond }) != Threat.end();
		}

		Position Player::checkKingPosition(){
			return king;
		}

		void Player::checkKing() const {
			std::cout << "king is at [" << char(king.w + 97) << char(8 - char(king.h - 48)) << "]" << std::endl;
		}

		void Player::setKing(int h, int w) {
			king = { h,w };
		}

		void Player::addScore(int score) {
			this -> score += score;
		}

		Position Player::findMove(char type, Position dest, Board& b) {
			return  moves.findMove(type, dest, b);
		}

		Position Player::findCapture(char type, Position dest, Board& b) {
			return  moves.findCapture(type, dest, b);
		}

		Position Player::findAmbRMove(char type, int source_h, Position dest, Board& b) {
			return  moves.findMoveR(type, source_h, dest, b);
		}

		Position Player::findAmbFMove(char type, int source_w, Position dest, Board& b) {
			return  moves.findMoveF(type, source_w, dest, b);
		}

		void Player::updateThreats(Board& b) {
			Threat.clear();
			int enemyColor;
			int pawnConst;
			if (color == RED) {
				enemyColor = GREEN;
				pawnConst = -1;
			}
			else if (color == GREEN) {
				enemyColor = RED;
				pawnConst = 1;
			}
			else {
				std::cout << "No such known color" << std::endl;
				enemyColor = 0;
				pawnConst = 0;
			}
			for (int i = 0; i < b.height; ++i) {
				for (int j = 0; j < b.width; ++j) {
					//Pawn
					if (b.hasFriendly('P', i, j, color)) {
						if (b.inBound(i + pawnConst, j + 1)) {
							if (not b.main[i + pawnConst][j + 1].hasPiece()) {
								Threat.insert({ i + pawnConst, j + 1, true });
							}
							else if (b.main[i + pawnConst][j + 1].checkPlayer() == enemyColor) {
								Threat.insert({ i + pawnConst, j + 1, false });
							}
						}
						if (b.inBound(i + pawnConst, j - 1)) {
							if (not b.main[i + pawnConst][j - 1].hasPiece()) {
								Threat.insert({ i + pawnConst, j - 1, true });
							}
							else if (b.main[i + pawnConst][j - 1].checkPlayer() == enemyColor) {
								Threat.insert({ i + pawnConst, j - 1, false });
							}
						}
					}

					//Knight
					else if (b.hasFriendly('N', i, j, color)) {
						//Check -2, -1
						if (b.inBound(i - 2, j - 1)) {
							if (not b.main[i - 2][j - 1].hasPiece()) {
								Threat.insert({ i - 2, j - 1, true });
							}
							else if (b.main[i - 2][j - 1].checkPlayer() == enemyColor) {
								Threat.insert({ i - 2, j - 1, false });
							}
						}
						//Check -2, 1
						if (b.inBound(i - 2, j + 1)) {
							if (not b.main[i - 2][j + 1].hasPiece()) {
								Threat.insert({ i - 2, j + 1, true });
							}
							else if (b.main[i - 2][j + 1].checkPlayer() == enemyColor) {
								Threat.insert({ i - 2, j + 1, false });
							}
						}
						//Check -1, 2
						if (b.inBound(i - 1, j + 2)) {
							if (not b.main[i - 1][j + 2].hasPiece()) {
								Threat.insert({ i - 1, j + 2, true });
							}
							else if (b.main[i - 1][j + 2].checkPlayer() == enemyColor) {
								Threat.insert({ i - 1, j + 2, false });
							}
						}
						//Check 1, 2
						if (b.inBound(i + 1, j + 2)) {
							if (not b.main[i + 1][j + 2].hasPiece()) {
								Threat.insert({ i + 1, j + 2, true });
							}
							else if (b.main[i + 1][j + 2].checkPlayer() == enemyColor) {
								Threat.insert({ i + 1, j + 2, false });
							}
						}
						//Check 2, 1
						if (b.inBound(i + 2, j + 1)) {
							if (not b.main[i + 2][j + 1].hasPiece()) {
								Threat.insert({ i + 2, j + 1, true });
							}
							else if (b.main[i + 2][j + 1].checkPlayer() == enemyColor) {
								Threat.insert({ i + 2, j + 1, false });
							}
						}
						//Check 2, -1
						if (b.inBound(i + 2, j - 1)) {
							if (not b.main[i + 2][j - 1].hasPiece()) {
								Threat.insert({ i + 2, j - 1, true });
							}
							else if (b.main[i + 2][j - 1].checkPlayer() == enemyColor) {
								Threat.insert({ i + 2, j - 1, false });
							}
						}
						//Check 1,-2
						if (b.inBound(i + 1, j - 2)) {
							if (not b.main[i + 1][j - 2].hasPiece()) {
								Threat.insert({ i + 1, j - 2, true });
							}
							else if (b.main[i + 1][j - 2].checkPlayer() == enemyColor) {
								Threat.insert({ i + 1, j - 2, false });
							}
						}
						//Check -1, -2
						if (b.inBound(i - 1, j - 2)) {
							if (not b.main[i - 1][j - 2].hasPiece()) {
								Threat.insert({ i - 1, j - 2, true });
							}
							else if (b.main[i - 1][j - 2].checkPlayer() == enemyColor) {
								Threat.insert({ i - 1, j - 2, false });
							}
						}
					}
					//Rook
					else if (b.hasFriendly('R', i, j, color)) {
						//Search above
						int it = i + 1;
						while (it <= 7 and not b.main[it][j].hasPiece()) {
							Threat.insert({ it, j, true });
							++it;
						}
						if (it <= 7 and b.main[it][j].checkPlayer() == enemyColor) {
							Threat.insert({ it, j, false });
						}
						//Search below
						it = i - 1;
						while (it >= 0 and not b.main[it][j].hasPiece()) {
							Threat.insert({ it, j, true });
							--it;
						}
						if (it >= 0 and b.main[it][j].checkPlayer() == enemyColor) {
							Threat.insert({ it, j, false });
						}
						//Search to the right
						it = j + 1;
						while (it <= 7 and not b.main[i][it].hasPiece()) {
							Threat.insert({ i, it, true });
							++it;
						}
						if (it <= 7 and b.main[i][it].checkPlayer() == enemyColor) {
							Threat.insert({ i, it, false });
						}
						//Search to the left
						it = j - 1;
						while (it >= 0 and not b.main[i][it].hasPiece()) {
							Threat.insert({ i, it });
							--it;
						}
						if (it >= 0 and b.main[i][it].checkPlayer() == enemyColor) {
							Threat.insert({ i, it, false });
						}
					}
					//Bishop
					else if (b.hasFriendly('B', i, j, color)) {
						//Search diagonal left-up
						int it_h = i + 1;
						int it_w = j - 1;
						while (it_h <= 7 and it_w >= 0 and not b.main[it_h][it_w].hasPiece()) {
							Threat.insert({ it_h, it_w, true });
							++it_h;
							--it_w;
						}
						if (it_h <= 7 and it_w >= 0 and b.main[it_h][it_w].checkPlayer() == enemyColor) {
							Threat.insert({ it_h, it_w, false });
						}
						//Search diagonal left-down
						it_h = i - 1;
						it_w = j - 1;
						while (it_h >= 0 and it_w >= 0 and not b.main[it_h][it_w].hasPiece()) {
							Threat.insert({ it_h, it_w, true });
							--it_h;
							--it_w;
						}
						if (it_h >= 0 and it_w >= 0 and b.main[it_h][it_w].checkPlayer() == enemyColor) {
							Threat.insert({ it_h, it_w, false });
						}
						//Search diagonal right-up
						it_h = i + 1;
						it_w = j + 1;
						while (it_h <= 7 and it_w <= 7 and not b.main[it_h][it_w].hasPiece()) {
							Threat.insert({ it_h, it_w, true });
							++it_h;
							++it_w;
						}
						if (it_h <= 7 and it_w <= 7 and b.main[it_h][it_w].checkPlayer() == enemyColor) {
							Threat.insert({ it_h, it_w, false });
						}
						//Search diagonal right-down
						it_h = i - 1;
						it_w = j + 1;
						while (it_h >= 0 and it_w <= 7 and not b.main[it_h][it_w].hasPiece()) {
							Threat.insert({ it_h, it_w, true });
							--it_h;
							++it_w;
						}
						if (it_h >= 0 and it_w <= 7 and b.main[it_h][it_w].checkPlayer() == enemyColor) {
							Threat.insert({ it_h, it_w, false });
						}
					}
					//Queen
					else if (b.hasFriendly('Q', i, j, color)) {
						//Search above
						int it = i + 1;
						while (it <= 7 and not b.main[it][j].hasPiece()) {
							Threat.insert({ it, j, true });
							++it;
						}
						if (it <= 7 and b.main[it][j].checkPlayer() == enemyColor) {
							Threat.insert({ it, j, false });
						}
						//Search below
						it = i - 1;
						while (it >= 0 and not b.main[it][j].hasPiece()) {
							Threat.insert({ it, j, true });
							--it;
						}
						if (it >= 0 and b.main[it][j].checkPlayer() == enemyColor) {
							Threat.insert({ it, j, false });
						}
						//Search to the right
						it = j + 1;
						while (it <= 7 and not b.main[i][it].hasPiece()) {
							Threat.insert({ i, it, true });
							++it;
						}
						if (it <= 7 and b.main[i][it].checkPlayer() == enemyColor) {
							Threat.insert({ i, it, false });
						}
						//Search to the left
						it = j - 1;
						while (it >= 0 and not b.main[i][it].hasPiece()) {
							Threat.insert({ i, it, false });
							--it;
						}
						if (it >= 0 and b.main[i][it].checkPlayer() == enemyColor) {
							Threat.insert({ i, it, false });
						}
						//Search diagonal left-up
						int it_h = i + 1;
						int it_w = j - 1;
						while (it_h <= 7 and it_w >= 0 and not b.main[it_h][it_w].hasPiece()) {
							Threat.insert({ it_h, it_w, true });
							++it_h;
							--it_w;
						}
						if (it_h <= 7 and it_w >= 0 and b.main[it_h][it_w].checkPlayer() == enemyColor) {
							Threat.insert({ it_h, it_w, false });
						}
						//Search diagonal left-down
						it_h = i - 1;
						it_w = j - 1;
						while (it_h >= 0 and it_w >= 0 and not b.main[it_h][it_w].hasPiece()) {
							Threat.insert({ it_h, it_w, true });
							--it_h;
							--it_w;
						}
						if (it_h >= 0 and it_w >= 0 and b.main[it_h][it_w].checkPlayer() == enemyColor) {
							Threat.insert({ it_h, it_w, false });
						}
						//Search diagonal right-up
						it_h = i + 1;
						it_w = j + 1;
						while (it_h <= 7 and it_w <= 7 and not b.main[it_h][it_w].hasPiece()) {
							Threat.insert({ it_h, it_w, true });
							++it_h;
							++it_w;
						}
						if (it_h <= 7 and it_w <= 7 and b.main[it_h][it_w].checkPlayer() == enemyColor) {
							Threat.insert({ it_h, it_w, false });
						}
						//Search diagonal right-down
						it_h = i - 1;
						it_w = j + 1;
						while (it_h >= 0 and it_w <= 7 and not b.main[it_h][it_w].hasPiece()) {
							Threat.insert({ it_h, it_w, true });
							--it_h;
							++it_w;
						}
						if (it_h >= 0 and it_w <= 7 and b.main[it_h][it_w].checkPlayer() == enemyColor) {
							Threat.insert({ it_h, it_w, false });
						}
					}
					//King
					else if (b.hasFriendly('K', i, j, color)) {
						for (int ii = -1; ii < 2; ++ii) {
							for (int jj = -1; jj < 2; ++jj) {
								if (b.inBound(i + ii, j + jj)) {
									if (not b.main[i + ii][j + jj].hasPiece()) {
										Threat.insert({ i + ii, j + jj, true });
									}
									else if (b.main[i + ii][j + jj].checkPlayer() == enemyColor) {
										Threat.insert({ i + ii, j + jj, false });
									}
								}
							}
						}
					}
				}
			}
		}

		void Player::updateMoveSet(Board& b){
			moves.update(color, b);
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

		int Player::checkScore() const {
			return score;
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
				std::cout << "[" << char((*it).w + 97) << char(8 - char((*it).h - 48)) << ", " << (*it).empty << "] ";
			}
			std::cout << std::endl;
		}

		bool Player::hasMoves() const {
			return not moves.empty();
		}

		void Player::checkMoves() const{
			if (MODE == DEBUG) {
				moves.checkDebug(color);
			}
		}
	}
}


