
#include "HolyStrength.h"
#include "Character.h"
#include "CharacterStats.h"
#include <QDebug>

void HolyStrength::buff_effect_when_applied() {
    pchar->get_stats()->increase_strength(100);
}

void HolyStrength::buff_effect_when_removed() {
    pchar->get_stats()->decrease_strength(100);
}
