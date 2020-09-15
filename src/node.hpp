#include <vector>
#define RED true
#define BLACK false

template <typename T> class node
{
	private:
		T data;
		unsigned key;
		bool color;
		node *left;
		node *right;

	public:
		node(T data, unsigned key);
		unsigned get_key();
		void set_key(unsigned);
		bool get_color();
		void set_color(bool);
		T get_data();
		void set_data(const T &);
		node *get_right();
		node *get_left();
		void insert(T);
		void set_right(node<T> *);
		void set_left(node<T> *);
		~node();
};

template <typename T> node<T>::node(T data, unsigned key)
{
	this->data = data;
	this->key = key;
	this->color = RED;
	this->left = nullptr;
	this->right = nullptr;
}

template<typename T> inline unsigned node<T>::get_key()
{
	return this->key;
}

template<typename T> inline void node<T>::set_key(unsigned key)
{
	this->key = key;
}

template<typename T> inline bool node<T>::get_color()
{
	return this->color;
}

template<typename T> inline void node<T>::set_color(bool color)
{
	this->color = color;
}

template<typename T> inline T node<T>::get_data()
{
	return this->data;
}

template<typename T> inline void node<T>::set_data(const T &data)
{
	this->data = data;
}

template <typename T> inline node<T>* node<T>::get_right()
{
	return this->right;
}

template <typename T> inline node<T>* node<T>::get_left()
{
	return this->left;
}

template <typename T> inline void node<T>::set_right(node<T> *n)
{
	this->right = n;
}

template <typename T> inline void node<T>::set_left(node<T> *n)
{
	this->left = n;
}

template<typename T> inline void node<T>::insert(T data)
{
	this->data.emplace_back(data);
}

template <typename T> node<T>::~node()
{
	if (this->right != nullptr)
		delete this->right;
	if (this->left != nullptr)
		delete this->left;
}
