#include "MageSpells.h"

#include "Combustion.h"
#include "Fireball.h"
#include "Ignite.h"
#include "IgniteBuff.h"
#include "Mage.h"
#include "MainhandAttack.h"
#include "RaidControl.h"

MageSpells::MageSpells(Mage* mage) :
    CharacterSpells(mage),
    mage(mage)
{
    this->mh_attack = new MainhandAttack(mage);

    add_spell_group({mh_attack});

    add_spell_group({
                        new Fireball(mage, this, 1),
                        new Fireball(mage, this, 2),
                        new Fireball(mage, this, 3),
                        new Fireball(mage, this, 4),
                        new Fireball(mage, this, 5),
                        new Fireball(mage, this, 6),
                        new Fireball(mage, this, 7),
                        new Fireball(mage, this, 8),
                        new Fireball(mage, this, 9),
                        new Fireball(mage, this, 10),
                        new Fireball(mage, this, 11),
                        new Fireball(mage, this, 12),
                    });

    auto* ignite_buff = dynamic_cast<IgniteBuff*>(mage->get_raid_control()->get_shared_raid_buff("Ignite"));
    if (ignite_buff == nullptr) {
        ignite_buff = new IgniteBuff(mage);
        ignite_buff->enable_buff();
    }
    ignite = new Ignite(mage, ignite_buff);
    add_spell_group({ignite});

    combustion = new Combustion(mage);
    add_spell_group({combustion});
}

void MageSpells::inflict_ignite(const double damage) {
    ignite->inflict_ignite(damage);
}

Combustion* MageSpells::get_combustion() const {
    return this->combustion;
}
