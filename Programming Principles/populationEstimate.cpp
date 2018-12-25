// This Program converts a number from 1 to 10
// into its roman numeral equivalent

// Ben Sebring


/*#include <iostream>
#include <string>
using namespace std;

// function prototypes

float validatePop();
float validatePerc();
int validateDays();
void calcPop(float, float, int);


int main()
{
	float population = validatePop();
	float percentage = validatePerc();
	int days = validateDays();
	calcPop(population, percentage, days);
	system("pause");
	return 0;
}

void calcPop(float population, float percent, int days)
{
	float newPop, addition;
	for (int i = 1; i <= days; i++)
	{
		addition = population * percent;
		newPop = population + addition;
		population = newPop;
		cout << "On day " << i+1 << " the population size was " << population << endl;
	}
}

// validation functions definition
// used to validate input
float validatePop()
{
	float population;
	cout << "Enter the starting number of organisms: ";
	cin >> population;
	while (population < 2)
	{
		cout << "\nThe starting number of organisms must be at least 2.\n";
		cout << "\nEnter the starting number of organisms: ";
		cin >> population;
	}
	return population;
}

float validatePerc()
{
	float percent;
	cout << "Enter the average daily population increase (as a percentage): ";
	cin >> percent;
	while (percent <= 0)
	{
		cout << "\nThe average daily population increase must be a positive value.\n";
		cout << "\nEnter the average daily population increase (as a percentage): ";
		cin >> percent;
	}
	return percent;
}


int validateDays()
{
	int days;
	cout << "\nEnter the number of days they will multiply: ";
	cin >> days;
	while (days < 1)
	{
		cout << "\nThe number of days must be at least 1.\n";
		cout << "\nEnter the number of days they will multiply: ";
		cin >> days;
	}
	return days;
}*/