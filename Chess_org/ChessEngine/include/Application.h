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
			void start();

		private:
			void play();
			void manRead_pgn();
			void fileRead_pgn();
			void credits();
			void printHelpDebug();
			void printHelp();
			bool open_browser(const char* URL);
		};
	}
}