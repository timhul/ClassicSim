#include "GeneralBuffs.h"

#include <QSet>

#include "Character.h"
#include "EssenceOfTheRed.h"
#include "ExternalBuff.h"
#include "Faction.h"
#include "Utils/Check.h"

GeneralBuffs::GeneralBuffs(Character* pchar, Faction* faction) :
    pchar(pchar),
    faction(faction),
    current_setup(0)
{
    QVector<ExternalBuffName> buff_names = get_buff_names_for_class(pchar->get_name());

    for (int i = 0; i < 3; ++i) {
        QVector<QPair<bool, ExternalBuff*>> external_buff_setup;

        for (const auto & buff_name : buff_names)
            external_buff_setup.append({false, get_external_buff_by_name(buff_name, pchar)});

        this->external_buffs.append(external_buff_setup);

        QVector<QPair<bool, ExternalBuff*>> external_debuff_setup = {
            {false, get_external_buff_by_name(ExternalBuffName::SunderArmor, pchar)},
            {false, get_external_buff_by_name(ExternalBuffName::CurseOfRecklessness, pchar)},
            {false, get_external_buff_by_name(ExternalBuffName::FaerieFire, pchar)},
            {false, get_external_buff_by_name(ExternalBuffName::Annihilator, pchar)},
        };

        this->external_debuffs.append(external_debuff_setup);
    }

    buffs.append(new EssenceOfTheRed(pchar));

    mutex_buff_groups.append({"Flask of Supreme Power", "Flask of Distilled Wisdom"});
    mutex_buff_groups.append({"Smoked Desert Dumplings", "Grilled Squid", "Nightfin Soup"});
    mutex_buff_groups.append({"Juju Power", "Elixir of Giants"});
    mutex_buff_groups.append({"Juju Might", "Winterfall Firewater"});
    mutex_buff_groups.append({"R.O.I.D.S", "Ground Scorpok Assay"});
}

GeneralBuffs::~GeneralBuffs() {
    for (const auto & buff : this->buffs) {
        delete buff;
    }

    for (const auto & external_buff : this->external_buffs) {
        for (const auto & j : external_buff) {
            delete j.second;
        }
    }

    for (const auto & external_debuff : this->external_debuffs) {
        for (const auto & j : external_debuff) {
            delete j.second;
        }
    }
}

void GeneralBuffs::switch_faction() {
    for (const auto & i : external_buffs[current_setup]) {
        if (!i.second->valid_for_faction(pchar->get_faction()->get_faction_as_enum())) {
            if (i.second->is_active())
                i.second->cancel_buff();
        }
        else if (i.first && !i.second->is_active())
            i.second->apply_buff();
    }
}

Buff* GeneralBuffs::get_general_buff_by_name(const QString& buff_name) const {
    for (const auto & buff : buffs) {
        if (buff->get_name() == buff_name)
            return buff;
    }

    return nullptr;
}

QVector<ExternalBuff*> GeneralBuffs::get_external_buffs() const {
    QVector<ExternalBuff*> vec;
    for (const auto & i : external_buffs[current_setup]) {
        if (i.second->valid_for_faction(pchar->get_faction()->get_faction_as_enum()))
            vec.append(i.second);
    }

    return vec;
}

QVector<ExternalBuff*> GeneralBuffs::get_external_debuffs() const {
    QVector<ExternalBuff*> vec;
    for (const auto & i : external_debuffs[current_setup])
        vec.append(i.second);

    return vec;
}

void GeneralBuffs::toggle_external(const QString& name, QVector<QVector<QPair<bool, ExternalBuff *>>> &vec) {
    for (auto & i : vec[current_setup]) {
        if (i.second->get_name() != name)
            continue;

        if (i.second->is_active()) {
            i.first = false;
            i.second->cancel_buff();
            check(!i.second->is_active(), "Failed to deactivate buff after cancel");
        }
        else {
            i.first = true;
            i.second->apply_buff();
            deactivate_mutex_buffs(name);
        }

        break;
    }
}

void GeneralBuffs::toggle_external_buff(const QString& buff_name) {
    toggle_external(buff_name, this->external_buffs);
}

void GeneralBuffs::toggle_external_debuff(const QString& debuff_name) {
    toggle_external(debuff_name, this->external_debuffs);
}

bool GeneralBuffs::external_buff_active(const QString& name, const QVector<QVector<QPair<bool, ExternalBuff *>>> &vec) const {
    for (const auto & i : vec[current_setup]) {
        if (i.second->get_name() == name)
            return i.second->is_active();
    }

    return false;
}

bool GeneralBuffs::buff_active(const QString& buff_name) const {
    return external_buff_active(buff_name, this->external_buffs);
}

bool GeneralBuffs::debuff_active(const QString& debuff_name) const {
    return external_buff_active(debuff_name, this->external_debuffs);
}

void GeneralBuffs::clear_all() {
    deactivate_buffs_for_current_setup();
}

void GeneralBuffs::change_setup(const int setup) {
    deactivate_buffs_for_current_setup();
    this->current_setup = setup;
    activate_buffs_for_current_setup();
}

void GeneralBuffs::activate_buffs_for_current_setup() {
    activate_externals(external_buffs);
    activate_externals(external_debuffs);
}

void GeneralBuffs::deactivate_buffs_for_current_setup() {
    deactivate_externals(external_buffs);
    deactivate_externals(external_debuffs);
}

void GeneralBuffs::activate_externals(const QVector<QVector<QPair<bool, ExternalBuff*>>>& vec) {
    for (const auto & i : vec[current_setup]) {
        if (i.first)
            i.second->apply_buff();
    }
}

void GeneralBuffs::deactivate_externals(const QVector<QVector<QPair<bool, ExternalBuff*>>>& vec) {
    for (const auto & i : vec[current_setup]) {
        if (i.second->is_active())
            i.second->cancel_buff();
    }
}

void GeneralBuffs::deactivate_mutex_buffs(const QString& name) {
    for (const auto & mutex_group : mutex_buff_groups) {
        if (!mutex_group.contains(name))
            continue;

        for (const auto & buff : mutex_group) {
            if (buff == name)
                continue;

            if (external_buff_active(buff, external_buffs))
                toggle_external_buff(buff);
        }
    }
}

QVector<ExternalBuffName> GeneralBuffs::get_buff_names_for_class(const QString& class_name) {
    QSet<QString> pure_magical_class = {"Mage", "Priest", "Warlock"};
    QSet<QString> hybrid_magical_class = {"Paladin", "Shaman", "Druid"};

    QVector<ExternalBuffName> common_raid_buffs = {
        ExternalBuffName::MarkOfTheWild,
    };

    QVector<ExternalBuffName> physical_blessings = {
        ExternalBuffName::BlessingOfMight,
        ExternalBuffName::BlessingOfKings,
    };

    QVector<ExternalBuffName> physical_totems = {
        ExternalBuffName::TotemStrengthOfEarth,
    };

    QVector<ExternalBuffName> physical_food = {
        ExternalBuffName::GrilledSquid,
        ExternalBuffName::SmokedDesertDumplings,
    };

    QVector<ExternalBuffName> physical_elixirs = {
        ExternalBuffName::ElixirOfBruteForce,
        ExternalBuffName::ElixirOfGiants,
        ExternalBuffName::ElixirOfTheMongoose,
    };

    QVector<ExternalBuffName> physical_farmables = {
        ExternalBuffName::WinterfallFirewater,
        ExternalBuffName::JujuMight,
        ExternalBuffName::JujuPower,
        ExternalBuffName::ScrollOfStrengthIV,
        ExternalBuffName::ROIDS,
        ExternalBuffName::GroundScorpokAssay,
        ExternalBuffName::BattleSquawk,
    };

    QVector<ExternalBuffName> physical_world_buffs = {
        ExternalBuffName::FengusFerocity,
        ExternalBuffName::RallyingCryOfTheDragonslayer,
        ExternalBuffName::SongflowerSerenade,
        ExternalBuffName::SpiritOfZandalar,
        ExternalBuffName::SaygesDarkFortuneOfDamage,
    };

    QVector<ExternalBuffName> all_blessings = {
        ExternalBuffName::BlessingOfMight,
        ExternalBuffName::BlessingOfKings,
        ExternalBuffName::BlessingOfWisdom,
    };

    QVector<ExternalBuffName> all_totems = {
        ExternalBuffName::TotemStrengthOfEarth,
        ExternalBuffName::TotemManaSpring,
    };

    QVector<ExternalBuffName> mana_food = {
        ExternalBuffName::NightfinSoup,
    };

    QVector<ExternalBuffName> mana_elixirs = {
        ExternalBuffName::MagebloodPotion,
    };

    QVector<ExternalBuffName> spell_damage_elixirs = {
        ExternalBuffName::GreaterArcaneElixir,
    };

    QVector<ExternalBuffName> all_worldbuffs = {
        ExternalBuffName::SlipkiksSavvy,
        ExternalBuffName::FengusFerocity,
        ExternalBuffName::RallyingCryOfTheDragonslayer,
        ExternalBuffName::SongflowerSerenade,
        ExternalBuffName::SpiritOfZandalar,
        ExternalBuffName::SaygesDarkFortuneOfDamage,
    };

    if (class_name == "Warrior") {
        // Hunters currently double-applies Battle Shout if given as external buff, so temporarily exclude it.
        QVector<ExternalBuffName> physical_raid_buffs = {ExternalBuffName::TrueshotAura};
        return physical_blessings + physical_totems + physical_raid_buffs + common_raid_buffs + physical_food + physical_elixirs + physical_farmables + physical_world_buffs;
    }

    if (class_name == "Rogue") {
        QVector<ExternalBuffName> physical_raid_buffs = {ExternalBuffName::BattleShout, ExternalBuffName::TrueshotAura};
        return physical_blessings + physical_totems + physical_raid_buffs + common_raid_buffs + physical_food + physical_elixirs + physical_farmables + physical_world_buffs;
    }

    if (class_name == "Hunter") {
        // Hunters currently double-applies Trueshot Aura if given as external buff, so temporarily exclude it.
        QVector<ExternalBuffName> physical_raid_buffs = {ExternalBuffName::BattleShout};
        return all_blessings + all_totems + physical_raid_buffs + common_raid_buffs + mana_food + physical_food + mana_elixirs + physical_elixirs + physical_farmables + all_worldbuffs;
    }

    if (hybrid_magical_class.contains(class_name)) {
        QVector<ExternalBuffName> physical_raid_buffs = {ExternalBuffName::BattleShout, ExternalBuffName::TrueshotAura};
        return all_blessings + all_totems + physical_raid_buffs + common_raid_buffs + mana_food + physical_food + mana_elixirs + spell_damage_elixirs + physical_elixirs + physical_farmables + all_worldbuffs;
    }

    if (pure_magical_class.contains(class_name))
        return {
                    ExternalBuffName::BlessingOfKings,
                    ExternalBuffName::BlessingOfWisdom,
                    ExternalBuffName::TotemManaSpring,
                    ExternalBuffName::MarkOfTheWild,
                    ExternalBuffName::NightfinSoup,
                    ExternalBuffName::MagebloodPotion,
                    ExternalBuffName::GreaterArcaneElixir,
                    ExternalBuffName::FlaskOfSupremePower,
                    ExternalBuffName::FlaskOfDistilledWisdom,
                    ExternalBuffName::SlipkiksSavvy,
                    ExternalBuffName::RallyingCryOfTheDragonslayer,
                    ExternalBuffName::SongflowerSerenade,
                    ExternalBuffName::SpiritOfZandalar,
                    ExternalBuffName::SaygesDarkFortuneOfDamage,
        };

    return {};
}
