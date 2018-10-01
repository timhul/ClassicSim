
#include "ExternalBuff.h"

#include <utility>

ExternalBuff::ExternalBuff(Character* pchar, const QString& name,
                           const int dur, const int base_charges,
                           QString icon, QString description,
                           QVersionNumber min_patch):
    Buff(pchar, name, dur, base_charges),
    icon(std::move(icon)),
    description(std::move(description)),
    min_patch(std::move(min_patch))
{}

ExternalBuff::~ExternalBuff() = default;

QString ExternalBuff::get_icon() const {
    return this->icon;
}

QString ExternalBuff::get_description() const {
    return this->description;
}

bool ExternalBuff::valid_for_patch(const QString& patch) const {
    QVersionNumber new_version = QVersionNumber::fromString(patch);

    return min_patch <= new_version;
}
