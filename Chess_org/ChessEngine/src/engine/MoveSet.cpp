#include "MoveSet.h"
#include "Board.h"
#include <tuple>		//for std::tie


namespace Chess {
	namespace Engine {

		MoveSet::MoveSet() {
			color = size = 0;
		}

		MoveSet::MoveSet(const int& color) :
			color(color) {
			size = 0;
		}

		//TODO: FIX THIS SORT FIRST CAPTURES
		bool comp(const Move& a, const Move& b) {
			return b < a;
		}

		void MoveSet::sortMoves() {
			std::sort(Set.begin(), Set.begin() + size, comp);
		}

		void MoveSet::update(Board& b) {
			int k = 0;
			for (int i = 0; i < 8; ++i) {
				for (int j = 0; j < 8; ++j) {
					if (b.main(i,j).checkPlayer() == color) {
						switch (b.main(i,j).checkPieceType()) {
						case 'P':
							if ((color == RED ? i > 1 : i < 6)) {
								//Pawn 1 up move
								if (not b.main(i - color, j).hasPiece() and
									b.makeFakeMove('P', { i, j }, { i - color, j }, color)) {
									//Type, Source, Dest, Capture, Prom, cK, cQ
									Set[k++] = Move('P', i, j, i - color, j);
								}
								//Pawn 2 up move
								if ((color == RED ? i == 6 : i == 1) and
									not b.main(i - color, j).hasPiece() and
									not b.main(i + 2 * (-color), j).hasPiece() and
									b.makeFakeMove('P', { i, j }, { i + 2 * (-color) , j}, color)) {
									//Type, Source, Dest, Capture, Prom, cK, cQ
									Set[k++] = Move('P', i, j, i + 2 * (-color), j);
								}
								//Pawn capture
								if (b.hasEnemy(i - color, j + 1, color) and
									b.makeFakeCapture('P', i, j, i - color, j + 1, color)) {
									//Type, Source, Dest, Capture, Prom, cK, cQ
									Set[k++] = Move('P', i, j, i - color, j + 1, true, false, false, false);
								}
								if (b.hasEnemy(i - color, j - 1, color) and
									b.makeFakeCapture('P', i, j, i - color, j - 1, color)) {
									//Type, Source, Dest, Capture, Prom, cK, cQ
									Set[k++] = Move('P', i, j, i - color, j - 1, true, false, false, false);
								}
								//Enpassants
								if (b.target.possible and
									b.target.h == i) {
									if (b.target.w == j + 1 and
										not b.main(i - color, j + 1).hasPiece() and
										b.hasEnemy('P', i, j + 1, color) and
										b.makeFakeEnPassant(i, j, i - color, j + 1, i, j + 1, color)) {
										//Type, Source, Dest, Capture, Prom, cK, cQ
										Set[k++] = Move('P', i, j, i - color, j + 1, true, false, false, false);
									}
									if (b.target.w == j - 1 and
										not b.main(i - color, j - 1).hasPiece() and
										b.hasEnemy('P', i, j - 1, color) and
										b.makeFakeEnPassant(i, j, i - color, j - 1, i, j - 1, color)) {
										//Type, Source, Dest, Capture, Prom, cK, cQ
										Set[k++] = Move('P', i, j, i - color, j - 1, true, false, false, false);
									}
								}
							}
							else {
								//Pawn 1 up move promote
								if (color == RED ? i == 1 : i == 6) {
									if (not b.main(i - color,j).hasPiece() and
										b.makeFakeMovePro({ i, j }, { i - color, j }, color)) {
										//Type, Source, Dest, Capture, Prom, cK, cQ
										Set[k++] = Move('Q', 'P', i, j, i - color, j, false, true, false, false);
										Set[k++] = Move('R', 'P', i, j, i - color, j, false, true, false, false);
										Set[k++] = Move('N', 'P', i, j, i - color, j, false, true, false, false);
										Set[k++] = Move('B', 'P', i, j, i - color, j, false, true, false, false);
									}
								}
								//Pawn capture
								if (b.hasEnemy(i - color, j + 1, color)
									and b.makeFakeCapturePro(i, j, i - color, j + 1, color)) {
									//Type, Source, Dest, Capture, Prom, cK, cQ
									Set[k++] = Move('Q', 'P', i, j, i - color, j + 1, true, true, false, false);
									Set[k++] = Move('R', 'P', i, j, i - color, j + 1, true, true, false, false);
									Set[k++] = Move('N', 'P', i, j, i - color, j + 1, true, true, false, false);
									Set[k++] = Move('B', 'P', i, j, i - color, j + 1, true, true, false, false);
								}
								if (b.hasEnemy(i - color, j - 1, color)
									and b.makeFakeCapturePro(i, j, i - color, j - 1, color)) {
									//Type, Source, Dest, Capture, Prom, cK, cQ
									Set[k++] = Move('Q', 'P', i, j, i - color, j - 1, true, true, false, false);
									Set[k++] = Move('R', 'P', i, j, i - color, j - 1, true, true, false, false);
									Set[k++] = Move('N', 'P', i, j, i - color, j - 1, true, true, false, false);
									Set[k++] = Move('B', 'P', i, j, i - color, j - 1, true, true, false, false);
								}
							}
							break;
						case 'N':
							//Check -2, -1
							addKnight(b, i, j, -2, -1, k);
							//Check -2, 1
							addKnight(b, i, j, -2, 1, k);
							//Check -1, -2
							addKnight(b, i, j, -1, -2, k);
							//Check -1, 2
							addKnight(b, i, j, -1, 2, k);
							//Check 1,-2
							addKnight(b, i, j, 1, -2, k);
							//Check 1, 2
							addKnight(b, i, j, 1, 2, k);
							//Check 2, -1
							addKnight(b, i, j, 2, -1, k);
							//Check 2, 1
							addKnight(b, i, j, 2, 1, k);
							break;
						case 'B':
							addBishopLike(b, i, j, 'B', k);
							break;
						case 'R':
							addRookLike(b, i, j, 'R', k);
							//castle kingside
							if (j == 7 and (color == RED ? i == 7 : i == 0) and b.castleFakeKingside(color)) {
								int h = color == RED ? 7 : 0;
								//Type, Source, Dest, Capture, Prom, cK, cQ
								//Set[k++] = Move('R', h, 7, h, 5, false, false, true, false);
								Set[k++] = Move('K', h, 4, h, 6, false, false, true, false);
							}
							//castle queenside
							else if (j == 0 and (color == RED ? i == 7 : i == 0) and b.castleFakeQueenside(color)) {
								int h = color == RED ? 7 : 0;
								//Type, Source, Dest, Capture, Prom, cK, cQ
								//Set[k++] = Move('R', h, 0, h, 3, false, false, false, true);
								Set[k++] = Move('K', h, 4, h, 2, false, false, false, true);
							}
							break;
						case 'Q':
							addRookLike(b, i, j, 'Q', k);
							addBishopLike(b, i, j, 'Q', k);
							break;
						case 'K':
							for (int ii = -1; ii < 2; ++ii) {
								for (int jj = -1; jj < 2; ++jj) {
									if (ii != 0 or jj != 0) {
										if (b.inBound(i + ii, j + jj)) {
											if (not b.main(i + ii, j + jj).hasPiece() and
												b.makeFakeMove('K', { i, j }, { i + ii, j + jj }, color)) {
												//Type, Source, Dest, Capture, Prom, cK, cQ
												Set[k++] = Move('K', i, j, i + ii, j + jj);
											}
											else if (b.main(i + ii, j + jj).checkPlayer() == (-color) and
												b.makeFakeCapture('K', i, j, i + ii, j + jj, color)) {
												//Type, Source, Dest, Capture, Prom, cK, cQ
												Set[k++] = Move('K', i, j, i + ii, j + jj, true, false, false, false);
											}
										}
									}
								}
							}
							break;
						}
					}
				}
			}
			size = k;
		}

		void MoveSet::addKnight(Board& b, const int& orig_h, const int& orig_w, const int& i, const int& j, int& k) {
			if (b.inBound(orig_h + i, orig_w + j)) {
				if (not b.main(orig_h + i, orig_w + j).hasPiece() and
					b.makeFakeMove('N', { orig_h, orig_w }, { orig_h + i, orig_w + j }, color)) {
					//Type, Source, Dest, Capture, Prom, cK, cQ
					Set[k++] = Move('N', orig_h, orig_w, orig_h + i, orig_w + j);
				}
				else if (b.main(orig_h + i, orig_w + j).checkPlayer() == (-color) and
					b.makeFakeCapture('N', orig_h, orig_w, orig_h + i, orig_w + j, color)) {
					//Type, Source, Dest, Capture, Prom, cK, cQ
					Set[k++] = Move('N', orig_h, orig_w, orig_h + i, orig_w + j, true, false, false, false);
				}
			}
		}

		void MoveSet::addRookLike(Board& b, const int& i, const int& j, const char& type, int& k) {
			//Search below
			int it = i + 1;
			while (it <= 7 and not b.main(it,j).hasPiece()) {
				if (b.makeFakeMove(type, { i, j }, { it, j }, color)) {
					//Type, Source, Dest, Capture, Prom, cK, cQ
					Set[k++] = Move(type, i, j, it, j);
				}
				++it;
			}
			if (it <= 7 and b.main(it,j).checkPlayer() == (-color) and
				b.makeFakeCapture(type, i, j, it, j, color)) {
				//Type, Source, Dest, Capture, Prom, cK, cQ
				Set[k++] = Move(type, i, j, it, j, true, false, false, false);
			}
			//Search above
			it = i - 1;
			while (it >= 0 and not b.main(it,j).hasPiece()) {
				if (b.makeFakeMove(type, { i, j }, { it, j }, color)) {
					//Type, Source, Dest, Capture, Prom, cK, cQ
					Set[k++] = Move(type, i, j, it, j);
				}
				--it;
			}
			if (it >= 0 and b.main(it,j).checkPlayer() == (-color) and
				b.makeFakeCapture(type, i, j, it, j, color)) {
				//Type, Source, Dest, Capture, Prom, cK, cQ
				Set[k++] = Move(type, i, j, it, j, true, false, false, false);
			}
			//Search to the right
			it = j + 1;
			while (it <= 7 and not b.main(i,it).hasPiece()) {
				if (b.makeFakeMove(type, { i, j }, { i, it }, color)) {
					//Type, Source, Dest, Capture, Prom, cK, cQ
					Set[k++] = Move(type, i, j, i, it);
				}
				++it;
			}
			if (it <= 7 and b.main(i,it).checkPlayer() == (-color) and
				b.makeFakeCapture(type, i, j, i, it, color)) {
				//Type, Source, Dest, Capture, Prom, cK, cQ
				Set[k++] = Move(type, i, j, i, it, true, false, false, false);
			}
			//Search to the left
			it = j - 1;
			while (it >= 0 and not b.main(i,it).hasPiece()) {
				if (b.makeFakeMove(type, { i, j }, { i, it }, color)) {
					//Type, Source, Dest, Capture, Prom, cK, cQ
					Set[k++] = Move(type, i, j, i, it);
				}
				--it;
			}
			if (it >= 0 and b.main(i,it).checkPlayer() == (-color) and
				b.makeFakeCapture(type, i, j, i, it, color)) {
				//Type, Source, Dest, Capture, Prom, cK, cQ
				Set[k++] = Move(type, i, j, i, it, true, false, false, false);
			}
		}

		void MoveSet::addBishopLike(Board& b, const int& i, const int& j, const char& type, int& k) {
			//Search diagonal left-down
			int it_h = i + 1;
			int it_w = j - 1;
			while (it_h <= 7 and it_w >= 0 and not b.main(it_h,it_w).hasPiece()) {
				if (b.makeFakeMove(type, { i, j }, { it_h, it_w }, color)) {
					//Type, Source, Dest, Capture, Prom, cK, cQ
					Set[k++] = Move(type, i, j, it_h, it_w);
				}
				++it_h;
				--it_w;
			}
			if (it_h <= 7 and it_w >= 0 and b.main(it_h,it_w).checkPlayer() == (-color) and
				b.makeFakeCapture(type, i, j, it_h, it_w, color)) {
				//Type, Source, Dest, Capture, Prom, cK, cQ
				Set[k++] = Move(type, i, j, it_h, it_w, true, false, false, false);
			}
			//Search diagonal left-up
			it_h = i - 1;
			it_w = j - 1;
			while (it_h >= 0 and it_w >= 0 and not b.main(it_h,it_w).hasPiece()) {
				if (b.makeFakeMove(type, { i, j }, { it_h, it_w }, color)) {
					//Type, Source, Dest, Capture, Prom, cK, cQ
					Set[k++] = Move(type, i, j, it_h, it_w);
				}
				--it_h;
				--it_w;
			}
			if (it_h >= 0 and it_w >= 0 and b.main(it_h,it_w).checkPlayer() == (-color) and
				b.makeFakeCapture(type, i, j, it_h, it_w, color)) {
				//Type, Source, Dest, Capture, Prom, cK, cQ
				Set[k++] = Move(type, i, j, it_h, it_w, true, false, false, false);
			}
			//Search diagonal right-down
			it_h = i + 1;
			it_w = j + 1;
			while (it_h <= 7 and it_w <= 7 and not b.main(it_h,it_w).hasPiece()) {
				if (b.makeFakeMove(type, { i, j }, { it_h, it_w }, color)) {
					//Type, Source, Dest, Capture, Prom, cK, cQ
					Set[k++] = Move(type, i, j, it_h, it_w);
				}
				++it_h;
				++it_w;
			}
			if (it_h <= 7 and it_w <= 7 and b.main(it_h,it_w).checkPlayer() == (-color) and
				b.makeFakeCapture(type, i, j, it_h, it_w, color)) {
				//Type, Source, Dest, Capture, Prom, cK, cQ
				Set[k++] = Move(type, i, j, it_h, it_w, true, false, false, false);
			}
			//Search diagonal right-up
			it_h = i - 1;
			it_w = j + 1;
			while (it_h >= 0 and it_w <= 7 and not b.main(it_h,it_w).hasPiece()) {
				if (b.makeFakeMove(type, { i, j }, { it_h, it_w }, color)) {
					//Type, Source, Dest, Capture, Prom, cK, cQ
					Set[k++] = Move(type, i, j, it_h, it_w);
				}
				--it_h;
				++it_w;
			}
			if (it_h >= 0 and it_w <= 7 and b.main(it_h,it_w).checkPlayer() == (-color) and
				b.makeFakeCapture(type, i, j, it_h, it_w, color)) {
				//Type, Source, Dest, Capture, Prom, cK, cQ
				Set[k++] = Move(type, i, j, it_h, it_w, true, false, false, false);
			}
		}

		void MoveSet::checkDebug() const{
			if (color == RED) {
				std::cout << "Red moves ";
			}
			else if (color == GREEN) {
				std::cout << "Green moves ";
			}
			else {
				std::cout << "No known player" << std::endl;
			}
			std::cout << "(" << size << "): ";
			if (size == 0) {
				std::cout << std::endl;
				return;
			}
			int k = 0;
			for (auto& it : Set) {
				std::cout << "[" << it.getType();
				std::cout << char(it.getSource().checkW() + 97) << char(8 - char(it.getSource().checkH()- 48));
				std::cout << char(it.getDestination().checkW() + 97) << char(8 - char(it.getDestination().checkH()- 48));

				if (it.isPromotion()) {
					std::cout << "pr" << it.getPromotedType();
				}
				if (it.isCapture()) {
					std::cout << "x";
				}
				else {
					std::cout << "m";
				}
				if (it.isCastleQueenside()) {
					std::cout << "cQ";
				}
				if (it.isCastleKingside()) {
					std::cout << "cK";
				}
				std::cout << "] ";
				if (k++ >= size - 1) {
					break;
				}
			}
			std::cout << std::endl;
		}
	}
}



