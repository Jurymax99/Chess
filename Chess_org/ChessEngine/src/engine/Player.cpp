#include "Player.h"
#include "Board.h"
#include "Color.h"
#include "Utilities.h"
#include <windows.h>		//for SetConsoleTextAttribute

namespace Chess {
	namespace Engine {
		Player::Player() {
			Dead = std::vector <char>();
			int score = 0;
			king = { 0,0 };
			color = 0;
			pieceCount = 16;
		}

		Player::Player(int color) {
			this->color = color;
			Dead = std::vector <char>();
			int score = 0;
			pieceCount = 16;
			castleKing = castleQueen = true;
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

		void Player::addDead(const char& piece) {
			--pieceCount;
			Dead.push_back(piece);
			std::sort(Dead.begin(), Dead.end());
		}

		inline void Player::addKnight(Board& b, const int& i, const int& j) {
			if (b.inBound(i, j)) {
				if (not b.main(i,j).hasPiece()) {
					b.main(i,j).setThreat(color);
				}
				else if (b.main(i,j).checkPlayer() == (-color)) {
					b.main(i,j).setThreat(color);
				}
			}
		}

		void Player::addRookLike(Board& b, const int& i, const int& j) {
			//Search below
			int it = i + 1;
			while (it <= 7 and not b.main(it,j).hasPiece()) {
				b.main(it,j).setThreat(color);
				++it;
			}
			if (it <= 7 and b.main(it,j).checkPlayer() == (-color)) {
				b.main(it,j).setThreat(color);
			}
			//Search above
			it = i - 1;
			while (it >= 0 and not b.main(it,j).hasPiece()) {
				b.main(it,j).setThreat(color);
				--it;
			}
			if (it >= 0 and b.main(it,j).checkPlayer() == (-color)) {
				b.main(it,j).setThreat(color);
			}
			//Search to the right
			it = j + 1;
			while (it <= 7 and not b.main(i,it).hasPiece()) {
				b.main(i,it).setThreat(color);
				++it;
			}
			if (it <= 7 and b.main(i,it).checkPlayer() == (-color)) {
				b.main(i,it).setThreat(color);
			}
			//Search to the left
			it = j - 1;
			while (it >= 0 and not b.main(i,it).hasPiece()) {
				b.main(i,it).setThreat(color);
				--it;
			}
			if (it >= 0 and b.main(i,it).checkPlayer() == (-color)) {
				b.main(i,it).setThreat(color);
			}
		}

		void Player::addBishopLike(Board& b, const int& i, const int& j) {
			//Search diagonal left-down
			int it_h = i + 1;
			int it_w = j - 1;
			while (it_h <= 7 and it_w >= 0 and not b.main(it_h,it_w).hasPiece()) {
				b.main(it_h,it_w).setThreat(color);
				++it_h;
				--it_w;
			}
			if (it_h <= 7 and it_w >= 0 and b.main(it_h,it_w).checkPlayer() == (-color)) {
				b.main(it_h,it_w).setThreat(color);
			}
			//Search diagonal left-up
			it_h = i - 1;
			it_w = j - 1;
			while (it_h >= 0 and it_w >= 0 and not b.main(it_h,it_w).hasPiece()) {
				b.main(it_h,it_w).setThreat(color);
				--it_h;
				--it_w;
			}
			if (it_h >= 0 and it_w >= 0 and b.main(it_h,it_w).checkPlayer() == (-color)) {
				b.main(it_h,it_w).setThreat(color);
			}
			//Search diagonal right-down
			it_h = i + 1;
			it_w = j + 1;
			while (it_h <= 7 and it_w <= 7 and not b.main(it_h,it_w).hasPiece()) {
				b.main(it_h,it_w).setThreat(color);
				++it_h;
				++it_w;
			}
			if (it_h <= 7 and it_w <= 7 and b.main(it_h,it_w).checkPlayer() == (-color)) {
				b.main(it_h,it_w).setThreat(color);
			}
			//Search diagonal right-up
			it_h = i - 1;
			it_w = j + 1;
			while (it_h >= 0 and it_w <= 7 and not b.main(it_h,it_w).hasPiece()) {
				b.main(it_h,it_w).setThreat(color);
				--it_h;
				++it_w;
			}
			if (it_h >= 0 and it_w <= 7 and b.main(it_h,it_w).checkPlayer() == (-color)) {
				b.main(it_h,it_w).setThreat(color);
			}
		}

		void Player::updateThreats(Board& b, const bool& clean) {
			if (clean) {
				for (int i = 0; i < 8; ++i) {
					for (int j = 0; j < 8; ++j) {
						b.main(i,j).removeThreat();
					}
				}
			}
			int pawnConst;
			int i;
			if (color == RED) {
				pawnConst = -1;
				i = 7;
			}
			else {
				pawnConst = 1;
				i = 0;
			}
			int auxCount = 0;
			while((color == RED ? i >= 0 : i < 8) and auxCount <= pieceCount) {
				for (int j = 0; j < 8 and auxCount <= pieceCount; ++j) {
					//std::cout << char(j + 97) << char(8 - (i - 48)) << std::endl;
					if (b.main(i,j).hasPiece() and b.main(i,j).checkPlayer() == color) {
						switch (b.main(i,j).checkPieceType()) {
						case 'P':
							//Pawn
							++auxCount;
							if (b.inBound(i + pawnConst, j + 1)) {
								if (not b.main(i + pawnConst,j + 1).hasPiece()) {
									b.main(i + pawnConst,j + 1).setThreat(color);
								}
								else if (b.main(i + pawnConst,j + 1).checkPlayer() == -(color)) {
									b.main(i + pawnConst,j + 1).setThreat(color);
								}
							}
							if (b.inBound(i + pawnConst, j - 1)) {
								if (not b.main(i + pawnConst,j - 1).hasPiece()) {
									b.main(i + pawnConst,j - 1).setThreat(color);
								}
								else if (b.main(i + pawnConst,j - 1).checkPlayer() == -(color)) {
									b.main(i + pawnConst,j - 1).setThreat(color);
								}
							}
							break;
						case 'N':
							//Knight
							++auxCount;
							//Check -2, -1
							addKnight(b, i - 2, j - 1);
							//Check -2, 1
							addKnight(b, i - 2, j + 1);
							//Check -1, 2
							addKnight(b, i - 1, j + 2);
							//Check 1, 2
							addKnight(b, i + 1, j + 2);
							//Check 2, 1
							addKnight(b, i + 2, j + 1);
							//Check 2, -1
							addKnight(b, i + 2, j - 1);
							//Check 1,-2
							addKnight(b, i + 1, j - 2);
							//Check -1, -2
							addKnight(b, i - 1, j - 2);
							break;
						case 'B':
							//Bishop
							++auxCount;
							addBishopLike(b, i, j);
							break;
						case 'R':
							//Rook
							++auxCount;
							addRookLike(b, i, j);
							break;
						case 'Q':
							//Queen
							++auxCount;
							addRookLike(b, i, j);
							addBishopLike(b, i, j);
							break;
						case 'K':
							//King
							++auxCount;
							for (int ii = -1; ii < 2; ++ii) {
								for (int jj = -1; jj < 2; ++jj) {
									if (b.inBound(i + ii, j + jj)) {
										if (not b.main(i + ii,j + jj).hasPiece()) {
											b.main(i + ii,j + jj).setThreat(color);
										}
										else if (b.main(i + ii,j + jj).checkPlayer() == -(color)) {
											b.main(i + ii,j + jj).setThreat(color);
										}
									}
								}
							}
							break;
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
				std::cout << Dead[i] << " ";
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
				std::cout << col << Dead[i] << def << " ";
				std::cout.flush();
			}
		}
	}
}


