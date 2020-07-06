#include "CharmOfTrickery.h"

#include "Character.h"
#include "CharacterStats.h"

CharmOfTrickery::CharmOfTrickery(Character* pchar) : SelfBuff(pchar, "Charm of Trickery", "Assets/items/Inv_jewelry_necklace_19.png", 1, 0) {}

void CharmOfTrickery::buff_effect_when_applied() {
    pchar->get_resource()->gain_resource(60);
}

void CharmOfTrickery::buff_effect_when_removed() {
}
