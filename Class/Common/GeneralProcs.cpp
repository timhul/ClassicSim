
#include "GeneralProcs.h"

#include "Character.h"
#include "Faction.h"

GeneralProcs::GeneralProcs(Character* pchar, Faction* faction) : pchar(pchar), faction(faction) {}

void GeneralProcs::switch_faction() const {}
