#include "filetransfer.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    filetransfer w;
    w.show();

    return a.exec();
}
