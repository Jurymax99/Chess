#include "MoveSet.h"
#include "Board.h"
#include <tuple>		//for std::tie


namespace Chess {
	namespace Engine {
		void MoveSet::update(int color, int pieceCount, Board& b) {
			Set.clear();
			int pawnConst = 0;
			int i = 0;
			if (color == RED) {
				pawnConst = -1;
				i = 7;
			}
			else {
				pawnConst = 1;
				i = 0;
			}
			int auxCount = 0;
			while ((color == RED ? i >= 0 : i < 8) and auxCount <= pieceCount) {
				for (int j = 0; j < 8 and auxCount <= pieceCount; ++j) {
					if (b.main(i,j).hasPiece() and b.main(i,j).checkPlayer() == color) {
						switch (b.main(i,j).checkPieceType()) {
						case 'P':
							++auxCount;
							if ((color == RED ? i > 1 : i < 6)) {
								//Pawn 1 up move
								if (not b.main(i + pawnConst,j).hasPiece() and
									b.makeFakeMove('P', i, j, i + pawnConst, j, color)) {
									//Type, Source, Dest, Capture, Prom, cK, cQ
									Set.push_back(Move('P', i, j, i + pawnConst, j, false, false, false, false));
								}
								//Pawn 2 up move
								if ((color == RED ? i == 6 : i == 1) and
									not b.main(i + pawnConst,j).hasPiece() and
									not b.main(i + 2 * pawnConst,j).hasPiece() and
									b.makeFakeMove('P', i, j, i + 2 * pawnConst, j, color)) {
									//Type, Source, Dest, Capture, Prom, cK, cQ
									Set.push_back(Move('P', i, j, i + 2 * pawnConst, j, false, false, false, false));
								}
								//Pawn capture
								if (b.hasEnemy(i + pawnConst, j + 1, color) and
									b.makeFakeCapture('P', i, j, i + pawnConst, j + 1, color)) {
									//Type, Source, Dest, Capture, Prom, cK, cQ
									Set.push_back(Move('P', i, j, i + pawnConst, j + 1, true, false, false, false));
								}
								if (b.hasEnemy(i + pawnConst, j - 1, color) and
									b.makeFakeCapture('P', i, j, i + pawnConst, j - 1, color)) {
									//Type, Source, Dest, Capture, Prom, cK, cQ
									Set.push_back(Move('P', i, j, i + pawnConst, j - 1, true, false, false, false));
								}
								//Enpassants
								if (b.target.possible and
									b.target.h == i and
									b.target.w == j + 1 and
									not b.main(i + pawnConst,j + 1).hasPiece() and
									b.hasEnemy('P', i, j + 1, color) and
									b.makeFakeEnPassant(i, j, i + pawnConst, j + 1, i, j + 1, color)) {
									//Type, Source, Dest, Capture, Prom, cK, cQ
									Set.push_back(Move('P', i, j, i + pawnConst, j + 1, true, false, false, false));
								}
								if (b.target.possible and
									b.target.h == i and
									b.target.w == j - 1 and
									not b.main(i + pawnConst,j - 1).hasPiece() and
									b.hasEnemy('P', i, j - 1, color) and
									b.makeFakeEnPassant(i, j, i + pawnConst, j - 1, i, j - 1, color)) {
									//Type, Source, Dest, Capture, Prom, cK, cQ
									Set.push_back(Move('P', i, j, i + pawnConst, j - 1, true, false, false, false));
								}
							}
							else {
								//Pawn 1 up move promote
								if (color == RED ? i == 1 : i == 6) {
									if (not b.main(i + pawnConst,j).hasPiece() and
										b.makeFakeMovePro(i, j, i + pawnConst, j, color)) {
										//Type, Source, Dest, Capture, Prom, cK, cQ
										Set.push_back(Move('P', i, j, i + pawnConst, j, false, true, false, false));
									}
								}
								//Pawn capture
								if (b.hasEnemy(i + pawnConst, j + 1, color)
									and b.makeFakeCapturePro(i, j, i + pawnConst, j + 1, color)) {
									//Type, Source, Dest, Capture, Prom, cK, cQ
									Set.push_back(Move('P', i, j, i + pawnConst, j + 1, true, true, false, false));
								}
								if (b.hasEnemy(i + pawnConst, j - 1, color)
									and b.makeFakeCapturePro(i, j, i + pawnConst, j - 1, color)) {
									//Type, Source, Dest, Capture, Prom, cK, cQ
									Set.push_back(Move('P', i, j, i + pawnConst, j - 1, true, true, false, false));
								}
							}
							break;
						case 'N':
							++auxCount;
							//Check -2, -1
							addKnight(b, i, j, i - 2, j - 1, color);
							//Check -2, 1
							addKnight(b, i, j, i - 2, j + 1, color);
							//Check -1, -2
							addKnight(b, i, j, i - 1, j - 2, color);
							//Check -1, 2
							addKnight(b, i, j, i - 1, j + 2, color);
							//Check 1,-2
							addKnight(b, i, j, i + 1, j - 2, color);
							//Check 1, 2
							addKnight(b, i, j, i + 1, j + 2, color);
							//Check 2, -1
							addKnight(b, i, j, i + 2, j - 1, color);
							//Check 2, 1
							addKnight(b, i, j, i + 2, j + 1, color);
							break;
						case 'B':
							++auxCount;
							addBishopLike(b, i, j, 'B', color);
							break;
						case 'R':
							++auxCount;
							addRookLike(b, i, j, 'R', color);
							//castle kingside
							if (j == 7 and (color == RED ? i == 7 : i == 0) and b.castleFakeKingside(color)) {
								int h = color == RED ? 7 : 0;
								//Type, Source, Dest, Capture, Prom, cK, cQ
								Set.push_back(Move('R', h, 7, h, 5, false, false, true, false));
								Set.push_back(Move('K', h, 4, h, 6, false, false, true, false));
							}
							//castle queenside
							else if (j == 0 and (color == RED ? i == 7 : i == 0) and b.castleFakeQueenside(color)) {
								int h = color == RED ? 7 : 0;
								//Type, Source, Dest, Capture, Prom, cK, cQ
								Set.push_back(Move('R', h, 0, h, 3, false, false, false, true));
								Set.push_back(Move('K', h, 4, h, 2, false, false, false, true));
							}
							break;
						case 'Q':
							++auxCount;
							addRookLike(b, i, j, 'Q', color);
							addBishopLike(b, i, j, 'Q', color);
							break;
						case 'K':
							++auxCount;
							for (int ii = -1; ii < 2; ++ii) {
								for (int jj = -1; jj < 2; ++jj) {
									if (b.inBound(i + ii, j + jj)) {
										if (not b.main(i + ii,j + jj).hasPiece() and
											b.makeFakeMove('K', i, j, i + ii, j + jj, color)) {
											//Type, Source, Dest, Capture, Prom, cK, cQ
											Set.push_back(Move('K', i, j, i + ii, j + jj, false, false, false, false));
										}
										else if (b.main(i + ii,j + jj).checkPlayer() == (-color) and
											b.makeFakeCapture('K', i, j, i + ii, j + jj, color)) {
											//Type, Source, Dest, Capture, Prom, cK, cQ
											Set.push_back(Move('K', i, j, i + ii, j + jj, true, false, false, false));
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

		void MoveSet::addKnight(Board& b, int orig_h, int orig_w, int i, int j, int color) {
			if (b.inBound(i, j)) {
				if (not b.main(i,j).hasPiece() and
					b.makeFakeMove('N', orig_h, orig_w, i, j, color)) {
					//Type, Source, Dest, Capture, Prom, cK, cQ
					Set.push_back(Move('N', orig_h, orig_w, i, j, false, false, false, false));
				}
				else if (b.main(i,j).checkPlayer() == (-color) and
					b.makeFakeCapture('N', orig_h, orig_w, i, j, color)) {
					//Type, Source, Dest, Capture, Prom, cK, cQ
					Set.push_back(Move('N', orig_h, orig_w, i, j, true, false, false, false));
				}
			}
		}

		void MoveSet::addRookLike(Board& b, int i, int j, char type, int color) {
			//Search below
			int it = i + 1;
			while (it <= 7 and not b.main(it,j).hasPiece()) {
				if (b.makeFakeMove(type, i, j, it, j, color)) {
					//Type, Source, Dest, Capture, Prom, cK, cQ
					Set.push_back(Move(type, i, j, it, j, false, false, false, false));
				}
				++it;
			}
			if (it <= 7 and b.main(it,j).checkPlayer() == (-color) and
				b.makeFakeCapture(type, i, j, it, j, color)) {
				//Type, Source, Dest, Capture, Prom, cK, cQ
				Set.push_back(Move(type, i, j, it, j, true, false, false, false));
			}
			//Search above
			it = i - 1;
			while (it >= 0 and not b.main(it,j).hasPiece()) {
				if (b.makeFakeMove(type, i, j, it, j, color)) {
					//Type, Source, Dest, Capture, Prom, cK, cQ
					Set.push_back(Move(type, i, j, it, j, false, false, false, false));
				}
				--it;
			}
			if (it >= 0 and b.main(it,j).checkPlayer() == (-color) and
				b.makeFakeCapture(type, i, j, it, j, color)) {
				//Type, Source, Dest, Capture, Prom, cK, cQ
				Set.push_back(Move(type, i, j, it, j, true, false, false, false));
			}
			//Search to the right
			it = j + 1;
			while (it <= 7 and not b.main(i,it).hasPiece()) {
				if (b.makeFakeMove(type, i, j, i, it, color)) {
					//Type, Source, Dest, Capture, Prom, cK, cQ
					Set.push_back(Move(type, i, j, i, it, false, false, false, false));
				}
				++it;
			}
			if (it <= 7 and b.main(i,it).checkPlayer() == (-color) and
				b.makeFakeCapture(type, i, j, i, it, color)) {
				//Type, Source, Dest, Capture, Prom, cK, cQ
				Set.push_back(Move(type, i, j, i, it, true, false, false, false));
			}
			//Search to the left
			it = j - 1;
			while (it >= 0 and not b.main(i,it).hasPiece()) {
				if (b.makeFakeMove(type, i, j, i, it, color)) {
					//Type, Source, Dest, Capture, Prom, cK, cQ
					Set.push_back(Move(type, i, j, i, it, false, false, false, false));
				}
				--it;
			}
			if (it >= 0 and b.main(i,it).checkPlayer() == (-color) and
				b.makeFakeCapture(type, i, j, i, it, color)) {
				//Type, Source, Dest, Capture, Prom, cK, cQ
				Set.push_back(Move(type, i, j, i, it, true, false, false, false));
			}
		}

		void MoveSet::addBishopLike(Board& b, int i, int j, char type, int color) {
			//Search diagonal left-down
			int it_h = i + 1;
			int it_w = j - 1;
			while (it_h <= 7 and it_w >= 0 and not b.main(it_h,it_w).hasPiece()) {
				if (b.makeFakeMove(type, i, j, it_h, it_w, color)) {
					//Type, Source, Dest, Capture, Prom, cK, cQ
					Set.push_back(Move(type, i, j, it_h, it_w, false, false, false, false));
				}
				++it_h;
				--it_w;
			}
			if (it_h <= 7 and it_w >= 0 and b.main(it_h,it_w).checkPlayer() == (-color) and
				b.makeFakeCapture(type, i, j, it_h, it_w, color)) {
				//Type, Source, Dest, Capture, Prom, cK, cQ
				Set.push_back(Move(type, i, j, it_h, it_w, true, false, false, false));
			}
			//Search diagonal left-up
			it_h = i - 1;
			it_w = j - 1;
			while (it_h >= 0 and it_w >= 0 and not b.main(it_h,it_w).hasPiece()) {
				if (b.makeFakeMove(type, i, j, it_h, it_w, color)) {
					//Type, Source, Dest, Capture, Prom, cK, cQ
					Set.push_back(Move(type, i, j, it_h, it_w, false, false, false, false));
				}
				--it_h;
				--it_w;
			}
			if (it_h >= 0 and it_w >= 0 and b.main(it_h,it_w).checkPlayer() == (-color) and
				b.makeFakeCapture(type, i, j, it_h, it_w, color)) {
				//Type, Source, Dest, Capture, Prom, cK, cQ
				Set.push_back(Move(type, i, j, it_h, it_w, true, false, false, false));
			}
			//Search diagonal right-down
			it_h = i + 1;
			it_w = j + 1;
			while (it_h <= 7 and it_w <= 7 and not b.main(it_h,it_w).hasPiece()) {
				if (b.makeFakeMove(type, i, j, it_h, it_w, color)) {
					//Type, Source, Dest, Capture, Prom, cK, cQ
					Set.push_back(Move(type, i, j, it_h, it_w, false, false, false, false));
				}
				++it_h;
				++it_w;
			}
			if (it_h <= 7 and it_w <= 7 and b.main(it_h,it_w).checkPlayer() == (-color) and
				b.makeFakeCapture(type, i, j, it_h, it_w, color)) {
				//Type, Source, Dest, Capture, Prom, cK, cQ
				Set.push_back(Move(type, i, j, it_h, it_w, true, false, false, false));
			}
			//Search diagonal right-up
			it_h = i - 1;
			it_w = j + 1;
			while (it_h >= 0 and it_w <= 7 and not b.main(it_h,it_w).hasPiece()) {
				if (b.makeFakeMove(type, i, j, it_h, it_w, color)) {
					//Type, Source, Dest, Capture, Prom, cK, cQ
					Set.push_back(Move(type, i, j, it_h, it_w, false, false, false, false));
				}
				--it_h;
				++it_w;
			}
			if (it_h >= 0 and it_w <= 7 and b.main(it_h,it_w).checkPlayer() == (-color) and
				b.makeFakeCapture(type, i, j, it_h, it_w, color)) {
				//Type, Source, Dest, Capture, Prom, cK, cQ
				Set.push_back(Move(type, i, j, it_h, it_w, true, false, false, false));
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
				std::cout << "[" << it->getType();
				std::cout << char(it -> getSource().checkW() + 97) << char(8 - char(it->getSource().checkH()- 48));
				std::cout << char(it->getDestination().checkW() + 97) << char(8 - char(it->getDestination().checkH()- 48));

				if (it->isPromotion()) {
					std::cout << "pr";
				}
				if (it->isCapture()) {
					std::cout << "x";
				}
				else {
					std::cout << "m";
				}
				if (it->isCastleQueenside()) {
					std::cout << "cQ";
				}
				if (it->isCastleKingside()) {
					std::cout << "cK";
				}
				std::cout << "] ";
			}
			std::cout << std::endl;
		}

		bool MoveSet::empty() const {
			return Set.empty();
		}
	}
}



