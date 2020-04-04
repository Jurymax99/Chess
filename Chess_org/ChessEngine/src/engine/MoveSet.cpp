#include "MoveSet.h"
#include "Board.h"
#include <tuple>		//for std::tie


namespace Chess {
	namespace Engine {
		void MoveSet::update(int color, int pieceCount, Board& b) {
			Set.clear();
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
				i = 0;
			}
			int auxCount = 0;
			while ((color == RED ? i >= 0 : i < b.height) and auxCount <= pieceCount) {
				for (int j = 0; j < b.width and auxCount <= pieceCount; ++j) {
					bool check = false;
					//Pawn
					if (b.hasFriendly('P', i, j, color)) {
						++auxCount;
						if ((color == RED and i > 1) or (color == GREEN and i < 6)) {
							//Pawn 1 up move
							if (b.inBound(i + pawnConst, j) and
								not b.main[i + pawnConst][j].hasPiece() and
								b.makeFakeMove('P', i, j, i + pawnConst, j, color, check)) {
								
								Set.insert({ 'P', {i,j},{ i + pawnConst, j}, false, true, false, false, false, check });
								check = false;
							}
							//Pawn 2 up move
							if (b.inBound(i + 2 * pawnConst, j) and
								not b.main[i + pawnConst][j].hasPiece() and
								not b.main[i + 2 * pawnConst][j].hasPiece() and
								b.main[i][j].isFirstMov() and
								b.makeFakeMove('P', i, j, i + 2*pawnConst, j, color, check)) {
								
								Set.insert({ 'P', {i,j},{ i + 2 * pawnConst, j}, false, true, false, false, false, check });
								check = false;
							}
							//Pawn capture
							if (b.hasEnemy(i + pawnConst, j + 1, color) and
								b.makeFakeCapture('P', i, j, i + pawnConst, j + 1, color, check)) {
								Set.insert({ 'P', {i,j},{ i + pawnConst, j + 1}, true, false, false, false, false, check });
								check = false;
							}
							if (b.hasEnemy(i + pawnConst, j - 1, color) and
								b.makeFakeCapture('P', i, j, i + pawnConst, j - 1, color, check)) {
								Set.insert({ 'P', {i,j},{ i + pawnConst, j - 1}, true, false, false, false, false, check });
								check = false;
							}
							//Enpassants
							if (b.hasEnemy('P', i, j + 1, color) and
								b.target.possible and
								b.target.h == i and
								b.target.w == j + 1 and
								not b.main[i + pawnConst][j + 1].hasPiece() and
								b.makeFakeEnPassant(i,j,i + pawnConst, j + 1, i, j + 1, color, check)) {
								Set.insert({ 'P', {i,j},{ i + pawnConst, j + 1}, true, false, false, false, false, check });
								check = false;
							}
							if (b.hasEnemy('P', i, j - 1, color) and
								b.target.possible and
								b.target.h == i and
								b.target.w == j - 1 and
								not b.main[i + pawnConst][j - 1].hasPiece() and
								b.makeFakeEnPassant(i, j, i + pawnConst, j - 1, i, j - 1, color, check)) {
								Set.insert({ 'P', {i,j},{ i + pawnConst, j - 1}, true, false, false, false, false, check });
								check = false;
							}
						}
						else {
							//Pawn 1 up move promote
							if (b.inBound(i + pawnConst, j)) {
								if (not b.main[i + pawnConst][j].hasPiece() and
									b.makeFakeMovePro(i, j, i + pawnConst, j, color, check)) {
									Set.insert({ 'P',{i,j},{ i + pawnConst, j}, false, true, false, false, true, check });
									check = false;
								}
							}
							//Pawn capture
							if (b.hasEnemy(i + pawnConst, j + 1, color)
								and	b.makeFakeCapturePro(i, j, i + pawnConst, j + 1, color, check)) {
								Set.insert({ 'P',{i,j},{ i + pawnConst, j + 1}, true, false, false, false, true, check });
								check = false;
							}
							if (b.hasEnemy(i + pawnConst, j - 1, color)
								and b.makeFakeCapturePro(i, j, i + pawnConst, j - 1, color, check)) {
								Set.insert({ 'P', {i,j},{ i + pawnConst, j - 1}, true, false, false, false, true, check });
								check = false;
							}
						}
					}
					
					//Knight
					else if (b.hasFriendly('N', i, j, color)) {
						++auxCount;
						//Check -2, -1
						addKnight(b, i, j, i - 2, j - 1, color, enemyColor);
						
						//Check -2, 1
						addKnight(b, i, j, i - 2, j + 1, color, enemyColor);
						
						//Check -1, -2
						addKnight(b, i, j, i - 1, j - 2, color, enemyColor);						
						
						//Check -1, 2
						addKnight(b, i, j, i - 1, j + 2, color, enemyColor);
						
						//Check 1,-2
						addKnight(b, i, j, i + 1, j - 2, color, enemyColor);
						
						//Check 1, 2
						addKnight(b, i, j, i + 1, j + 2, color, enemyColor);
						
						//Check 2, -1
						addKnight(b, i, j, i + 2, j - 1, color, enemyColor);
						
						//Check 2, 1
						addKnight(b, i, j, i + 2, j + 1, color, enemyColor);
					}
					//Rook
					else if (b.hasFriendly('R', i, j, color)) {
						++auxCount;
						//Search below
						int it = i + 1;
						while (it <= 7 and not b.main[it][j].hasPiece()) {
							if (b.makeFakeMove('R', i, j, it, j, color, check)) {
								Set.insert({ 'R', {i,j},{ it, j }, false, true, false, false, false, check });
								check = false;
							}
							++it;
						}
						if (it <= 7 and b.main[it][j].checkPlayer() == enemyColor and
							b.makeFakeCapture('R', i, j, it, j, color, check)) {
							Set.insert({ 'R', {i,j},{ it, j }, true, false, false, false, false, check });
							check = false;
						}
						//Search above
						it = i - 1;
						while (it >= 0 and not b.main[it][j].hasPiece()) {
							if (b.makeFakeMove('R', i, j, it, j, color, check)) {
								Set.insert({ 'R', {i,j},{ it, j }, false, true, false, false, false, check });
								check = false;
							}
							--it;
						}
						if (it >= 0 and b.main[it][j].checkPlayer() == enemyColor and
							b.makeFakeCapture('R', i, j, it, j, color, check)) {
							Set.insert({ 'R', {i,j},{ it, j }, true, false, false, false, false, check });
							check = false;
						}
						//Search to the right
						it = j + 1;
						while (it <= 7 and not b.main[i][it].hasPiece()) {
							if (b.makeFakeMove('R', i, j, i, it, color, check)) {
								Set.insert({ 'R', {i,j},{ i, it }, false, true, false, false, false, check });
								check = false;
							}
							++it;
						}
						if (it <= 7 and b.main[i][it].checkPlayer() == enemyColor and
							b.makeFakeCapture('R', i, j, i, it, color, check)) {
							Set.insert({ 'R', {i,j},{ i, it }, true, false, false, false, false, check });
							check = false;
						}
						//Search to the left
						it = j - 1;
						while (it >= 0 and not b.main[i][it].hasPiece()) {
							if (b.makeFakeMove('R', i, j, i, it, color, check)) {
								Set.insert({ 'R', {i,j},{ i, it }, false, true, false, false, false, check });
								check = false;
							}
							--it;
						}
						if (it >= 0 and b.main[i][it].checkPlayer() == enemyColor and
							b.makeFakeCapture('R', i, j, i, it, color, check)) {
							Set.insert({ 'R', {i,j},{ i, it }, true, false, false, false, false, check });
							check = false;
						}
						//castle kingside
						if (j == 7 and (i == 7 or i == 0) and b.castleFakeKingside(color, check)) {
							int h;
							if (color == RED) {
								h = 7;
							}
							else if(color == GREEN){
								h = 0;
							}	
							else {
								std::cout << "No known player" << std::endl;
							}
							Set.insert({ 'R', {h,7},{ h, 5 }, false, true, true, false, false, check });
							Set.insert({ 'K', {h,4},{ h, 6 }, false, true, true, false, false, check });
							check = false;
						}
						//castle queenside
						else if (j == 0 and (i == 7 or i == 0) and b.castleFakeQueenside(color, check)) {
							int h;
							if (color == RED) {
								h = 7;
							}
							else if (color == GREEN) {
								h = 0;
							}
							else {
								std::cout << "No known player" << std::endl;
							}
							Set.insert({ 'R', {h,0},{ h, 3 }, false, true, false, true, false, check });
							Set.insert({ 'K', {h,4},{ h, 2 }, false, true, false, true, false, check });
							check = false;
						}
					}
					//Bishop
					else if (b.hasFriendly('B', i, j, color)) {
						++auxCount;
						//Search diagonal left-down
						int it_h = i + 1;
						int it_w = j - 1;
						while (it_h <= 7 and it_w >= 0 and not b.main[it_h][it_w].hasPiece()) {
							if (b.makeFakeMove('B', i, j, it_h, it_w, color, check)) {
								Set.insert({ 'B', {i,j},{ it_h, it_w }, false, true, false, false, false, check });
								check = false;
							}
							++it_h;
							--it_w;
						}
						if (it_h <= 7 and it_w >= 0 and b.main[it_h][it_w].checkPlayer() == enemyColor and
							b.makeFakeCapture('B', i, j, it_h, it_w, color, check)) {
							Set.insert({ 'B', {i,j},{ it_h, it_w }, true, false, false, false, false, check });
							check = false;
						}
						//Search diagonal left-up
						it_h = i - 1;
						it_w = j - 1;
						while (it_h >= 0 and it_w >= 0 and not b.main[it_h][it_w].hasPiece()) {
							if (b.makeFakeMove('B', i, j, it_h, it_w, color, check)) {
								Set.insert({ 'B', {i,j},{ it_h, it_w }, false, true, false, false, false, check });
								check = false;
							}
							--it_h;
							--it_w;
						}
						if (it_h >= 0 and it_w >= 0 and b.main[it_h][it_w].checkPlayer() == enemyColor and
							b.makeFakeCapture('B', i, j, it_h, it_w, color, check)) {
							Set.insert({ 'B', {i,j},{ it_h, it_w }, true, false, false, false, false, check });
							check = false;
						}
						//Search diagonal right-down
						it_h = i + 1;
						it_w = j + 1;
						while (it_h <= 7 and it_w <= 7 and not b.main[it_h][it_w].hasPiece()) {
							if (b.makeFakeMove('B', i, j, it_h, it_w, color, check)) {
								Set.insert({ 'B', {i,j},{ it_h, it_w }, false, true, false, false, false, check });
								check = false;
							}
							++it_h;
							++it_w;
						}
						if (it_h <= 7 and it_w <= 7 and b.main[it_h][it_w].checkPlayer() == enemyColor and
							b.makeFakeCapture('B', i, j, it_h, it_w, color, check)) {
							Set.insert({ 'B', {i,j},{ it_h, it_w }, true, false, false, false, false, check });
							check = false;
						}
						//Search diagonal right-up
						it_h = i - 1;
						it_w = j + 1;
						while (it_h >= 0 and it_w <= 7 and not b.main[it_h][it_w].hasPiece()) {
							if (b.makeFakeMove('B', i, j, it_h, it_w, color, check)) {
								Set.insert({ 'B', {i,j},{ it_h, it_w }, false, true, false, false, false, check });
								check = false;
							}
							--it_h;
							++it_w;
						}
						if (it_h >= 0 and it_w <= 7 and b.main[it_h][it_w].checkPlayer() == enemyColor and
							b.makeFakeCapture('B', i, j, it_h, it_w, color, check)) {
							Set.insert({ 'B',{i,j},{ it_h, it_w }, true, false, false, false, false, check });
							check = false;
						}
					}
					//Queen
					else if (b.hasFriendly('Q', i, j, color)) {
						++auxCount;
						//Search below
						int it = i + 1;
						while (it <= 7 and not b.main[it][j].hasPiece()) {
							if (b.makeFakeMove('Q', i, j, it, j, color, check)) {
								Set.insert({ 'Q', {i,j},{ it, j }, false, true, false, false, false, check });
								check = false;
							}
							++it;
						}
						if (it <= 7 and b.main[it][j].checkPlayer() == enemyColor and
							b.makeFakeCapture('Q', i, j, it, j, color, check)) {
							Set.insert({ 'Q', {i,j},{ it, j }, true, false, false, false, false, check });
							check = false;
						}
						//Search above
						it = i - 1;
						while (it >= 0 and not b.main[it][j].hasPiece()) {
							if (b.makeFakeMove('Q', i, j, it, j, color, check)) {
								Set.insert({ 'Q', {i,j},{ it, j }, false, true, false, false, false, check });
								check = false;
							}
							--it;
						}
						if (it >= 0 and b.main[it][j].checkPlayer() == enemyColor and
							b.makeFakeCapture('Q', i, j, it, j, color, check)) {
							Set.insert({ 'Q',{i,j},{ it, j }, true, false, false, false, false, check });
							check = false;
						}
						//Search to the right
						it = j + 1;
						while (it <= 7 and not b.main[i][it].hasPiece()) {
							if (b.makeFakeMove('Q', i, j, i, it, color, check)) {
								Set.insert({ 'Q',{i,j},{ i, it }, false, true, false, false, false, check });
								check = false;
							}
							++it;
						}
						if (it <= 7 and b.main[i][it].checkPlayer() == enemyColor and
							b.makeFakeCapture('Q', i, j, i, it, color, check)) {
							Set.insert({ 'Q',{i,j},{ i, it }, true, false, false, false, false, check });
							check = false;
						}
						//Search to the left
						it = j - 1;
						while (it >= 0 and not b.main[i][it].hasPiece()) {
							if (b.makeFakeMove('Q', i, j, i, it, color, check)) {
								Set.insert({ 'Q', {i,j},{ i, it }, false, true, false, false, false, check });
								check = false;
							}
							--it;
						}
						if (it >= 0 and b.main[i][it].checkPlayer() == enemyColor and
							b.makeFakeCapture('Q', i, j, i, it, color, check)) {
							Set.insert({ 'Q', {i,j},{ i, it }, true, false, false, false, false, check });
							check = false;
						}
						//Search diagonal left-down
						int it_h = i + 1;
						int it_w = j - 1;
						while (it_h <= 7 and it_w >= 0 and not b.main[it_h][it_w].hasPiece()) {
							if (b.makeFakeMove('Q', i, j, it_h, it_w, color, check)) {
								Set.insert({ 'Q',{i,j},{ it_h, it_w }, false, true, false, false, false, check });
								check = false;
							}
							++it_h;
							--it_w;
						}
						if (it_h <= 7 and it_w >= 0 and b.main[it_h][it_w].checkPlayer() == enemyColor and
							b.makeFakeCapture('Q', i, j, it_h, it_w, color, check)) {
							Set.insert({ 'Q', {i,j},{ it_h, it_w }, true, false, false, false, false, check });
							check = false;
						}
						//Search diagonal left-up
						it_h = i - 1;
						it_w = j - 1;
						while (it_h >= 0 and it_w >= 0 and not b.main[it_h][it_w].hasPiece()) {
							if (b.makeFakeMove('Q', i, j, it_h, it_w, color, check)) {
								Set.insert({ 'Q', {i,j},{ it_h, it_w }, false, true, false, false, false, check });
								check = false;
							}
							--it_h;
							--it_w;
						}
						if (it_h >= 0 and it_w >= 0 and b.main[it_h][it_w].checkPlayer() == enemyColor and
							b.makeFakeCapture('Q', i, j, it_h, it_w, color, check)) {
							Set.insert({ 'Q', {i,j},{ it_h, it_w }, true, false, false, false, false, check });
							check = false;
						}
						//Search diagonal right-down
						it_h = i + 1;
						it_w = j + 1;
						while (it_h <= 7 and it_w <= 7 and not b.main[it_h][it_w].hasPiece()) {
							if (b.makeFakeMove('Q', i, j, it_h, it_w, color, check)) {
								Set.insert({ 'Q', {i,j},{ it_h, it_w }, false, true, false, false, false, check });
								check = false;
							}
							++it_h;
							++it_w;
						}
						if (it_h <= 7 and it_w <= 7 and b.main[it_h][it_w].checkPlayer() == enemyColor and
							b.makeFakeCapture('Q', i, j, it_h, it_w, color, check)) {
							Set.insert({ 'Q', {i,j},{ it_h, it_w }, true, false, false, false, false, check });
							check = false;
						}
						//Search diagonal right-up
						it_h = i - 1;
						it_w = j + 1;
						while (it_h >= 0 and it_w <= 7 and not b.main[it_h][it_w].hasPiece()) {
							if (b.makeFakeMove('Q', i, j, it_h, it_w, color, check)) {
								Set.insert({ 'Q', {i,j},{ it_h, it_w }, false, true, false, false, false, check });
								check = false;
							}
							--it_h;
							++it_w;
						}
						if (it_h >= 0 and it_w <= 7 and b.main[it_h][it_w].checkPlayer() == enemyColor and
							b.makeFakeCapture('Q', i, j, it_h, it_w, color, check)) {
							Set.insert({ 'Q', {i,j},{ it_h, it_w }, true, false, false, false, false, check });
							check = false;
						}
					}
					//King
					else if (b.hasFriendly('K', i, j, color)) {
						++auxCount;
						for (int ii = -1; ii < 2; ++ii) {
							for (int jj = -1; jj < 2; ++jj) {
								if (b.inBound(i + ii, j + jj)) {
									if (not b.main[i + ii][j + jj].hasPiece() and
										b.makeFakeMove('K',i, j, i + ii, j + jj,color, check)) {
										Set.insert({ 'K', {i,j},{ i + ii, j + jj }, false, true, false, false, false, check });
									}
									else if (b.main[i + ii][j + jj].checkPlayer() == enemyColor and
										b.makeFakeCapture('K', i, j, i + ii, j + jj, color, check)) {
										Set.insert({ 'K', {i,j},{ i + ii, j + jj }, true, false, false, false, false, check });
									}
									check = false;
								}
							}
						}
					}
				}
				color == RED ? --i : ++i;
			}
			b.Red.updateThreats(b);
			b.Green.updateThreats(b);
		}

		inline void MoveSet::addKnight(Board& b, int orig_h, int orig_w, int i, int j, int color, int enemyColor) {
			bool check = false;
			if (b.inBound(i, j)) {
				if (not b.main[i][j].hasPiece() and
					b.makeFakeMove('N', orig_h, orig_w, i, j, color, check)) {
					Set.insert({ 'N', {orig_h, orig_w},{ i, j}, false, true, false, false, false, check });
				}
				else if (b.main[i][j].checkPlayer() == enemyColor and
					b.makeFakeCapture('N', orig_h, orig_w, i, j, color, check)) {
					Set.insert({ 'N', {orig_h, orig_w},{ i, j}, true, false, false, false, false, check });
				}
			}
		}

		void MoveSet::checkDebug(int color) const{
			if (color == RED) {
				std::cout << "Red moves: ";
			}
			else if (color == GREEN) {
				std::cout << "Green moves: ";
			}
			else {
				std::cout << "No known player" << std::endl;
			}
			auto it = Set.begin();
			for (; it != Set.end(); ++it) {
				std::cout << "[" << it->type;
				std::cout << char(it -> source.w + 97) << char(8 - char(it->source.h - 48));
				std::cout << char(it->destination.w + 97) << char(8 - char(it->destination.h - 48));

				if (it->promote) {
					std::cout << "pr";
				}
				if (it->capture) {
					std::cout << "x";
				}
				if (it->move) {
					std::cout << "m";
				}
				if (it->castleQueen) {
					std::cout << "cQ";
				}
				if (it->castleKing) {
					std::cout << "cK";
				}
				if (it->check) {
					std::cout << "+";
				}
				std::cout << "] ";
				std::cout.flush();
			}
			std::cout << std::endl;
		}

		bool MoveSet::Move::operator<(const Move& rhs) const {
			return std::tie(type,source.w, source.h, destination.w, destination.h, 
				move, capture, check, castleKing, castleQueen)
				< std::tie(rhs.type, rhs.source.w, rhs.source.h, rhs.destination.w, rhs.destination.h, 
				rhs.move, rhs.capture, rhs.check, rhs.castleKing, rhs.castleQueen);
		}

		bool MoveSet::empty() const {
			return Set.empty();
		}
	}
}



