#ifndef PEMODEL_H
#define PEMODEL_H

#include <memory>
#include <QAbstractItemModel>
#include <LIEF/LIEF.h>

struct Node : public std::enable_shared_from_this<Node> {
    typedef std::shared_ptr<Node> Ptr;
    enum Type { DLL, FUNC };
    Node *        parent;
    QList<Node *> children;
    QString       text;
    Type          type;
    size_t row;
    Node(const QString &t) {
        text   = t;
        parent = nullptr;
    }
    ~Node() {
        clear();
    }
    void clear() {
        qDeleteAll(children);
        children.clear();
    }
};
class PeModel : public QAbstractItemModel {
public:
    explicit PeModel(QObject* parent = nullptr);
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int         rowCount(const QModelIndex &parent) const;
    int         columnCount(const QModelIndex &parent) const;
    QVariant    data(const QModelIndex &index, int role) const;
    QMap<int, QVariant>   itemData(const QModelIndex &index) const;
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const;
    QModelIndex rootIndex();
    void setData(Pe_Binary_t* pe);
private:
    Node::Ptr root_item_;
    Node* root_node_;

    inline Node* getNode(const QModelIndex &index) const;
};

#endif // PEMODEL_H
