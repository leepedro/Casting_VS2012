#include <stdexcept>
#include <iostream>
#include <limits>

void test(void)
{
	int int_max = std::numeric_limits<int>::max();

	// 2147483647 as maximum int value
	long long l1 = int_max;

	// -2147483648 -> RHS is considered as int, so it is overflowed.
	long long l2 = int_max + 1;

	// -2147483648 -> Inside of () in RHS is considered as int, so it is already overflowed in prior to static_cast<>.
	long long l3 = static_cast<long long>(int_max + 1);

	// 2147483648 -> We have to cast each member to the widest data type.
	long long l4 = static_cast<long long>(int_max) + 1;

	// 4294967295
	long long l5 = std::numeric_limits<unsigned int>::max();
}

void ImplicitVsExplicit(void)
{
	int int_max = std::numeric_limits<int>::max();
	long long long_zero = 0, long_1 = int_max + 1;

	// widening conversion: safe implicit casting without warning.
	long long l1 = int_max;
	long long l2(int_max);

	// narrowing conversion: implicit casting with warning.
	int i1 = long_zero;	// warning C4244
	int i2 = long_1;	// warning C4244 + overflow

	// narrowing conversion: explicit casting without warning.
	int i3 = static_cast<int>(long_zero);	// Risky?
	int i4 = static_cast<int>(long_1);		// OVERFLOW WITHOUT WARNING! BAD! BAD! BAD!

	/* Suggestion:
	If you know what data value is coming for sure, you may take a risk by explicitly casting down.
	However, if you are not sure, then do NOT use explicit casting for narrowing conversion. */
}

int main(void)
{
	try
	{
		test();
		ImplicitVsExplicit();
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}