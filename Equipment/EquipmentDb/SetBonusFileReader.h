#pragma once

#include <QXmlStreamReader>

class Item;

class SetBonusFileReader {
public:
    void read_set_bonuses(const QString &path,
                          QMap<int, QString>& possible_set_items,
                          QMap<QString, QVector<QPair<int, QString>>> &set_bonus_tooltips);

private:
    void set_bonus_file_handler(QXmlStreamReader &reader,
                                QMap<int, QString> &possible_set_items,
                                QMap<QString, QVector<QPair<int, QString>>>& set_bonus_tooltips);
};
