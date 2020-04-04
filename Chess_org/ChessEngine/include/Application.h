#pragma once
#include "Board.h"

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
			void playComputer();
			void manRead_pgn();
			void fileRead_pgn();
			void largeFileRead_pgn();
			void credits() const;
			void printHelpDebug() const;
			void printHelp() const;
			bool open_browser(const char* URL) const;
			void print_end(Board::Ending status) const;
		};
	}
}