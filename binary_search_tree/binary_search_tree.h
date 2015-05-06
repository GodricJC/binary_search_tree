#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <ostream>
#include <stack>
#include <stdexcept>

using std::shared_ptr;
using std::unique_ptr;
using std::ostream;
using std::stack;

/*
 * in order to solve the problem of circular reference
 * we can only use shared_ptr to manage left and right child, but not the point of parent
 */
template <typename T>
class BinarySearchTree
{
public:
	struct Node
	{
		/*
		 * shared_ptr<> is not suitabe here, because circular reference happens if it is used
		 * then destructor will never called
		 */
		Node* p_{ nullptr };
		shared_ptr<Node> l_{ nullptr };
		shared_ptr<Node> r_{ nullptr };
		unique_ptr<T> v_{ nullptr };
		bool flag_ { false }; // flag used in non-recursion postorder tree walk

		Node(){}
		Node(const T& v) : v_(new T(v)){}
		~Node(){}

		bool operator<(const Node& rhs)
		{
			return *this->v_ < *rhs.v_;
		}
		bool isEqual(const Node& rhs)
		{
			return *this->v_ == *rhs.v_;
		}
		friend ostream& operator<<(ostream& out, const Node& n)
		{
			return out << *n.v_;
		}
	};
public:
	void insert(const T& v)
	{
		shared_ptr<Node> cNode(new Node(v));
		if (!root_)
			root_ = cNode;
		else
		{
			shared_ptr<Node> current = root_;
			shared_ptr<Node> previous = nullptr;
			while (current)
			{
				previous = current;
				if (*cNode < *current)
					current = current->l_;
				else
					current = current->r_;
			}
			if (*cNode < *previous)
				previous->l_ = cNode;
			else
				previous->r_ = cNode;
			// attention that parent is a raw pointer
			cNode->p_ = previous.get();
		}
	}

	void inorder_r(ostream& out) const 
	{
		inoder_r_impl(root_, out);
	}

	void preorder_r(ostream& out) const 
	{
		preorder_r_impl(root_, out);
	}

	void postorder_r(ostream& out) const 
	{
		postorder_r_impl(root_, out);
	}

	void inorder_nr(ostream& out) const
	{
		stack <shared_ptr<Node>> nodeStack;
		auto current = root_;
		while (current || !nodeStack.empty())
		{
			while (current)
			{
				nodeStack.push(current);
				current = current->l_;
			}
			current = nodeStack.top();
			nodeStack.pop();
			out << *current << " ";
			current = current->r_;
		}
	}

	void preorder_nr(ostream& out) const 
	{
		stack<shared_ptr<Node>> nodeStack;
		if (root_)
			nodeStack.push(root_);
		while (!nodeStack.empty())
		{
			auto current = nodeStack.top();
			nodeStack.pop();
			out << *current << " ";
			if (current->r_)
				nodeStack.push(current->r_);
			if (current->l_)
				nodeStack.push(current->l_);
		}
	}

	void postorder_nr(ostream& out) const 
	{
		stack<shared_ptr<Node>> nodeStack;
		auto current = root_;
		while (current)
		{
			current->flag_ = false;
			nodeStack.push(current);
			current = current->l_;
		}
		while (!nodeStack.empty())
		{
			current = nodeStack.top();
			if (current->flag_)
			{
				out << *current << " ";
				nodeStack.pop();
			}
			else
			{
				current->flag_ = true;
				current = current->r_;
				while (current)
				{
					nodeStack.push(current);
					current = current->l_;
				}
			}
		}
	}

	const Node* search_r(const T& v) const
	{
		shared_ptr<Node> temp(new Node(v));
		return search_r_impl(root_, temp);
	}

	const Node* search_nr(const T& v) const
	{
		shared_ptr<Node> temp(new Node(v));
		auto current = root_;
		while (current)
		{
			if (temp->isEqual(*current))
				return current.get();
			else if (*temp < *current)
				current = current->l_;
			else
				current = current->r_;
		}
		return nullptr;
	}

	T minV() const
	{
		return minV_impl(root_);
	}
	
	T  maxV() const
	{
		return maxV_impl(root_);
	}

	T successor(const T& v) const
	{
		auto temp = search_nr(v);
		if (temp->r_)
			return minV_impl(temp->r_);
		auto p = temp->p_;
		while (p && temp != p->l_.get())
		{
			temp = p;
			p = p->p_;
		}
		if (!p)
			throw std::runtime_error("No successor");
		return *p->v_;
	}

	T predecessor(const T& v) const
	{
		auto temp = search_nr(v);
		if (temp->l_)
			return maxV_impl(temp->l_);
		auto p = temp->p_;
		while (p && temp == p->l_.get())
		{
			temp = p;
			p = p->p_;
		}
		if (!p)
			throw std::runtime_error("No predecessor");
		return *p->v_;
	}

private:
	void inoder_r_impl(shared_ptr<Node> root, ostream& out) const
	{
		if (root)
		{
			inoder_r_impl(root->l_, out);
			out << *root << " ";
			inoder_r_impl(root->r_, out);
		}
	}

	void preorder_r_impl(shared_ptr<Node> root, ostream& out) const
	{
		if (root)
		{
			out << *root << " ";
			preorder_r_impl(root->l_, out);
			preorder_r_impl(root->r_, out);
		}
	}

	void postorder_r_impl(shared_ptr<Node> root, ostream& out) const
	{
		if (root)
		{
			postorder_r_impl(root->l_, out);
			postorder_r_impl(root->r_, out);
			cout << *root << " ";
		}
	}

	const Node* search_r_impl(shared_ptr<Node> root, shared_ptr<Node> v) const
	{
		if (!root)
			return nullptr;
		if (v->isEqual(*root))
			return root.get();
		else if (*v < *root)
			return search_r_impl(root->l_, v);
		else
			return search_r_impl(root->r_, v);
	}

	const T minV_impl(shared_ptr<Node> root) const
	{
		auto current = root;
		while (current->l_)
			current = current->l_;
		return *current->v_;
	}

	const T maxV_impl(shared_ptr<Node> root) const
	{
		auto current = root;
		while (current->r_)
			current = current->r_;
		return *current->v_;
	}

private:
	shared_ptr<Node> root_{ nullptr };
};

#endif