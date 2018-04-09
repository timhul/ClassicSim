
#include "DeathWishBuff.h"
#include "Warrior.h"
#include <QDebug>

void DeathWishBuff::buff_effect_when_applied() {
    dynamic_cast<Warrior*>(pchar)->increase_total_phys_dmg_mod(rank_talents[rank_talent]);
}

void DeathWishBuff::buff_effect_when_removed() {
    dynamic_cast<Warrior*>(pchar)->decrease_total_phys_dmg_mod(rank_talents[rank_talent]);
}
