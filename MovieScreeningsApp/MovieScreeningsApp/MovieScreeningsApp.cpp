// JsonSerializationApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <utility>
using namespace std;


namespace model {

    struct session {
        std::string name;
        std::string time;
        std::string duration;
        std::string directedBy;
        int cost = 0;
        int count = 0;

        bool operator==(const session& session) const {
            return name == session.name
                && time == session.time
                && duration == session.duration
                && directedBy == session.directedBy
                && cost == session.cost
                && count == session.count;
        }

        string to_string() const
        {
            return name + "," + time + "," + duration + "," + directedBy + "," + std::to_string(cost) + "," + std::to_string(count);
        }

        void init(const string& name, const string& time, const string& duration, const string& directedBy, int cost, int count)
        {
            this->name = name;
            this->time = time;
            this->duration = duration;
            this->directedBy = directedBy;
            this->cost = cost;
            this->count = count;
        }

        void init(string str)
        {
            string items[6];
            for (size_t i = 0, j = 0, start = 0, end = 0; i < str.length(); i++)
            {
                if (i + 1 == str.length() || str[i + 1] == ',')
                {
                    end = i + 1;
                    items[j] = str.substr(start, end - start);
                    start = end + 1;
                    j++;
                }
                std::cout << str[i];
            }

            init(items[0], items[1], items[2], items[3], std::stoi(items[4]), std::stoi(items[5]));
        }
    };

}



int main()
{
    std::cout << "Hello World!\n";

	string str = "Pulp Fiction,Some text,154,Quentin Tarantino,10,50";

	model::session session;
    //session.init("Pulp Fiction", "Some text", "154", "Quentin Tarantino", 10, 50);
    session.init("Pulp Fiction,Some text,154,Quentin Tarantino,10,50");

    std::ofstream file;
    file.open("example.txt");
    file << session.to_string();
    file.close();

    string line;
    ifstream stream("example.txt");
    if (stream.is_open())
    {
        while (getline(stream, line))
        {
            cout << line << '\n';
        }
        stream.close();
    }
    else {
        cout << "Unable to open file";
    }

    file.close();
}

// Run program: Ctrl + "," + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
