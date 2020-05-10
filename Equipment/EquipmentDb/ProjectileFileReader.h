#pragma once

#include "ItemFileReader.h"

class ProjectileFileReader : public ItemFileReader {
public:
    ProjectileFileReader(EnchantInfo* enchant_info) : ItemFileReader(enchant_info) {}

    void file_handler(QXmlStreamReader& reader, QVector<Item*>& items);

private:
    void dps_element_reader(const QXmlStreamAttributes& attrs, QMap<QString, QString>& item);
    void create_projectile(QVector<Item*>& items, QMap<QString, QString>& item_map, QSet<int>& mutex_item_ids);
    int get_projectile_type(const QString& type);
    QString get_type_string(const QString& slot, const QString& type);
};
