#pragma once

namespace Chess {
	namespace Engine {
		class Application {
			int gameCount = 1;
			bool ended = true;
		public:
			Application();
			~Application();
			void start();

		private:
			void play();
			void read_pgn();
		};
	}
}