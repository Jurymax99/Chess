#pragma once

namespace Chess {
	namespace Engine {
		class Application {
			static int gameCount;
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