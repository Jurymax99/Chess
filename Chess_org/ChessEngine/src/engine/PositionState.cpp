#include "PositionState.h"
#include <tuple>

namespace Chess {
	namespace Engine {
		PositionState::PositionState(const PositionState& rhs) {
			h = rhs.h;
			w = rhs.w;
			empty = rhs.empty;
		}

		bool PositionState::operator<(const PositionState& rhs) const {
			return std::tie(h, w) < std::tie(rhs.h, rhs.w);
		}

		bool PositionState::operator==(const PositionState& rhs) const {
			return std::tie(h, w, empty) == std::tie(rhs.h, rhs.w, rhs.empty);
		}

		void PositionState::operator=(const PositionState& rhs) {
			h = rhs.h;
			w = rhs.w;
			empty = rhs.empty;
		}
	}
}
