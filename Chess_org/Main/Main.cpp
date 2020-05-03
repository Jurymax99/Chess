#include "Application.h"

int main() {
	using namespace Chess::Engine;
	Application app;
	app.start();
}

/*
minimal
F 11c  F 12c  F 21l  F 22l F 20l F 14c  F 15c  F 16c  F 17c  F 18c  F 3  F 1  F 4  F 5  F 19l  F 7  F 21l F 1 F 26s F 27s F 28s F 29s F 11c  F 12c  F 21l  F 22l F 20l F 14c  F 15c  F 16c  F 17c  F 18c  F 3  F 1  F 4  F 5  F 19l  F 7  F 21l F 1 F 26s F 27s F 28s F 29s F 11c  F 12c  F 21l  F 22l F 20l F 14c  F 15c  F 16c  F 17c  F 18c  F 3  F 1  F 4  F 5  F 19l  F 7  F 21l F 1 F 26s F 27s F 28s F 29s F 11c  F 12c  F 21l  F 22l F 20l F 14c  F 15c  F 16c  F 17c  F 18c  F 3  F 1  F 4  F 5  F 19l  F 7  F 21l F 1 F 26s F 27s F 28s F 29s F 11c  F 12c  F 21l  F 22l F 20l F 14c  F 15c  F 16c  F 17c  F 18c  F 3  F 1  F 4  F 5  F 19l  F 7  F 21l F 1 F 26s F 27s F 28s F 29s F 11c  F 12c  F 21l  F 22l F 20l F 14c  F 15c  F 16c  F 17c  F 18c  F 3  F 1  F 4  F 5  F 19l  F 7  F 21l F 1 F 26s F 27s F 28s F 29s F 11c  F 12c  F 21l  F 22l F 20l F 14c  F 15c  F 16c  F 17c  F 18c  F 3  F 1  F 4  F 5  F 19l  F 7  F 21l F 1 F 26s F 27s F 28s F 29s F 11c  F 12c  F 21l  F 22l F 20l F 14c  F 15c  F 16c  F 17c  F 18c  F 3  F 1  F 4  F 5  F 19l  F 7  F 21l F 1 F 26s F 27s F 28s F 29s F 11c  F 12c  F 21l  F 22l F 20l F 14c  F 15c  F 16c  F 17c  F 18c  F 3  F 1  F 4  F 5  F 19l  F 7  F 21l F 1 F 26s F 27s F 28s F 29s F 11c  F 12c  F 21l  F 22l F 20l F 14c  F 15c  F 16c  F 17c  F 18c  F 3  F 1  F 4  F 5  F 19l  F 7  F 21l F 1 F 26s F 27s F 28s F 29s F 11c  F 12c  F 21l  F 22l F 20l F 14c  F 15c  F 16c  F 17c  F 18c  F 3  F 1  F 4  F 5  F 19l  F 7  F 21l F 1 F 26s F 27s F 28s F 29s 
*/
/*
less
F 11c  n F 12c  n F 21l  n F 22l n F 20l n F 14c  n F 15c  n F 16c  n F 17c  n F 18c  n F 3  n F 1  n F 4  n F 5  n F 19l  n F 7  n F 21l n F 1 n F 26s n F 27s n F 28s n F 29s n F 11c  n F 12c  n F 21l  n F 22l n F 20l n F 14c  n F 15c  n F 16c  n F 17c  n F 18c  n F 3  n F 1  n F 4  n F 5  n F 19l  n F 7  n F 21l n F 1 n F 26s n F 27s n F 28s n F 29s n F 11c  n F 12c  n F 21l  n F 22l n F 20l n F 14c  n F 15c  n F 16c  n F 17c  n F 18c  n F 3  n F 1  n F 4  n F 5  n F 19l  n F 7  n F 21l n F 1 n F 26s n F 27s n F 28s n F 29s n F 11c  n F 12c  n F 21l  n F 22l n F 20l n F 14c  n F 15c  n F 16c  n F 17c  n F 18c  n F 3  n F 1  n F 4  n F 5  n F 19l  n F 7  n F 21l n F 1 n F 26s n F 27s n F 28s n F 29s n F 11c  n F 12c  n F 21l  n F 22l n F 20l n F 14c  n F 15c  n F 16c  n F 17c  n F 18c  n F 3  n F 1  n F 4  n F 5  n F 19l  n F 7  n F 21l n F 1 n F 26s n F 27s n F 28s n F 29s n F 11c  n F 12c  n F 21l  n F 22l n F 20l n F 14c  n F 15c  n F 16c  n F 17c  n F 18c  n F 3  n F 1  n F 4  n F 5  n F 19l  n F 7  n F 21l n F 1 n F 26s n F 27s n F 28s n F 29s n F 11c  n F 12c  n F 21l  n F 22l n F 20l n F 14c  n F 15c  n F 16c  n F 17c  n F 18c  n F 3  n F 1  n F 4  n F 5  n F 19l  n F 7  n F 21l n F 1 n F 26s n F 27s n F 28s n F 29s n F 11c  n F 12c  n F 21l  n F 22l n F 20l n F 14c  n F 15c  n F 16c  n F 17c  n F 18c  n F 3  n F 1  n F 4  n F 5  n F 19l  n F 7  n F 21l n F 1 n F 26s n F 27s n F 28s n F 29s n F 11c  n F 12c  n F 21l  n F 22l n F 20l n F 14c  n F 15c  n F 16c  n F 17c  n F 18c  n F 3  n F 1  n F 4  n F 5  n F 19l  n F 7  n F 21l n F 1 n F 26s n F 27s n F 28s n F 29s n F 11c  n F 12c  n F 21l  n F 22l n F 20l n F 14c  n F 15c  n F 16c  n F 17c  n F 18c  n F 3  n F 1  n F 4  n F 5  n F 19l  n F 7  n F 21l n F 1 n F 26s n F 27s n F 28s n F 29s n F 11c  n F 12c  n F 21l  n F 22l n F 20l n F 14c  n F 15c  n F 16c  n F 17c  n F 18c  n F 3  n F 1  n F 4  n F 5  n F 19l  n F 7  n F 21l n F 1 n F 26s n F 27s n F 28s n F 29s n
*/
/*
test
F 11c  F 12c  F 21l  F 22l F 20l F 14c
*/