/**
*
* Solution to homework task 3
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* 2018/2019 academic year
*
* @author Nikola Totev
* @idnumber 62271
* @task 3
* @compiler VC
*
*/

#include <iostream>
const int MAX_LENGTH = 200;
int main()
{
	char sentence[MAX_LENGTH];
	std::cin.get(sentence, MAX_LENGTH);
	int sentenceLength = strlen(sentence)+1;
	int counter = 1;
	if(sentence[0] == ' ' || sentence[0] == 0 || sentence[0] == '\t')
	{
		counter = 0;
	}
	for (int i = 0; i < sentenceLength; ++i)
	{
		if (sentence[i] == ' ' || sentence[i] == 0 || sentence[i] == '\t')
		{
			if((sentence[i+1]!= ' ' && sentence[i+1]!= 0 && sentence[i+1]!='\t') && (i+1) < sentenceLength)
			{
				counter++;
			}			
		}

	}

	std::cout << "This sentence has " << counter << " words in it.";
}

