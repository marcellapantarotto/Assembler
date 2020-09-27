#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

ifstream read_input_file(string filePath);
void input_format();
void preprocess();

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Input with the wrong amount of parameters!" << endl;
        input_format();
        return 1;
    }
    else if (strncmp(argv[1], "-p", 2) == 0)
    {
        preprocess();
    }
    else if (strncmp(argv[1], "-o", 2) == 0)
    {
        cout << "-o" << endl;
    }
    else
    {
        cout << "Wrong type of input parameters!" << endl;
        input_format();
        return 1;
    }

    // read_input_file("examples/bin.asm");

    return 0;
}

void input_format()
{
    cout << "\nRight input format:" << endl;
    cout << "./montador -p assemble_program.asm \n   or\n./montador -o preprocess_file.pre" << endl;
}

ifstream read_input_file(string filePath)
{
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

void preprocess(){
    cout << "Preprocessing file!" << endl;
}