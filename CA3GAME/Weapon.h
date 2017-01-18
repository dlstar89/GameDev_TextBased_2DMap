//Weapon.h

#ifndef WEAPON_H
#define WEAPON_H

#include "Range.h"
#include <string>

struct Weapon
{
	std::string Name;
	Range DamageRange;
};

#endif //WEAPON_H