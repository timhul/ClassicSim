#include "Target.h"

#include <QDebug>

#include "Buff.h"
#include "CharacterStats.h"
#include "Mechanics.h"
#include "Stats.h"
#include "Utils/Check.h"

Target::Target(const unsigned target_lvl):
    target_lvl(target_lvl),
    base_armor(Mechanics::get_boss_base_armor()),
    target_type(CreatureType::Dragonkin),
    stats(new Stats()),
    string_to_creature_type({
                              {"Beast", CreatureType::Beast},
                              {"Demon", CreatureType::Demon},
                              {"Dragonkin", CreatureType::Dragonkin},
                              {"Elemental", CreatureType::Elemental},
                              {"Giant", CreatureType::Giant},
                              {"Humanoid", CreatureType::Humanoid},
                              {"Mechanical", CreatureType::Mechanical},
                              {"Undead", CreatureType::Undead}
                            }),
    creature_type_strings({
                              {CreatureType::Beast, "Beast"},
                              {CreatureType::Demon, "Demon"},
                              {CreatureType::Dragonkin, "Dragonkin"},
                              {CreatureType::Elemental, "Elemental"},
                              {CreatureType::Giant, "Giant"},
                              {CreatureType::Humanoid, "Humanoid"},
                              {CreatureType::Mechanical, "Mechanical"},
                              {CreatureType::Undead, "Undead"}
                          })
{
    stats->increase_armor(base_armor);

    this->magic_school_damage_changes.insert(MagicSchool::Arcane, {});
    this->magic_school_damage_changes.insert(MagicSchool::Fire, {});
    this->magic_school_damage_changes.insert(MagicSchool::Frost, {});
    this->magic_school_damage_changes.insert(MagicSchool::Holy, {});
    this->magic_school_damage_changes.insert(MagicSchool::Nature, {});
    this->magic_school_damage_changes.insert(MagicSchool::Physical, {});
    this->magic_school_damage_changes.insert(MagicSchool::Shadow, {});

    this->magic_school_damage_modifiers.insert(MagicSchool::Arcane, 1.0);
    this->magic_school_damage_modifiers.insert(MagicSchool::Fire, 1.0);
    this->magic_school_damage_modifiers.insert(MagicSchool::Frost, 1.0);
    this->magic_school_damage_modifiers.insert(MagicSchool::Holy, 1.0);
    this->magic_school_damage_modifiers.insert(MagicSchool::Nature, 1.0);
    this->magic_school_damage_modifiers.insert(MagicSchool::Physical, 1.0);
    this->magic_school_damage_modifiers.insert(MagicSchool::Shadow, 1.0);

    this->magic_school_modifier_buffs_with_charges.insert(MagicSchool::Arcane, {});
    this->magic_school_modifier_buffs_with_charges.insert(MagicSchool::Fire, {});
    this->magic_school_modifier_buffs_with_charges.insert(MagicSchool::Frost, {});
    this->magic_school_modifier_buffs_with_charges.insert(MagicSchool::Holy, {});
    this->magic_school_modifier_buffs_with_charges.insert(MagicSchool::Nature, {});
    this->magic_school_modifier_buffs_with_charges.insert(MagicSchool::Physical, {});
    this->magic_school_modifier_buffs_with_charges.insert(MagicSchool::Shadow, {});

    this->school_resistances.insert(MagicSchool::Arcane, 70);
    this->school_resistances.insert(MagicSchool::Fire, 70);
    this->school_resistances.insert(MagicSchool::Frost, 70);
    this->school_resistances.insert(MagicSchool::Holy, 0);
    this->school_resistances.insert(MagicSchool::Nature, 70);
    this->school_resistances.insert(MagicSchool::Physical, 0);
    this->school_resistances.insert(MagicSchool::Shadow, 70);
}

Target::~Target() {
    delete stats;
}

Stats* Target::get_stats() const {
    return stats;
}

unsigned Target::get_lvl() const {
    return target_lvl;
}

void Target::set_lvl(const unsigned new_tlvl) {
    target_lvl = new_tlvl;
}

unsigned Target::get_defense() const {
    return target_lvl * 5;
}

int Target::get_armor() const {
    return stats->get_armor() < 0 ? 0 : stats->get_armor();
}

void Target::set_base_armor(const int armor) {
    const int delta = base_armor - armor;
    this->base_armor = armor;

    if (delta < 0)
        increase_armor(-delta);
    else
        decrease_armor(delta);
}

void Target::increase_armor(const int armor) {
    stats->increase_armor(armor);
}

void Target::decrease_armor(const int armor) {
    stats->decrease_armor(armor);
}

int Target::get_base_armor() const {
    return this->base_armor;
}

int Target::get_resistance(const MagicSchool school) const {
    return school_resistances[school] < 0 ? 0 : school_resistances[school];
}

void Target::increase_resistance(const MagicSchool school, const int value) {
    school_resistances[school] += value;
}

void Target::decrease_resistance(const MagicSchool school, const int value) {
    school_resistances[school] -= value;
}

double Target::get_magic_school_damage_mod(const MagicSchool school, const ConsumeCharge consume_charge) const {
    const double mod = magic_school_damage_modifiers[school];

    if (consume_charge == ConsumeCharge::Yes) {
        for (auto & buff : magic_school_modifier_buffs_with_charges[school])
            buff->use_charge();
    }

    return mod;
}

void Target::increase_magic_school_damage_mod(const int increase, const MagicSchool school) {
    CharacterStats::add_multiplicative_effect(magic_school_damage_changes[school], increase, magic_school_damage_modifiers[school]);
}

void Target::decrease_magic_school_damage_mod(const int decrease, const MagicSchool school) {
    CharacterStats::remove_multiplicative_effect(magic_school_damage_changes[school], decrease, magic_school_damage_modifiers[school]);
}

unsigned Target::get_spell_damage(const MagicSchool school, const ConsumeCharge consume_charge) const {
    const unsigned bonus = stats->get_spell_damage(school);

    if (consume_charge == ConsumeCharge::Yes) {
        for (auto & buff : damage_bonus_buffs_with_charges_for_all_magic_schools)
            buff->use_charge();
    }

    return bonus;
}

Target::CreatureType Target::get_creature_type() const {
    return this->target_type;
}

QString Target::get_creature_type_string() const {
    return creature_type_strings[target_type];
}

void Target::set_creature_type(const QString& target) {
    if (!string_to_creature_type.contains(target)) {
        qDebug() << "Creature type" << target << "not known.";
        return;
    }

    target_type = string_to_creature_type[target];
}

bool Target::add_debuff(Buff* debuff, const Priority priority) {
    check((priority != Priority::Invalid),
          QString("Debuff %1 has invalid priority %2").arg(debuff->name).toStdString());

    if (size_debuffs == debuff_limit) {
        if (!remove_oldest_lowest_priority_debuff(static_cast<int>(priority)))
            return false;
    }

    debuffs[static_cast<int>(priority)].append(debuff);
    ++size_debuffs;
    return true;
}

bool Target::remove_oldest_lowest_priority_debuff(const int up_to_priority) {
    for (int i = 0; i < up_to_priority; ++i) {
        if (debuffs[i].empty())
            continue;

        Buff* debuff = debuffs[i].takeFirst();
        debuff->cancel_buff();
        --size_debuffs;
        return true;
    }

    return false;
}

bool Target::remove_buff_if_exists(QVector<Buff*>& vector, const int instance_id_to_remove) {
    for (int i = 0; i < vector.size(); ++i) {
        if (instance_id_to_remove == vector[i]->get_instance_id()) {
            vector.removeAt(i);
            return true;
        }
    }

    return false;
}

void Target::remove_debuff(Buff* debuff) {
    for (auto & priority_buffs: debuffs) {
        if (!remove_buff_if_exists(priority_buffs, debuff->get_instance_id()))
            continue;

        --size_debuffs;
        return;
    }
}

void Target::check_clean() {
    for (const auto & priority_debuffs : debuffs)
        check(priority_debuffs.empty(), "Target debuffs not properly cleared");

    for (const auto & buffs : magic_school_modifier_buffs_with_charges)
        check(buffs.empty(), "Magic school modifier buffs not properly cleared");

    check(damage_bonus_buffs_with_charges_for_all_magic_schools.empty(), "Damage bonus buffs with charges not properly cleared");

    check((size_debuffs == 0), "Target debuff size unexpectedly non-zero");
}

void Target::add_charge_debuff(Buff* buff, const ConsumedWhen consumed_when) {
    switch (consumed_when) {
    case ConsumedWhen::OnSpellDamageFlat:
        damage_bonus_buffs_with_charges_for_all_magic_schools.append(buff);
        break;
    default:
        check(false, QString("Target::add_charge_debuff generic failed for %1").arg(buff->name).toStdString());
    }
}

void Target::add_charge_debuff(Buff* buff, const ConsumedWhen consumed_when, const MagicSchool school) {
    switch (consumed_when) {
    case ConsumedWhen::OnSpellDamageMod:
        magic_school_modifier_buffs_with_charges[school].append(buff);
        break;
    default:
        check(false, QString("Target::add_charge_debuff school-specific failed for %1").arg(buff->name).toStdString());
    }
}

void Target::remove_charge_debuff(Buff* buff, const ConsumedWhen consumed_when) {
    switch (consumed_when) {
    case ConsumedWhen::OnSpellDamageFlat:
        remove_buff_if_exists(damage_bonus_buffs_with_charges_for_all_magic_schools, buff->get_instance_id());
        break;
    default:
        check(false, QString("Target::remove_charge_debuff generic failed for %1").arg(buff->name).toStdString());
    }
}

void Target::remove_charge_debuff(Buff* buff, const ConsumedWhen consumed_when, const MagicSchool school) {
    switch (consumed_when) {
    case ConsumedWhen::OnSpellDamageMod:
        remove_buff_if_exists(magic_school_modifier_buffs_with_charges[school], buff->get_instance_id());
        break;
    default:
        check(false, QString("Target::remove_charge_debuff school-specific failed for %1").arg(buff->name).toStdString());
    }
}
