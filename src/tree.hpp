#include "node.hpp"
#include <optional>
#include <stdexcept>

template<typename T> class tree
{
	private:
		node<T> *root;
		node<T> *__insert(node<T> *, T, unsigned);
		node<T> *rotate_left(node<T> *);
		node<T> *rotate_right(node<T> *);
		node<T> *move_left(node<T> *);
		node<T> *move_right(node<T> *);
		node<T> *balance(node<T> *);
		bool get_color(node<T> *);
		void switch_color(node<T> *);
		bool search(node<T> *, unsigned);
		T search_value(node<T> *, unsigned);
		node<T> *search_smallest(node<T> *);
		node<T> *remove_smallest(node<T> *);
		node<T> *remove_node(node<T> *, unsigned);

	public:
		tree();
		tree(T, unsigned);
		void insert(T, unsigned);
		void remove(unsigned);
		const T operator[](const unsigned) const;
		~tree();
};

template<typename T> tree<T>::tree()
{
	this->root = nullptr;
}

template<typename T> tree<T>::tree(T data, unsigned key)
{
	this->root = new node<T>(data, key);
}

template<typename T> bool tree<T>::get_color(node<T> *root)
{
	if (root == nullptr)
		return BLACK;
	else
		return root->get_color();
}

template<typename T> void tree<T>::switch_color(node<T> *root)
{
	root->set_color(!root->get_color());
	if (root->get_right() != nullptr)
		root->get_right()->set_color(!root->get_right()->get_color());
	if (root->get_left() != nullptr)
		root->get_left()->set_color(!root->get_left()->get_color());
}

template<typename T> node<T> *tree<T>::rotate_left(node<T> *root)
{
	node<T> *aux;
	aux = root->get_right();
	root->set_right(aux->get_left());
	aux->set_left(root);
	aux->set_color(root->get_color());
	root->set_color(RED);
	return aux;
}

template<typename T> node<T> *tree<T>::rotate_right(node<T> *root)
{
	node<T> *aux;
	aux = root->get_left();
	root->set_left(aux->get_right());
	aux->set_right(root);
	aux->set_color(root->get_color());
	root->set_color(RED);
	return aux;
}

template<typename T> node<T> *tree<T>::move_left(node<T> *root)
{
	this->switch_color(root);
	if (this->get_color(root->get_left()->get_right()))
	{
		root->set_right(this->rotate_right(root->get_right()));
		root = this->rotate_left(root);
		this->switch_color(root);
	}
	return root;
}

template<typename T> node<T> *tree<T>::move_right(node<T> *root)
{
	switch_color(root);
	if (this->get_color(root->get_left()->get_left()))
	{
		root = this->rotate_right(root);
		this->switch_color(root);
	}
	return root;
}

template<typename T> node<T> *tree<T>::balance(node<T> *root)
{
	if (get_color(root->get_right()))
		root = rotate_left(root);
	if (root->get_left() != nullptr && get_color(root->get_left()) && get_color(root->get_left()->get_left()))
		root = rotate_right(root);
	if (get_color(root->get_left()) && get_color(root->get_right()))
		switch_color(root);
	return root;
}

template<typename T> node<T> *tree<T>::__insert(node<T> *root, T data, unsigned key)
{
	if (root == nullptr)
		return new node<T>(data, key);
	if (root->get_key() == key)
		throw std::invalid_argument("Key already exists");
	else if (key > root->get_key())
	{
		if (root->get_right() == nullptr)
			root->set_right(new node<T>(data, key));
		else
			root->set_right(this->__insert(root->get_right(), data, key));
	}
	else
	{
		if (root->get_left() == nullptr)
			root->set_left(new node<T>(data, key));
		else
			root->set_left(this->__insert(root->get_left(), data, key));
	}
	if (this->get_color(root->get_right()) && !this->get_color(root->get_left()))
		root = this->rotate_left(root);
	if (this->get_color(root->get_left()) && this->get_color(root->get_left()->get_left()))
		root = this->rotate_right(root);
	if (this->get_color(root->get_left()) && this->get_color(root->get_right()))
		this->switch_color(root);
	return root;
}

template<typename T> void tree<T>::insert(T data, unsigned key)
{
	this->root = this->__insert(this->root, data, key);
}

template<typename T> bool tree<T>::search(node<T> *root, unsigned key)
{
	if (root == nullptr)
		return false;
	else if (root->get_key() == key)
		return true;
	else if (key > root->get_key())
		return search(root->get_right(), key);
	else
		return search(root->get_left(), key);
}

template<typename T> T tree<T>::search_value(node<T> *root, unsigned key)
{
	if (root == nullptr)
		throw std::invalid_argument("Key does not exist");
	else if (root->get_key() == key)
		return root->get_data();
	else if (key > root->get_key())
		return search_value(root->get_right(), key);
	else
		return search_value(root->get_left(), key);
}

template<typename T> node<T> *tree<T>::search_smallest(node<T> *root)
{
	auto n1 = root;
	auto n2 = root->get_left();
	while (n2 != nullptr)
	{
		n1 = n2;
		n2 = n2->get_left();
	}
	return n1;
}

template<typename T> node<T> *tree<T>::remove_smallest(node<T> *root)
{
	if (root->get_left() == nullptr)
	{
		delete root;
		return nullptr;
	}
	if (!get_color(root->get_left()) && !get_color(root->get_left()->get_left()))
		root = move_left(root);
	root->set_left(remove_smallest(root->get_left()));
	return balance(root);
}

template <typename T> node<T> *tree<T>::remove_node(node<T> *root, unsigned key)
{
	if (key < root->get_key())
	{
		if (!get_color(root->get_left()) && !get_color(root->get_left()->get_left()))
			root = move_left(root);
		root->set_left(remove_node(root->get_left(), key));
	}
	else
	{
		if (get_color(root->get_left()))
			root = rotate_right(root);
		if (key == root->get_key() && root->get_right() == nullptr)
		{
			delete root;
			return nullptr;
		}
		if (!get_color(root->get_right()) && !get_color(root->get_right()->get_left()))
			root = move_right(root);
		if (key == root->get_key())
		{
			auto x = search_smallest(root->get_right());
			root->set_key(x->get_key());
			root->set_data(x->get_data());
			root->set_right(remove_smallest(root->get_right()));
		}
		else
			root->set_right(remove_node(root->get_right(), key));
	}
	return balance(root);
}

template<typename T> void tree<T>::remove(unsigned key)
{
	if (search(this->root, key))
	{
		this->root = remove_node(this->root, key);
		if (this->root != nullptr)
			this->root->set_color(BLACK);
	}
	else
		throw std::invalid_argument("Key does not exist");
}

template<typename T> const T tree<T>::operator[](const unsigned key) const
{
	return search_value(this->root, key);
}

template<typename T> tree<T>::~tree()
{
	delete this->root;
}
