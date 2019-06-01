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
    this->alliance_only_buffs.append(get_external_buff_by_name(ExternalBuffName::BlessingOfKings, pchar));
    this->alliance_only_buffs.append(get_external_buff_by_name(ExternalBuffName::BlessingOfMight, pchar));
    if (character_is_mana_user())
        this->alliance_only_buffs.append(get_external_buff_by_name(ExternalBuffName::BlessingOfWisdom, pchar));

    this->horde_only_buffs.append(get_external_buff_by_name(ExternalBuffName::StrengthOfEarthTotem, pchar));
    if (character_is_mana_user())
        this->horde_only_buffs.append(get_external_buff_by_name(ExternalBuffName::ManaSpringTotem, pchar));

    for (int i = 0; i < 3; ++i) {
        this->external_buffs.append(QVector<QPair<bool, ExternalBuff*>>());

        if (pchar->get_name() != "Warrior")
            this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::BattleShout, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::MarkOfTheWild, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::ElixirOfBruteForce, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::ElixirOfGiants, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::ElixirOfTheMongoose, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::MagebloodPotion, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::FlaskOfDistilledWisdom, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::FlaskOfSupremePower, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::WinterfallFirewater, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::JujuPower, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::ScrollOfStrengthIV, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::SmokedDesertDumplings, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::GrilledSquid, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::ROIDS, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::SongflowerSerenade, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::SpiritOfZandalar, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::RallyingCryOfTheDragonslayer, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::BattleSquawk, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::FengusFerocity, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::JujuMight, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::GroundScorpokAssay, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::GreaterArcaneElixir, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::SaygesDarkFortuneOfDamage, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::NightfinSoup, pchar)));

        this->external_debuffs.append(QVector<QPair<bool, ExternalBuff*>>());
        this->external_debuffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::SunderArmor, pchar)));
        this->external_debuffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::CurseOfRecklessness, pchar)));
        this->external_debuffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::FaerieFire, pchar)));
        this->external_debuffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::Annihilator, pchar)));

        if (faction->is_alliance()) {
            for (const auto & buff : alliance_only_buffs)
                this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(buff->get_enum_value(), pchar)));
        }
        else {
            for (const auto & buff : horde_only_buffs)
                this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(buff->get_enum_value(), pchar)));
        }
    }

    buffs.append(new EssenceOfTheRed(pchar));

    mutex_buff_groups.append({"Flask of Supreme Power", "Flask of Distilled Wisdom"});
    mutex_buff_groups.append({"Smoked Desert Dumplings", "Grilled Squid", "Nightfin Soup"});
    mutex_buff_groups.append({"Juju Power", "Elixir of Giants"});
    mutex_buff_groups.append({"Juju Might", "Winterfall Firewater"});
    mutex_buff_groups.append({"R.O.I.D.S", "Ground Scorpok Assay"});
}

GeneralBuffs::~GeneralBuffs()
{
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

    this->buffs.clear();
    this->external_buffs.clear();
    this->external_debuffs.clear();
}

void GeneralBuffs::switch_faction() {
    for (auto & setup : external_buffs) {
        QVector<QPair<bool, ExternalBuff*>>::iterator it = setup.begin();

        while (it != setup.end()) {
            if (!it->second->valid_for_faction(faction->get_faction_as_enum())) {
                delete it->second;
                it = setup.erase(it);
            }
            else
                ++it;
        }
    }

    for (auto & setup : external_buffs) {
        if (faction->is_alliance()) {
            for (auto & buff : alliance_only_buffs)
                setup.append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(buff->get_enum_value(), pchar)));
        }
        else {
            for (auto & buff : horde_only_buffs)
                setup.append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(buff->get_enum_value(), pchar)));
        }
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
        vec.append(i.second);
    }
    return vec;
}

QVector<ExternalBuff*> GeneralBuffs::get_external_debuffs() const {
    QVector<ExternalBuff*> vec;
    for (const auto & i : external_debuffs[current_setup]) {
        vec.append(i.second);
    }
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

bool GeneralBuffs::character_is_mana_user() const {
    QSet<QString> mana_users = {"Druid", "Hunter", "Mage", "Paladin", "Priest", "Shaman", "Warlock"};

    return mana_users.contains(pchar->get_name());
}
