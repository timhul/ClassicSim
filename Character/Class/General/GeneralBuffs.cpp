
#include "GeneralBuffs.h"
#include "Character.h"
#include "ExternalBuff.h"
#include "EssenceOfTheRed.h"

GeneralBuffs::GeneralBuffs(Character* pchar, Faction* faction, QObject* parent) :
    QObject(parent),
    pchar(pchar),
    faction(faction),
    current_setup(0)
{
    for (int i = 0; i < 3; ++i) {
        this->external_buffs.append(QVector<QPair<bool, ExternalBuff*>>());
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::ElixirOfBruteForce, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::ElixirOfGiants, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::ElixirOfTheMongoose, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::RallyingCryOfTheDragonslayer, pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::SongflowerSerenade, pchar)));

        this->external_debuffs.append(QVector<QPair<bool, ExternalBuff*>>());
        this->external_debuffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::SunderArmor, pchar)));
        this->external_debuffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::CurseOfRecklessness, pchar)));
        this->external_debuffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::FaerieFire, pchar)));
        this->external_debuffs[i].append(QPair<bool, ExternalBuff*>(false, get_external_buff_by_name(ExternalBuffName::Annihilator, pchar)));
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
