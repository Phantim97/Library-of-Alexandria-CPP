#include <vector>
#include <iostream>

template <typename T>
class TreeNode
{
private:
    T data_ {};

public:
    std::vector<TreeNode*> children;

    explicit TreeNode(T data)
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

    void insert(const T data)
    {
        TreeNode<T>* node = new TreeNode<T>(data);
        children.push_back(node);
    }

    void insert(TreeNode<T>* node)
    {
        children.push_back(node);
    }

    T data() const
    {
        return data_;
    }

    size_t size() const
    {
        return children.size();
    }

    TreeNode<T>* operator[](const int idx)
    {
        return children[idx];
    }
    
	size_t count_nodes() const
    {
        size_t count = 1;

        for (int i = 0; i < children.size(); i++)
        {
            count += children[i]->count_nodes();
        }

        return count;
    }
    
    size_t height() const
    {
        size_t max_height = 0;

        for (int i = 0; i < children.size(); i++)
        {
            size_t child_height = children[i]->height();
            
            if (child_height > max_height)
            {
                max_height = child_height;
            }
        }

        return max_height + 1;
    }
    
    size_t print_at_depth(const int depth) const
    {
        if (depth == 0)
        {
            std::cout << data_ << " ";
            return 1;
        }

        size_t count = 0;
        for (int i = 0; i < children.size(); i++)
        {
            count += children[i]->print_at_depth(depth - 1);
        }

        return count;
    }
};

void print(TreeNode<int>* root)
{
    std::cout << root->data() << std::endl;
    for (int i = 0; i < root->size(); i++)
    {
        print(root->children[i]);
    }
}

// pre-order traversal is where we visit the root node first, then the left
void preorder(TreeNode<int>* root)
{
    if (root == nullptr)
    {
        return;
    }

    std::cout << root->data() << ' ';
    
    for (int i = 0; i < root->size(); i++)
    {
        preorder(root->children[i]);
    }
}

//post-order traversal is where we visit the children first, then the root
void postorder(TreeNode<int>* root)
{
    if (root == nullptr)
    {
        return;
    }

    for (int i = 0; i < root->size(); i++)
    {
        postorder(root->children[i]);
    }
    
    std::cout << root->data() << ' ';
}

int main()
{
    TreeNode<int>* root = new TreeNode<int>(1);
    TreeNode<int>* node1 = new TreeNode<int>(2);
    TreeNode<int>* node2 = new TreeNode<int>(3);
    TreeNode<int>* node3 = new TreeNode<int>(4);

    root->insert(node1);
    root->insert(node2);
    root->insert(node3);

    root->insert(5);

    print(root);

    delete root;

    return 0;
}
