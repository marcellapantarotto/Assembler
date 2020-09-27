#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

void input_format();
string read_input_file(string filePath, string data);
void write_output_file(string inputFilePath, string outputFilePath);
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

    string data;
    read_input_file("examples/bin.asm", data);
    cout << data << endl;
    
    write_output_file("examples/bin.asm", "output.txt");

    return 0;
}

void input_format()
{
    cout << "\nRight input format:" << endl;
    cout << "./montador -p assemble_program.asm \n   or\n./montador -o preprocess_file.pre" << endl;
}

string read_input_file(string filePath, string data)
{
    string line;
    ifstream myfile(filePath);

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {

            // cout << line << endl;
            data += line;
        }
    }
    else
        cout << "Unable to open file";

    return data;
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
        cout << "Unable to open file";
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