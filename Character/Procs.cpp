
#include "Procs.h"
#include "Character.h"
#include "WindfuryTotemAttack.h"
#include "Crusader.h"

Procs::Procs(Character* pchar, QObject* parent) :
    QObject(parent),
    pchar(pchar)
{
    this->melee_attack_procs = {new WindfuryTotemAttack(pchar->get_engine(), pchar, pchar->get_combat_roll())};
    this->mainhand_attack_procs = {new Crusader(pchar->get_engine(), pchar, pchar->get_combat_roll(), EnchantSlot::MAINHAND)};
    this->offhand_attack_procs = {new Crusader(pchar->get_engine(), pchar, pchar->get_combat_roll(), EnchantSlot::OFFHAND)};
}

Procs::~Procs()
{
    for (int i = 0; i < melee_attack_procs.size(); ++i) {
        delete melee_attack_procs[i];
    }

    for (int i = 0; i < mainhand_attack_procs.size(); ++i) {
        delete mainhand_attack_procs[i];
    }

    for (int i = 0; i < offhand_attack_procs.size(); ++i) {
        delete offhand_attack_procs[i];
    }

    melee_attack_procs.clear();
    mainhand_attack_procs.clear();
    offhand_attack_procs.clear();
}

void Procs::run_general_proc_effects() {
    for (int i = 0; i < melee_attack_procs.size(); ++i) {
        melee_attack_procs[i]->perform(0);
    }
}

void Procs::run_mh_specific_proc_effects() {
    run_general_proc_effects();

    for (int i = 0; i < mainhand_attack_procs.size(); ++i) {
        mainhand_attack_procs[i]->perform(0);
    }
}

void Procs::run_oh_specific_proc_effects() {
    run_general_proc_effects();

    for (int i = 0; i < offhand_attack_procs.size(); ++i) {
        offhand_attack_procs[i]->perform(0);
    }
}

void Procs::add_general_proc_effect(Proc* proc) {
    melee_attack_procs.append(proc);
}

void Procs::add_mh_specific_proc_effect(Proc* proc) {
    mainhand_attack_procs.append(proc);
}

void Procs::add_oh_specific_proc_effect(Proc* proc) {
    offhand_attack_procs.append(proc);
}

void Procs::remove_general_proc_effect(const Proc *proc) {
    remove_one_proc_effect(melee_attack_procs, proc);
}

void Procs::remove_mh_specific_proc_effect(const Proc* proc) {
    remove_one_proc_effect(mainhand_attack_procs, proc);
}

void Procs::remove_oh_specific_proc_effect(const Proc* proc) {
    remove_one_proc_effect(offhand_attack_procs, proc);
}

void Procs::remove_one_proc_effect(QVector<Proc*>& vec, const Proc* proc) {
    for (int i = 0; i < vec.size(); ++i) {
        if (vec.at(i)->get_name() == proc->get_name()) {
            vec.removeAt(i);
            break;
        }
    }
}

void Procs::reset() {
    for (int i = 0; i < melee_attack_procs.size(); ++i) {
        melee_attack_procs[i]->reset();
    }

    for (int i = 0; i < mainhand_attack_procs.size(); ++i) {
        mainhand_attack_procs[i]->reset();
    }

    for (int i = 0; i < offhand_attack_procs.size(); ++i) {
        offhand_attack_procs[i]->reset();
    }
}
