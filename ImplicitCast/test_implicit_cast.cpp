#include <stdexcept>
#include <iostream>
#include <limits>

void test(void)
{
	// 2147483647 as maximum int value
	long long l1 = std::numeric_limits<int>::max();

	// -2147483648 -> RHS is considered as int, so it is overflowed.
	long long l2 = std::numeric_limits<int>::max() + 1;

	// -2147483648 -> Inside of () in RHS is considered as int, so it is already overflowed in prior to static_cast<>.
	long long l3 = static_cast<long long>(std::numeric_limits<int>::max() + 1);

	// 2147483648 -> We have to cast each member to the widest data type.
	long long l4 = static_cast<long long>(std::numeric_limits<int>::max()) + 1;
}

int main(void)
{
	try
	{
		test();
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}