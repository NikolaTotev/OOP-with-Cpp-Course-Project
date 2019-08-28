/**
*
* Solution to homework task 2
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* 2018/2019 academic year
*
* @author Nikola Totev
* @idnumber 62271
* @task 2
* @compiler VC
*
*/


#include <iostream>

bool leapYearCheck(int year)
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			return (year % 400) != 0;
		}
		return false;
	}
	return false;
}

int main()
{
	const int MAX_DATE_LEN = 11;
	char date[MAX_DATE_LEN];
	std::cin.get(date, MAX_DATE_LEN);
	int daysInMonthNormal[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int daysInMonthLeap[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	int dateLength = strlen(date);
	int day = 0;
	int month = 0;
	int year = 0;


	if (date[0] != '0')
	{
		day = date[0] - '0';
	}

	int dayEnd = 0;
	int monthEnd = 0;
	int yearLength = 0;
	int counter = 0;
	for (int i = 0; i < dateLength; ++i)
	{
		if (date[i] == '.')
		{
			switch (counter)
			{
			case 0:
				dayEnd = i;
				break;
			case 1:
				monthEnd = i;
				break;
			}
			counter++;
		}
	}

	yearLength = dateLength - monthEnd - 1;

	for (int i = 0; i <= 3; i++)
	{
		switch (i)
		{
		case 1:
			if (dayEnd == 2)
			{
				day = (date[0] - '0') * 10 + date[1] - '0';

			}
			else
			{
				day = date[0] - '0';
			}
			break;

		case 2:
			switch (monthEnd)
			{

			case 3:


				month = date[2] - '0';
				break;
			case 4:
				if (dayEnd == 2)
				{
					month = date[3] - '0';

				}
				else if (dayEnd == 1)
				{
					month = 10 * (date[2] - '0') + date[3] - '0';
				}
				break;
			case 5:
				month = 10 * (date[3] - '0') + date[4] - '0';
				break;

			}
			break;
		case 3:
			switch (yearLength)
			{
			case 1:
				year = (date[monthEnd + 1] - '0');
				break;
			case 2:
				year = (date[monthEnd + 1] - '0') * 10 + (date[monthEnd + 2] - '0');
				break;
			case 3:
				year = (date[monthEnd + 1] - '0') * 100 + (date[monthEnd + 2] - '0') * 10 + (date[monthEnd + 3] - '0');
				break;
			case 4:
				year = (date[monthEnd + 1] - '0') * 1000 + (date[monthEnd + 2] - '0') * 100 + (date[monthEnd + 3] - '0') * 10 + (date[monthEnd + 4] - '0');
				break;
			}
			break;


		}
	}

	if (day < 1 || day > 31 || month > 12 || month < 1)
	{
		std::cout << "Invalid date!" << std::endl;
		return 0;
	}

	bool isLeapYear = leapYearCheck(year);

	int yearsFromStart = year - 1;

	int daysInYearsFromStart = 0;
	for (int i = 0; i < year - 1; ++i)
	{
		if (!leapYearCheck(i))
		{
			daysInYearsFromStart += 365;
		}
		else
		{
			daysInYearsFromStart += 366;
		}
	}

	int daysFromCurrentYear = day;


	for (int i = 0; i < month - 1; i++)
	{
		if (!isLeapYear)
		{
			daysFromCurrentYear += daysInMonthNormal[i];
		}
		else
		{
			daysFromCurrentYear += daysInMonthLeap[i];
		}
	}

	int totalDays = daysFromCurrentYear + daysInYearsFromStart;


	std::cout << "From 01.01.01 to " << day<<"."<<month  <<"."<<year<< " there are " << totalDays <<" days"<< std::endl;
	return 0;
}

