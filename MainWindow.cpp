#include "MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QTreeView *parent) : QTreeView(parent)
{
    model_ = new PeModel(this);
    setModel(model_);
    setAcceptDrops(true);
    setRootIndex(model_->rootIndex());
    setDragDropMode(DragDropMode::DropOnly);
    header()->hide();
    resize(800,600);
    setAutoScroll(true);
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
    if (pe_)
        pe_binary_destroy(pe_);

    pe_ = pe_parse(file_name.toLocal8Bit().data());
    model_->setData(pe_);
    setRootIndex(model_->rootIndex());
}

void MainWindow::drawRow(QPainter *painter, const QStyleOptionViewItem &options, const QModelIndex &index) const
{
    Node* n = static_cast<Node*>(index.internalPointer());
    if (n) {
        if (n->type == Node::DLL) {
            QApplication::style()->drawItemText(painter,options.rect,options.displayAlignment,QApplication::palette(),true,"DLL");
        } else if (n->type == Node::FUNC) {
            QApplication::style()->drawItemText(painter,options.rect,options.displayAlignment,QApplication::palette(),true,"FUNC");
        }
    }
    QTreeView::drawRow(painter,options,index);
}
