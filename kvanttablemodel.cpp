#include "kvanttablemodel.h"

KvantTableModel::KvantTableModel(QObject *parent): QAbstractTableModel(parent) {
    table.append(headers.toVector());
}

int KvantTableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return table.size();
}

int KvantTableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return headers.size();
}

QVariant KvantTableModel::data(const QModelIndex &index, int role) const {
    switch (role) {
    case TableDataRole:
        return table.at(index.row()).at(index.column());
    case HeadingRole:
        if (index.row() == 0) {
            return true;
        } else {
            return false;
        }
    default:
        break;
    }
    return QVariant();
}

QHash<int, QByteArray> KvantTableModel::roleNames() const {
    return { {TableDataRole, "tabledata"},
        {HeadingRole,   "heading"} };
}

void KvantTableModel::importFile(QString filePath) {

    filePath.remove("file:///");
    inputFile.setFileName(filePath);

    if (!inputFile.exists()) {
        emit showMessage(QString("File %1 not exist!").arg(filePath));
        return;
    }

    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit showMessage(QString("Cann't open file %1 to read!").arg(filePath));
        return;
    }

    table.clear();
    table.append(headers.toVector());

    while (!inputFile.atEnd()) {
        tempString = inputFile.readLine();
        tempList = tempString.split(";");
        if (tempList.size() == headers.size() + 1) {
            table.append({tempList[0], tempList[1], tempList[2]});
        }
    }

    inputFile.close();

    emit updateTable();

}

void KvantTableModel::clearModel() {
    table.clear();
    emit updateTable();
}
