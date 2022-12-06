
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
};

void print(TreeNode<int>* root)
{
    std::cout << root->data() << '\n';
    
    for (int i = 0; i < root->size(); i++)
    {
        print(root->operator[](i));
    }
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
