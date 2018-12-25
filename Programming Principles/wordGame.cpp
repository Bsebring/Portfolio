//// This Program tells a story based on what the user 
//// inputs for choices
//
//// Ben Sebring
//
//
//#include <iostream>
//#include <string>
//using namespace std;
//
//// function prototype
//string wordGame(string, string, string, string, string, string, string);
//
//int main()
//{
//	// declaring necessary variables
//	string name, city, age, college, profession, animal, animalName;
//	
//	// collecting the data for the game
//	cout << "Please enter the following and I will tell a story!\n\n";
//	cout << "Name: ";
//	getline(cin, name);
//	cout << "\nCity: ";
//	getline(cin, city);
//	cout << "\nAge: ";
//	getline(cin, age);
//	cout << "\nCollege: ";
//	getline(cin, college);
//	cout << "\nProffesion: ";
//	getline(cin, profession);
//	cout << "\nAnimal: ";
//	getline(cin, animal);
//	cout << "\nPet Name: ";
//	getline(cin, animalName);
//
//	// calling the wordGame function
//	cout << "\n\n" << wordGame(name, city, age, college, profession, animal, animalName);
//
//	return 0;
//}
//
//// wordGame function
//string wordGame(string name, string city, string age, string college, string profession, string animal, string petName)
//{
//	string story = "There once was a person named " + name + " who lived in " + city + ".\nAt The age of " +
//		age + ", " + name + " went to college at " + college + ".\n" + name + " graduated and went to work as a " + 
//		profession + ".\nThen, " + name + " adopted a(n) " + animal + " named " + petName + 
//		".\nThey both lived happily ever after!\n\n";
//	return story;
//}
