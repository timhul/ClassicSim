#ifndef CHARACTERDECODER_H
#define CHARACTERDECODER_H

#include <QVector>
#include <QMap>

class Character;
class Item;
class Rotation;

class CharacterDecoder {
public:
    void initialize(const QString &setup_string);

    QString get_class();
    QString get_race();
    QString get_value(const QString& key);
    QVector<QPair<QString, QString>> get_key_val_pairs(const QString& key);

    void dump();

private:
    QMap<QString, QString> setup_map;
    QMap<QString, QVector<QPair<QString, QString>>> setup_lists;

    void parse_list(QString &string_list);

    QPair<QString, QString> get_key_val(const QString& key_val) const;
};

#endif // CHARACTERDECODER_H
