#include <vector>

template <typename T>
class TreeNode
{
private:
    T data_;
    std::vector<TreeNode<T>*> children;

public:
    TreeNode(T data)
    {
        this->data_ = data;
    }

    ~TreeNode()
    {
        for (int i = 0; i < children.size(); i++)
        {
            delete children[i];
        }
    }

    void insert(T data)
    {
        TreeNode<T>* node = new TreeNode<T>(data);
        children.push_back(node);
    }

    void insert(TreeNode<T>* node)
    {
        children.push_back(node);
    }

    T operator[](int idx)
    {
        return children[idx];
    }
};
