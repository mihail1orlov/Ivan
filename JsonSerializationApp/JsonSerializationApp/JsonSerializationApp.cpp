// JsonSerializationApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    std::cout << "Hello World!\n";
    std::ofstream file;
	file.open("example.txt");
	file << "Writing this to a file.0000\n";
	file << "Writing this to a file.1111\n";
	file << "Writing this to a file.2222\n";
	file << "Writing this to a file.3333\n";
	file << "Writing this to a file.4444\n";
    file.close();

    string line;
    ifstream myfile("example.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            cout << line << '\n';
        }
        myfile.close();
    }
    else {
        cout << "Unable to open file";
    }
	
	file.close();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
