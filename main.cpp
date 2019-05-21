#include <LIEF/LIEF.h>
#include <QApplication>
#include <QDebug>
#include <MainWindow.h>
#include <PeModel.h>
#include <QHeaderView>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow m;
    m.show();
    return a.exec();
}
