#include "Target.h"

#include <QDebug>

#include "Buff.h"
#include "Mechanics.h"

Target::Target(int target_lvl):
    target_lvl(target_lvl),
    target_armor(Mechanics::get_boss_base_armor()),
    base_armor(Mechanics::get_boss_base_armor()),
    target_type(CreatureType::Beast)
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
}

int Target::get_lvl() const {
    return target_lvl;
}

void Target::set_lvl(int new_tlvl) {
    target_lvl = new_tlvl;
}

int Target::get_defense() const {
    return target_lvl * 5;
}

int Target::get_armor() const {
    return target_armor < 0 ? 0 : target_armor;
}

void Target::set_base_armor(const int armor) {
    const int delta = base_armor - armor;
    this->base_armor = armor;

    if (delta < 0)
        return increase_armor(-delta);
    else
        return decrease_armor(delta);
}

void Target::increase_armor(const int armor) {
    this->target_armor += armor;
}

void Target::decrease_armor(const int armor) {
    this->target_armor -= armor;
}

int Target::get_base_armor() const {
    return this->base_armor;
}

int Target::get_resistance(const MagicSchool school) const {
    return school != MagicSchool::Holy ? 70 : 0;
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

void Target::reset() {
    debuffs.clear();
    size_debuffs = 0;
}
