
#include "Protection.h"
#include "Talent.h"
#include <QDebug>

Protection::Protection(QObject* parent) :
    TalentTree("Protection", parent)
{
    QMap<QString, Talent*> tier1 {{"1ML", new Talent("Shield Specialization", 5)},
                                  {"1MR", new Talent("Anticipation", 5)}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2LL", new Talent("Improved Bloodrage", 2)},
                                  {"2MR", new Talent("Toughness", 5)},
                                  {"2RR", new Talent("Iron Will", 5)}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent("Last Stand", 1)},
                                  {"3ML", new Talent("Improved Shield Block", 3)},
                                  {"3MR", new Talent("Improved Revenge", 3)},
                                  {"3RR", new Talent("Defiance", 5)}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4LL", new Talent("Improved Sunder Armor", 3)},
                                  {"4ML", new Talent("Improved Disarm", 3)},
                                  {"4MR", new Talent("Improved Taunt", 2)}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL", new Talent("Improved Shield Wall", 2)},
                                  {"5ML", new Talent("Concussion Blow", 1)},
                                  {"5MR", new Talent("Improved Shield Bash", 2)}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6MR", new Talent("One-Handed Weapon Specialization", 5)}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Talent("Shield Slam", 1)}};
    add_talents(tier7);
}

Protection::~Protection()
{}
