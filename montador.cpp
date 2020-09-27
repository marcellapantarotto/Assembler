#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

void input_format();
ifstream read_input_file(string filePath);
ofstream write_output_file(string inputFilePath, string outputFilePath);
void preprocess();
void assemble();

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
        assemble();
    }
    else
    {
        cout << "Wrong type of input parameters!" << endl;
        input_format();
        return 1;
    }

    // read_input_file("examples/bin.asm");
    write_output_file("examples/bin.asm", "output.txt");

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
            cout << line << endl;
        }
    }
    else
        cout << "Unable to open file";

    return myfile;
}

ofstream write_output_file(string inputFilePath, string outputFilePath)
{
    ofstream outputFile(outputFilePath);
    string line;
    ifstream inputFile(inputFilePath);

    if (outputFile.is_open())
    {
        while (getline(inputFile, line))
        {
            // cout << line << endl;
            outputFile << line << endl;
        }

        outputFile.close();
    }
    else
        cout << "Unable to open file";

    return outputFile;
}

void preprocess()
{
    // pass file to extension .pre
    cout << "Preprocessing file!" << endl;
}

void assemble()
{
    // pass file to extension .obj
    cout << "Assembling file!" << endl;
}