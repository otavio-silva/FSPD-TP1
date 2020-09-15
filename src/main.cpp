#include "tree.hpp"
#include <iostream>

int main([[maybe_unused]] int argc, [[maybe_unused]] char const *argv[])
{
	auto t = tree<int>(1, 1);
	t.insert(0, 0);
	t.insert(2, 2);
	t.insert(3, 3);
	t.insert(4, 4);
	t.insert(5, 5);
	t.remove(3);
	t.remove(4);
	std::cout << t[1] << '\n';
	std::cout << t[2] << '\n';
	return 0;
}
