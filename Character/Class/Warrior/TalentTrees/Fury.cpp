
#include "Fury.h"
#include "Talent.h"
#include <QDebug>

Fury::Fury(QObject* parent) :
    TalentTree("Fury", parent)
{
    QMap<QString, Talent*> tier1 {{"1ML", new Talent("Booming Voice", 5)},
                                  {"1MR", new Talent("Cruelty", 5)}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2ML", new Talent("Improved Demoralizing Shout", 5)},
                                  {"2MR", new Talent("Unbridled Wrath", 5)}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent("Improved Cleave", 3)},
                                  {"3ML", new Talent("Piercing Howl", 1)},
                                  {"3MR", new Talent("Blood Craze", 3)},
                                  {"3RR", new Talent("Improved Battle Shout", 5)}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4LL", new Talent("Dual Wield Specialization", 5)},
                                  {"4ML", new Talent("Improved Execute", 2)},
                                  {"4MR", new Talent("Enrage", 5)}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL", new Talent("Improved Slam", 5)},
                                  {"5ML", new Talent("Death Wish", 1)},
                                  {"5RR", new Talent("Improved Intercept", 2)}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6LL", new Talent("Improved Berserker Rage", 2)},
                                  {"6MR", new Talent("Flurry", 5)}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Talent("Bloodthirst", 1)}};
    add_talents(tier7);
}

Fury::~Fury()
{}
