#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <sstream>

template <typename T>
struct BinaryTree;

template <typename T>
struct Node
{
	T value;
	Node<T> *left{nullptr}, *right{nullptr}, *parent{nullptr};
	BinaryTree<T>* tree{nullptr};

	Node(T value, Node<T> *left, Node<T> *right) : value(value), left(left), right(right)
	{
		if (left)
		{
			left->tree = tree;
			left->parent = this;
		}
		if (right)
		{
			right->tree = tree;
			right->parent = this;
		}
	}

	void set_tree(BinaryTree<T>* t)
	{
		tree = t;
		if (left)
		{
			left->set_tree(t);
		}
		if (right)
		{
			right->set_tree(t);
		}
	}

	~Node()
	{
		delete left;
		delete right;
	}
};

template <typename T>
struct BinaryTree
{
	Node<T>* root{nullptr};

	BinaryTree(Node<T> *root) : root(root)
	{
		root->set_tree(this);
	}

	~BinaryTree()
	{
		if (root)
		{
			delete root;
		}
	}

	template <typename U>
	struct PreOrderIterator
	{
		Node<U>* current;
		PreOrderIterator(Node<U>* current) : current(current) {}

		bool operator !=(const PreOrderIterator<U>& other)
		{
			return current != other.current;
		}

		// Preorder traversal (no recursion)
		PreOrderIterator<U>& operator++()
		{
			if (current->right)
			{
				current = current->right;
				while(current->left)
				{
					current = current->left;
				}
			}
			else
			{
				Node<T>* p = current->parent;
				while (p && current == p->right)
				{
					current = p;
					p = p->parent;
				}
				current = p;
			}

			return *this;
		}

		Node<U>& operator*()
		{
			return *current;
		}
	};

	typedef PreOrderIterator<T> iterator;

	iterator begin()
	{
		Node<T>* n = root;

		if (n)
		{
			while(n->left)
			{
				n = n->left;
			}
			return {n};
		}

		return end();
	}

	iterator end()
	{
		return iterator{nullptr};
	}
};

int main()
{
	// Fixing the ambiguous constructor call by explicitly using parentheses
	Node<std::string>* mother = new Node<std::string>(
			"mother",
			new Node<std::string>("mother's mother", nullptr, nullptr),
			new Node<std::string>("mother's father", nullptr, nullptr)
	);

	Node<std::string>* me = new Node<std::string>(
			"me",
			mother,
			nullptr
	);

	BinaryTree<std::string> family(me);

	for (auto it = family.begin(); it != family.end(); ++it)
	{
		std::cout << (*it).value << std::endl;
	}

	return 0;
}
