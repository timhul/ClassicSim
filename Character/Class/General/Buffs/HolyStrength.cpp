
#include "HolyStrength.h"
#include "Character.h"
#include <QDebug>

void HolyStrength::buff_effect_when_applied() {
    pchar->increase_strength(100);
}

void HolyStrength::buff_effect_when_removed() {
    pchar->decrease_strength(100);
}
