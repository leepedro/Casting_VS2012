#include <limits>
#include <iostream>

int main(void)
{
	int i_min(std::numeric_limits<int>::min()), i_max(std::numeric_limits<int>::max());
	float f_min(std::numeric_limits<float>::min()), f_max(std::numeric_limits<float>::max());

	std::cout << "int: " << i_min << " ~ " << i_max << std::endl;
	std::cout << "float: " << f_min << " ~ " << f_max << std::endl;

	if (static_cast<float>(i_min) < f_min)	// YES
		std::cout << "float(i_min) < f_min" << std::endl;
	if (i_min < static_cast<int>(f_min))	// YES
		std::cout << "i_min < int(f_min)" << std::endl;
	if (static_cast<float>(i_max) < f_max)	// YES
		std::cout << "float(i_max) < f_max" << std::endl;
	if (i_max <= static_cast<int>(f_max))	// NO!!! -> Do NOT cast float to int!
		std::cout << "i_max <= int(f_max)" << std::endl;
	int int_f_max = static_cast<int>(f_max);	// Overflowed to a negative value!!!
}