#include "Fire.h"

#include "Mage.h"
#include "MageSpells.h"
#include "Talent.h"

Fire::Fire(Mage* mage) :
    TalentTree("Fire", "Assets/mage/mage_fire.jpg"),
    mage(mage),
    spells(dynamic_cast<MageSpells*>(mage->get_spells()))
{
    QMap<QString, Talent*> tier1 {{"1ML", new Talent(mage, this, "Improved Fireball", "1ML", "Assets/spell/Spell_fire_flamebolt.png", 5, "Reduces the casting time of your Fireball spell by %1 sec.", QVector<QPair<double, double>>{{0.1, 0.1}})},
                                  {"1MR", new Talent(mage, this, "Impact", "1MR", "Assets/spell/Spell_fire_meteorstorm.png", 5, "Gives your Fire spells a %1% chance to stun the target for 2 sec.", QVector<QPair<unsigned, unsigned>>{{2, 2}})}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2LL", new Talent(mage, this, "Ignite", "2LL", "Assets/spell/Spell_fire_incinerate.png", 5, "Your critical strikes from Fire damage spells cause the target to burn for an additional %1% of your spell's damage over 4 sec.", QVector<QPair<unsigned, unsigned>>{{8, 8}})},
                                  {"2ML", new Talent(mage, this, "Flame Throwing", "2ML", "Assets/spell/Spell_fire_flare.png", 2, "Increases the range of your Fire spells by %1 yards.", QVector<QPair<unsigned, unsigned>>{{3, 3}})},
                                  {"2MR", new Talent(mage, this, "Improved Fire Blast", "2MR", "Assets/spell/Spell_fire_fireball.png", 3, "Reduces the cooldown of your Fire Blast spell by %1 sec.", QVector<QPair<double , double>>{{0.5, 0.5}})}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent(mage, this, "Incinerate", "3LL", "Assets/spell/Spell_fire_flameshock.png", 2, "Increases the critical strike chance of your Fire Blast and Scorch spells by %1%.", QVector<QPair<unsigned, unsigned>>{{2, 2}})},
                                  {"3ML", new Talent(mage, this, "Improved Flamestrike", "3ML", "Assets/spell/Spell_fire_selfdestruct.png", 3, "Increases the critical strike chance of your Flamestrike spell by %1%.", QVector<QPair<unsigned, unsigned>>{{5, 5}})},
                                  {"3MR", new Talent(mage, this, "Pyroblast", "3MR", "Assets/spell/Spell_fire_fireball02.png", 1, "Hurls an immense fiery boulder that causes 141 to 187 Fire damage and an additional 56 Fire damage over 12 sec.", QVector<QPair<unsigned, unsigned>>{})},
                                  {"3RR", new Talent(mage, this, "Burning Soul", "3RR", "Assets/spell/Spell_fire_fire.png", 2, "Gives your Fire spells a %1% chance to not lose casting time when you take damage and reduces the threat caused by your Fire spells by %2%.", QVector<QPair<unsigned, unsigned>>{{35, 35}, {15, 15}})}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4LL", improved_scorch()},
                                  {"4ML", new Talent(mage, this, "Improved Fire Ward", "4ML", "Assets/items/Inv_shield_05.png", 2, "Causes your Fire Ward to have a %1% chance to reflect Fire spells while active.", QVector<QPair<unsigned, unsigned>>{{10, 10}})},
                                  {"4RR", new Talent(mage, this, "Master of Elements", "4RR", "Assets/spell/Spell_fire_masterofelements.png", 3, "Your Fire and Frost spell criticals will refund %1% of their base mana cost.", QVector<QPair<unsigned, unsigned>>{{10, 10}})}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5ML", new Talent(mage, this, "Critical Mass", "5ML", "Assets/spell/Spell_nature_wispheal.png", 3, "Increases the critical strike chance of your Fire spells by %1%.", QVector<QPair<unsigned, unsigned>>{{2, 2}})},
                                  {"5MR", new Talent(mage, this, "Blast Wave", "5MR", "Assets/spell/Spell_holy_excorcism_02.png", 1, "A wave of flame radiates outward from the caster, damaging all enemies caught within the blast for 154 to 186 Fire damage, and dazing them for 6 sec.", QVector<QPair<unsigned, unsigned>>{})}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6MR", new Talent(mage, this, "Fire Power", "6MR", "Assets/spell/Spell_fire_immolation.png", 5, "Increases the damage done by your Fire spells by %1%.", QVector<QPair<unsigned, unsigned>>{{2, 2}})}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Talent(mage, this, "Combustion", "7ML", "Assets/spell/Spell_fire_sealoffire.png", 1, "When activated, this spell causes each of your Fire damage spell hits to increase your critical strike chance with Fire damage spells by 10%. This effect lasts until you have caused 3 critical strikes with Fire spells.", QVector<QPair<unsigned, unsigned>>())}};
    add_talents(tier7);

    talents["3MR"]->talent->set_bottom_child(talents["5MR"]->talent);
    talents["5MR"]->talent->set_parent(talents["3MR"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["5ML"]->talent);
}

Talent* Fire::improved_scorch() {
    QString base_str = "Your Scorch spells have a %1% chance to cause your target to be vulnerable to Fire damage. This vulnerability increases the Fire damage dealt to your target by 3% and lasts 30 sec. Stacks up to 5 times.";
    QMap<unsigned, QString> rank_descriptions {{0, base_str.arg(33)}, {1, base_str.arg(33)},
                                               {2, base_str.arg(66)},
                                               {3, base_str.arg(100)}};
    Talent* talent = new Talent(mage, this, "Improved Scorch", "4LL", "Assets/spell/Spell_fire_soulburn.png", 3,
                                rank_descriptions);

    return talent;
}
