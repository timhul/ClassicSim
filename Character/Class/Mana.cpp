#include <cassert>

#include "Character.h"
#include "CharacterStats.h"
#include "Engine.h"
#include "Mana.h"
#include "ManaTick.h"
#include "ResourceGain.h"

Mana::Mana(Character* pchar) :
    pchar(pchar),
    mana_per_tick(0)
{
    this->max = get_max_mana();
    this->current = max;
    this->mana_tick = new ManaTick(pchar, this);
}

Mana::~Mana() {
    delete mana_tick;
}

unsigned Mana::get_max_mana() const {
    return pchar->get_stats()->get_intellect() * 15;
}

void Mana::gain_resource(const unsigned Mana) {
    current += Mana;

    if (current > max)
        current = max;
}

void Mana::add_next_tick() {
    auto* event = new ResourceGain(pchar, mana_tick, pchar->get_engine()->get_current_priority() + 5.0);
    pchar->get_engine()->add_event(event);
}

void Mana::tick_mana() {
    if (current == max)
        return;

    gain_resource(mana_per_tick);
    pchar->add_player_reaction_event();

    add_next_tick();
}

void Mana::lose_resource(const unsigned mana) {
    if (current == max)
        add_next_tick();

    assert(current >= mana);
    current -= mana;
}

void Mana::reset_resource() {
    max = get_max_mana();
    current = max;
    mana_per_tick = 0;
}
