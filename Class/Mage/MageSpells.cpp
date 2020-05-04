#include "MageSpells.h"

#include "ArcaneMissiles.h"
#include "ArcanePower.h"
#include "Berserking.h"
#include "ClearcastingMage.h"
#include "Combustion.h"
#include "ElementalVulnerability.h"
#include "Evocation.h"
#include "FireVulnerability.h"
#include "Fireball.h"
#include "Frostbolt.h"
#include "GenericBuffProc.h"
#include "GenericStatBuff.h"
#include "Ignite.h"
#include "IgniteBuff.h"
#include "ImprovedScorch.h"
#include "ItemStatsEnum.h"
#include "Mage.h"
#include "MageArmor.h"
#include "MainhandAttack.h"
#include "RaidControl.h"
#include "RobeOfTheArchmage.h"
#include "Scorch.h"
#include "SuppressCastBuff.h"
#include "WintersChill.h"
#include "WintersChillProc.h"

MageSpells::MageSpells(Mage* mage) : CharacterSpells(mage), mage(mage) {
    this->berserking = new Berserking(pchar, ResourceType::Mana, 100);
    add_spell_group({berserking});

    this->mh_attack = new MainhandAttack(mage);
    add_spell_group({mh_attack});

    auto winters_chill_buff = static_cast<WintersChill*>(mage->get_raid_control()->get_shared_raid_buff("Winter's Chill"));
    if (winters_chill_buff == nullptr) {
        winters_chill_buff = new WintersChill(mage);
        winters_chill_buff->enable_buff();
    }
    winters_chill_proc = new WintersChillProc(mage, winters_chill_buff);

    add_spell_group({
        new Frostbolt(mage, this, winters_chill_proc, 1),
        new Frostbolt(mage, this, winters_chill_proc, 2),
        new Frostbolt(mage, this, winters_chill_proc, 3),
        new Frostbolt(mage, this, winters_chill_proc, 4),
        new Frostbolt(mage, this, winters_chill_proc, 5),
        new Frostbolt(mage, this, winters_chill_proc, 6),
        new Frostbolt(mage, this, winters_chill_proc, 7),
        new Frostbolt(mage, this, winters_chill_proc, 8),
        new Frostbolt(mage, this, winters_chill_proc, 9),
        new Frostbolt(mage, this, winters_chill_proc, 10),
        new Frostbolt(mage, this, winters_chill_proc, 11),
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

    auto fire_vulnerability_buff = static_cast<FireVulnerability*>(mage->get_raid_control()->get_shared_raid_buff("Fire Vulnerability"));
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

    auto ignite_buff = static_cast<IgniteBuff*>(mage->get_raid_control()->get_shared_raid_buff("Ignite"));
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
    add_spell_group({new MageArmor(mage)});

    this->clearcasting = new ClearcastingMage(mage);
    this->elemental_vulnerability = new ElementalVulnerability(mage);
    this->t3_6piece_proc = new GenericBuffProc(mage, "Elemental Vulnerability 6p T3", "Assets/spell/Spell_holy_dizzy.png",
                                               {ProcInfo::Source::MagicSpell}, 0.2, EnabledAtStart::No, MaintainBuffEnabled::No,
                                               elemental_vulnerability);

    add_spell_group({new RobeOfTheArchmage(mage)});

    this->t2_8piece_buff = new SuppressCastBuff(mage, "Netherwind Focus", "Assets/spell/Spell_shadow_teleport.png", BuffDuration::PERMANENT, 1);
    this->t2_8piece_proc = new GenericBuffProc(mage, "Netherwind Focus", "Assets/spell/Spell_shadow_teleport.png", {ProcInfo::Source::Manual}, 0.1,
                                               EnabledAtStart::No, MaintainBuffEnabled::Yes, t2_8piece_buff);
    this->enigma_5p_buff = new GenericStatBuff(mage, "Enigma's Answer", "Assets/spell/Spell_nature_astralrecalgroup.png", 20,
                                               {{ItemStats::SpellHit, 500}});
}

MageSpells::~MageSpells() {
    delete clearcasting;
    delete imp_scorch;
    delete winters_chill_proc;
    delete t3_6piece_proc;
    delete elemental_vulnerability;
    delete t2_8piece_proc;
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

Proc* MageSpells::get_winters_chill_proc() const {
    return this->winters_chill_proc;
}

Proc* MageSpells::get_t3_6piece_proc() const {
    return this->t3_6piece_proc;
}

Buff* MageSpells::get_t3_6piece_buff() const {
    return this->elemental_vulnerability;
}

Proc* MageSpells::get_t2_8piece_proc() const {
    return this->t2_8piece_proc;
}

Buff* MageSpells::get_t2_8piece_buff() const {
    return this->t2_8piece_buff;
}

Buff* MageSpells::get_enigma_5p_buff() const {
    return this->enigma_5p_buff;
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

void MageSpells::roll_netherwind_focus() {
    if (!t2_8piece_proc->is_enabled())
        return;

    if (t2_8piece_proc->check_proc_success())
        t2_8piece_proc->perform();
}
