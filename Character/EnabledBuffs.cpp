#include "Character.h"
#include "ClassStatistics.h"
#include "EnabledBuffs.h"
#include "Faction.h"
#include "GeneralBuffs.h"
#include "ExternalBuff.h"
#include "SharedBuff.h"

EnabledBuffs::EnabledBuffs(Character* pchar, Faction* faction) :
    pchar(pchar),
    faction(faction),
    next_instance_id(BuffStatus::INITIAL_ID),
    general_buffs(new GeneralBuffs(pchar, faction))
{}

EnabledBuffs::~EnabledBuffs()
{
    delete general_buffs;
}

void EnabledBuffs::add_buff(Buff* buff) {
    assert(buff->is_enabled());
    enabled_buffs.append(buff);

    if (buff->get_instance_id() == BuffStatus::INACTIVE) {
        buff->set_instance_id(next_instance_id);
        ++next_instance_id;
    }
}

void EnabledBuffs::remove_buff(Buff* buff) {
    assert(buff->is_enabled());
    for (int i = 0; i < enabled_buffs.size(); ++i) {
        if (enabled_buffs.at(i)->get_instance_id() == buff->get_instance_id())
            return enabled_buffs.removeAt(i);
    }
}

Buff* EnabledBuffs::get_buff_by_name(const QString& name) const {
    for (auto & buff : enabled_buffs) {
        if (buff->get_name() == name)
            return buff;
    }

    return nullptr;
}

SharedBuff *EnabledBuffs::use_shared_buff(const QString& name) const {
    for (auto & buff : enabled_buffs) {
        if (buff->get_name() == name) {
            auto* uniq_buff = dynamic_cast<SharedBuff*>(buff);
            uniq_buff->increment_reference();
            return dynamic_cast<SharedBuff*>(buff);
        }
    }

    return nullptr;
}

void EnabledBuffs::return_shared_buff(Buff* shared_buff) {
    for (auto & buff : enabled_buffs) {
        if (buff->get_name() != shared_buff->get_name())
            continue;

        auto* uniq_buff = dynamic_cast<SharedBuff*>(buff);
        uniq_buff->decrement_reference();

        if (uniq_buff->unused()) {
            remove_buff(uniq_buff);
            delete uniq_buff;
        }

        return;
    }

    assert(false);
}

void EnabledBuffs::reset() {
    for (auto & buff : enabled_buffs)
        buff->reset();
}

void EnabledBuffs::clear_all() {
    while (!enabled_buffs.empty()) {
        Buff* buff = enabled_buffs.takeFirst();
        buff->cancel_buff();
        buff->disable_buff();
    }

    general_buffs->clear_all();
}

void EnabledBuffs::switch_faction() {
    general_buffs->switch_faction();

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

GeneralBuffs* EnabledBuffs::get_general_buffs() {
    return this->general_buffs;
}

QVector<QString> EnabledBuffs::get_active_external_buffs() {
    QVector<ExternalBuff*> buffs = general_buffs->get_external_buffs();
    QVector<QString> active_external_buffs;

    for (auto & buff : buffs) {
        if (buff->is_active())
            active_external_buffs.append(buff->get_name());
    }

    return active_external_buffs;
}

void EnabledBuffs::prepare_set_of_combat_iterations() {
    for (auto & buff : enabled_buffs)
        buff->prepare_set_of_combat_iterations();
}
