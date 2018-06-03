
#include "Buffs.h"
#include "Buff.h"
#include "Character.h"
#include "ClassStatistics.h"
#include "Faction.h"

Buffs::Buffs(Character* pchar, Faction* faction, QObject* parent) :
    QObject(parent),
    pchar(pchar),
    faction(faction),
    next_instance_id(BuffStatus::INITIAL_ID)
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

    if (buff->get_instance_id() == BuffStatus::INACTIVE) {
        buff->set_instance_id(next_instance_id);
        ++next_instance_id;
    }
}

void Buffs::remove_buff(Buff* buff) {
    for (int i = 0; i < buffs.size(); ++i) {
        if (buffs.at(i)->get_instance_id() == buff->get_instance_id()) {
            buffs.at(i)->reset();
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
            remove_buff(horde_only_buffs[i]);
        }

        for (int i = 0; i < alliance_only_buffs.size(); ++i) {
            add_buff(alliance_only_buffs[i]);
        }
    }
    else {
        for (int i = 0; i < alliance_only_buffs.size(); ++i) {
            remove_buff(alliance_only_buffs[i]);
        }

        for (int i = 0; i < horde_only_buffs.size(); ++i) {
            add_buff(horde_only_buffs[i]);
        }
    }
}
