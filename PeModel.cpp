#include "PeModel.h"
#include <QDebug>

PeModel::PeModel(QObject *parent):QAbstractItemModel(parent) {
    root_item_ = std::make_shared<Node>("");
    root_item_->parent = nullptr;
}

QModelIndex PeModel::index(int row, int column, const QModelIndex &parent) const {
    if (!hasIndex(row, column, parent))
        return QModelIndex();
    Node *p = getNode(parent);
    if (p) {
        Node *c = p->children.at(row);
        if (c)
            return createIndex(row, 0, c);
    }

    return QModelIndex();
}

QModelIndex PeModel::parent(const QModelIndex &child) const {
    Node *n = getNode(child);
    if (n == nullptr)
        return QModelIndex();
    Node *p = n->parent;
    if (!p)
        return QModelIndex();
    return createIndex(p->row, 0, p);
}

int PeModel::rowCount(const QModelIndex &parent) const {
    Node *p = getNode(parent);
    if (p == nullptr)
        return 0;
    return p->children.size();
}

int PeModel::columnCount(const QModelIndex &parent) const {
    return 1;
}

QVariant PeModel::data(const QModelIndex &index, int role) const {
    if (index.column() > 0)
        return QVariant();
    Node *n = getNode(index);
    if (n == nullptr)
        return QVariant();

    if (index.column() == 0) {
        switch (role) {
            case Qt::DisplayRole:
                return n->text;
            case Qt::ToolTipRole:
                return n->text;
            case Qt::EditRole:
                return n->text;
            default:
                return QVariant();
        }
    }
    return QVariant();
}

QMap<int, QVariant> PeModel::itemData(const QModelIndex &index) const {
    QMap<int, QVariant> roles;
    for (int i = 0; i < Qt::UserRole; ++i) {
        QVariant variantData = data(index, i);
        if (variantData.isValid())
            roles.insert(i, variantData);
    }
    return roles;
}

bool PeModel::hasChildren(const QModelIndex &parent) const
{
    Node* n = getNode(parent);
    if(n) {
        if (!n->children.isEmpty())
            return true;
    }
    return false;
}

QModelIndex PeModel::rootIndex()
{
    return createIndex(0,0,root_item_.get());
}

void PeModel::setData(Pe_Binary_t* pe) {
    if (pe == nullptr) return;
    beginResetModel();
    root_item_->clear();
    root_node_         = new Node(QString(pe->name)+"("+QString(MACHINE_TYPES_to_string(pe->header.machine))+")");
    root_node_->parent = root_item_.get();
    root_node_->row = 0;
    root_node_->type = Node::DLL;
    root_item_->children.append(root_node_);

    Pe_Import_t **imports = pe->imports;
    for (size_t i = 0; imports[ i ] != nullptr; ++i) {
        Node *dll = new Node(imports[ i ]->name);
        dll->parent = root_node_;
        dll->row = i;
        dll->type = Node::DLL;
        root_node_->children.append(dll);

        Pe_ImportEntry_t **entries = imports[ i ]->entries;
        for (size_t j = 0; entries[ j ] != nullptr; ++j) {
            if (entries[ j ]->name != nullptr) {
                Node *func = new Node(entries[ j ]->name);
                func->parent = dll;
                func->row = j;
                func->type = Node::FUNC;
                dll->children.append(func);
            }
        }
    }
    endResetModel();
}

Node *PeModel::getNode(const QModelIndex &index) const {
//    if (index.isValid()) {
//        return static_cast<Node *>(index.internalPointer());
//    } else {
//        return root_node_.get();
//    }
//    if (index.internalPointer() == nullptr) {
//        return root_node_.get();
//    }
//    if (index.row() == 0 && index.column() == 0 && index.internalPointer() == nullptr)
//        return root_node_.get();
    if (index.internalPointer() == nullptr)
        return nullptr;
    return static_cast<Node *>(index.internalPointer());
}
