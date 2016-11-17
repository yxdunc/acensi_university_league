#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>


int main()
{
    double n;

    std::cin>>n;
    if (n > 4)
        std::cout << 8.0;
    else
        std::cout << n * 2.0;

	return (0);
}
