
#include "ActiveBuffs.h"
#include "Buff.h"
#include "Character.h"
#include "ClassStatistics.h"
#include "Faction.h"
#include "GeneralBuffs.h"

ActiveBuffs::ActiveBuffs(Character* pchar, Faction* faction, QObject* parent) :
    QObject(parent),
    pchar(pchar),
    faction(faction),
    next_instance_id(BuffStatus::INITIAL_ID),
    general_buffs(new GeneralBuffs(pchar, faction))
{}

ActiveBuffs::~ActiveBuffs()
{
    delete general_buffs;
}

void ActiveBuffs::add_buff(Buff* buff) {
    active_buffs.append(buff);

    if (buff->get_instance_id() == BuffStatus::INACTIVE) {
        buff->set_instance_id(next_instance_id);
        ++next_instance_id;
    }
}

void ActiveBuffs::remove_buff(Buff* buff) {
    for (int i = 0; i < active_buffs.size(); ++i) {
        if (active_buffs.at(i)->get_instance_id() == buff->get_instance_id()) {
            active_buffs.at(i)->reset();
            active_buffs.removeAt(i);
            break;
        }
    }
}

void ActiveBuffs::reset() {
    for (int i = 0; i < active_buffs.size(); ++i) {
        active_buffs[i]->reset();
    }
}

void ActiveBuffs::switch_faction() {
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
