
#include <stdexcept>
#include <iostream>

// 1) Negative risk only. (A & ~B)
// If an overflow is about to happen, throws an exception.
template <typename T, typename U>
typename std::enable_if<
	(std::is_signed<T>::value && std::is_unsigned<U>::value) &&
	!(std::is_integral<T>::value && std::is_integral<U>::value && ((sizeof(T) > sizeof(U)) || 
	(std::is_unsigned<T>::value && std::is_signed<U>::value && sizeof(T) == sizeof(U)))),
	void>::type SafeCast(const T src, U &dst)
{
	if (src < 0)
		throw std::overflow_error("Source value is negative.");
	else
		dst = static_cast<U>(src);
}

// 2) Positive risk only. (~A & B)
// If an overflow is about to happen, throws an exception.
template <typename T, typename U>
typename std::enable_if<
	!(std::is_signed<T>::value && std::is_unsigned<U>::value) &&
	(std::is_integral<T>::value && std::is_integral<U>::value && ((sizeof(T) > sizeof(U)) || 
	(std::is_unsigned<T>::value && std::is_signed<U>::value && sizeof(T) == sizeof(U)))),
	void>::type SafeCast(const T src, U &dst)
{
	if (src > static_cast<T>(std::numeric_limits<U>::max()))
		throw std::overflow_error("Source value is too high.");
	else
		dst = static_cast<U>(src);
}

// 3) Both negative and positive risks. (A & B)
// If an overflow is about to happen, throws an exception.
template <typename T, typename U>
typename std::enable_if<
	(std::is_signed<T>::value && std::is_unsigned<U>::value) &&
	(std::is_integral<T>::value && std::is_integral<U>::value && ((sizeof(T) > sizeof(U)) || 
	(std::is_unsigned<T>::value && std::is_signed<U>::value && sizeof(T) == sizeof(U)))),
	void>::type SafeCast(const T src, U &dst)
{
	if (src < 0)
		throw std::overflow_error("Source value is negative.");
	else if (src > static_cast<T>(std::numeric_limits<U>::max()))
		throw std::overflow_error("Source value is too high.");
	else
		dst = static_cast<U>(src);
}

// 4) No risk. (~A & ~B)
// If an overflow is about to happen, throws an exception.
template <typename T, typename U>
typename std::enable_if<
	!(std::is_signed<T>::value && std::is_unsigned<U>::value) &&
	!(std::is_integral<T>::value && std::is_integral<U>::value && ((sizeof(T) > sizeof(U)) || 
	(std::is_unsigned<T>::value && std::is_signed<U>::value && sizeof(T) == sizeof(U)))),
	void>::type SafeCast(const T src, U &dst)
{
	dst = static_cast<U>(src);
}

template <typename T, typename U>
void test_safe_cast(const T &src, U &dst)
{
	try
	{
		SafeCast(src, dst);
	}
	catch (const std::overflow_error &)
	{
		std::cout << "Overflow!" << std::endl;
	}
	catch (const std::exception &)
	{
		throw;
	}
}

void test1(void)
{
	int i_max(std::numeric_limits<int>::max()), i_neg(-1), i_small(1), i_dst;
	unsigned int ui_max(std::numeric_limits<unsigned int>::max()), ui_small(1), ui_dst;
	long long ll_max(std::numeric_limits<long long>::max()), ll_neg(-1), ll_small(1);
	unsigned long long ull_dst;
	float f_small(1.0), f_dst;
	double d_neg(-1.0), d_small(1.0), d_dst;

	// negative integer overflow risk.
	std::cout << std::endl;
	std::cout << "negative integer overflow risk" << std::endl;
	test_safe_cast(d_neg, ui_dst);		// Warning C4244, overflow detected.
	test_safe_cast(d_small, ui_dst);	// Warning C4244
	test_safe_cast(i_neg, ui_dst);		// overflow detected.
	test_safe_cast(i_small, ui_dst);

	// positive integer overflow risk.
	std::cout << std::endl;
	std::cout << "positive integer overflow risk" << std::endl;
	test_safe_cast(ll_max, i_dst);		// overflow detected.
	test_safe_cast(ll_small, i_dst);
	test_safe_cast(ui_max, i_dst);		// overflow detected.
	test_safe_cast(ui_small, i_dst);

	// both negative and positive
	std::cout << std::endl;
	std::cout << "both negative and positive integer overflow risk" << std::endl;
	test_safe_cast(ll_max, ui_dst);		// overflow detected.
	test_safe_cast(ll_neg, ui_dst);		// overflow detected.
	test_safe_cast(ll_small, ui_dst);

	// no risk
	std::cout << std::endl;
	std::cout << "no risk" << std::endl;
	test_safe_cast(ui_max, ull_dst);
	test_safe_cast(f_small, d_dst);
	test_safe_cast(d_small, f_dst);
}

int main(void)
{
	try
	{
		test1();
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}