/**
*
* Solution to homework task 1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* 2018/2019 academic year
*
* @author Nikola Totev
* @idnumber 62271
* @task 1
* @compiler VC
*
*/


#include <iostream>

const int LIMIT = 65000;

int* separateNumbers(int input)
{
	std::cout << "INPUT IS " << input<< std::endl;
	if (input > -LIMIT && input < LIMIT)
	{
		int numberOfDigits = 0;
		for (int temp = abs(input); temp >= 1;)
		{
			temp /= 10;
			numberOfDigits++;
		}

		int* numbers = new int[numberOfDigits + 1];
		numbers[0] = numberOfDigits;
		int counter = 1;
		for (int temp = abs(input); temp >= 1;)
		{

			numbers[counter] = (temp % 10);
			temp /= 10;
			counter++;
		}
		return numbers + 1;
	}

	std::cout << "Invalid input!" << std::endl;
	return nullptr;
}

int main()
{
	int number;
	std::cin >> number;
	if(std::cin.fail())
	{
		std::cout << "INVALID INPUT!" << std::endl;
		return 0;
	}
	const int INITIAL_MAX = 2;
	int current_max = INITIAL_MAX;
	int maxAdvance = 100;
	int* inputs = new int[INITIAL_MAX];
	int counter = 1;
	inputs[0] = number;
	

	

	while (number > -LIMIT && number < LIMIT)
	{
		if(counter == current_max)
		{
			current_max += maxAdvance;
			int* temp = new int[current_max];
			for (int i = 0; i < counter; ++i)
			{
				temp[i] = inputs[i];
			}
			delete[] inputs;
			inputs = temp;
		}

		std::cin >> number;

		if(std::cin.fail())
		{
			std::cout << "INVALID INPUT!" << std::endl;
			return 0;
		}

		if(number > -LIMIT && number < LIMIT)
		{
		 inputs[counter] = number;
		 counter++;
		}
	}

	std::cout << inputs[0] << std::endl;
	for (int i = 0; i < counter; ++i)
	{

		int* num = separateNumbers(inputs[i]);
		for (int i = 0; i < *(num - 1); ++i)
		{
			std::cout << num[i] << " ";
		}
		delete[](num - 1);

		std::cout << std::endl;		
		std::cout << std::endl;		
	}

	delete[] inputs;
}


