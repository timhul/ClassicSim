#include "ShamanSpells.h"

#include "Berserking.h"
#include "ClearcastingShaman.h"
#include "ElementalDevastation.h"
#include "Flurry.h"
#include "LightningBolt.h"
#include "MainhandAttack.h"
#include "RaidControl.h"
#include "Shaman.h"
#include "Stormstrike.h"
#include "StormstrikeBuff.h"
#include "WindfuryWeapon.h"

ShamanSpells::ShamanSpells(Shaman* shaman) :
    CharacterSpells(shaman),
    shaman(shaman)
{
    this->berserking = new Berserking(pchar, ResourceType::Mana, 120);
    add_spell_group({berserking});

    this->mh_attack = new MainhandAttack(shaman);

    add_spell_group({mh_attack});

    add_spell_group({
                        new LightningBolt(shaman, this, 1),
                        new LightningBolt(shaman, this, 2),
                        new LightningBolt(shaman, this, 3),
                        new LightningBolt(shaman, this, 4),
                        new LightningBolt(shaman, this, 5),
                        new LightningBolt(shaman, this, 6),
                        new LightningBolt(shaman, this, 7),
                        new LightningBolt(shaman, this, 8),
                        new LightningBolt(shaman, this, 9),
                        new LightningBolt(shaman, this, 10),
                    });

    add_spell_group({
                        new WindfuryWeapon(shaman, 1),
                        new WindfuryWeapon(shaman, 2),
                        new WindfuryWeapon(shaman, 3),
                        new WindfuryWeapon(shaman, 4),
                    });

    this->flurry = new Flurry(shaman);
    this->clearcasting = new ClearcastingShaman(shaman);
    this->elemental_devastation = new ElementalDevastation(shaman);

    auto stormstrike_buff = static_cast<StormstrikeBuff*>(pchar->get_raid_control()->get_shared_raid_buff("Stormstrike"));
    if (stormstrike_buff == nullptr) {
        stormstrike_buff = new StormstrikeBuff(shaman);
        stormstrike_buff->enable_buff();
    }
    add_spell_group({new Stormstrike(shaman, this, stormstrike_buff)});
}

ShamanSpells::~ShamanSpells() {
    delete flurry;
    delete clearcasting;
}

Buff* ShamanSpells::get_elemental_devastation() const {
    return this->elemental_devastation;
}

Buff* ShamanSpells::get_flurry() const {
    return this->flurry;
}

Proc* ShamanSpells::get_clearcasting() const {
    return this->clearcasting;
}

bool ShamanSpells::clearcasting_active() const {
    return clearcasting->buff->is_active();
}

void ShamanSpells::roll_clearcasting() {
    if (!clearcasting->is_enabled())
        return;

    clearcasting->buff->use_charge();
    if (clearcasting->check_proc_success())
        clearcasting->perform();
}
