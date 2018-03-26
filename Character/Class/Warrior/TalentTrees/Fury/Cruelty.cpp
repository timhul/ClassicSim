
#include "Cruelty.h"
#include <QDebug>

Cruelty::Cruelty(Character *pchar) :
    Talent(pchar, "Cruelty", "1MR", "Assets/warrior/fury/tier1/Ability_rogue_eviscerate.png", 5)
{
    QString base_str = "Increases your chance to get a critical strike with melee weapons by %1%.";
    initialize_rank_descriptions(base_str, 1, 1);
}

Cruelty::~Cruelty() {

}
