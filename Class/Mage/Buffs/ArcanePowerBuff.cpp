#include "ArcanePowerBuff.h"

#include "Character.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "Spell.h"
#include "SpellRankGroup.h"

ArcanePowerBuff::ArcanePowerBuff(Character* pchar):
    SelfBuff(pchar, "Arcane Power", "Assets/spell/Spell_nature_lightning.png", 15, 0),
    affected_spells({
                    "Blizzard", "Frostbolt", "Arcane Explosion", "Fire Blast", "Scorch", "Fireball",
                    "Pyroblast", "Blast Wave", "Frost Nova", "Flamestrike", "Cone of Cold",
                    "Arcane Missiles",
                    })
{}

void ArcanePowerBuff::buff_effect_when_applied() {
    pchar->get_stats()->increase_magic_school_damage_mod(30);

    for (const auto & spell_name : affected_spells) {
        SpellRankGroup* group = pchar->get_spells()->get_spell_rank_group_by_name(spell_name);
        if (group == nullptr)
            continue;

        for (const auto & spell : group->spell_group)
            spell->increase_resource_cost_modifier(30);
    }
}

void ArcanePowerBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_magic_school_damage_mod(30);

    for (const auto & spell_name : affected_spells) {
        SpellRankGroup* group = pchar->get_spells()->get_spell_rank_group_by_name(spell_name);
        if (group == nullptr)
            continue;

        for (const auto & spell : group->spell_group)
            spell->decrease_resource_cost_modifier(30);
    }
}
