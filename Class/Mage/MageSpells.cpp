#include "MageSpells.h"

#include "ArcaneMissiles.h"
#include "ArcanePower.h"
#include "ClearcastingMage.h"
#include "Combustion.h"
#include "ElementalVulnerability.h"
#include "Evocation.h"
#include "FireVulnerability.h"
#include "Fireball.h"
#include "Frostbolt.h"
#include "GenericBuffProc.h"
#include "Ignite.h"
#include "IgniteBuff.h"
#include "ImprovedScorch.h"
#include "Mage.h"
#include "MainhandAttack.h"
#include "RaidControl.h"
#include "Scorch.h"

MageSpells::MageSpells(Mage* mage) :
    CharacterSpells(mage),
    mage(mage)
{
    this->mh_attack = new MainhandAttack(mage);

    add_spell_group({mh_attack});

    add_spell_group({
                        new Frostbolt(mage, this, 1),
                        new Frostbolt(mage, this, 2),
                        new Frostbolt(mage, this, 3),
                        new Frostbolt(mage, this, 4),
                        new Frostbolt(mage, this, 5),
                        new Frostbolt(mage, this, 6),
                        new Frostbolt(mage, this, 7),
                        new Frostbolt(mage, this, 8),
                        new Frostbolt(mage, this, 9),
                        new Frostbolt(mage, this, 10),
                        new Frostbolt(mage, this, 11),
                    });

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

    add_spell_group({
                        new ArcaneMissiles(mage, this, 1),
                        new ArcaneMissiles(mage, this, 2),
                        new ArcaneMissiles(mage, this, 3),
                        new ArcaneMissiles(mage, this, 4),
                        new ArcaneMissiles(mage, this, 5),
                        new ArcaneMissiles(mage, this, 6),
                        new ArcaneMissiles(mage, this, 7),
                        new ArcaneMissiles(mage, this, 8),
                    });

    auto fire_vulnerability_buff = dynamic_cast<FireVulnerability*>(mage->get_raid_control()->get_shared_raid_buff("Fire Vulnerability"));
    if (fire_vulnerability_buff == nullptr) {
        fire_vulnerability_buff = new FireVulnerability(mage);
        fire_vulnerability_buff->enable_buff();
    }
    this->imp_scorch = new ImprovedScorch(mage, fire_vulnerability_buff);
    add_spell_group({
                        new Scorch(mage, this, imp_scorch, 1),
                        new Scorch(mage, this, imp_scorch, 2),
                        new Scorch(mage, this, imp_scorch, 3),
                        new Scorch(mage, this, imp_scorch, 4),
                        new Scorch(mage, this, imp_scorch, 5),
                        new Scorch(mage, this, imp_scorch, 6),
                        new Scorch(mage, this, imp_scorch, 7),
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

    add_spell_group({new ArcanePower(mage)});
    add_spell_group({new Evocation(mage)});

    this->clearcasting = new ClearcastingMage(mage);
    this->elemental_vulnerability = new ElementalVulnerability(mage);
    this->t3_6piece_proc = new GenericBuffProc(mage, "Elemental Vulnerability 6p T3", "Assets/spell/Spell_holy_dizzy.png", {ProcInfo::Source::MagicSpell},
                                               0.2, EnabledAtStart::No, MaintainBuffEnabled::No, elemental_vulnerability);
}

MageSpells::~MageSpells() {
    delete clearcasting;
    delete imp_scorch;
    delete t3_6piece_proc;
    delete elemental_vulnerability;
}

Combustion* MageSpells::get_combustion() const {
    return this->combustion;
}

Proc* MageSpells::get_clearcasting() const {
    return this->clearcasting;
}

Proc* MageSpells::get_improved_scorch() const {
    return this->imp_scorch;
}

Proc* MageSpells::get_t3_6piece_proc() const {
    return this->t3_6piece_proc;
}

Buff* MageSpells::get_t3_6piece_buff() const {
    return this->elemental_vulnerability;
}

void MageSpells::inflict_ignite(const double damage) {
    ignite->inflict_ignite(damage);
}

bool MageSpells::clearcasting_active() const {
    return clearcasting->buff->is_active();
}

void MageSpells::roll_clearcasting() {
    if (!clearcasting->is_enabled())
        return;

    clearcasting->buff->use_charge();
    if (clearcasting->check_proc_success())
        clearcasting->perform();
}
