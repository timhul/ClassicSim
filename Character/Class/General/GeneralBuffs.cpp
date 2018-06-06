
#include "GeneralBuffs.h"
#include "Character.h"
#include "HolyStrength.h"
#include "ElixirOfBruteForce.h"
#include "ElixirOfGiants.h"
#include "ElixirOfTheMongoose.h"
#include "RallyingCryOfTheDragonslayer.h"
#include "SongflowerSerenade.h"

GeneralBuffs::GeneralBuffs(Character* pchar, Faction* faction, QObject* parent) :
    QObject(parent),
    pchar(pchar),
    faction(faction)
{
    this->holy_strength_mh = new HolyStrength(pchar);
    this->holy_strength_oh = new HolyStrength(pchar);

    this->buffs = {holy_strength_mh, holy_strength_oh};

    this->external_buffs.append(new ElixirOfBruteForce(pchar));
    this->external_buffs.append(new ElixirOfGiants(pchar));
    this->external_buffs.append(new ElixirOfTheMongoose(pchar));
    this->external_buffs.append(new RallyingCryOfTheDragonslayer(pchar));
    this->external_buffs.append(new SongflowerSerenade(pchar));
}

GeneralBuffs::~GeneralBuffs()
{
    for (int i = 0; i < this->buffs.size(); ++i) {
        delete this->buffs[i];
    }

    this->buffs.clear();

    for (int i = 0; i < this->external_buffs.size(); ++i) {
        delete this->external_buffs[i];
    }

    this->external_buffs.clear();
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
    return this->external_buffs;
}

void GeneralBuffs::toggle_external_buff(const QString& buff_name) {
    for (int i = 0; i < external_buffs.size(); ++i) {
        if (external_buffs[i]->get_name() == buff_name) {
            if (external_buffs[i]->is_active()) {
                external_buffs[i]->use_charge();
                assert(!external_buffs[i]->is_active());
            }
            else {
                external_buffs[i]->apply_buff();
            }

            break;
        }
    }
}

bool GeneralBuffs::buff_active(const QString& buff_name) const {
    for (int i = 0; i < external_buffs.size(); ++i) {
        if (external_buffs[i]->get_name() == buff_name)
            return external_buffs[i]->is_active();
    }

    return false;
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
