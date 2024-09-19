#include <iostream>
#include "List.h"
using namespace std;


int main()
{
    List<double> list1;

	for (double i = 1.1; i < 10; i+= 1.1)
	{
		list1.PushBack(i);
	}

	list1.Show();
    return 0;
}

