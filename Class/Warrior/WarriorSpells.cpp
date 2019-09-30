#include "WarriorSpells.h"

#include "AngerManagement.h"
#include "BattleShout.h"
#include "BattleShoutBuff.h"
#include "BattleStance.h"
#include "BerserkerRage.h"
#include "BerserkerStance.h"
#include "BerserkerStanceBuff.h"
#include "Berserking.h"
#include "Bloodrage.h"
#include "Bloodthirst.h"
#include "CharacterStats.h"
#include "DeathWish.h"
#include "DeathWishBuff.h"
#include "DeepWounds.h"
#include "DefensiveStanceBuff.h"
#include "Engine.h"
#include "Execute.h"
#include "Flurry.h"
#include "Hamstring.h"
#include "HeroicStrike.h"
#include "MainhandAttackWarrior.h"
#include "MortalStrike.h"
#include "NoEffectSelfBuff.h"
#include "OffhandAttackWarrior.h"
#include "Overpower.h"
#include "RaidControl.h"
#include "Recklessness.h"
#include "RecklessnessBuff.h"
#include "Rend.h"
#include "Slam.h"
#include "SpellRankGroup.h"
#include "SwordSpecialization.h"
#include "UnbridledWrath.h"
#include "Warrior.h"
#include "Whirlwind.h"

WarriorSpells::WarriorSpells(Warrior* pchar) :
    CharacterSpells(pchar),
    warr(pchar)
{
    this->berserking = new Berserking(pchar, ResourceType::Rage, 5);
    add_spell_group({berserking});

    this->anger_management = new AngerManagement(pchar);
    this->battle_stance = new BattleStance(pchar);
    this->berserker_rage = new BerserkerRage(pchar);
    this->berserker_stance = new BerserkerStance(pchar);
    this->bloodrage = new Bloodrage(pchar);
    this->bt = new Bloodthirst(pchar, this, new_cooldown_control("Bloodthirst", 6.0));
    this->death_wish = new DeathWish(pchar);
    this->deep_wounds = new DeepWounds(pchar);
    this->execute = new Execute(pchar, this);
    this->hamstring = new Hamstring(pchar, this);

    this->mortal_strike = new MortalStrike(pchar, this, new_cooldown_control("Mortal Strike", 6.0));
    this->overpower = new Overpower(pchar, this, new_cooldown_control("Overpower", 5.0));
    this->recklessness = new Recklessness(pchar, this);
    this->rend = new Rend(pchar, this);
    this->slam = new Slam(pchar, this);
    this->warr_mh_attack = new MainhandAttackWarrior(pchar, this);
    this->warr_oh_attack = new OffhandAttackWarrior(pchar, this);
    this->whirlwind = new Whirlwind(pchar, this);

    auto* buff = dynamic_cast<BattleShoutBuff*>(pchar->get_raid_control()->get_shared_party_buff("Battle Shout", pchar->get_party()));
    if (buff == nullptr) {
        buff = new BattleShoutBuff(pchar);
        buff->enable_buff();
    }
    add_spell_group({
                        new BattleShout(pchar, buff, 1),
                        new BattleShout(pchar, buff, 2),
                        new BattleShout(pchar, buff, 3),
                        new BattleShout(pchar, buff, 4),
                        new BattleShout(pchar, buff, 5),
                        new BattleShout(pchar, buff, 6),
                        new BattleShout(pchar, buff, 7),
                    });

    add_spell_group({anger_management});
    add_spell_group({battle_stance});
    add_spell_group({berserker_rage});
    add_spell_group({berserker_stance});
    add_spell_group({bloodrage});
    add_spell_group({bt});
    add_spell_group({death_wish});
    add_spell_group({deep_wounds});
    add_spell_group({execute});
    add_spell_group({hamstring});

    this->hs_buff = new NoEffectSelfBuff(pchar, BuffDuration::PERMANENT, "Heroic Strike Queued", "Assets/ability/Ability_rogue_ambush.png", Hidden::No);
    this->hs_buff->enable_buff();
    add_spell_group({
                        new HeroicStrike(pchar, this, hs_buff, 1),
                        new HeroicStrike(pchar, this, hs_buff, 2),
                        new HeroicStrike(pchar, this, hs_buff, 3),
                        new HeroicStrike(pchar, this, hs_buff, 4),
                        new HeroicStrike(pchar, this, hs_buff, 5),
                        new HeroicStrike(pchar, this, hs_buff, 6),
                        new HeroicStrike(pchar, this, hs_buff, 7),
                        new HeroicStrike(pchar, this, hs_buff, 8),
                        new HeroicStrike(pchar, this, hs_buff, 9),
                    });

    add_spell_group({overpower});
    add_spell_group({mortal_strike});
    add_spell_group({recklessness});
    add_spell_group({rend});
    add_spell_group({slam});
    add_spell_group({whirlwind});
    add_spell_group({warr_mh_attack});
    add_spell_group({warr_oh_attack});

    this->battle_stance_buff = new NoEffectSelfBuff(pchar, BuffDuration::PERMANENT, "Battle Stance");
    this->berserker_stance_buff = new BerserkerStanceBuff(pchar);
    this->defensive_stance_buff = new DefensiveStanceBuff(pchar);
    this->flurry = new Flurry(pchar);
    this->overpower_buff = new NoEffectSelfBuff(pchar, 5, "Overpower");
    this->recklessness_buff = new RecklessnessBuff(pchar);
    battle_stance_buff->enable_buff();
    berserker_stance_buff->enable_buff();
    defensive_stance_buff->enable_buff();
    overpower_buff->enable_buff();
    recklessness_buff->enable_buff();

    this->sword_spec = new SwordSpecialization(pchar);
    this->unbridled_wrath = new UnbridledWrath(pchar);
}

WarriorSpells::~WarriorSpells() {
    delete sword_spec;
    delete unbridled_wrath;

    delete battle_stance_buff;
    delete berserker_stance_buff;
    delete defensive_stance_buff;
    delete flurry;
    delete overpower_buff;
    delete recklessness_buff;
    delete hs_buff;
}

void WarriorSpells::mh_auto_attack(const int iteration) {
    if (!warr_mh_attack->attack_is_valid(iteration))
        return;

    if (!is_melee_attacking())
        return;

    if (heroic_strike->is_queued() && heroic_strike->get_spell_status() == SpellStatus::Available) {
        heroic_strike->calculate_damage();
    }
    else {
        if (heroic_strike->is_queued())
            heroic_strike->cancel();

        warr_mh_attack->perform();
    }

    add_next_mh_attack();
}

void WarriorSpells::oh_auto_attack(const int iteration) {
    if (!warr_oh_attack->attack_is_valid(iteration))
        return;

    if (!is_melee_attacking())
        return;

    warr_oh_attack->perform();

    add_next_oh_attack();
}

void WarriorSpells::add_next_mh_attack() {
    warr_mh_attack->add_next_mh_attack();
}

void WarriorSpells::add_next_oh_attack() {
    warr_oh_attack->add_next_oh_attack();
}

MainhandAttack* WarriorSpells::get_mh_attack() const {
    return dynamic_cast<MainhandAttack*>(warr_mh_attack);
}

OffhandAttack* WarriorSpells::get_oh_attack() const {
    return dynamic_cast<OffhandAttack*>(warr_oh_attack);
}

BerserkerStance* WarriorSpells::get_berserker_stance() const {
    return this->berserker_stance;
}

Bloodthirst* WarriorSpells::get_bloodthirst() const {
    return this->bt;
}

DeepWounds* WarriorSpells::get_deep_wounds() const {
    return this->deep_wounds;
}

Execute* WarriorSpells::get_execute() const {
    return this->execute;
}

MortalStrike* WarriorSpells::get_mortal_strike() const {
    return this->mortal_strike;
}

Overpower* WarriorSpells::get_overpower() const {
    return this->overpower;
}

DeathWish* WarriorSpells::get_death_wish() const {
    return this->death_wish;
}

Bloodrage* WarriorSpells::get_bloodrage() const {
    return this->bloodrage;
}

Whirlwind* WarriorSpells::get_whirlwind() const {
    return this->whirlwind;
}

Slam* WarriorSpells::get_slam() const {
    return this->slam;
}

Rend* WarriorSpells::get_rend() const {
    return this->rend;
}

Recklessness* WarriorSpells::get_recklessness() const {
    return this->recklessness;
}

void WarriorSpells::apply_deep_wounds() {
    deep_wounds->perform();
}

void WarriorSpells::cancel_heroic_strike() {
    heroic_strike->cancel();
}

bool WarriorSpells::is_heroic_strike_queued() const {
    return hs_buff->is_active();
}

void WarriorSpells::prepare_set_of_combat_iterations_class_specific() {
    heroic_strike = dynamic_cast<HeroicStrike*>(get_spell_rank_group_by_name("Heroic Strike")->get_max_available_spell_rank());
}

Buff* WarriorSpells::get_flurry() const {
    return this->flurry;
}

Buff* WarriorSpells::get_berserker_stance_buff() const {
    return this->berserker_stance_buff;
}

Buff* WarriorSpells::get_defensive_stance_buff() const {
    return this->defensive_stance_buff;
}

Buff* WarriorSpells::get_overpower_buff() const {
    return this->overpower_buff;
}

Buff* WarriorSpells::get_recklessness_buff() const {
    return this->recklessness_buff;
}

Proc* WarriorSpells::get_sword_spec() const {
    return this->sword_spec;
}

Proc* WarriorSpells::get_unbridled_wrath() const {
    return this->unbridled_wrath;
}
