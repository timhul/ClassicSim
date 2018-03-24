
#include "Arms.h"
#include "Talent.h"
#include <QDebug>

Arms::Arms(QObject* parent) :
    TalentTree("Arms", parent)
{
    QString base_url = "Assets/warrior/arms/";

    QMap<QString, Talent*> tier1 {{"1LL", new Talent("Improved Heroic Strike", base_url + "tier1/Ability_rogue_ambush.png", 3)},
                                  {"1ML", new Talent("Deflection", base_url + "tier1/Ability_parry.png", 5)},
                                  {"1MR", new Talent("Improved Rend", base_url + "tier1/Ability_gouge.png", 3)}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2LL", new Talent("Improved Charge", base_url + "tier2/Ability_warrior_charge.png", 2)},
                                  {"2ML", new Talent("Tactical Mastery", base_url + "tier2/Spell_nature_enchantarmor.png", 5)},
                                  {"2RR", new Talent("Improved Thunder Clap", base_url + "tier2/Spell_nature_thunderclap.png", 3)}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent("Improved Overpower", base_url + "tier3/Inv_sword_05.png", 2)},
                                  {"3ML", new Talent("Anger Management", base_url + "tier3/anger_management.png", 1)},
                                  {"3MR", new Talent("Deep Wounds", base_url + "tier3/Ability_backstab.png", 3)}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4ML", new Talent("Two-Handed Weapon Specialization", base_url + "tier4/Inv_axe_09.png", 5)},
                                  {"4MR", new Talent("Impale", base_url + "tier4/Ability_searingarrow.png", 2)}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL", new Talent("Axe Specialization", base_url + "tier5/Inv_axe_06.png", 5)},
                                  {"5ML", new Talent("Sweeping Strikes", base_url + "tier5/Ability_rogue_slicedice.png", 1)},
                                  {"5MR", new Talent("Mace Specialization", base_url + "tier5/Inv_mace_01.png", 5)},
                                  {"5RR", new Talent("Sword Specialization", base_url + "tier5/Inv_sword_27.png", 5)}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6LL", new Talent("Polearm Specialization", base_url + "tier6/Inv_weapon_halbard_01.png", 5)},
                                  {"6MR", new Talent("Improved Hamstring", base_url + "tier6/Ability_shockwave.png", 3)}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Talent("Mortal Strike", base_url + "tier7/Ability_warrior_savageblow.png", 1)}};
    add_talents(tier7);
}

Arms::~Arms()
{}
