#include "Judgement.h"

#include "Buff.h"
#include "Paladin.h"
#include "PaladinSeal.h"
#include "PaladinSpells.h"

Judgement::Judgement(Paladin* pchar) :
    Spell("Judgement", "Assets/spell/Spell_holy_righteousfury.png", pchar, RestrictedByGcd::Yes, 10, ResourceType::Mana, 86),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Benediction", 5, DisabledAtZero::No),
                                                new TalentRequirerInfo("Improved Judgement", 2, DisabledAtZero::No)}),
    paladin(pchar)
{}

void Judgement::spell_effect() {
    add_gcd_event();

    dynamic_cast<PaladinSpells*>(paladin->get_spells())->get_seal()->judge_seal();

    pchar->lose_mana(resource_cost);
}

SpellStatus Judgement::is_ready_spell_specific() const {
    PaladinSeal* seal = dynamic_cast<PaladinSpells*>(paladin->get_spells())->get_seal();

    if (!seal || !seal->get_buff()->is_active())
        return SpellStatus::BuffInactive;

    return SpellStatus::Available;
}

void Judgement::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Benediction")
        resource_cost = static_cast<unsigned>(round(base_mana_cost * benediction_ranks[curr]));
    if (talent_name == "Improved Judgement")
        cooldown = 10 - curr;
}

void Judgement::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Benediction")
        resource_cost = static_cast<unsigned>(round(base_mana_cost * benediction_ranks[curr]));
    if (talent_name == "Improved Judgement")
        cooldown = 10 - curr;
}
