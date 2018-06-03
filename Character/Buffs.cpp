
#include "Buffs.h"
#include "Buff.h"
#include "Character.h"
#include "ClassStatistics.h"
#include "Faction.h"

Buffs::Buffs(Character* pchar, Faction* faction, QObject* parent) :
    QObject(parent),
    pchar(pchar),
    faction(faction)
{}

Buffs::~Buffs()
{
    for (int i = 0; i < buffs.size(); ++i) {
        delete buffs[i];
    }

    buffs.clear();
}

void Buffs::add_buff(Buff* buff) {
    buffs.append(buff);
}

void Buffs::remove_one_buff(Buff* buff) {
    for (int i = 0; i < buffs.size(); ++i) {
        if (buff->get_name() == buffs[i]->get_name()) {
            buff->reset();
            buffs.removeAt(i);
            break;
        }
    }
}

void Buffs::reset() {
    for (int i = 0; i < buffs.size(); ++i) {
        buffs[i]->reset();
    }
}

void Buffs::switch_faction() {
    if (faction->is_alliance()) {
        for (int i = 0; i < horde_only_buffs.size(); ++i) {
            remove_one_buff(horde_only_buffs[i]);
        }

        for (int i = 0; i < alliance_only_buffs.size(); ++i) {
            add_buff(alliance_only_buffs[i]);
        }
    }
    else {
        for (int i = 0; i < alliance_only_buffs.size(); ++i) {
            remove_one_buff(alliance_only_buffs[i]);
        }

        for (int i = 0; i < horde_only_buffs.size(); ++i) {
            add_buff(horde_only_buffs[i]);
        }
    }
}

void Buffs::add_statistics() {
    for (int i = 0; i < buffs.size(); ++i) {
        if (buffs[i]->is_hidden())
            continue;
        pchar->get_statistics()->add_buff_statistics(buffs[i]->get_statistics_for_buff());
    }
}
