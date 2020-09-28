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
void print_tokens();
void preprocess(string fileName);
void assemble();

vector<string> tokens;

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
        preprocess(argv[2]);
        read_input_file(argv[2], ' ');
    }
    else if (strncmp(argv[1], "-o", 2) == 0)
    {
        assemble();
        read_input_file(argv[2], ' ');
    }
    else
    {
        cout << "Wrong type of input parameters!" << endl;
        input_format();
        return 1;
    }

    print_tokens();
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

    if (myfile.is_open())
    {
        while (getline(myfile, token, delim))
        {
            tokens.push_back(token);
        }
        myfile.close();
    }
    else
        cout << "Unable to open file" << endl;
}

void print_tokens()
{
    cout << "\n----- TOKENS: -----\n"
         << endl;
    for (auto i : tokens)
        cout << i << endl; // this will print all the tokens of the program
}

void write_output_file(string inputFilePath, string outputFilePath)
{
    ifstream inputFile(inputFilePath);
    ofstream outputFile(outputFilePath);
    string line;

    if (outputFile.is_open())
    {
        while (getline(inputFile, line))
            outputFile << line << endl;

        outputFile.close();
    }
    else
        cout << "Unable to open file" << endl;
}

void preprocess(string fileName)
{
    // pass file to extension .pre
    cout << "Preprocessing file!\n"
         << endl;

    ifstream inFile;  // object for reading from a file
    ofstream outFile; // object for writing to a file

    // inFile.open(fileName + ".asm");

    string str = fileName; // "this is a test string."
    str.replace(8, 4, ".pre");

    // outFile.open(fileName + ".pre");
    outFile.open(str);
}

void assemble()
{
    // pass file to extension .obj
    cout << "Assembling file!\n"
         << endl;
}