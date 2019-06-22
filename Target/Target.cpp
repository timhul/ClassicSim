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
    target_type(CreatureType::Beast),
    stats(new Stats())
{
    creature_type_strings = {{CreatureType::Beast, "Beast"},
                             {CreatureType::Demon, "Demon"},
                             {CreatureType::Dragonkin, "Dragonkin"},
                             {CreatureType::Elemental, "Elemental"},
                             {CreatureType::Giant, "Giant"},
                             {CreatureType::Humanoid, "Humanoid"},
                             {CreatureType::Mechanical, "Mechanical"},
                             {CreatureType::Undead, "Undead"}};

    string_to_creature_type = {{"Beast", CreatureType::Beast},
                               {"Demon", CreatureType::Demon},
                               {"Dragonkin", CreatureType::Dragonkin},
                               {"Elemental", CreatureType::Elemental},
                               {"Giant", CreatureType::Giant},
                               {"Humanoid", CreatureType::Humanoid},
                               {"Mechanical", CreatureType::Mechanical},
                               {"Undead", CreatureType::Undead}};

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

    this->magic_school_buffs_with_charges.insert(MagicSchool::Arcane, {});
    this->magic_school_buffs_with_charges.insert(MagicSchool::Fire, {});
    this->magic_school_buffs_with_charges.insert(MagicSchool::Frost, {});
    this->magic_school_buffs_with_charges.insert(MagicSchool::Holy, {});
    this->magic_school_buffs_with_charges.insert(MagicSchool::Nature, {});
    this->magic_school_buffs_with_charges.insert(MagicSchool::Physical, {});
    this->magic_school_buffs_with_charges.insert(MagicSchool::Shadow, {});
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
    return school != MagicSchool::Holy ? 70 : 0;
}

double Target::get_magic_school_damage_mod(const MagicSchool school) const {
    const double mod = magic_school_damage_modifiers[school];

    for (auto & buff : magic_school_buffs_with_charges[school])
        buff->use_charge();

    return mod;
}

void Target::increase_magic_school_damage_mod(const int increase, const MagicSchool school, Buff* buff_with_charges) {
    CharacterStats::add_multiplicative_effect(magic_school_damage_changes[school], increase, magic_school_damage_modifiers[school]);

    if (buff_with_charges != nullptr)
        magic_school_buffs_with_charges[school].append(buff_with_charges);
}

void Target::decrease_magic_school_damage_mod(const int decrease, const MagicSchool school, Buff* buff_to_remove) {
    CharacterStats::remove_multiplicative_effect(magic_school_damage_changes[school], decrease, magic_school_damage_modifiers[school]);

    if (buff_to_remove != nullptr) {
        for (int i = 0; i < magic_school_buffs_with_charges[school].size(); ++i) {
            Buff* buff = magic_school_buffs_with_charges[school][i];
            if (buff->get_instance_id() == buff_to_remove->get_instance_id()) {
                magic_school_buffs_with_charges[school].removeAt(i);
                return;
            }
        }

        check(false, QString("Target::decrease_spell_dmg_mod failed to remove buff %1").arg(buff_to_remove->get_name()).toStdString());
    }
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

bool Target::add_debuff(Buff* debuff, const int priority) {
    if (size_debuffs == debuff_limit) {
        if (!remove_oldest_lowest_priority_debuff(priority))
            return false;
    }

    debuffs[priority].append(debuff);
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

void Target::remove_debuff(Buff* debuff) {
    for (auto & priority_buffs: debuffs) {
        for (int i = 0; i < priority_buffs.size(); ++i) {
            if (priority_buffs[i]->get_instance_id() != debuff->get_instance_id())
                continue;

            priority_buffs.removeAt(i);
            --size_debuffs;
            return;
        }
    }
}

void Target::check_clean() {
    for (const auto & priority_debuffs : debuffs)
        check(priority_debuffs.empty(), "Target debuffs not properly cleared");

    check((size_debuffs == 0), "Target debuff size unexpectedly non-zero");
}
