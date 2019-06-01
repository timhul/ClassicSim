#include "LightningBolt.h"

#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "DotTick.h"
#include "Engine.h"
#include "NoEffectBuff.h"
#include "Random.h"
#include "Shaman.h"
#include "ShamanSpells.h"
#include "Utils/Check.h"

LightningBolt::LightningBolt(Shaman* pchar, ShamanSpells* spells, const int spell_rank) :
    SpellCastingTime("Lightning Bolt", "Assets/spell/Spell_nature_lightning.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::Yes, ResourceType::Mana, 0, spell_rank),
    TalentRequirer(QVector<TalentRequirerInfo*>{
                   new TalentRequirerInfo("Tidal Mastery", 5, DisabledAtZero::No),
                   new TalentRequirerInfo("Call of Thunder", 5, DisabledAtZero::No),
                   new TalentRequirerInfo("Concussion", 5, DisabledAtZero::No),
                   new TalentRequirerInfo("Convection", 5, DisabledAtZero::No),
                   new TalentRequirerInfo("Lightning Mastery", 5, DisabledAtZero::No),
                   }),
    spells(spells)
{
    switch (spell_rank) {
    case 1:
        base_damage_min = 13;
        base_damage_max = 15;
        base_resource_cost = 15;
        casting_time_ms = 1500;
        level_req = 1;
        break;
    case 2:
        base_damage_min = 26;
        base_damage_max = 30;
        base_resource_cost = 30;
        casting_time_ms = 2000;
        level_req = 8;
        break;
    case 3:
        base_damage_min = 45;
        base_damage_max = 53;
        base_resource_cost = 45;
        casting_time_ms = 2500;
        level_req = 14;
        break;
    case 4:
        base_damage_min = 85;
        base_damage_max = 95;
        base_resource_cost = 75;
        casting_time_ms = 3000;
        level_req = 20;
        break;
    case 5:
        base_damage_min = 125;
        base_damage_max = 143;
        base_resource_cost = 105;
        casting_time_ms = 3000;
        level_req = 26;
        break;
    case 6:
        base_damage_min = 172;
        base_damage_max = 194;
        base_resource_cost = 135;
        casting_time_ms = 3000;
        level_req = 32;
        break;
    case 7:
        base_damage_min = 227;
        base_damage_max = 255;
        base_resource_cost = 165;
        casting_time_ms = 3000;
        level_req = 38;
        break;
    case 8:
        base_damage_min = 282;
        base_damage_max = 316;
        base_resource_cost = 195;
        casting_time_ms = 3000;
        level_req = 44;
        break;
    case 9:
        base_damage_min = 347;
        base_damage_max = 389;
        base_resource_cost = 230;
        casting_time_ms = 3000;
        level_req = 50;
        break;
    case 10:
        base_damage_min = 419;
        base_damage_max = 467;
        base_resource_cost = 265;
        casting_time_ms = 3000;
        level_req = 56;
        break;
    default:
        check(false, QString("%1 does not support rank %2").arg(name).arg(spell_rank).toStdString());
    }

    this->random = new Random(base_damage_min, base_damage_max);
    this->spell_dmg_coefficient = spell_coefficient_from_casting_time();
    this->resource_cost = base_resource_cost;
}

LightningBolt::~LightningBolt() {
    delete cooldown;
}

bool LightningBolt::is_rank_learned() const {
    if (spell_rank >= 1 && spell_rank <= 10)
        return pchar->get_clvl() >= level_req;

    check(false, QString("%1::is_rank_learned() failed for rank %2").arg(name).arg(spell_rank).toStdString());
    return false;
}

void LightningBolt::spell_effect() {
    pchar->get_spells()->stop_attack();
    cooldown->add_gcd_event();
    start_cast();
}

void LightningBolt::complete_cast_effect() {
    if (!spells->clearcasting_active())
        pchar->lose_mana(resource_cost);

    pchar->get_spells()->start_attack();

    const int hit_roll = roll->get_spell_ability_result(MagicSchool::Nature, pchar->get_stats()->get_spell_crit_chance() + tidal_mastery_mod + call_of_thunder_mod);
    const int resist_roll = roll->get_spell_resist_result(MagicSchool::Nature);

    if (hit_roll == MagicAttackResult::MISS)
        return increment_miss();
    if (resist_roll == MagicResistResult::FULL_RESIST)
        return increment_full_resist();

    spells->roll_clearcasting();

    const unsigned damage_dealt = random->get_roll() + static_cast<unsigned>(round(pchar->get_stats()->get_spell_damage(MagicSchool::Nature) * spell_dmg_coefficient));

    const double resist_mod = get_partial_resist_dmg_modifier(resist_roll);
    const double damage_mod =  pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Nature);

    if (hit_roll == MagicAttackResult::CRITICAL) {
        pchar->spell_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt * damage_mod * pchar->get_stats()->get_spell_crit_dmg_mod() * resist_mod * concussion_mod)), resource_cost, 0);
    }
    else {
        pchar->spell_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt * damage_mod * resist_mod * concussion_mod)), resource_cost, 0);
    }
}

void LightningBolt::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Tidal Mastery")
        tidal_mastery_mod = tidal_mastery_ranks[curr];
    if (talent_name == "Call of Thunder")
        call_of_thunder_mod = call_of_thunder_ranks[curr];
    if (talent_name == "Concussion")
        concussion_mod = concussion_ranks[curr];
    if (talent_name == "Convection")
        resource_cost = static_cast<unsigned>(round(base_resource_cost * convection_ranks[curr]));
    if (talent_name == "Lightning Mastery")
        casting_time_ms -= lightning_mastery_mod;
}

void LightningBolt::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Tidal Mastery")
        tidal_mastery_mod = tidal_mastery_ranks[curr];
    if (talent_name == "Call of Thunder")
        call_of_thunder_mod = call_of_thunder_ranks[curr];
    if (talent_name == "Concussion")
        concussion_mod = concussion_ranks[curr];
    if (talent_name == "Convection")
        resource_cost = static_cast<unsigned>(round(base_resource_cost * convection_ranks[curr]));
    if (talent_name == "Lightning Mastery")
        casting_time_ms += lightning_mastery_mod;
}
