#include "GeneralBuffs.h"

#include "Character.h"
#include "EssenceOfTheRed.h"
#include "ExternalBuff.h"
#include "Faction.h"

GeneralBuffs::GeneralBuffs(Character* pchar, Faction* faction) :
    pchar(pchar),
    faction(faction),
    current_setup(0)
{
    this->alliance_only_buffs.append(get_external_buff_by_name(ExternalBuffName::BlessingOfKings, pchar));
    this->alliance_only_buffs.append(get_external_buff_by_name(ExternalBuffName::BlessingOfMight, pchar));

    this->horde_only_buffs.append(get_external_buff_by_name(ExternalBuffName::StrengthOfEarthTotem, pchar));

    for (int i = 0; i < 3; ++i) {
        this->external_buffs.append(QVector<QPair<bool, ExternalBuff*>>());

        if (pchar->get_name() != "Warrior")
            this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::BattleShout, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::MarkOfTheWild, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::ElixirOfBruteForce, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::ElixirOfGiants, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::ElixirOfTheMongoose, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::WinterfallFirewater, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::JujuPower, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::ScrollOfStrengthIV, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::SmokedDesertDumplings, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::ROIDS, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::SongflowerSerenade, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::SpiritOfZandalar, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::RallyingCryOfTheDragonslayer, pchar)));

        this->external_debuffs.append(QVector<QPair<bool, ExternalBuff*>>());
        this->external_debuffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::SunderArmor, pchar)));
        this->external_debuffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::CurseOfRecklessness, pchar)));
        this->external_debuffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::FaerieFire, pchar)));
        this->external_debuffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::Annihilator, pchar)));

        if (faction->is_alliance()) {
            for (auto & buff : alliance_only_buffs)
                this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(buff->get_enum_value(), pchar)));
        }
        else {
            for (auto & buff : horde_only_buffs)
                this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(buff->get_enum_value(), pchar)));
        }
    }

    buffs.append(new EssenceOfTheRed(pchar));
}

GeneralBuffs::~GeneralBuffs()
{
    for (auto & buff : this->buffs) {
        delete buff;
    }

    for (auto & external_buff : this->external_buffs) {
        for (auto & j : external_buff) {
            delete j.second;
        }
    }

    for (auto & external_debuff : this->external_debuffs) {
        for (auto & j : external_debuff) {
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
    for (auto & buff : buffs) {
        if (buff->get_name() == buff_name)
            return buff;
    }

    return nullptr;
}

QVector<ExternalBuff*> GeneralBuffs::get_external_buffs() const {
    QVector<ExternalBuff*> vec;
    for (auto i : external_buffs[current_setup]) {
        vec.append(i.second);
    }
    return vec;
}

QVector<ExternalBuff*> GeneralBuffs::get_external_debuffs() const {
    QVector<ExternalBuff*> vec;
    for (auto i : external_debuffs[current_setup]) {
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
            assert(!i.second->is_active());
        }
        else {
            i.first = true;
            i.second->apply_buff();
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
    for (auto i : vec[current_setup]) {
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
    for (auto i : vec[current_setup]) {
        if (i.first)
            i.second->apply_buff();
    }
}

void GeneralBuffs::deactivate_externals(const QVector<QVector<QPair<bool, ExternalBuff*>>>& vec) {
    for (auto i : vec[current_setup]) {
        if (i.second->is_active())
            i.second->cancel_buff();
    }
}
