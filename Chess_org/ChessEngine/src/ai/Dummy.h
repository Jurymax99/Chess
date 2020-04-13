#pragma once
#include "Player.h"
#include <unordered_map>

namespace Chess {
	namespace Engine {

		class Dummy : public Player {

		private:
			int enemyColor;
			static std::unordered_map<char, float> evaluationPoints;

			float checkPoints(char type) const;

			float evaluateBoard(const Board& b) const;
			float evaluateByPos(char type, const int& i, const int& j, const int& player, const int& pieceCount) const;
			void choseRandMove(Move& m);
			float minimax_r(Board& position, float alpha, float beta, int depth, bool maximizingPlayer, bool& ended);
			Move minimax(Board& position, int depth, float& delta);
			bool gameOver(Board& b);
			bool gameOver2(Board& b, float& pen, const int& depth, bool& ended);
			void printMove(const Move& m) const;

			static const std::vector<std::vector<float>> RedPawnPos;
			static const std::vector<std::vector<float>> RedKnightPos;
			static const std::vector<std::vector<float>> RedBishopPos;
			static const std::vector<std::vector<float>> RedRookPos;
			static const std::vector<std::vector<float>> RedQueenPos;
			static const std::vector<std::vector<float>> RedKingPos;

			static const std::vector<std::vector<float>> GreenPawnPos;
			static const std::vector<std::vector<float>> GreenKnightPos;
			static const std::vector<std::vector<float>> GreenBishopPos;
			static const std::vector<std::vector<float>> GreenRookPos;
			static const std::vector<std::vector<float>> GreenQueenPos;
			static const std::vector<std::vector<float>> GreenKingPos;

			static const std::vector<std::vector<float>> EndKing;



		public:
			Dummy();
			Dummy(int color);

			void move(Board& b);
		};
	}
}
		