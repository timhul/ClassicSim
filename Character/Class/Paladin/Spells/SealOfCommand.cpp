#include "SealOfCommand.h"

#include "CharacterStats.h"
#include "CombatRoll.h"
#include "NoEffectBuff.h"
#include "Paladin.h"
#include "Random.h"
#include "SealOfCommandProc.h"
#include "Utils/Check.h"

SealOfCommand::SealOfCommand(Paladin* pchar) :
    PaladinSeal("Seal of Command", "Assets/ability/Ability_warrior_innerrage.png", pchar,
                RestrictedByGcd::Yes,
                0,
                ResourceType::Mana, 65,
                new NoEffectBuff(pchar, 30, "Seal of Command", "Assets/ability/Ability_warrior_innerrage.png", Hidden::No)),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Seal of Command", 1, DisabledAtZero::Yes),
                                                new TalentRequirerInfo("Benediction", 5, DisabledAtZero::No)}),
    proc(new SealOfCommandProc(pchar))
{
    this->random = new Random(base_min_dmg, base_max_dmg);
    enabled = false;
    seal->disable_buff();
    dynamic_cast<NoEffectBuff*>(seal)->link_proc_application(proc);
    dynamic_cast<NoEffectBuff*>(seal)->link_proc_expiration(proc);
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

void SealOfCommand::judge_effect() {
    const int hit_roll = roll->get_ranged_ability_result(pchar->get_ranged_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());
    const int resist_roll = roll->get_spell_resist_result(MagicSchool::Holy);

    if (hit_roll == PhysicalAttackResult::MISS) {
        return increment_full_resist();
    }

    double damage_dealt = random->get_roll() + pchar->get_stats()->get_spell_damage(MagicSchool::Holy) * 0.43;
    damage_dealt *= pchar->get_stats()->get_spell_dmg_mod(MagicSchool::Holy);

    double resist_mod = 1.0;
    switch (resist_roll) {
    case MagicResistResult::NO_RESIST:
        break;
    case MagicResistResult::PARTIAL_RESIST_25:
        resist_mod = 0.75;
        break;
    case MagicResistResult::PARTIAL_RESIST_50:
        resist_mod = 0.5;
        break;
    case MagicResistResult::FULL_RESIST:
    case MagicResistResult::PARTIAL_RESIST_75:
        resist_mod = 0.25;
        break;
    default:
        check(false, "SealOfCommandProc::proc_effect reached end of switch");
    }

    if (hit_roll == MagicAttackResult::CRITICAL) {
        pchar->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt * pchar->get_stats()->get_spell_crit_dmg_mod() * resist_mod)), resource_cost, 0);
    }
    else {
        pchar->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt * resist_mod)), resource_cost, 0);
    }
}

void SealOfCommand::prepare_set_of_combat_iterations_spell_specific() {
    proc->prepare_set_of_combat_iterations();
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
