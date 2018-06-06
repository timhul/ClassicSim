
#include "ExternalBuff.h"

ExternalBuff::ExternalBuff(Character* pchar, const QString name,
                           const int dur, const int base_charges,
                           const QString icon, const QString description,
                           const QVersionNumber min_patch):
    Buff(pchar, name, dur, base_charges),
    icon(icon),
    description(description),
    min_patch(min_patch)
{}

ExternalBuff::~ExternalBuff() {
}

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
