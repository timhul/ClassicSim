#include "Judgement.h"

#include <cmath>

#include "Buff.h"
#include "CooldownControl.h"
#include "Paladin.h"
#include "PaladinSeal.h"
#include "PaladinSpells.h"

Judgement::Judgement(Paladin* paladin, PaladinSpells* paladin_spells, CooldownControl* cooldown_control) :
    Spell("Judgement", "Assets/spell/Spell_holy_righteousfury.png", paladin, cooldown_control, RestrictedByGcd::No, ResourceType::Mana, 86),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo("Benediction", 5, DisabledAtZero::No),
                                                 new TalentRequirerInfo("Improved Judgement", 2, DisabledAtZero::No)}),
    paladin(paladin),
    paladin_spells(paladin_spells) {}

void Judgement::spell_effect() {
    paladin_spells->get_active_seal()->judge_seal();

    pchar->lose_mana(get_resource_cost());
}

SpellStatus Judgement::is_ready_spell_specific() const {
    PaladinSeal* seal = paladin_spells->get_active_seal();

    if (!seal || !seal->get_buff()->is_active())
        return SpellStatus::BuffInactive;

    return SpellStatus::Available;
}

void Judgement::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Benediction")
        resource_cost = static_cast<unsigned>(round(base_mana_cost * benediction_ranks[curr]));
    if (talent_name == "Improved Judgement")
        cooldown->base = 10 - curr;
}

void Judgement::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Benediction")
        resource_cost = static_cast<unsigned>(round(base_mana_cost * benediction_ranks[curr]));
    if (talent_name == "Improved Judgement")
        cooldown->base = 10 - curr;
}
