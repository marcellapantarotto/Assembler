#include <iostream>
#include <fstream>
#include <string>

using namespace std;


ifstream read_input_file(string filePath){
    string line;
    ifstream myfile(filePath);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            cout << line << '\n';
        }
    }

    else
        cout << "Unable to open file";

    return myfile;
}


int main()
{
    read_input_file("examples/bin.asm");

    return 0;
}