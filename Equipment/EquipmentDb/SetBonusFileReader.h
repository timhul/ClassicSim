#pragma once

#include <QXmlStreamReader>

class Item;

enum class ItemStats: int;

class SetBonusFileReader {
public:
    void read_set_bonuses(const QString &path,
                          QMap<int, QString>& possible_set_items,
                          QMap<QString, QVector<QPair<int, QString>>>& set_bonus_tooltips,
                          QMap<QString, QMap<int, QPair<ItemStats, unsigned>>>& set_bonus_effects);

private:
    void set_bonus_file_handler(QXmlStreamReader &reader,
                                QMap<int, QString> &possible_set_items,
                                QMap<QString, QVector<QPair<int, QString>>>& set_bonus_tooltips,
                                QMap<QString, QMap<int, QPair<ItemStats, unsigned>>>& set_bonus_effects);
};
