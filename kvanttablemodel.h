#ifndef KVANTTABLEMODEL_H
#define KVANTTABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QFile>

#include <QDebug>


class KvantTableModel: public QAbstractTableModel {
    Q_OBJECT

    QStringList headers{"id", "name", "phone"};

    enum TableRoles {
        TableDataRole = Qt::UserRole + 1,
        HeadingRole
    };

    QFile inputFile;
    QString tempString;
    QStringList tempList;
    QVector<QVector<QString>> table;

public:
    explicit KvantTableModel(QObject *parent = nullptr);

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const;

    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void importFile(QString filePath);

    Q_INVOKABLE void clearModel();

signals:
    void showMessage(QString message);
    void updateTable();
};

#endif // KVANTTABLEMODEL_H
