#pragma once
#include "Player.h"
#include <algorithm>

namespace Chess {
	namespace Engine {

		class Dummy : public Player {
		private:

			template<typename S>
			auto select_random(const S& s, size_t n) {
				auto it = std::begin(s);
				std::advance(it, n);
				return it;
			}


		public:
			Dummy();
			Dummy(int color);

			void move(Board& b);
			void choseRandMove(MoveSet& m);
		};
	}
}
		