#include "fileitemdelegate.hpp"
#include <QApplication>
#include <QDebug>
#include <QPainter>
#include <QPen>

FileItemDelegate::FileItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

void FileItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if(index.column() != 2)
    {
        QStyleOptionProgressBarV2 *progressBarOption = new QStyleOptionProgressBarV2;
        QRect rect = option.rect;
        QSize size(rect.width()*9.5/10,rect.height()*9.5/10);
        rect.setSize(size);
        progressBarOption->state = QStyle::State_Enabled;
        progressBarOption->direction = QApplication::layoutDirection();
        progressBarOption->rect =rect;
        progressBarOption->fontMetrics = QApplication::fontMetrics();
        QPalette pal = progressBarOption->palette;
        QColor col;
        col.setNamedColor("#6BC260");
        pal.setColor(QPalette::Window,col);
        progressBarOption->palette = pal;
        progressBarOption->type = QStyleOption::SO_ProgressBar;
        progressBarOption->version = 2;
        progressBarOption->minimum = 0;
        progressBarOption->maximum = 100;
        progressBarOption->textAlignment = Qt::AlignCenter;
        progressBarOption->textVisible = true;
        int progress = index.data(Qt::DisplayRole).toInt();//TCP client or server must changes this value emitting signal bytesWritten(qint64)
        progressBarOption->progress = progress;
        progressBarOption->text = QString("%1%").arg(progressBarOption->progress);

        // Draw the progress bar onto the view.
        QApplication::style()->drawControl(QStyle::CE_ProgressBar, progressBarOption, painter,0);

    }
    else
    {
        FileItemDelegate::paint(painter, option, index);
    }

}

QSize FileItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QIcon fileIcon = QIcon(":/icons/icon64.png");
    QSize fileIconSize = fileIcon.actualSize(option.decorationSize);

    static const int VERTICAL_PADDING = 2;

    return QSize(fileIconSize.width(), VERTICAL_PADDING + fileIconSize.height() + VERTICAL_PADDING);
}
