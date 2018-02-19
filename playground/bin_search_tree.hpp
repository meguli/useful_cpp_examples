#ifndef CHOPS_BST_H
#define CHOPS_BST_H
#include <memory>
#include <utility>
#include <iostream>

template <typename T>
class bin_search_tree
{
    struct node_t
    {
        T value;
        std::shared_ptr<node_t> _left;
        std::shared_ptr<node_t> _right;
        std::weak_ptr<node_t> _parent;

        node_t(T val) :value(std::move(val)) {}
        node_t() = default;
        ~node_t() = default;
    };
    std::shared_ptr<node_t> _root;
public:

    using nodeptr = std::shared_ptr<node_t>;
    using const_nodeptr = std::shared_ptr<const node_t>;
    using value_type = T;

    bin_search_tree() = default;
    ~bin_search_tree() = default;

    bool is_empty() const { return _root == nullptr; }

    // TODO: will we take by reference or by value or by move??
    void insert(T val){
        nodeptr target = std::make_shared<node_t>(val);

        // nullptr by default const
        nodeptr trailing_node;
        nodeptr cur = _root;

        while(cur != nullptr){
            trailing_node = cur;
            if(target->value < cur->value)
                cur = cur->_left;
            else
                cur = cur->_right;
        }
        target->_parent = trailing_node;

        if(trailing_node == nullptr)
            _root = target;
        else if(target->value < trailing_node->value)
            trailing_node->_left = target;
        else
            trailing_node->_right = target;
    }

    const_nodeptr find(const T& val) const
    {
        const_nodeptr cur = _root;;
        while(cur != nullptr && val != cur->value)
        {
            if(val < cur->value)
                cur = cur->_left;
            else
                cur = cur->_right;
        }
        return cur;
    }

    // Recursive traversal, implement with iterators as well
    void inorder_traverse(nodeptr it)
    {
        nodeptr cur = it;
        if(cur == nullptr)
            return;
        else
        {
            inorder_traverse(cur->_left);
            std::cout << cur->value;
            inorder_traverse(cur->_right);
        }
    }

    void inorder_traverse()
    {
        inorder_traverse(_root);
    }
};

#endif