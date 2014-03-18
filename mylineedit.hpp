#ifndef MYLINEEDIT_HPP
#define MYLINEEDIT_HPP

#include <QLineEdit>
#include <QPushButton>
#include <QResizeEvent>
#include <QToolButton>
#include <QString>

class QToolButton;

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyLineEdit(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void updateSearchButton(const QString &text);

private:
    QString styleSheetForCurrentState() const;
    QString buttonStyleSheetForCurrentState() const;

    QToolButton *mSearchButton;
};

#endif // MYLINEEDIT_HPP
