
#include "Procs.h"
#include "Character.h"
#include "Faction.h"
#include "WindfuryTotemAttack.h"
#include "Crusader.h"

Procs::Procs(Character* pchar, Faction* faction, QObject* parent) :
    QObject(parent),
    pchar(pchar),
    faction(faction)
{
    this->horde_only_procs = {new WindfuryTotemAttack(pchar->get_engine(), pchar, pchar->get_combat_roll())};
    // TODO: Find way to activate and deactivate baseline procs such as WF/Crusader, etc.
//    this->melee_attack_procs = {new WindfuryTotemAttack(pchar->get_engine(), pchar, pchar->get_combat_roll())};
//    this->mainhand_attack_procs = {new Crusader(pchar->get_engine(), pchar, pchar->get_combat_roll(), EnchantSlot::MAINHAND)};
//    this->offhand_attack_procs = {new Crusader(pchar->get_engine(), pchar, pchar->get_combat_roll(), EnchantSlot::OFFHAND)};
}

Procs::~Procs()
{
    for (int i = 0; i < procs.size(); ++i) {
        delete procs[i];
    }

    procs.clear();
}

void Procs::run_proc_effects(ProcInfo::Source source) {
    for (int i = 0; i < procs.size(); ++i) {
        if (procs[i]->procs_from_source(source))
            procs[i]->perform(0);
    }
}

void Procs::add_proc_effect(Proc* proc) {
    procs.append(proc);
}

void Procs::remove_proc_effect(const Proc *proc) {
    for (int i = 0; i < procs.size(); ++i) {
        if (procs.at(i)->get_name() == proc->get_name()) {
            procs.removeAt(i);
            break;
        }
    }
}

void Procs::reset() {
    for (int i = 0; i < procs.size(); ++i) {
        procs[i]->reset();
    }
}

void Procs::switch_faction() {
    if (faction->is_alliance()) {
        for (int i = 0; i < horde_only_procs.size(); ++i) {
            remove_proc_effect(horde_only_procs[i]);
        }
    }
    else {
        for (int i = 0; i < horde_only_procs.size(); ++i) {
            add_proc_effect(horde_only_procs[i]);
        }
    }
}

void Procs::add_statistics() {
    for (int i = 0; i < procs.size(); ++i)
        procs[i]->add_proc_statistic();
}

void Procs::remove_statistics() {
    for (int i = 0; i < procs.size(); ++i)
        procs[i]->remove_proc_statistic();
}
