#pragma once
#include "Player.h"
#include <unordered_map>

namespace Chess {
	namespace Engine {

		class Dummy : public Player {

		private:
			enum class Phase : int {
				UNDEFINED = -1,
				OPENING,
				MIDDLE,
				END
			};

			Phase phase;

			float evaluateBoard(const Board& b, const int& player);
			float evaluateByPos(char type, const int& i, const int& player, const int& pieceCount) const;
			float evaluateByPos(char type, const int& i, const int& player, const int& pieceCount, const int& turn) const;
			void choseRandMove(Move& m);
			Move negamax(Board& position, int depth, float& delta);
			float negamax(Board& position, float alpha, float beta, int depth, bool& ended, const int& player);
			bool gameOver(const Board& b);
			bool gameOver2(Board& b, float& pen, const int& depth, bool& ended, const int& player);
			void printMove(const Move& m) const;

			static const std::vector<float> RedPawnPos;
			static const std::vector<float> RedKnightPos;
			static const std::vector<float> RedBishopPos;
			static const std::vector<float> RedRookPos;
			static const std::vector<float> RedQueenPos;
			static const std::vector<float> RedKingPos;

			static const std::vector<float> GreenPawnPos;
			static const std::vector<float> GreenKnightPos;
			static const std::vector<float> GreenBishopPos;
			static const std::vector<float> GreenRookPos;
			static const std::vector<float> GreenQueenPos;
			static const std::vector<float> GreenKingPos;

			static const std::vector<float> EndKing;


		public:
			Dummy() noexcept;
			Dummy(int color) noexcept;

			void move(Board& b);
		};
	}
}
		