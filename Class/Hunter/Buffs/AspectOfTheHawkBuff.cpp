#include "AspectOfTheHawkBuff.h"

#include <cmath>

#include "Character.h"
#include "CharacterStats.h"
#include "Utils/Check.h"

AspectOfTheHawkBuff::AspectOfTheHawkBuff(Character* pchar):
    SelfBuff(pchar, "Aspect of the Hawk", "Assets/spell/Spell_nature_ravenform.png", BuffDuration::PERMANENT, 0),
    SetBonusRequirer({"Dragonstalker Armor"})
{}

void AspectOfTheHawkBuff::buff_effect_when_applied() {
    pchar->get_stats()->increase_ranged_ap(static_cast<unsigned>(round(120 * dragonstalker_bonus)));
}

void AspectOfTheHawkBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_ranged_ap(static_cast<unsigned>(round(120 * dragonstalker_bonus)));
}

void AspectOfTheHawkBuff::activate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == "Dragonstalker Armor") {
        switch (set_bonus) {
        case 3:
            dragonstalker_bonus = 1.2;
            break;
        default:
            check(false, "AspectOfTheHawkBuff::activate_set_bonus_effect reached end of switch");
        }
    }
}

void AspectOfTheHawkBuff::deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == "Dragonstalker Armor") {
        switch (set_bonus) {
        case 3:
            dragonstalker_bonus = 1.0;
            break;
        default:
            check(false, "AspectOfTheHawkBuff::deactivate_set_bonus_effect reached end of switch");
        }
    }
}
