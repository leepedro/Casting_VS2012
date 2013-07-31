#include <limits>
#include <iostream>

template <typename T, typename U>
typename std::enable_if<std::is_integral<T>::value && std::is_floating_point<U>::value, void>::type integer_vs_floating(void)
{
	int i_min(std::numeric_limits<T>::min()), i_max(std::numeric_limits<I>::max());
	float f_min(std::numeric_limits<U>::min()), f_max(std::numeric_limits<U>::max());

	std::cout << typeid(T).name() << ": " << i_min << " ~ " << i_max << std::endl;
	std::cout << typeid(U).name() << ": " << f_min << " ~ " << f_max << std::endl;

	if (static_cast<float>(i_min) < f_min)
		std::cout << "float(i_min) < f_min" << std::endl;
	if (i_min < static_cast<int>(f_min))
		std::cout << "i_min < int(f_min)" << std::endl;
	if (static_cast<float>(i_max) < f_max)
		std::cout << "float(i_max) < f_max" << std::endl;
	if (i_max <= static_cast<int>(f_max))	// NO!!! -> Do NOT cast float to int!
		std::cout << "i_max <= int(f_max)" << std::endl;
}

void test1(void)
{
	int i_min(std::numeric_limits<int>::min()), i_max(std::numeric_limits<int>::max());
	float f_min(std::numeric_limits<float>::min()), f_max(std::numeric_limits<float>::max());
	float f_max_neg = -f_max;

	if (f_min > 0)
		std::cout << "f_min > 0 !!!" << std::endl;	// !!!! The minimum float value is POSITIVE!!!

	std::cout << "int: " << i_min << " ~ " << i_max << std::endl;
	std::cout << "float: " << f_max_neg << " ~ " << f_min << " ~ " << f_max << std::endl;

	float float_i_min(static_cast<float>(i_min));
	if (float_i_min > f_max_neg)
		std::cout << "float(i_min) > f_min" << std::endl;

	if (static_cast<float>(i_min) < f_min)	// YES
		std::cout << "float(i_min) < f_min" << std::endl;
	if (i_min < static_cast<int>(f_min))	// YES
		std::cout << "i_min < int(f_min)" << std::endl;
	if (static_cast<float>(i_max) < f_max)	// YES
		std::cout << "float(i_max) < f_max" << std::endl;
	if (i_max <= static_cast<int>(f_max))	// NO!!! -> Do NOT cast float to int!
		std::cout << "i_max <= int(f_max)" << std::endl;
	int int_f_max = static_cast<int>(f_max);	// Overflowed to a negative value!!!

	int int_float_i_max = static_cast<int>(static_cast<float>(i_max) + 1.0f);	// Overflowed to a negative value!!!
}

int main(void)
{
	test1();
	//int ll_min(std::numeric_limits<long long>::min()), ll_max(std::numeric_limits<long long>::max());
	//float f_min(std::numeric_limits<float>::min()), f_max(std::numeric_limits<float>::max());

}