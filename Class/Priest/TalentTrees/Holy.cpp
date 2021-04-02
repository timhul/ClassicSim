#include "Holy.h"

#include "Talent.h"
#include "TalentStatIncrease.h"
#include "Priest.h"
#include "PriestSpells.h"

    Holy::Holy(Priest* priest) :
    TalentTree("Holy", "Assets/priest/priest_curses.jpg"), priest(priest), spells(static_cast<PriestSpells*>(priest->get_spells())) {
    talent_names_to_locations = {
            {"Healing Focus", "1LL"},
            {"Improved Renew", "1ML"},
            {"Holy Specialization", "1MR"},
            {"Spell Warding", "2ML"},
            {"Divine Fury", "2MR"},
            {"Holy Nova", "3LL"},
            {"Blessed Recovery", "3ML"},
            {"Inspiration", "3RR"},
            {"Holy Reach", "4LL"},
            {"Improved Healing", "4ML"},
            {"Searing Light", "4MR"},
            {"Improved Prayer of Healing", "5LL"},
            {"Spirit of Redemption", "5ML"},
            {"Spiritual Guidance", "5MR"},
            {"Spiritual Healing", "6MR"},
            {"Lightwell", "7ML"}
        };

    QMap<QString, Talent*> tier1 {
        {"1LL", new Talent(priest, this, "Healing Focus", "1LL", "Assets/spell/", 2,
                           "Gives you a %1% chance to avoid interruption caused by damage while casting any healing spell.",
                           QVector<QPair<unsigned, unsigned>> {{35, 35}})},
        {"1ML", new Talent(priest, this, "Improved Renew", "1ML", "Assets/spell/", 3,
                           "Increases the amount healed by your Renew spell by %1%.",
                           QVector<QPair<double, double>> {{5, 5}})},
        {"1MR", new Talent(priest, this, "Holy Specialization", "1MR", "Assets/spell/", 5,
                           "Increases the critical effect chance of your Holy spells by %1%.",
                           QVector<QPair<unsigned, unsigned>> {{1, 1}})}
    };
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {
        {"2ML", new Talent(priest, this, "Spell Warding", "2ML", "Assets/spell/", 5,
                           "Reduces all spell damage taken by %1%.",
                           QVector<QPair<unsigned, unsigned>> {{2, 2}})},
        {"2MR", new Talent(priest, this, "Divine Fury", "2MR", "Assets/spell/", 5,
                           "Reduces the casting time of your Smite, Holy Fire, Heal and Greater Heal spells by %1 sec.",
                           QVector<QPair<double, double>> {{0.1, 0.1}})}
    };
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {
        {"3LL", new Talent(priest, this, "Holy Nova", "3LL", "Assets/spell/", 1,
                           "Causes an explosion of holy light around the caster, causing 29 to 34 Holy damage to all enemy targets within 10 yards and healing all party members within 10 yards for 54 to 63. These effects cause no threat.",
                           QVector<QPair<unsigned, unsigned>> {})},
        {"3ML", new Talent(priest, this, "Blessed Recovery", "3ML", "Assets/spell/", 3,
                           "After being struck by a melee or ranged critical hit, heal %1% of the damage taken over 6 sec.",
                           QVector<QPair<unsigned, unsigned>> {{8 ,8}})},
        {"3RR", new Talent(priest, this, "Inspiration", "3RR", "Assets/spell/", 3,
                           "Increases your target's armor by %1% for 15 sec after getting a critical effect from your Flash Heal, Heal, Greater Heal, or Prayer of Healing spell.",
                           QVector<QPair<unsigned, unsigned>> {{8, 8}})}
    };
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {
        {"4LL", new Talent(priest, this, "Holy Reach", "4LL", "Assets/spell/", 2,
                           "Increases the range of your Smite and Holy Fire spells and the radius of your Prayer of Healing and Holy Nova spells by %1%.",
                           QVector<QPair<unsigned, unsigned>> {{10, 10}})},
        {"4ML", new Talent(priest, this, "Improved Healing", "4ML", "Assets/spell/", 3,
                           "Reduces the Mana cost of your Lesser Heal, Heal, and Greater Heal spells by %1%.",
                           QVector<QPair<unsigned, unsigned>> {{5, 5}})},
        {"4MR", new Talent(priest, this, "Searing Light", "4MR", "Assets/spell/", 2,
                           "Increases the damage of your Smite and Holy Fire spells by %1%.",
                           QVector<QPair<unsigned, unsigned>> {{5, 5}})}
    };
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {
        {"5LL", new Talent(priest, this, "Improved Prayer of Healing", "5LL", "Assets/spell/", 2,
                           "Reduces the Mana cost of your Prayer of Healing spell by %1%.",
                           QVector<QPair<unsigned, unsigned>> {{10 ,10}})},
        {"5ML", new Talent(priest, this, "Spirit of Redemption", "5ML", "Assets/spell/", 1,
                           "Upon death, the priest becomes the Spirit of Redemption for 10 sec. The Spirit of Redemption cannot move, attack, be attacked or targeted by any spells or effects. While in this form the priest can cast any healing spell free of cost. When the effect ends, the priest dies.",
                           QVector<QPair<unsigned, unsigned>> {})},
        {"5MR", new Talent(priest, this, "Spiritual Guidance", "5MR", "Assets/spell/", 5,
                           "Increases spell damage and healing by up to %1% of your total Spirit.",
                           QVector<QPair<unsigned, unsigned>> {{5, 5}})}
    };
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {
        {"6MR", new Talent(priest, this, "Spiritual Healing", "6MR", "Assets/spell/", 5,
                           "Increases the amount healed by your healing spells by %1%.",
                           QVector<QPair<unsigned, unsigned>> {{2, 2}})}
    };
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {
        {"7ML", new Talent(priest, this, "Lightwell", "5RR", "Assets/spell/", 1,
                           "Creates a holy Lightwell near the priest. Members of your raid or party can click the Lightwell to restore 800 health over 10 sec. Being attacked cancels the effect. Lightwell lasts for 3 min or 5 charges.",
                           QVector<QPair<unsigned, unsigned>> {})}
    };
    add_talents(tier7);

    talents["2MR"]->talent->set_bottom_child(talents["4MR"]->talent);
    talents["4MR"]->talent->set_parent(talents["2MR"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["5ML"]->talent);
}
