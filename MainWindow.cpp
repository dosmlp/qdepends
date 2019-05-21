#include "MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QTreeView *parent) : QTreeView(parent)
{
    model_ = new PeModel(this);
    //model_->parse(pe_parse("D:/BaiduNetdisk_6.7.3.exe"));
    setModel(model_);
    setAcceptDrops(true);
    setRootIndex(model_->rootIndex());
    setDragDropMode(DragDropMode::DropOnly);
    header()->hide();
    resize(800,600);
    expandAll();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasFormat("text/uri-list"))
            e->acceptProposedAction();
}

void MainWindow::dragMoveEvent(QDragMoveEvent *e)
{
    if (e->mimeData()->hasFormat("text/uri-list")) {
        e->setDropAction(Qt::MoveAction);
        e->accept();
    } else {
        e->ignore();
    }

}

void MainWindow::dropEvent(QDropEvent *e)
{
    QString file_name = e->mimeData()->urls().first().toLocalFile();
    delete model_;
    if (pe_)
        pe_binary_destroy(pe_);

    pe_ = pe_parse(file_name.toLocal8Bit().data());
    model_ = new PeModel(this);
    model_->parse(pe_);
    setModel(model_);
    setRootIndex(model_->rootIndex());
}
