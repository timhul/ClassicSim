#include "WintersChill.h"

#include "Character.h"
#include "Stats.h"
#include "Target.h"

WintersChill::WintersChill(Character* pchar):
    SharedDebuff(pchar, "Winter's Chill", "Assets/spell/Spell_frost_chillingblast.png", Priority::Mid, 15, 0)
{
    max_stacks = 5;
}

void WintersChill::buff_effect_when_applied() {
    if (current_stacks == max_stacks)
        return;

    current_increment += increment;
    pchar->get_target()->get_stats()->increase_spell_crit(MagicSchool::Frost, increment);
}

void WintersChill::buff_effect_when_removed() {
    pchar->get_target()->get_stats()->decrease_spell_crit(MagicSchool::Frost, current_increment);
    current_increment = 0;
}

void WintersChill::buff_effect_when_refreshed() {
    buff_effect_when_applied();
}
