#include "node.hpp"

template<typename T> class tree
{
	private:
		node<T> *root;
		node<T> *__insert(node<T> *, T, unsigned);
		node<T> *rotate_left(node<T> *);
		node<T> *rotate_right(node<T> *);
		node<T> *move_left(node<T> *);
		node<T> *move_right(node<T> *);
		bool get_color(node<T> *);
		void switch_color(node<T> *);
	
	public:
		tree(T data, unsigned key);
		void insert(T data, unsigned key);
		~tree();
};

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
	node<T> *aux = root;
	this->switch_color(aux);
	if (this->get_color(aux->get_left()->get_right()))
	{
		aux->set_right(this->rotate_right(root->get_right()));
		aux = this->rotate_left(aux);
		this->switch_color(aux);
	}
	return aux;
}

template<typename T> node<T> *tree<T>::move_right(node<T> *root)
{
	node<T> *aux = root;
	switch_color(aux);
	if (this->get_color(aux->get_left()->get_left()))
	{
		aux = this->rotate_right(aux);
		this->switch_color(aux);
	}
	return aux;
}

template<typename T> node<T> *tree<T>::__insert(node<T> *root, T data, unsigned key)
{
	if (root == nullptr)
		return new node<T>(data, key);
	
	if (root->get_key() == key)
		root->insert(data);
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

template<typename T> tree<T>::~tree()
{
	delete this->root;
}
