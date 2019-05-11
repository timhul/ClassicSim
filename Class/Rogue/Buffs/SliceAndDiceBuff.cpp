#include "SliceAndDiceBuff.h"

#include "Character.h"
#include "Utils/Check.h"

SliceAndDiceBuff::SliceAndDiceBuff(Character* pchar):
    Buff(pchar, "Slice and Dice", "Assets/ability/Ability_rogue_slicedice.png", 9, 0)
{
    durations = {9, 12, 15, 18, 21};
    imp_snd_duration_modifiers = {1.0, 1.15, 1.30, 1.45};
    imp_snd_modifier = imp_snd_duration_modifiers[0];
}

void SliceAndDiceBuff::buff_effect_when_applied() {
    pchar->increase_melee_attack_speed(30);
}

void SliceAndDiceBuff::buff_effect_when_removed() {
    pchar->decrease_melee_attack_speed(30);
}

void SliceAndDiceBuff::change_duration_modifier(const int curr) {
    check((curr >= 0 && curr < imp_snd_duration_modifiers.size()), "Index out of range");

    imp_snd_modifier = imp_snd_duration_modifiers[curr];
}

void SliceAndDiceBuff::update_duration(const unsigned combo_points) {
    int index = static_cast<int>(combo_points) - 1;
    check((index >= 0 && index <= durations.size() - 1), "Index out of range");

    duration = static_cast<int>(round(double(durations[index]) * imp_snd_modifier));
}
