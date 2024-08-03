#pragma once
#include <queue>
#include <iostream>
template <typename T>
class BinaryTreeNode
{
public:
    T data;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    BinaryTreeNode(int n)
    {
        this->data = n;
        left_ = nullptr;
        right_ = nullptr;
    }

    ~BinaryTreeNode()
    {
        delete left;
        delete right;
    }
    
    void insert(T n)
    {
        if (n < this->data)
        {
            if (left == nullptr)
            {
                left = new BinaryTreeNode(n);
            }
            else
            {
                left ->insert(n);
            }
        }
        else
        {
            if (right == nullptr)
            {
                right = new BinaryTreeNode(n);
            }
            else
            {
                right->insert(n);
            }
        }
    }
    
    void print() const
    {
        if (left != nullptr)
        {
            left->print();
        }
        std::cout << data << ' ';
        if (right != nullptr)
        {
            right->print();
        }
    }
    
    bool contains(const T n) const
    {
        if (n == this->data)
        {
            return true;
        }
        else if (data < this->data)
        {
            if (left == nullptr)
            {
                return false;
            }
            else
            {
                return left->contains(n);
            }
        }
        else
        {
            if (right == nullptr)
            {
                return false;
            }
            else
            {
                return right->contains(n);
            }
        }
    }
    
    void remove(const T n, BinaryTreeNode* parent)
    {
        if (n < this->data)
        {
            if (left != nullptr)
            {
                left->remove(data, this);
            }
        }
        else if (n > this->data)
        {
            if (right != nullptr)
            {
                right->remove(n, this);
            }
        }
        else
        {
            if (left != nullptr && right != nullptr)
            {
                this->data = right->min();
                right->remove(this->data_, this);
            }
            else if (parent->left == this)
            {
                parent->left = (left != nullptr) ? left : right;
            }
            else if (parent->right == this)
            {
                parent->right = (left != nullptr) ? left : right;
            }
        }
    }
    
    int min() const
    {
        if (left == nullptr)
        {
            return data;
        }
        else
        {
            return left->min();
        }
    }
    
    int max() const
    {
        if (right == nullptr)
        {
            return data;
        }
        else
        {
            return right->max();
        }
    }
    
    void print_level_order() const
    {
        std::queue<BinaryTreeNode*> q;
        q.push(this);
        
        while (!q.empty())
        {
            BinaryTreeNode* current = q.front();
            q.pop();
            
            std::cout << current->data << ' ';
            
            if (current->left != nullptr)
            {
                q.push(current->left);
            }
            if (current->right != nullptr)
            {
                q.push(current->right);
            }
        }
    }
};
