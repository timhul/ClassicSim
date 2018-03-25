
#include "Talent.h"
#include <QDebug>

Talent::Talent(const QString &name_, const QString &icon_, const int max_points_) :
    name(name_),
    icon(icon_),
    max_points(max_points_),
    curr_points(0)
{
    assert(max_points > 0 && max_points <= 5);
}

Talent::~Talent() {
}

QString Talent::get_name() const {
    return name;
}

QString Talent::get_icon() const {
    return icon;
}

int Talent::get_current_rank() const {
    return curr_points;
}

int Talent::get_max_rank() const {
    return max_points;
}

bool Talent::increment_rank() {
    if (curr_points == max_points)
        return false;

    if (parent != nullptr && !parent->is_maxed()) {
        return false;
    }

    curr_points++;
    return true;
}

bool Talent::decrement_rank() {
    if (children_active())
        return false;

    if (curr_points == 0)
        return false;

    curr_points--;
    return true;
}

void Talent::set_rank(const int new_rank) {
    if (new_rank > curr_points) {
        assert(new_rank < max_points);
        while (curr_points < new_rank)
            increment_rank();
    }
    else if (new_rank < curr_points) {
        assert(curr_points >= 0);
        if (children_active())
            return;

        while (curr_points > new_rank)
            decrement_rank();
    }
}

bool Talent::is_active() const {
    return curr_points > 0;
}

bool Talent::is_maxed() const {
    return curr_points == max_points;
}

bool Talent::children_active() const {
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->is_active())
            return true;
    }

    return false;
}
