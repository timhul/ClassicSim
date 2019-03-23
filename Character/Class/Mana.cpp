#include "Mana.h"

#include "Character.h"
#include "CharacterStats.h"
#include "Engine.h"
#include "ManaTick.h"
#include "ResourceGain.h"
#include "Utils/Check.h"
#include "Utils/CompareDouble.h"

Mana::Mana(Character* pchar) :
    pchar(pchar),
    base_mana(0),
    last_use_of_mana(0)
{
    this->max = get_max_mana();
    this->current = max;
    this->mana_tick = new ManaTick(pchar, this);
}

Mana::~Mana() {
    delete mana_tick;
}

void Mana::set_base_mana(const unsigned base_mana) {
    this->base_mana = base_mana;
    reset_resource();
}

unsigned Mana::get_max_mana() const {
    return base_mana + pchar->get_stats()->get_intellect() * 15;
}

void Mana::gain_resource(const unsigned mana) {
    current += mana;

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

    gain_resource(pchar->get_stats()->get_mp5());

    if (lhs_almost_equal_or_less(5.0, pchar->get_engine()->get_current_priority() - last_use_of_mana))
        gain_resource(pchar->get_mp5_from_spirit());

    pchar->add_player_reaction_event();

    add_next_tick();
}

void Mana::lose_resource(const unsigned mana) {
    if (current == max)
        add_next_tick();

    check((current >= mana), "Underflow decrease");
    current -= mana;
    last_use_of_mana = pchar->get_engine()->get_current_priority();
}

void Mana::reset_resource() {
    max = get_max_mana();
    current = max;
    last_use_of_mana = 0;
}
