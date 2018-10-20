
#include "ActiveBuffs.h"
#include "Character.h"
#include "ClassStatistics.h"
#include "Faction.h"
#include "GeneralBuffs.h"
#include "ExternalBuff.h"
#include "SharedBuff.h"

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
            active_buffs.removeAt(i);
            break;
        }
    }
}

SharedBuff *ActiveBuffs::use_shared_buff(const QString& name) const {
    for (auto & buff : active_buffs) {
        if (buff->get_name() == name) {
            SharedBuff* uniq_buff = dynamic_cast<SharedBuff*>(buff);
            uniq_buff->increment_reference();
            return dynamic_cast<SharedBuff*>(buff);
        }
    }

    return nullptr;
}

void ActiveBuffs::return_shared_buff(Buff* shared_buff) {
    for (auto & buff : active_buffs) {
        if (buff->get_name() != shared_buff->get_name())
            continue;

        SharedBuff* uniq_buff = dynamic_cast<SharedBuff*>(buff);
        uniq_buff->decrement_reference();

        if (uniq_buff->unused()) {
            remove_buff(uniq_buff);
            delete uniq_buff;
        }

        return;
    }

    assert(false);
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

void ActiveBuffs::prepare_set_of_combat_iterations() {
    for (auto & buff : active_buffs)
        buff->prepare_set_of_combat_iterations();
}
