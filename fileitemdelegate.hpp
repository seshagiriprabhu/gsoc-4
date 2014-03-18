#ifndef FILEITEMDELEGATE_HPP
#define FILEITEMDELEGATE_HPP

#include <QItemDelegate>

class FileItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit FileItemDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem&  option, const QModelIndex& index) const;

     enum {FileTransferRole = Qt::UserRole, FileIconRole, FileNameRole, TransferedfFileSizeRole,
           TotalFileSizeRole, TimeRemainingRole, NetworkSpeedRole};

signals:

public slots:

};

#endif // FILEITEMDELEGATE_HPP
