#include "Dummy.h"
#include "Board.h"

namespace Chess {
	namespace Engine {
		Dummy::Dummy() {
			color = 0;
		}

		Dummy::Dummy(int color) {
			this->color = color;
		}

		void Dummy::move(Board& b) {
			//TODO HANDLE MOVEMENTS FROM HERE
		}

		void Dummy::choseRandMove(MoveSet& m) {
			auto r = rand() % m.Set.size();
			auto it = *select_random(m.Set, r);
		}
	}
}