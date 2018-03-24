
#include "TalentTree.h"
#include "Talent.h"
#include <QDebug>

TalentTree::TalentTree(const QString &name_) :
    name(name_),
    matrix(QVector<QVector<Talent*>>())
{}

TalentTree::~TalentTree() {
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] != nullptr) {
                delete matrix[i][j];
            }
        }
    }
}

QString TalentTree::get_name() const {
    return name;
}

void TalentTree::leftClickedPosition(const int tier, const QString position) {
    qDebug() << "Clicked tier" << tier << "position" << position;
}
