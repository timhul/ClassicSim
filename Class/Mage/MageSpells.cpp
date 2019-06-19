#include "MageSpells.h"

#include "Mage.h"
#include "MainhandAttack.h"
#include "Fireball.h"

MageSpells::MageSpells(Mage* mage) :
    CharacterSpells(mage),
    mage(mage)
{
    this->mh_attack = new MainhandAttack(mage);

    add_spell_group({mh_attack});

    add_spell_group({
                        new Fireball(mage, 1),
                        new Fireball(mage, 2),
                        new Fireball(mage, 3),
                        new Fireball(mage, 4),
                        new Fireball(mage, 5),
                        new Fireball(mage, 6),
                        new Fireball(mage, 7),
                        new Fireball(mage, 8),
                        new Fireball(mage, 9),
                        new Fireball(mage, 10),
                        new Fireball(mage, 11),
                        new Fireball(mage, 12),
                    });
}
