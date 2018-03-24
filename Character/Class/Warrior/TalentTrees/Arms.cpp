
#include "Arms.h"
#include "Talent.h"
#include <QDebug>

Arms::Arms(QObject* parent) :
    TalentTree("Arms", parent)
{
    QMap<QString, Talent*> tier1 {{"1LL", new Talent("Improved Heroic Strike", 3)},
                                  {"1ML", new Talent("Deflection", 5)},
                                  {"1MR", new Talent("Improved Rend", 3)}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2LL", new Talent("Improved Charge", 2)},
                                  {"2ML", new Talent("Tactical Mastery", 5)},
                                  {"2RR", new Talent("Improved Thunder Clap", 3)}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent("Improved Overpower", 2)},
                                  {"3ML", new Talent("Anger Management", 1)},
                                  {"3MR", new Talent("Deep Wounds", 3)}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4ML", new Talent("Two-Handed Weapon Specialization", 5)},
                                  {"4MR", new Talent("Impale", 2)}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL", new Talent("Axe Specialization", 5)},
                                  {"5ML", new Talent("Sweeping Strikes", 1)},
                                  {"5MR", new Talent("Mace Specialization", 5)},
                                  {"5RR", new Talent("Sword Specialization", 5)}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6LL", new Talent("Polearm Specialization", 5)},
                                  {"6MR", new Talent("Improved Hamstring", 3)}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Talent("Mortal Strike", 1)}};
    add_talents(tier7);
}

Arms::~Arms()
{}
