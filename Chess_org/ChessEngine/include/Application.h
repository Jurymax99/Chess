#pragma once
#include "Utilities.h"

namespace Chess {
	namespace Engine {
		class Application {
			static int gameCount;
			bool ended = true;
		public:
			Application();
			~Application();
			void start(int mode);

		private:
			void play(int mode);
			void read_pgn(int mode);
		};
	}
}