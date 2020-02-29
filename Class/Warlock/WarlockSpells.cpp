#include "WarlockSpells.h"

#include "ImprovedShadowBolt.h"
#include "MainhandAttack.h"
#include "RaidControl.h"
#include "ShadowBolt.h"
#include "Warlock.h"

WarlockSpells::WarlockSpells(Warlock* warlock) : CharacterSpells(warlock), warlock(warlock) {
    this->mh_attack = new MainhandAttack(warlock);

    add_spell_group({mh_attack});

    auto improved_shadow_bolt = static_cast<ImprovedShadowBolt*>(warlock->get_raid_control()->get_shared_raid_buff("Improved Shadow Bolt"));
    if (improved_shadow_bolt == nullptr) {
        improved_shadow_bolt = new ImprovedShadowBolt(warlock);
        improved_shadow_bolt->enable_buff();
    }

    add_spell_group({
        new ShadowBolt(warlock, this, 1, improved_shadow_bolt),
        new ShadowBolt(warlock, this, 2, improved_shadow_bolt),
        new ShadowBolt(warlock, this, 3, improved_shadow_bolt),
        new ShadowBolt(warlock, this, 4, improved_shadow_bolt),
        new ShadowBolt(warlock, this, 5, improved_shadow_bolt),
        new ShadowBolt(warlock, this, 6, improved_shadow_bolt),
        new ShadowBolt(warlock, this, 7, improved_shadow_bolt),
        new ShadowBolt(warlock, this, 8, improved_shadow_bolt),
        new ShadowBolt(warlock, this, 9, improved_shadow_bolt),
        new ShadowBolt(warlock, this, 10, improved_shadow_bolt),
    });
}
