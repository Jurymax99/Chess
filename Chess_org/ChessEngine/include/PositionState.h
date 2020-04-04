#pragma once

namespace Chess {
	namespace Engine {
		class PositionState {
		private:
			int h, w;
			bool empty = true;
		public:
			PositionState(const PositionState& rhs);
			void operator=(const PositionState& rhs);
			PositionState(const int& h, const int& w, const bool& cond)
				: h(h), w(w), empty(cond) {}

			inline int checkH() const {return h;}
			inline int checkW() const { return w; }
			inline int isEmpty() const { return empty; }

			bool operator <(const PositionState& rhs) const;
			bool operator ==(const PositionState& rhs) const;
		};
	}
}
