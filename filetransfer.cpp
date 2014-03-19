#include "filetransfer.hpp"
#include "ui_filetransfer.h"
#include "fileitemdelegate.hpp"

#include <QHBoxLayout>
#include <QFileInfo>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QDebug>

void filetransfer::onFileTransferContextMenuRequested(const QPoint &pos)
{
    QPoint globalPos = ui->fileView->viewport()->mapToGlobal(pos);
    globalPos.setX(globalPos.x() + 1);
    fileTransferContextMenu->exec(globalPos);
}

void filetransfer::onPauseActionTriggered()
{

}

void filetransfer::onStopActionTriggered()
{

}

void filetransfer::onPropertiesActionTriggered()
{

}

void filetransfer::onRemoveActionTriggered()
{

}

filetransfer::filetransfer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::filetransfer)
{

    ui->setupUi(this);

    QAction* pauseAction = new QAction(QIcon(":/icons/pause.png"), "Pause", this);
    connect(pauseAction, &QAction::triggered, this, &filetransfer::onPauseActionTriggered);

    QAction* stopAction = new QAction(QIcon(":/icons/stop.png"), "Stop", this);
    connect(stopAction, &QAction::triggered, this, &filetransfer::onStopActionTriggered);

    QAction* propertiesAction = new QAction(QIcon(":/icons/info.png"), "Properties", this);
    connect(propertiesAction, &QAction::triggered, this, &filetransfer::onPropertiesActionTriggered);

    QAction* removeAction = new QAction(QIcon(":/icons/remove.png"), "Remove", this);
    connect(removeAction, &QAction::triggered, this, &filetransfer::onRemoveActionTriggered);

    fileTransferContextMenu = new QMenu(this);
    fileTransferContextMenu->setStyleSheet("QMenu{background:;}");
    fileTransferContextMenu->popup(QCursor::pos());
    fileTransferContextMenu->addActions(QList<QAction*>() << pauseAction << stopAction << removeAction << propertiesAction);

    ui->toxLogo->setPixmap(QPixmap(":/icons/toxlogo.png"));
    ui->toxLogo->setAlignment(Qt::AlignVCenter);
    ui->toxLogo->setContentsMargins(0,0,0,0);

    QVBoxLayout *sideLayout = new QVBoxLayout();
    sideLayout->addWidget(ui->toxLogo);
    sideLayout->setSizeConstraint(QLayout::SetDefaultConstraint);

    ui->frame->setContentsMargins(0,0,0,0);
    ui->frame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    ui->frame->setLayout(sideLayout);

    lineEdit = new MyLineEdit;
    lineEdit->setFixedWidth(250);
    lineEdit->setFixedHeight(30);
    lineEdit->setAlignment(Qt::AlignLeft);

    ui->searchButtonLayout->addWidget(lineEdit);
    ui->searchButtonLayout->setContentsMargins(5,5,0,5);
    ui->searchButtonLayout->addSpacerItem(new QSpacerItem(310, 1));

    ui->fileView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->fileView->setIconSize(QSize(32, 32));
    ui->fileView->setRootIsDecorated(true);

    ui->fileView->setSortingEnabled(true);
    ui->fileView->setIndentation(0);
    ui->fileView->setAlternatingRowColors(true);
    ui->fileView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->fileView->setItemDelegateForColumn(1, new FileItemDelegate(ui->fileView));
    ui->fileView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->fileView, &QTreeWidget::customContextMenuRequested, this, &filetransfer::onFileTransferContextMenuRequested);


    int fileHigh = 1000000, fileLow = 1;
    int statusRand;
    int fileRandSize, randValue;
    int statusHigh = 4, High = 100;
    int statusLow = 1, Low = 0;
    QString status, fileSize, speed;

    ui->fileView->setHeaderLabels(QStringList() << "FileName" << "Progress" << "FileSize" << "Status" << "FriendID" << "Speed");
    for (int i = 0; i < 50; ++i)
    {
        randValue = (qrand() % ((High + 1) - Low) + Low);
        statusRand = (qrand() % ((statusHigh + 1) - statusLow) + statusLow);
        speed = QString::number(randValue);
        speed += " Kb/s";
        fileRandSize = (qrand() % ((fileHigh + 1) - fileLow) + fileLow);
        if ((fileRandSize/1024) > 1 && (fileRandSize/1024) < 1024) {
            fileSize = QString::number(fileRandSize/1024);
            fileSize += " Mb";
        } else if ((fileRandSize/100000) > 1) {
            fileSize = QString::number(fileRandSize/1048576);
            fileSize += " Gb";
        } else {
            fileSize = QString::number(fileRandSize);
            fileSize += " Kb";
        }

        if (randValue == 100) {
            if (statusRand == 1) {
                status = "Received Completed";
            } else {
                status = "Send Completed";
            }
        } else {
            if (statusRand == 1) {
                status = "Sending";
            } else if (statusRand == 2){
                status = "Receiving";
            } else if (statusRand == 3) {
                status = "Stopped";
            } else {
                status = "Paused";
            }
        }

        new QTreeWidgetItem(ui->fileView, QStringList() << QString("File-%1").arg(i)
                            << QString::number(qrand() % ((High + 1) - Low) + Low)
                            << fileSize << status << QString("User-%1").arg(randValue) << speed);
    }


    ui->PageLayout->addWidget(ui->fileView);

    ui->mainLayout->setContentsMargins(0,0,0,0);
    ui->mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(ui->mainLayout);
    setWindowIcon(QIcon(":/icons/icon64.png"));
    setWindowTitle("File Transfer Manager");

}

void filetransfer::sendFile(const QString &filename, const QString &fileSize)
{
    QFileInfo info(filename);
    QString ext =  info.suffix();
    QStandardItem* item = new QStandardItem();
    item->setData(filename, FileItemDelegate::FileNameRole);
    item->setData(ext, FileItemDelegate::FileIconRole);
    item->setData(QString("%1").arg(filename), Qt::ToolTipRole);
    item->setData(fileSize, FileItemDelegate::TotalFileSizeRole);
    item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
}


filetransfer::~filetransfer()
{
    delete ui;
}
