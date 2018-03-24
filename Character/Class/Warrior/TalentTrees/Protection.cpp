
#include "Protection.h"
#include "Talent.h"
#include <QDebug>

Protection::Protection(QObject* parent) :
    TalentTree("Protection", parent)
{
    QString base_url = "Assets/warrior/protection/";

    QMap<QString, Talent*> tier1 {{"1ML", new Talent("Shield Specialization", base_url + "tier1/Inv_shield_06.png", 5)},
                                  {"1MR", new Talent("Anticipation", base_url + "tier1/Spell_nature_mirrorimage.png", 5)}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2LL", new Talent("Improved Bloodrage", base_url + "tier2/Ability_racial_bloodrage.png", 2)},
                                  {"2MR", new Talent("Toughness", base_url + "tier2/Spell_holy_devotion.png", 5)},
                                  {"2RR", new Talent("Iron Will", base_url + "tier2/Spell_magic_magearmor.png", 5)}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent("Last Stand", base_url + "tier3/Spell_holy_ashestoashes.png", 1)},
                                  {"3ML", new Talent("Improved Shield Block", base_url + "tier3/Ability_defend.png", 3)},
                                  {"3MR", new Talent("Improved Revenge", base_url + "tier3/Ability_warrior_revenge.png", 3)},
                                  {"3RR", new Talent("Defiance", base_url + "tier3/Ability_warrior_innerrage.png", 5)}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4LL", new Talent("Improved Sunder Armor", base_url + "tier4/Ability_warrior_sunder.png", 3)},
                                  {"4ML", new Talent("Improved Disarm", base_url + "tier4/Ability_warrior_disarm.png", 3)},
                                  {"4MR", new Talent("Improved Taunt", base_url + "tier4/Spell_nature_reincarnation.png", 2)}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL", new Talent("Improved Shield Wall", base_url + "tier5/Ability_warrior_shieldwall.png", 2)},
                                  {"5ML", new Talent("Concussion Blow", base_url + "tier5/Ability_thunderbolt.png", 1)},
                                  {"5MR", new Talent("Improved Shield Bash", base_url + "tier5/Ability_warrior_shieldbash.png", 2)}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6MR", new Talent("One-Handed Weapon Specialization", base_url + "tier6/Inv_sword_20.png", 5)}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Talent("Shield Slam", base_url + "tier7/Inv_shield_05.png", 1)}};
    add_talents(tier7);
}

Protection::~Protection()
{}
