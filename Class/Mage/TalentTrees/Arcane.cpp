#include "Arcane.h"

#include "Mage.h"
#include "MageSpells.h"
#include "Talent.h"

Arcane::Arcane(Mage* mage) :
    TalentTree("Arcane", "Assets/mage/mage_arcane.jpg"),
    mage(mage),
    spells(dynamic_cast<MageSpells*>(mage->get_spells()))
{
    QMap<QString, Talent*> tier1 {{"1LL", new Talent(mage, this, "Arcane Subtlety", "1LL", "Assets/spell/Spell_holy_dispelmagic.png", 2, "Reduces your target's resistance to all your spells by %1 and reduces the threat caused by your Arcane spells by %2%.", QVector<QPair<unsigned, unsigned>>{{5, 5}, {20, 20}})},
                                  {"1ML", new Talent(mage, this, "Arcane Focus", "1ML", "Assets/spell/Spell_holy_devotion.png", 5, "Reduces the chance that the opponent can resist your Arcane spells by %1%.", QVector<QPair<unsigned, unsigned>>{{2, 2}})},
                                  {"1MR", new Talent(mage, this, "Improved Arcane Missiles", "1MR", "Assets/spell/Spell_nature_starfall.png", 5, "Gives you a %1% chance to avoid interruption caused by damage while channeling Arcane Missiles.", QVector<QPair<unsigned, unsigned>>{{20, 20}})}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2LL", new Talent(mage, this, "Wand Specialization", "2LL", "Assets/items/Inv_wand_01.png", 2, "Increases your damage with Wands by %1%.", QVector<QPair<unsigned, unsigned>>{{13, 12}})},
                                  {"2ML", new Talent(mage, this, "Magic Absorption", "2ML", "Assets/spell/Spell_nature_astralrecalgroup.png", 5, "Increases all resistances by %1 and causes all spells you fully resist to restore %2% of your total mana. 1 sec. cooldown.", QVector<QPair<unsigned, unsigned>>{{2, 2}, {1, 1}})},
                                  {"2MR", new Talent(mage, this, "Arcane Concentration", "2MR", "Assets/spell/Spell_shadow_manaburn.png", 5, "Gives you a %1% chance of entering a Clearcasting state after any damage spell hits a target. The Clearcasting state reduces the mana cost of your next damage spell by 100%.", QVector<QPair<unsigned, unsigned>>{{2, 2}})}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent(mage, this, "Magic Attunement", "3LL", "Assets/items/Spell_nature_abolishmagic.png", 2, "Increases the effect of your Amplify Magic and Dampen Magic spells by %1%.", QVector<QPair<unsigned, unsigned>>{{25, 25}})},
                                  {"3ML", new Talent(mage, this, "Improved Arcane Explosion", "3ML", "Assets/spell/Spell_nature_wispsplode.png", 3, "Increases the critical strike chance of your Arcane Explosion spell by an additional %1%.", QVector<QPair<unsigned, unsigned>>{{2, 2}})},
                                  {"3MR", new Talent(mage, this, "Arcane Resilience", "3MR", "Assets/spell/Spell_arcane_arcaneresilience.png", 1, "Increases your armor by an amount equal to 50% of your Intellect.", QVector<QPair<unsigned, unsigned>>{})}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4LL", new Talent(mage, this, "Improved Mana Shield", "4LL", "Assets/spell/Spell_shadow_detectlesserinvisibility.png", 2, "Decreases the mana lost per point of damage taken when Mana Shield is active by %1%.", QVector<QPair<unsigned, unsigned>>{{10, 10}})},
                                  {"4ML", new Talent(mage, this, "Improved Counterspell", "4ML", "Assets/spell/Spell_frost_iceshock.png", 2, "Gives your Counterspell a %1% chance to silence the target for 4 sec.", QVector<QPair<unsigned, unsigned>>{{50, 50}})},
                                  {"4RR", new Talent(mage, this, "Arcane Meditation", "4RR", "Assets/spell/Spell_shadow_siphonmana.png", 3, "Allows %1% of your Mana regeneration to continue while casting.", QVector<QPair<unsigned, unsigned>>{{5, 5}})}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5ML", new Talent(mage, this, "Presence of Mind", "5ML", "Assets/spell/Spell_nature_enchantarmor.png", 1, "When activated, your next Mage spell with a casting time less than 10 sec becomes an instant cast spell.", QVector<QPair<unsigned, unsigned>>{})},
                                  {"5MR", new Talent(mage, this, "Arcane Mind", "5MR", "Assets/spell/Spell_shadow_charm.png", 5, "Increases your maximum Mana by %1%.", QVector<QPair<unsigned, unsigned>>{{2, 2}})}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6ML", new Talent(mage, this, "Arcane Instability", "6ML", "Assets/spell/Spell_shadow_teleport.png", 3, "Increases your spell damage and critical strike chance by %1%.", QVector<QPair<unsigned, unsigned>>{{1, 1}})}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Talent(mage, this, "Arcane Power", "7ML", "Assets/spell/Spell_nature_lightning.png", 1, "When activated, your spells deal 30% more damage while costing 30% more mana to cast. This effect lasts 15 sec.", QVector<QPair<unsigned, unsigned>>())}};
    add_talents(tier7);

    talents["3MR"]->talent->set_bottom_child(talents["5MR"]->talent);
    talents["5MR"]->talent->set_parent(talents["3MR"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["6ML"]->talent);
    talents["6ML"]->talent->set_parent(talents["5ML"]->talent);

    talents["6ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["6ML"]->talent);
}
