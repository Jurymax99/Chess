#include "Board.h"
#include "Utilities.h"

namespace Chess {
	namespace Engine {

		bool Board::makeMove(const char& type, const Position& source, const Position& dest, const int& player, const bool& enp) {
			Player* mover = player == RED ? &Red : &Green;
			main(dest) = main(source);
			main(source).removePiece();
			++halfMoves;
			target.possible = false;
			if (type == 'K') {
				mover->setKing(dest);
				if (player == RED) {
					Red.setCastleKing(false);
					Red.setCastleQueen(false);
				}
				else {
					Green.setCastleKing(false);
					Green.setCastleQueen(false);
				}
			}
			else if (type == 'R') {
				if (dest.checkH() == (player == RED ? 7 : 0)) {
					if (dest.checkW() == 0) {
						player == RED ? Red.setCastleQueen(false) : Green.setCastleQueen(false);
					}
					else if (dest.checkW() == 7) {
						player == RED ? Red.setCastleKing(false) : Green.setCastleKing(false);
					}
				}
			}
			else if (type == 'P'){
				if (enp) {
					target = { dest.checkH(), dest.checkW(), true };
				}
				halfMoves = 0;
			}
			++turn;
			return true;
		}

		bool Board::makeFakeMove(const char& type, const Position& source, const Position& dest, const int& player) {
			Player* mover = player == RED ? &Red : &Green;
			main(dest) = main(source);
			main(source).removePiece();
			if (type == 'K') {
				mover->setKing(dest);
			}
			int player_checked = player;
			bool totChecked = whoChecked(player_checked);
			//rollback
			if (type == 'K') {
				mover->setKing(source);
			}
			main(source) = main(dest);
			main(dest).removePiece();
			if (not totChecked) {
				return true;
			}
			if (player_checked == player) {
				if (MODE == DEBUG) {
					if (player == RED) {
						std::cout << "FAKEMOVE::The red king is in check" << std::endl;
					}
					else {
						std::cout << "FAKEMOVE::The green king is in check" << std::endl;
					}
				}
				return false;
			}
			else {
				return true;
			}
		}

		bool Board::makeFakeMovePro(const Position& source, const Position& dest, const int& player) {
			Player* mover = player == RED ? &Red : &Green;
			bool first = main(source).isFirstMov();
			std::vector<char> types = { 'Q', 'N', 'R', 'B' };
			int i = 0;
			while (i < 4) {
				main(dest).addPiece(types[i], player);
				main(source).removePiece();
				int player_checked = player;
				bool totChecked = whoChecked(player_checked);

				main(dest).removePiece();
				main(source).addPiece('P', player);
				if (not first) {
					main(source).makeFirstMov();
				}
				if (totChecked) {
					if (player_checked == player) {
						if (MODE == DEBUG) {
							if (player == RED) {
								std::cout << "FAKEMOVE::The red king is in check" << std::endl;
							}
							else {
								std::cout << "FAKEMOVE::The green king is in check" << std::endl;
							}
						}
						return false;
					}
					else {
						return true;
					}
				}
				++i;
			}
			return true;
		}

		bool Board::pawnPromote(const Position& source, const Position& dest, const char& type, const int& player) {
			Player* mover = player == RED ? &Red : &Green;
			main(dest).addPiece(type, player);
			main(source).removePiece();
			++halfMoves;
			target.possible = false;
			halfMoves = 0;
			main(dest).makeFirstMov();
			++turn;
			return true;
		}
	}
}