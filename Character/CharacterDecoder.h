#ifndef CHARACTERDECODER_H
#define CHARACTERDECODER_H

#include <QObject>
#include <QVector>
#include <QMap>

class Character;
class Item;

class CharacterDecoder: public QObject {
    Q_OBJECT

public:
    CharacterDecoder(QObject* parent = 0);

    void initialize(const QString &setup_string);

    QString get_class();
    QString get_race();
    QString get_key(const QString& key);
    QVector<QPair<QString, QString>> get_key_val_pairs(const QString& key);

protected:
private:
    QMap<QString, QString> setup_map;
    QMap<QString, QVector<QPair<QString, QString>>> setup_lists;

    void parse_list(QString &string_list);

    QPair<QString, QString> get_key_val(const QString& key_val) const;
};

#endif // CHARACTERDECODER_H
