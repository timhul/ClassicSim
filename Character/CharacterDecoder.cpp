#include "CharacterDecoder.h"

#include <QDebug>

#include "CharacterEncoding.h"

void CharacterDecoder::initialize(const QString& setup_string) {
    if (!setup_map.empty()) {
        qDebug() << "Not all map entries were consumed in previous setup:" << setup_map;
        setup_map.clear();
    }
    QStringList entries = setup_string.split(Encoding::ENTRY_SEPARATOR);

    for (int i = 0; i < entries.size(); ++i) {
        QStringList key_val = entries[i].split(Encoding::KEY_VAL_SEPARATOR);

        if (key_val[0].contains(Encoding::LIST_INITIALIZER)) {
            if (!key_val[key_val.size() - 1].contains(Encoding::LIST_END)) {
                qDebug() << "Missing closing bracket in list" << entries[i];
                continue;
            }
            parse_list(entries[i]);
        }
        else if (key_val.size() != 2) {
            qDebug() << "Malformed element" << key_val;
            continue;
        }
        else
            setup_map.insert(key_val[0], key_val[1]);
    }
}

void CharacterDecoder::parse_list(QString& string_list) {
    QStringList list_elements = string_list.split(Encoding::LIST_INITIALIZER);
    QString list_name = list_elements.takeFirst();
    assert(list_elements.size() == 1);
    list_elements[0] = list_elements[0].remove(Encoding::LIST_END);

    setup_lists.insert(list_name, QVector<QPair<QString, QString>>());

    QStringList list_key_val_pairs = list_elements[0].split(Encoding::LIST_ELEMENT_SEPARATOR);
    for (int i = 0; i < list_key_val_pairs.size(); ++i) {
        QPair<QString, QString> key_val_pair = get_key_val(list_key_val_pairs[i]);
        setup_lists[list_name].append(key_val_pair);
    }
}

QString CharacterDecoder::get_key(const QString& key) {
    return setup_map.take(key);
}

QString CharacterDecoder::get_race() {
    return get_key("RACE");
}

QString CharacterDecoder::get_class() {
    return get_key("CLASS");
}

QPair<QString, QString> CharacterDecoder::get_key_val(const QString& key_val_string) const {
    QStringList key_val = key_val_string.split(Encoding::KEY_VAL_SEPARATOR);
    if (key_val.size() != 2) {
        qDebug() << "Malformed element" << key_val;
        return QPair<QString, QString>();
    }

    return QPair<QString, QString>(key_val[0], key_val[1]);
}

QVector<QPair<QString, QString> > CharacterDecoder::get_key_val_pairs(const QString& key) {
    return setup_lists.take(key);
}

void CharacterDecoder::dump() {
    qDebug() << "setup_map" << setup_map;
    qDebug() << "setup_lists" << setup_lists;
}
