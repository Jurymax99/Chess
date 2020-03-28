#pragma once
#include "Color.h"
#include <algorithm>
#include <iostream>

#define RED 1
#define GREEN 2

#define RELEASE 0
#define DEBUG 1
#define MODE RELEASE

#define VISUAL 0
#define OUTSIDE 1
#define ENVIRONMENT VISUAL

struct Position {
	int h, w;
};