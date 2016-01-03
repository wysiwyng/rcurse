#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Character.hpp"

namespace rcurse {
class Projectile : public Character {
	int _dx, _dy;

public:
	Projectile(const char symbol, int y, int x, int dx, int dy, int initial_health);
	
	
}
}
#endif
