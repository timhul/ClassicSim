
#include "Protection.h"
#include "Talent.h"
#include <QDebug>

Protection::Protection(Character *pchar, QObject* parent) :
    TalentTree("Protection", "Assets/warrior/warrior_protection.jpg", parent)
{
    QString base_url = "Assets/warrior/protection/";

    QMap<QString, Talent*> tier1 {{"1ML", new Talent(pchar, "Shield Specialization", "1ML", base_url + "tier1/Inv_shield_06.png", 5)},
                                  {"1MR", new Talent(pchar, "Anticipation", "1MR", base_url + "tier1/Spell_nature_mirrorimage.png", 5)}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2LL", new Talent(pchar, "Improved Bloodrage", "2LL", base_url + "tier2/Ability_racial_bloodrage.png", 2)},
                                  {"2MR", new Talent(pchar, "Toughness", "2MR", base_url + "tier2/Spell_holy_devotion.png", 5)},
                                  {"2RR", new Talent(pchar, "Iron Will", "2RR", base_url + "tier2/Spell_magic_magearmor.png", 5)}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent(pchar, "Last Stand", "3LL", base_url + "tier3/Spell_holy_ashestoashes.png", 1)},
                                  {"3ML", new Talent(pchar, "Improved Shield Block", "3ML", base_url + "tier3/Ability_defend.png", 3)},
                                  {"3MR", new Talent(pchar, "Improved Revenge", "3MR", base_url + "tier3/Ability_warrior_revenge.png", 3)},
                                  {"3RR", new Talent(pchar, "Defiance", "3RR", base_url + "tier3/Ability_warrior_innerrage.png", 5)}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4LL", new Talent(pchar, "Improved Sunder Armor", "4LL", base_url + "tier4/Ability_warrior_sunder.png", 3)},
                                  {"4ML", new Talent(pchar, "Improved Disarm", "4ML", base_url + "tier4/Ability_warrior_disarm.png", 3)},
                                  {"4MR", new Talent(pchar, "Improved Taunt", "4MR", base_url + "tier4/Spell_nature_reincarnation.png", 2)}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL", new Talent(pchar, "Improved Shield Wall", "5LL", base_url + "tier5/Ability_warrior_shieldwall.png", 2)},
                                  {"5ML", new Talent(pchar, "Concussion Blow", "5ML", base_url + "tier5/Ability_thunderbolt.png", 1)},
                                  {"5MR", new Talent(pchar, "Improved Shield Bash", "5MR", base_url + "tier5/Ability_warrior_shieldbash.png", 2)}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6MR", new Talent(pchar, "One-Handed Weapon Specialization", "6MR", base_url + "tier6/Inv_sword_20.png", 5)}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Talent(pchar, "Shield Slam", "7ML", base_url + "tier7/Inv_shield_05.png", 1)}};
    add_talents(tier7);
}

Protection::~Protection()
{}
