#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

ifstream read_input_file(string filePath);
void input_format();

int main(int argc, char *argv[])
{

    // cout << "You have entered " << argc << " arguments:"
    //      << "\n";

    // for (int i = 0; i < argc; ++i)
    //     cout << argv[i] << "\n";

    // cout << "\n";

    if (argc != 3)
    {
        cout << "Input with the wrong amount of parameters!\n";
        input_format();
        return 1;
    }
    else if (strncmp(argv[1], "-p", 2) == 0)
    {
        cout << "-p\n";
    }
    else if (strncmp(argv[1], "-o", 2) == 0)
    {
        cout << "-o\n";
    }
    else
    {
        cout << "else\n";
    }

    // read_input_file("examples/bin.asm");

    return 0;
}

void input_format(){
    cout << "\nRight input format:" << endl;
    cout << "./montador -p assemble_program.asm \n   or\n./montador -o preprocess_file.pre\n";
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
