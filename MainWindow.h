#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTreeView>
#include <PeModel.h>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QHeaderView>
#include <QMimeData>

class MainWindow : public QTreeView
{
    Q_OBJECT
public:
    explicit MainWindow(QTreeView *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *e);
    void dragMoveEvent(QDragMoveEvent *e);
    void dropEvent(QDropEvent *e);

private:
    PeModel* model_;
    Pe_Binary_t* pe_ = nullptr;
};

#endif // MAINWINDOW_H
