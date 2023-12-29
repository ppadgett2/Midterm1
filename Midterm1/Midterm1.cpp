// Author: Parker Padgett
// Assignment: Midterm Project
// Description: Using vectors or arrays, read in an unknown number of movies, years, and gross totals
//				from input files, remove <html> tags from the movie names, sort the data based on 
//				box office gross from highest to lowest, and use functions to do this. 
// Date: 3/2/2022


#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <cctype>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

// Constants
const int ARRAY_SIZE = 50;

// Function Declaration
void inputCheck(ifstream& iFile);
int getData(ifstream& iFile, ifstream& jFile, ifstream& kFile, vector<string>& vecm, vector<int>& vecy, vector<double>& vecg);
void htmlCheck(vector<string>& movieName, int counter);
void sortData(vector<string>& movieName, vector<int>& year, vector<double>& gross, int counter);
void output(vector<string>& movieName, vector<int>& year, vector<double>& gross);


int main()
{
	// Variable declaration
	ifstream mFile, yFile, gFile;
	int counter = 0;
	vector<string> movieName;
	vector<int> year;
	vector<double> gross;


	// Open input files
	mFile.open("movie.txt");
	yFile.open("year.txt");
	gFile.open("gross.txt");


	// Check to see if the input files were found
	inputCheck(mFile);
	inputCheck(yFile);
	inputCheck(gFile);


	// Get data from input files and store them into vectors
	counter = getData(mFile, yFile, gFile, movieName, year, gross);


	// Remove all html tags from movie names
	htmlCheck(movieName, counter);


	// Sort all data based on gross from highest to lowest
	sortData(movieName, year, gross, counter);


	// Output sorted data to the screen
	output(movieName, year, gross);


	// Close input files
	mFile.close();
	yFile.close();
	gFile.close();

	return 0;
}

// Functions
void inputCheck(ifstream& iFile)
{
	if (!iFile.is_open())
	{
		cout << "Input file not found";
		exit(1);
	}
}

int getData(ifstream& iFile, ifstream& jFile, ifstream& kFile, vector<string>& vecm, vector<int>& vecy, vector<double>& vecg)
{
	int counter = 0;
	string text;
	double num;

	while (!iFile.eof())
	{
		getline(iFile, text);
		vecm.push_back(text);

		while (jFile >> num)
		{
			vecy.push_back(num);
		}

		while (kFile >> num)
		{
			vecg.push_back(num);
		}

		counter++;
	}
	return counter;
}

void htmlCheck(vector<string>& movieName, int counter)
{
	for (int i = 0; i < counter; i++)
	{
		string temp = movieName[i];
		for (int a = 0; a < temp.length(); a++)
		{
			if (temp[a] == '<')
			{
				for (int b = a + 1; b < temp.length(); b++)
				{
					if (temp[b] == '>')
					{
						temp.erase(a, b - a + 1);
						movieName[i] = temp;
						a = 0;
						break;
					}
				}
			}
		}
	}
}

void sortData(vector<string>& movieName, vector<int>& year, vector<double>& gross, int counter)
{
	string tempM;
	int tempY;
	double tempG;

	for (int a = 0; a < counter; a++)
	{
		for (int b = a + 1; b < counter; b++)
		{
			if (year[b] > year[a])
			{
				tempM = movieName[a];
				movieName[a] = movieName[b];
				movieName[b] = tempM;

				tempY = year[a];
				year[a] = year[b];
				year[b] = tempY;

				tempG = gross[a];
				gross[a] = gross[b];
				gross[b] = tempG;

				a = 0;
			}
		}
	}
}

void output(vector<string>& movieName, vector<int>& year, vector<double>& gross)
{
	for (int i = 0; i < movieName.size(); i++)
	{
		cout << "Movie: " << movieName[i] << endl;
		cout << "Year: " << year[i] << endl;
		cout << "Gross: " << gross[i] << endl << endl;
	}
}