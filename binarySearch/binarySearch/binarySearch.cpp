#include <iostream>
#include <vector>


// Binary Search can find element in ONLY SORTED array, 
// Algorithm complexity = O(log n)
int _bsearch(std::vector<int> numbers, int value)
{
	int size = numbers.size();
	int low = 0;
	int high = size - 1; // last el = 9, cause arr start from 0

	// while there is an area in which you can search
	while (low <= high) {
		
		int mid = (low + high) / 2; // finding mid in arr

		if (value == numbers[mid]) 
		{
			std::cout << "Value " << value << " is located in indedex " << mid << std::endl;
			return 0;
		}
		else if (value > numbers[mid]) 
		{
			low = mid + 1;
		}
		else 
		{
			high = mid - 1;
		}
	}
	return 1;
}

int main() 
{
	std::vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	_bsearch(numbers, 3);

	system("pause"); return 0;
}