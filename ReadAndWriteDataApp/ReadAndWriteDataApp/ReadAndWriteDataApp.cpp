// ReadAndWriteDataApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const char* PERSON_FORMAT_IN = "(%[^,], %[^,], %[^,], %[^,], %d, %d)\n";
const char* PERSON_FORMAT_OUT = "(%s, %s, %s, %s, %d, %d)\n";

const char* PERSON_FORMAT_IN1 = "(%s, %d)\n";
const char* PERSON_FORMAT_OUT1 = "(%s, %d)\n";

class session // The class
{
public: // Access specifier
    string name;
    string time;
    string duration;
    string directedBy;
    int cost;
    int count;
};

int main()
{
    session session, s1;  // Create an object of session

    // Access attributes and set values
    session.name = "Pulp Fiction";
    session.time = "Some text";
    session.duration = "154";
    session.directedBy = "Quentin Tarantino";
    session.cost = 10;
    session.count = 50;
    
    // Print attribute values
    cout << session.name << "\n";
    cout << session.time << "\n";
    cout << session.duration << "\n";
    cout << session.directedBy << "\n";
    cout << session.cost << "\n";
    cout << session.count << "\n";

    FILE* file;
    fopen_s(&file, "session.dat", "w+");
    if (file == nullptr)
    {
        return 1;
    }


    int    i = 10;
    double fp = 1.5;
    char   s[] = "some text";
    char   c = '\n';

    fprintf_s(file, "%s%c", s, c);
    fprintf_s(file, "%d\n", i);
    fprintf_s(file, "%f\n", fp);
    fclose(file);

    return 0;
	
    fprintf_s(file, PERSON_FORMAT_OUT1, session.name, session.cost);
    fseek(file, 0, SEEK_SET);

    fscanf_s(file, PERSON_FORMAT_IN1, s1.name, s1.cost);

	return 0;

    fprintf_s(file, PERSON_FORMAT_OUT, session.name, session.time, session.duration, session.directedBy, session.cost, session.count);
    fseek(file, 0, SEEK_SET);

    fscanf_s(file, PERSON_FORMAT_IN, session.name, session.time, session.duration, session.directedBy, &session.cost, &session.count);
	
    string input;
    cin >> input;
    ofstream out("output.txt");
    out << input;
    out.close();
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
