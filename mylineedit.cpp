#include "mylineedit.hpp"
#include <QLineEdit>
#include <QToolButton>
#include <QStyle>

MyLineEdit::MyLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    mSearchButton = new QToolButton(this);
    mSearchButton->setFixedSize(18, 18);
    mSearchButton->setCursor(Qt::ArrowCursor);
    mSearchButton->setAutoRaise(true);
    mSearchButton->setStyleSheet(buttonStyleSheetForCurrentState());
    QObject::connect(this, SIGNAL(textChanged(QString)), SLOT(updateSearchButton(QString)));
    setPlaceholderText(tr("Search"));
    setStyleSheet(styleSheetForCurrentState());

    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    QSize minSizeHint = minimumSizeHint();
    setMinimumSize(qMax(minSizeHint.width(), mSearchButton->sizeHint().width() + frameWidth * 2 + 2),
                         qMax(minSizeHint.height(), mSearchButton->sizeHint().height() + frameWidth * 2 + 2));
    setSizePolicy(QSizePolicy::Maximum, sizePolicy().verticalPolicy());
}


void MyLineEdit::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    QSize size = mSearchButton->sizeHint();
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    mSearchButton->move(rect().right() - frameWidth - size.width() - 2, (rect().bottom() + 2 - size.height()) / 2);
}

void MyLineEdit::updateSearchButton(const QString &text)
{
    if (!text.isEmpty())
    {
        // We have some text in the box - set the button to clear the text
        connect(mSearchButton, &QPushButton::clicked, this, &QLineEdit::clear);
    }
    else
    {
        // The text box is empty - make the icon do nothing when clicked
        disconnect(mSearchButton, &QPushButton::clicked, this, &QLineEdit::clear);
    }

    setStyleSheet(styleSheetForCurrentState());
    mSearchButton->setStyleSheet(buttonStyleSheetForCurrentState());
}

QString MyLineEdit::styleSheetForCurrentState() const
{
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);

    QString style;
    style += "QLineEdit {";
    if (text().isEmpty())
    {
        style += "font-family: 'MS Sans Serif';";
        style += "font-style: italic;";
    }

    style += "padding-left: 3px;";
    style += QString("padding-right: %1px;").arg(this->mSearchButton->sizeHint().width() + frameWidth + 1);
    style += "border-width: 3px;";
    style += "border-radius: 15px; border: 1px ;";
    style += "background-color: rgba(255, 255, 255, 204);";
    style += "}";
    style += "QLineEdit:hover, QLineEdit:focus {";
    style += "background-color: rgba(255, 255, 255, 255);";
    style += "}";
    return style;
}

QString MyLineEdit::buttonStyleSheetForCurrentState() const
{
    QString style;
    style += "QToolButton {";
    style += "border: none; margin: 0; padding: 0;";
    style += QString("background-image: url(:/icons/%1.png);").arg(text().isEmpty() ? "search" : "clear");
    style += "}";

    if (!text().isEmpty())
    {
        //style += "QToolButton:hover { background-image: url(:/icons/esf-clear-hover.png); }";
        //style += "QToolButton:pressed { background-image: url(:/icons/esf-clear-active.png); }";
    }

    return style;
}
