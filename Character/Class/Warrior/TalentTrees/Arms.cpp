
#include "Arms.h"
#include "Talent.h"
#include "ImprovedRend.h"
#include "DeepWounds.h"
#include <QDebug>

Arms::Arms(QObject* parent) :
    TalentTree("Arms", parent)
{
    QString base_url = "Assets/warrior/arms/";

    QMap<QString, Talent*> tier1 {{"1LL", new Talent("Improved Heroic Strike", "1LL", base_url + "tier1/Ability_rogue_ambush.png", 3)},
                                  {"1ML", new Talent("Deflection", "1ML", base_url + "tier1/Ability_parry.png", 5)},
                                  {"1MR", new ImprovedRend()}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2LL", new Talent("Improved Charge", "2LL", base_url + "tier2/Ability_warrior_charge.png", 2)},
                                  {"2ML", new Talent("Tactical Mastery", "2ML", base_url + "tier2/Spell_nature_enchantarmor.png", 5)},
                                  {"2RR", new Talent("Improved Thunder Clap", "2RR", base_url + "tier2/Spell_nature_thunderclap.png", 3)}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent("Improved Overpower", "3LL", base_url + "tier3/Inv_sword_05.png", 2)},
                                  {"3ML", new Talent("Anger Management", "3ML", base_url + "tier3/anger_management.png", 1)},
                                  {"3MR", new DeepWounds()}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4ML", new Talent("Two-Handed Weapon Specialization", "4ML", base_url + "tier4/Inv_axe_09.png", 5)},
                                  {"4MR", new Talent("Impale", "4MR", base_url + "tier4/Ability_searingarrow.png", 2)}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL", new Talent("Axe Specialization", "5LL", base_url + "tier5/Inv_axe_06.png", 5)},
                                  {"5ML", new Talent("Sweeping Strikes", "5ML", base_url + "tier5/Ability_rogue_slicedice.png", 1)},
                                  {"5MR", new Talent("Mace Specialization", "5MR", base_url + "tier5/Inv_mace_01.png", 5)},
                                  {"5RR", new Talent("Sword Specialization", "5RR", base_url + "tier5/Inv_sword_27.png", 5)}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6LL", new Talent("Polearm Specialization", "6LL", base_url + "tier6/Inv_weapon_halbard_01.png", 5)},
                                  {"6MR", new Talent("Improved Hamstring", "6MR", base_url + "tier6/Ability_shockwave.png", 3)}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Talent("Mortal Strike", "7ML", base_url + "tier7/Ability_warrior_savageblow.png", 1)}};
    add_talents(tier7);

    talents["1MR"]->set_bottom_child(talents["3MR"]);
    talents["3MR"]->set_parent(talents["1MR"]);
}

Arms::~Arms()
{}
