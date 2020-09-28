#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <iomanip>

using namespace std;
const int size = 100;

void input_format();
void read_input_file(string filePath, char delim);
void write_output_file(string inputFilePath, string outputFilePath);
void preprocess();
void assemble();

vector<vector<string>> program(size);


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

    read_input_file(argv[2], ' ');
    // write_output_file("examples/bin.asm", "output.txt");

    return 0;
}

void input_format()
{
    cout << "\nRight input format:" << endl;
    cout << "./montador -p assemble_program.asm \n   or\n./montador -o preprocess_file.pre" << endl;
}

void read_input_file(string filePath, char delim = ' ')
{
    ifstream myfile(filePath);
    string token;
    vector<string> instLine;
    vector<vector<string>> codeLine;

    if (myfile.is_open())
    {
        while (getline(myfile, token, delim))
        {
            cout << token << endl;
            instLine.push_back(token);
        }
        codeLine.push_back(instLine);
        myfile.close();
    }
    else
        cout << "Unable to open file" << endl;

    // cout << "\n==== INSTRUCTION LINE:\n" << endl;
    // for (auto i : instLine)
    //     cout << i << endl; // this will print all the contents of instruction line

    // cout << "" << endl;
    // cout << "==== CODE LINE:\n" << endl;
    // for (auto line : codeLine)
    //     for (auto i : line)
    //     cout << i << endl; // this will print all the contents of code line
}

void write_output_file(string inputFilePath, string outputFilePath)
{
    ifstream inputFile(inputFilePath);
    ofstream outputFile(outputFilePath);
    string line;

    if (outputFile.is_open())
    {
        while (getline(inputFile, line))
        {
            outputFile << line << endl;
        }

        outputFile.close();
    }
    else
        cout << "Unable to open file" << endl;
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