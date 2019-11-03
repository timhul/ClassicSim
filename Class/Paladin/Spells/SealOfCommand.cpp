#include "SealOfCommand.h"

#include "CharacterStats.h"
#include "CombatRoll.h"
#include "EnabledProcs.h"
#include "NoEffectSelfBuff.h"
#include "Paladin.h"
#include "PaladinSpells.h"
#include "Random.h"
#include "SealOfCommandProc.h"
#include "Utils/Check.h"

SealOfCommand::SealOfCommand(Paladin* paladin, PaladinSpells* paladin_spells) :
    PaladinSeal("Seal of Command", "Assets/ability/Ability_warrior_innerrage.png", paladin,
                RestrictedByGcd::Yes,
                ResourceType::Mana, 65,
                new NoEffectSelfBuff(paladin, 30, "Seal of Command", "Assets/ability/Ability_warrior_innerrage.png", Hidden::No)),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Seal of Command", 1, DisabledAtZero::Yes),
                                                new TalentRequirerInfo("Benediction", 5, DisabledAtZero::No)}),
    paladin_spells(paladin_spells),
    proc(new SealOfCommandProc(paladin, this))
{
    this->random = new Random(base_min_dmg, base_max_dmg);
    enabled = false;
    seal->disable_buff();
    static_cast<NoEffectSelfBuff*>(seal)->link_proc_application(proc);
    static_cast<NoEffectSelfBuff*>(seal)->link_proc_expiration(proc);
}

SealOfCommand::~SealOfCommand() {
    proc->disable_proc();
    if (proc->is_enabled())
        proc->disable();

    delete proc;
    delete random;
}

void SealOfCommand::refresh_seal() const {

}

Proc* SealOfCommand::get_proc() const {
    return this->proc;
}

void SealOfCommand::signal_proc_in_progress()  {
    check(!proc_in_progress, "SealOfCommand was signalled proc in progress while proc already in progress");
    proc_in_progress = true;
}

bool SealOfCommand::proc_is_in_progress() const {
    return proc_in_progress;
}

void SealOfCommand::judge_effect() {
    const int hit_roll = roll->get_ranged_ability_result(pchar->get_ranged_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());
    int resist_roll = roll->get_spell_resist_result(MagicSchool::Holy);

    if (hit_roll == PhysicalAttackResult::MISS) {
        return increment_full_resist();
    }

    double damage_dealt = random->get_roll() + pchar->get_stats()->get_spell_damage(MagicSchool::Holy) * 0.43;
    damage_dealt *= pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Holy);

    switch (resist_roll) {
    case MagicResistResult::FULL_RESIST:
        resist_roll = MagicResistResult::PARTIAL_RESIST_75;
        break;
    }
    const double resist_mod = get_partial_resist_dmg_modifier(resist_roll);

    if (hit_roll == MagicAttackResult::CRITICAL) {
        pchar->melee_mh_yellow_critical_effect();
        add_spell_crit_dmg(static_cast<int>(round(damage_dealt * pchar->get_stats()->get_spell_crit_dmg_mod() * resist_mod)), get_resource_cost(), 0, resist_roll);
    }
    else {
        pchar->melee_mh_yellow_hit_effect();
        add_spell_hit_dmg(static_cast<int>(round(damage_dealt * resist_mod)), get_resource_cost(), 0, resist_roll);
    }
}

void SealOfCommand::run_proc() {
    proc_in_progress = false;

    const int result = roll->get_melee_ability_result(pchar->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        return;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        return;
    }

    PaladinSeal* seal = paladin_spells->get_seal();
    if (seal != nullptr)
        seal->refresh_seal();

    double damage_dealt = (pchar->get_random_normalized_mh_dmg() + pchar->get_stats()->get_spell_damage(MagicSchool::Holy) * 0.2) * 0.7;
    damage_dealt *= pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Holy);

    int resist_result = roll->get_spell_resist_result(MagicSchool::Holy);
    switch (resist_result) {
    case MagicResistResult::FULL_RESIST:
        resist_result = MagicResistResult::PARTIAL_RESIST_75;
        break;
    }
    const double resist_mod = get_partial_resist_dmg_modifier(resist_result);

    damage_dealt *= resist_mod;

    pchar->get_enabled_procs()->ignore_proc_in_next_proc_check(proc->get_instance_id());

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= pchar->get_stats()->get_melee_ability_crit_dmg_mod();
        pchar->melee_mh_yellow_critical_effect();
        return add_spell_crit_dmg(static_cast<int>(round(damage_dealt)), 0, pchar->global_cooldown(), resist_result);
    }
    pchar->melee_mh_yellow_hit_effect();
    return add_spell_hit_dmg(static_cast<int>(round(damage_dealt)), 0, pchar->global_cooldown(), resist_result);
}

void SealOfCommand::prepare_set_of_combat_iterations_spell_specific() {
    proc->prepare_set_of_combat_iterations();
}

void SealOfCommand::reset_effect() {
    proc_in_progress = false;
}

void SealOfCommand::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Benediction")
        resource_cost = static_cast<unsigned>(round(base_mana_cost * benediction_ranks[curr]));

    if (talent_name == "Seal of Command") {
        seal->enable_buff();
        proc->enable();
    }
}

void SealOfCommand::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Benediction")
        resource_cost = static_cast<unsigned>(round(base_mana_cost * benediction_ranks[curr]));

    if (talent_name == "Seal of Command") {
        seal->disable_buff();
        proc->disable();
    }
}
