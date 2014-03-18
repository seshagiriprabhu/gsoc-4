#ifndef FILETRANSFER_HPP
#define FILETRANSFER_HPP

#include "mylineedit.hpp"
#include "fileitemdelegate.hpp"
#include <QDialog>
#include <QStyleOptionViewItem>
#include <QStandardItemModel>
#include <QTreeWidget>
#include <QMenu>
#include <QTime>

namespace Ui {
class filetransfer;
}

class filetransfer : public QDialog
{
    Q_OBJECT

private slots:
    void onFileTransferContextMenuRequested(const QPoint& pos);
    void onPauseActionTriggered();
    void onStopActionTriggered();
    void onPropertiesActionTriggered();
    void onRemoveActionTriggered();

public:
    explicit filetransfer(QWidget *parent = 0);
    QSize sizeHint(const QStyleOptionViewItem&  option, const QModelIndex& index) const;
    void sendFile(const QString& filename, const QString& fileSize);

    ~filetransfer();

private:
    Ui::filetransfer *ui;
    MyLineEdit *lineEdit;
    //QStandardItemModel *model;
    FileItemDelegate *fileItemDelegate;
    QMenu *fileTransferContextMenu;

};

#endif // FILETRANSFER_HPP
