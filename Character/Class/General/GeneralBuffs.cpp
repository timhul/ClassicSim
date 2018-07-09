
#include "GeneralBuffs.h"
#include "Character.h"
#include "HolyStrength.h"
#include "ElixirOfBruteForce.h"
#include "ElixirOfGiants.h"
#include "ElixirOfTheMongoose.h"
#include "RallyingCryOfTheDragonslayer.h"
#include "SongflowerSerenade.h"

#include "AnnihilatorBuff.h"
#include "CurseOfRecklessnessBuff.h"
#include "FaerieFireBuff.h"
#include "SunderArmorBuff.h"

GeneralBuffs::GeneralBuffs(Character* pchar, Faction* faction, QObject* parent) :
    QObject(parent),
    pchar(pchar),
    faction(faction),
    current_setup(0)
{
    this->holy_strength_mh = new HolyStrength(pchar);
    this->holy_strength_oh = new HolyStrength(pchar);

    this->buffs = {holy_strength_mh, holy_strength_oh};

    for (int i = 0; i < 3; ++i) {
        this->external_buffs.append(QVector<QPair<bool, ExternalBuff*>>());
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, new ElixirOfBruteForce(pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, new ElixirOfGiants(pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, new ElixirOfTheMongoose(pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, new RallyingCryOfTheDragonslayer(pchar)));
        this->external_buffs[i].append(QPair<bool, ExternalBuff*>(false, new SongflowerSerenade(pchar)));

        this->external_debuffs.append(QVector<QPair<bool, ExternalBuff*>>());
        this->external_debuffs[i].append(QPair<bool, ExternalBuff*>(false, new SunderArmorBuff(pchar)));
        this->external_debuffs[i].append(QPair<bool, ExternalBuff*>(false, new CurseOfRecklessnessBuff(pchar)));
        this->external_debuffs[i].append(QPair<bool, ExternalBuff*>(false, new FaerieFireBuff(pchar)));
        this->external_debuffs[i].append(QPair<bool, ExternalBuff*>(false, new AnnihilatorBuff(pchar)));
    }
}

GeneralBuffs::~GeneralBuffs()
{
    for (int i = 0; i < this->buffs.size(); ++i) {
        delete this->buffs[i];
    }

    for (int i = 0; i < this->external_buffs.size(); ++i) {
        for (int j = 0; j < this->external_buffs[i].size(); ++j) {
            delete this->external_buffs[i][j].second;
        }
    }

    for (int i = 0; i < this->external_debuffs.size(); ++i) {
        for (int j = 0; j < this->external_debuffs[i].size(); ++j) {
            delete this->external_debuffs[i][j].second;
        }
    }

    this->buffs.clear();
    this->external_buffs.clear();
    this->external_debuffs.clear();
}

void GeneralBuffs::switch_faction() {
}

HolyStrength* GeneralBuffs::get_holy_strength_mh() const {
    return this->holy_strength_mh;
}

HolyStrength* GeneralBuffs::get_holy_strength_oh() const {
    return this->holy_strength_oh;
}

QVector<ExternalBuff*> GeneralBuffs::get_external_buffs() const {
    QVector<ExternalBuff*> vec;
    for (int i = 0; i < external_buffs[current_setup].size(); ++i) {
        vec.append(external_buffs[current_setup][i].second);
    }
    return vec;
}

QVector<ExternalBuff*> GeneralBuffs::get_external_debuffs() const {
    QVector<ExternalBuff*> vec;
    for (int i = 0; i < external_debuffs[current_setup].size(); ++i) {
        vec.append(external_debuffs[current_setup][i].second);
    }
    return vec;
}

void GeneralBuffs::toggle_external(const QString& name, QVector<QVector<QPair<bool, ExternalBuff *>>> &vec) {
    for (int i = 0; i < vec[current_setup].size(); ++i) {
        if (vec[current_setup][i].second->get_name() == name) {
            if (vec[current_setup][i].second->is_active()) {
                vec[current_setup][i].first = false;
                vec[current_setup][i].second->cancel_buff();
                assert(!vec[current_setup][i].second->is_active());
            }
            else {
                vec[current_setup][i].first = true;
                vec[current_setup][i].second->apply_buff();
            }

            break;
        }
    }
}

void GeneralBuffs::toggle_external_buff(const QString& buff_name) {
    toggle_external(buff_name, this->external_buffs);
}

void GeneralBuffs::toggle_external_debuff(const QString& debuff_name) {
    toggle_external(debuff_name, this->external_debuffs);
}

bool GeneralBuffs::external_buff_active(const QString& name, const QVector<QVector<QPair<bool, ExternalBuff *>>> &vec) const {
    for (int i = 0; i < vec[current_setup].size(); ++i) {
        if (vec[current_setup][i].second->get_name() == name)
            return vec[current_setup][i].second->is_active();
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
    for (int i = 0; i < vec[current_setup].size(); ++i) {
        if (vec[current_setup][i].first == true) {
            vec[current_setup][i].second->apply_buff();
        }
    }
}

void GeneralBuffs::deactivate_externals(const QVector<QVector<QPair<bool, ExternalBuff*>>>& vec) {
    for (int i = 0; i < vec[current_setup].size(); ++i) {
        if (vec[current_setup][i].second->is_active())
            vec[current_setup][i].second->cancel_buff();
    }
}

/*
ListElement {
    bname: "BATTLE_SHOUT"
    bicon: "Assets/warrior/fury/tier3/Ability_warrior_battleshout.png"
    btext: "Improved Battle Shout\nIncreases attack power by 290"
}
ListElement {
    bname: "LEADER_OF_THE_PACK"
    bicon: "Assets/buffs/Spell_nature_unyeildingstamina.png"
    btext: "Leader of the Pack\n+3% Critical Strike"
}
ListElement {
    bname: "WINDFURY"
    bicon: "Assets/buffs/Spell_nature_windfury.png"
    btext: "Windfury Totem\n20% chance to grant 1 extra attack with extra melee ap"
}
ListElement {
    bname: "MARK_OF_THE_WILD"
    bicon: "Assets/buffs/Spell_nature_regeneration.png"
    btext: "Improved Mark of the Wild\n+20 all attributes"
}
ListElement {
    bname: "BLESSING_OF_KINGS"
    bicon: "Assets/buffs/Spell_magic_greaterblessingofkings.png"
    btext: "Greater Blessing of Kings\nIncreases total stats by 10%"
}
ListElement {
    bname: "BLESSING_OF_MIGHT"
    bicon: "Assets/buffs/Spell_holy_greaterblessingofkings.png"
    btext: "Greater Blessing of Might\nIncreases melee attack power by 185"
}
ListElement {
    bname: "JUJU_POWER"
    bicon: "Assets/buffs/Inv_misc_monsterscales_11.png"
    btext: "Juju Power\n+30 Strength"
}
ListElement {
    bname: "JUJU_MIGHT"
    bicon: "Assets/buffs/Inv_misc_monsterscales_07.png"
    btext: "Juju Might\n+40 Attack power"
}
ListElement {
    bname: "ROIDS"
    bicon: "Assets/buffs/Inv_stone_15.png"
    btext: "R.O.I.D.S\n+25 Strength"
}
ListElement {
    bname: "WINTERFALL_FIREWATER"
    bicon: "Assets/buffs/Inv_potion_92.png"
    btext: "Winterfall Firewater\n+35 Melee attack power"
}
ListElement {
    bname: "SMOKED_DESERT_DUMPLINGS"
    bicon: "Assets/buffs/Inv_misc_food_64.png"
    btext: "Smoked Desert Dumplings\n+20 Strength"
}
ListElement {
    bname: "SCROLL_OF_STRENGTH_IV"
    bicon: "Assets/buffs/Inv_scroll_02.png"
    btext: "Scroll of Strength IV\n+17 Strength"
}
ListElement {
    bname: "SPIRIT_OF_ZANDALAR"
    bicon: "Assets/buffs/Ability_creature_poison_05.png"
    btext: "Spirit of Zandalar\n15% all stats and 10% movement speed"
}
ListElement {
    bname: "FENGUS_FEROCITY"
    bicon: "Assets/buffs/Spell_nature_undyingstrength.png"
    btext: "Fengus' Ferocity\n+200 Attack power"
}
*/
