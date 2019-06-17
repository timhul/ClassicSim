#include "Frost.h"

#include "Mage.h"
#include "MageSpells.h"
#include "Talent.h"

Frost::Frost(Mage* mage) :
    TalentTree("Frost", "Assets/mage/mage_frost.jpg"),
    mage(mage),
    spells(dynamic_cast<MageSpells*>(mage->get_spells()))
{
    QMap<QString, Talent*> tier1 {{"1LL", new Talent(mage, this, "Frost Warding", "1LL", "Assets/spell/Spell_frost_frostward.png", 2, "Increases the armor and resistances given by your Frost Armor and Ice Armor spells by %1%. In addition, gives your Frost Ward a %2% chance to reflect Frost spells and effects while active.", QVector<QPair<unsigned, unsigned>>{{15, 15}, {10, 10}})},
                                  {"1ML", new Talent(mage, this, "Improved Frostbolt", "1ML", "Assets/spell/Spell_frost_frostbolt02.png", 5, "Reduces the casting time of your Frostbolt spell by %1 sec.", QVector<QPair<double, double>>{{0.1, 0.1}})},
                                  {"1MR", new Talent(mage, this, "Elemental Precision", "1MR", "Assets/spell/Spell_ice_magicdamage.png", 3, "Reduces the chance that the opponent can resist your Frost and Fire spells by %1%.", QVector<QPair<unsigned, unsigned>>{{2, 2}})}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2LL", new Talent(mage, this, "Ice Shards", "2LL", "Assets/items/Spell_frost_iceshard.png", 5, "Increases the critical strike damage bonus of your Frost spells by %1%.", QVector<QPair<unsigned, unsigned>>{{20, 20}})},
                                  {"2ML", new Talent(mage, this, "Frostbite", "2ML", "Assets/spell/Spell_frost_frostarmor.png", 3, "Gives your Chill effects a %1% chance to freeze the target for 5 sec.", QVector<QPair<unsigned, unsigned>>{{5, 5}})},
                                  {"2MR", new Talent(mage, this, "Improved Frost Nova", "2MR", "Assets/spell/Spell_frost_freezingbreath.png", 2, "Reduces the cooldown of your Frost Nova spell by %1 sec.", QVector<QPair<unsigned, unsigned>>{{2, 2}})},
                                  {"2RR", new Talent(mage, this, "Permafrost", "2RR", "Assets/spell/Spell_frost_wisp.png", 3, "Increases the duration of your Chill effects by %1 sec and reduces the target's speed by an additional %2%.", QVector<QPair<unsigned, unsigned>>{{1, 1}, {4, 3}})}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent(mage, this, "Piercing Ice", "3LL", "Assets/spell/Spell_frost_frostbolt.png", 3, "Increases the damage done by your Frost spells by %1%.", QVector<QPair<unsigned, unsigned>>{{2, 2}})},
                                  {"3ML", new Talent(mage, this, "Cold Snap", "3ML", "Assets/spell/Spell_frost_wizardmark.png", 1, "When activated, this spell finishes the cooldown on all of your Frost spells.", QVector<QPair<unsigned, unsigned>>{})},
                                  {"3RR", improved_blizzard()}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4LL", new Talent(mage, this, "Arctic Reach", "4LL", "Assets/spell/Spell_shadow_darkritual.png", 2, "Increases the range of your Frostbolt and Blizzard spells and the radius of your Frost Nova and Cone of Cold spells by %1%.", QVector<QPair<unsigned, unsigned>>{{10, 10}})},
                                  {"4ML", new Talent(mage, this, "Frost Channeling", "4ML", "Assets/spell/Spell_frost_stun.png", 3, "Reduces the mana cost of your Frost spells by %1% and reduces the threat caused by your Frost spells by %2%.", QVector<QPair<unsigned, unsigned>>{{5, 5}, {10, 10}})},
                                  {"4MR", new Talent(mage, this, "Shatter", "4MR", "Assets/spell/Spell_frost_frostshock.png", 5, "Increases the critical strike chance of all your spells against frozen targets by %1%.", QVector<QPair<unsigned, unsigned>>{{10, 10}})}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5ML", new Talent(mage, this, "Ice Block", "5ML", "Assets/spell/Spell_frost_frost.png", 1, "You become encased in a block of ice, protecting you from all physical attacks and spells for 10 sec, but during that time you cannot attack, move or cast spells.", QVector<QPair<unsigned, unsigned>>{})},
                                  {"5MR", new Talent(mage, this, "Improved Cone of Cold", "5MR", "Assets/spell/Spell_frost_glacier.png", 3, "Increases the damage dealt by your Cone of Cold spell by %1%.", QVector<QPair<unsigned, unsigned>>{{15, 10}})}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6MR", new Talent(mage, this, "Winter's Chill", "6MR", "Assets/spell/Spell_frost_chillingblast.png", 5, "Gives your Frost damage spells a %1% chance to apply the Winter's Chill effect, which increases the chance a Frost spell will critically hit the target by 2% for 15 sec. Stacks up to 5 times.", QVector<QPair<unsigned, unsigned>>{{20, 20}})}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Talent(mage, this, "Ice Barrier", "7ML", "Assets/spell/Spell_ice_lament.png", 1, "Instantly shields you, absorbing 438 damage. Lasts 1 min. While the shield holds, spells will not be interrupted.", QVector<QPair<unsigned, unsigned>>())}};
    add_talents(tier7);

    talents["2MR"]->talent->set_bottom_child(talents["4MR"]->talent);
    talents["4MR"]->talent->set_parent(talents["2MR"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["5ML"]->talent);
}

Talent* Frost::improved_blizzard() {
    QString base_str = "Adds a chill effect to your Blizzard spell. This effect lowers the target's movement speed by %1%. Lasts 1.50 sec.";
    QMap<unsigned, QString> rank_descriptions {{0, base_str.arg(30)}, {1, base_str.arg(30)},
                                               {2, base_str.arg(50)},
                                               {3, base_str.arg(65)}};
    Talent* talent = new Talent(mage, this, "Improved Blizzard", "3RR", "Assets/spell/Spell_frost_icestorm.png", 3,
                                rank_descriptions);

    return talent;
}
