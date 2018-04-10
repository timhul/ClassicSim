#ifndef EQUIPMENTDB_H
#define EQUIPMENTDB_H

#include <QObject>
#include <QFile>
#include <QXmlStreamReader>

class EquipmentDb: public QObject {
public:
    EquipmentDb(QObject* parent = 0);

    ~EquipmentDb() {}

protected:
private:
    void read_equipment_file(const QString &path);
    void weapon_file_handler(QXmlStreamReader &reader);

    void info_element_reader(const QXmlStreamAttributes &attrs, QMap<QString, QString> &item);
    void dmg_range_element_reader(const QXmlStreamAttributes &attrs, QMap<QString, QString> &item);
    void class_restriction_element_reader(const QXmlStreamAttributes &attrs, QMap<QString, QString> &item);
    void stats_element_reader(QXmlStreamReader &reader, QMap<QString, QString> &item);
    void proc_element_reader(QXmlStreamReader &reader, QVector<QMap<QString, QString>> &procs);

    void add_mandatory_attr(const QXmlStreamAttributes &attrs, const QString& attr, QMap<QString, QString> &item);
    void add_attr(const QXmlStreamAttributes &attrs, const QString& attr, QMap<QString, QString> &item);

};

#endif // EQUIPMENTDB_H
