
#include "ActiveBuffs.h"
#include "Buff.h"
#include "Character.h"
#include "ClassStatistics.h"
#include "Faction.h"
#include "GeneralBuffs.h"
#include "ExternalBuff.h"

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
    for (auto & active_buff : active_buffs) {
        active_buff->reset();
    }
}

void ActiveBuffs::switch_faction() {
    if (faction->is_alliance()) {
        for (auto & horde_only_buff : horde_only_buffs) {
            remove_buff(horde_only_buff);
        }

        for (auto & alliance_only_buff : alliance_only_buffs) {
            add_buff(alliance_only_buff);
        }
    }
    else {
        for (auto & alliance_only_buff : alliance_only_buffs) {
            remove_buff(alliance_only_buff);
        }

        for (auto & horde_only_buff : horde_only_buffs) {
            add_buff(horde_only_buff);
        }
    }
}

GeneralBuffs* ActiveBuffs::get_general_buffs() {
    return this->general_buffs;
}

QVector<QString> ActiveBuffs::get_active_external_buffs() {
    QVector<ExternalBuff*> buffs = general_buffs->get_external_buffs();
    QVector<QString> active_external_buffs;

    for (auto & buff : buffs) {
        if (buff->is_active())
            active_external_buffs.append(buff->get_name());
    }

    return active_external_buffs;
}
