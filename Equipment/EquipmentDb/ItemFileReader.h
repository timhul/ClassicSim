#pragma once

#include <QFile>
#include <QObject>
#include <QXmlStreamReader>

class EnchantInfo;
class Item;

class ItemFileReader : public QObject {
public:
    ItemFileReader(EnchantInfo* enchant_info, QObject* parent = nullptr);

    void read_items(QVector<Item*>& items, const QString& path);

protected:
    EnchantInfo* enchant_info;

    void item_file_handler(QXmlStreamReader& reader, QVector<Item*>& items);

    // Element readers
    void info_element_reader(const QXmlStreamAttributes& attrs, QMap<QString, QString>& item);
    void class_restriction_element_reader(const QXmlStreamAttributes& attrs, QMap<QString, QString>& item);
    void stats_element_reader(QXmlStreamReader& reader, QVector<QPair<QString, QString>>& stats);
    void proc_element_reader(QXmlStreamReader& reader, QVector<QMap<QString, QString>>& procs);
    void use_element_reader(QXmlStreamReader& reader, QVector<QMap<QString, QString>>& uses);
    void modifies_element_reader(QXmlStreamReader& reader, QVector<QString>& spell_modifications);
    void mutex_element_reader(const QXmlStreamAttributes& attrs, QSet<int>& mutex_item_ids);
    void random_affixes_element_reader(QXmlStreamReader& reader, QVector<int>& random_affixes);

    void add_mandatory_attr(const QXmlStreamAttributes& attrs, const QString& attr, QMap<QString, QString>& item);
    void add_attr(const QXmlStreamAttributes& attrs, const QString& attr, QMap<QString, QString>& item);

    void create_item(QVector<Item*>& items,
                     QMap<QString, QString>& item_map,
                     QVector<QPair<QString, QString>>& stats,
                     QVector<QMap<QString, QString>>& procs,
                     QVector<QMap<QString, QString>>& uses,
                     QVector<QString>& spell_modifications,
                     QVector<QString>& special_equip_effects,
                     QSet<int>& mutex_item_ids,
                     QVector<int>& random_affixes);

    void extract_info(QMap<QString, QString>& item, QMap<QString, QString>& info);
    void extract_stats(QMap<QString, QString>& item, QMap<QString, QString>& stats);
    void extract(QVector<QString> handled_keys, QMap<QString, QString>& source, QMap<QString, QString>& target);

    void warn_remaining_keys(QMap<QString, QString>& item);
};
