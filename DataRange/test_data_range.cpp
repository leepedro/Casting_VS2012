#include <limits>
#include <iostream>

/* integer to floating, floating to integer

floating to integer casting shows some unexpected behaviors by setting the value as the
negative minimum value.
integer to floating casting seems working and the dynamic range of floating point data type
is practically wider than its integer counter part with the same memory size.

-> Use static_cast<T> without any value checking for integer to floating point casting.
-> Must check the value for floating point to integer casting.

@Example
if (static_cast<floating>(integer_max) < f) || (static_cast<floating>(integer_min) > f)
 throw std:overflow();
else
 return static_cast<integer>(f);

 */

void test1(void)
{
	int i_min(std::numeric_limits<int>::min()), i_max(std::numeric_limits<int>::max());
	float f_min(std::numeric_limits<float>::min()), f_max(std::numeric_limits<float>::max());
	float f_max_neg = -f_max;

	if (f_min > 0)
		std::cout << "f_min(=" << f_min << ") > 0 !!!" << std::endl;	// !!!! The minimum float value is POSITIVE!!!
	int int_f_min(static_cast<int>(f_min));		// == 0 !!!

	std::cout << "int: " << i_min << " ~ " << i_max << std::endl;
	std::cout << "float: " << f_max_neg << " ~ " << f_min << " ~ " << f_max << std::endl;

	float float_i_min(static_cast<float>(i_min));
	if (float_i_min > f_max_neg)
		std::cout << "float(i_min) > f_min" << std::endl;	// float is practically wider than int
	else
		std::cout << "float(i_min) < f_min" << std::endl;

	int int_f_max_neg(static_cast<int>(f_max_neg));
	if (i_min < int_f_max_neg)
		std::cout << "i_min < int(f_min)" << std::endl;	
	else if (i_min == int_f_max_neg)
		std::cout << "i_min == int(f_min)" << std::endl;	// saturated to min value instead of overflow
	else
		std::cout << "i_min > int(f_min)" << std::endl;

	float float_i_max(static_cast<float>(i_max));
	if (float_i_max < f_max)
		std::cout << "float(i_max) < f_max" << std::endl;	// float is practically wider than int
	else
		std::cout << "float(i_max) > f_max" << std::endl;

	int int_f_max(static_cast<int>(f_max));
	if (i_max > int_f_max)
		std::cout << "i_max > int(f_max)" << std::endl;		// Overflowed and saturated to a negative min value!!!
	else if (i_max == int_f_max)
		std::cout << "i_max == int(f_max)" << std::endl;
	else
		std::cout << "i_max < int(f_max)" << std::endl;	

	int int_float_i_max = static_cast<int>(static_cast<float>(i_max) + 1.0f);	// Overflowed and saturated to a negative min value!!!
}

void test2(void)
{
	long long l_min(std::numeric_limits<long long>::min()), l_max(std::numeric_limits<long long>::max());
	double d_min(std::numeric_limits<double>::min()), d_max(std::numeric_limits<double>::max());
	double d_max_neg = -d_max;

	if (d_min > 0)
		std::cout << "d_min > 0 !!!" << std::endl;	// !!!! The minimum double value is POSITIVE!!!

	std::cout << "long long: " << l_min << " ~ " << l_max << std::endl;
	std::cout << "double: " << d_max_neg << " ~ " << d_min << " ~ " << d_max << std::endl;

	double double_l_min(static_cast<double>(l_min));
	if (double_l_min > d_max_neg)
		std::cout << "double(l_min) > d_min" << std::endl;	// double is practically wider than long long
	else
		std::cout << "double(l_min) < d_min" << std::endl;

	long long long_d_max_neg(static_cast<long long>(d_max_neg));
	if (l_min < long_d_max_neg)
		std::cout << "l_min < long long(d_min)" << std::endl;	
	else if (l_min == long_d_max_neg)
		std::cout << "l_min == long long(d_min)" << std::endl;	// saturated to min value instead of overflow
	else
		std::cout << "l_min > long long(d_min)" << std::endl;

	double double_l_max(static_cast<double>(l_max));
	if (double_l_max < d_max)
		std::cout << "double(l_max) < d_max" << std::endl;	// double is practically wider than long long
	else
		std::cout << "double(l_max) > d_max" << std::endl;

	long long long_d_max(static_cast<long long>(d_max));
	if (l_max > long_d_max)
		std::cout << "l_max > long long(d_max)" << std::endl;		// Overflowed and saturated to a negative min value!!!
	else if (l_max == long_d_max)
		std::cout << "l_max == long long(d_max)" << std::endl;
	else
		std::cout << "l_max < long long(d_max)" << std::endl;	

	long long long_double_l_max = static_cast<long long>(static_cast<double>(l_max) + 1.0f);	// Overflowed and saturated to a negative min value!!!
}

int main(void)
{
	test1();
	test2();
	//int ll_min(std::numeric_limits<long long>::min()), ll_max(std::numeric_limits<long long>::max());
	//float f_min(std::numeric_limits<float>::min()), f_max(std::numeric_limits<float>::max());

}