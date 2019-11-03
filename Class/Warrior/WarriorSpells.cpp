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

WarriorSpells::WarriorSpells(Warrior* warrior) :
    CharacterSpells(warrior),
    warr(warrior)
{
    this->berserking = new Berserking(warrior, ResourceType::Rage, 5);
    add_spell_group({berserking});

    this->anger_management = new AngerManagement(warrior, this);
    this->battle_stance = new BattleStance(warrior);
    this->berserker_rage = new BerserkerRage(warrior);
    this->berserker_stance = new BerserkerStance(warrior);
    this->bloodrage = new Bloodrage(warrior);
    this->bt = new Bloodthirst(warrior, this, new_cooldown_control("Bloodthirst", 6.0));
    this->death_wish = new DeathWish(warrior);
    this->deep_wounds = new DeepWounds(warrior);
    this->execute = new Execute(warrior, this);
    this->hamstring = new Hamstring(warrior, this);

    this->mortal_strike = new MortalStrike(warrior, this, new_cooldown_control("Mortal Strike", 6.0));
    this->overpower = new Overpower(warrior, this, new_cooldown_control("Overpower", 5.0));
    this->recklessness = new Recklessness(warrior, this);
    this->rend = new Rend(warrior, this);
    this->slam = new Slam(warrior, this);
    this->warr_mh_attack = new MainhandAttackWarrior(warrior, this);
    this->warr_oh_attack = new OffhandAttackWarrior(warrior, this);
    this->whirlwind = new Whirlwind(warrior, this);

    auto* buff = static_cast<BattleShoutBuff*>(warrior->get_raid_control()->get_shared_party_buff("Battle Shout", warrior->get_party()));
    if (buff == nullptr) {
        buff = new BattleShoutBuff(warrior);
        buff->enable_buff();
    }
    add_spell_group({
                        new BattleShout(warrior, buff, 1),
                        new BattleShout(warrior, buff, 2),
                        new BattleShout(warrior, buff, 3),
                        new BattleShout(warrior, buff, 4),
                        new BattleShout(warrior, buff, 5),
                        new BattleShout(warrior, buff, 6),
                        new BattleShout(warrior, buff, 7),
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

    this->hs_buff = new NoEffectSelfBuff(warrior, BuffDuration::PERMANENT, "Heroic Strike Queued", "Assets/ability/Ability_rogue_ambush.png", Hidden::No);
    this->hs_buff->enable_buff();
    add_spell_group({
                        new HeroicStrike(warrior, this, hs_buff, 1),
                        new HeroicStrike(warrior, this, hs_buff, 2),
                        new HeroicStrike(warrior, this, hs_buff, 3),
                        new HeroicStrike(warrior, this, hs_buff, 4),
                        new HeroicStrike(warrior, this, hs_buff, 5),
                        new HeroicStrike(warrior, this, hs_buff, 6),
                        new HeroicStrike(warrior, this, hs_buff, 7),
                        new HeroicStrike(warrior, this, hs_buff, 8),
                        new HeroicStrike(warrior, this, hs_buff, 9),
                    });

    add_spell_group({overpower});
    add_spell_group({mortal_strike});
    add_spell_group({recklessness});
    add_spell_group({rend});
    add_spell_group({slam});
    add_spell_group({whirlwind});
    add_spell_group({warr_mh_attack});
    add_spell_group({warr_oh_attack});

    this->battle_stance_buff = new NoEffectSelfBuff(warrior, BuffDuration::PERMANENT, "Battle Stance");
    this->berserker_stance_buff = new BerserkerStanceBuff(warrior);
    this->defensive_stance_buff = new DefensiveStanceBuff(warrior);
    this->flurry = new Flurry(warrior);
    this->overpower_buff = new NoEffectSelfBuff(warrior, 5, "Overpower");
    this->recklessness_buff = new RecklessnessBuff(warrior);
    battle_stance_buff->enable_buff();
    berserker_stance_buff->enable_buff();
    defensive_stance_buff->enable_buff();
    overpower_buff->enable_buff();
    recklessness_buff->enable_buff();

    this->sword_spec = new SwordSpecialization(warrior);
    this->unbridled_wrath = new UnbridledWrath(warrior);
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
    return static_cast<MainhandAttack*>(warr_mh_attack);
}

OffhandAttack* WarriorSpells::get_oh_attack() const {
    return static_cast<OffhandAttack*>(warr_oh_attack);
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
    heroic_strike = static_cast<HeroicStrike*>(get_spell_rank_group_by_name("Heroic Strike")->get_max_available_spell_rank());
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
