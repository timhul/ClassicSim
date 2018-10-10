
#include "TalentRequirer.h"
#include "Buff.h"
#include "Spell.h"
#include <cassert>

TalentRequirer::TalentRequirer(const int max_talent_rank, const bool disabled_at_zero):
    curr_talent_rank(0),
    max_talent_rank(max_talent_rank),
    disabled_at_zero(disabled_at_zero)
{
    assert(max_talent_rank > 0 && max_talent_rank <= 10); // TODO: should be 5, refactor when BS done
}

void TalentRequirer::increase_talent_rank(Buff* buff, const QString &talent_name) {
    ++curr_talent_rank;
    assert(curr_talent_rank <= max_talent_rank);

    increase_talent_rank_effect(talent_name);

    if (curr_talent_rank == 1 && disabled_at_zero)
        buff->enable_buff();
}

void TalentRequirer::decrease_talent_rank(Buff* buff, const QString &talent_name) {
    --curr_talent_rank;
    assert(curr_talent_rank >= 0);

    decrease_talent_rank_effect(talent_name);

    if (curr_talent_rank == 0 && disabled_at_zero)
        buff->disable_buff();
}

void TalentRequirer::increase_talent_rank(Spell* spell, const QString& talent_name) {
    ++curr_talent_rank;
    assert(curr_talent_rank <= max_talent_rank);

    increase_talent_rank_effect(talent_name);

    if (curr_talent_rank == 1 && disabled_at_zero)
        spell->enable();
}

void TalentRequirer::decrease_talent_rank(Spell* spell, const QString &talent_name) {
    --curr_talent_rank;
    assert(curr_talent_rank >= 0);

    decrease_talent_rank_effect(talent_name);

    if (curr_talent_rank == 0 && disabled_at_zero)
        spell->disable();
}
