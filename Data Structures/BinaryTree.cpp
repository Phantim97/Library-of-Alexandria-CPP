
#include <queue>
template <typename T>
class BinaryTreeNode
{
public:
    T data;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    BinaryTreeNode(int data)
    {
        this->data = data;
        left = nullptr;
        right = nullptr;
    }

    ~BinaryTreeNode()
    {
        delete left;
        delete right;
    }
    
    void insert(T data)
    {
        if (data < this->data)
        {
            if (left == nullptr)
            {
                left = new BinaryTreeNode(data);
            }
            else
            {
                left->insert(data);
            }
        }
        else
        {
            if (right == nullptr)
            {
                right = new BinaryTreeNode(data);
            }
            else
            {
                right->insert(data);
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
    
    bool contains(T data) const
    {
        if (data == this->data)
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
                return left->contains(data);
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
                return right->contains(data);
            }
        }
    }
    
    void remove(T data, BinaryTreeNode* parent)
    {
        if (data < this->data)
        {
            if (left != nullptr)
            {
                left->remove(data, this);
            }
        }
        else if (data > this->data)
        {
            if (right != nullptr)
            {
                right->remove(data, this);
            }
        }
        else
        {
            if (left != nullptr && right != nullptr)
            {
                this->data = right->min();
                right->remove(this->data, this);
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
