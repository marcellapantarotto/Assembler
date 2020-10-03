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
void change_extension(string fileName, string option);
void print_tokens();
void clean_tokens();
void preprocess(string fileName, string action);
void assemble(string fileName, string action);

vector<string> tokens; // declaring vector of tokens
vector<string> tokens_after_clean; // declaring vector of tokens
// vector<int>::iterator it = tokens.begin(); // declaring an iterator
auto iter = tokens.begin();

class operation
{
public:
    operation(/* args */);
    ~operation();
    string mnemonic;
    int num_operators;
    int code;
    int size;
    bool is_instruction;
};

operation::operation(/* args */)
{
}

operation::~operation()
{
}

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
        preprocess(argv[2], argv[1]);
        read_input_file(argv[2], ' ');
        clean_tokens();
        cout << "\nafter clean\n" << endl;
        print_tokens();
    }
    else if (strncmp(argv[1], "-o", 2) == 0)
    {
        assemble(argv[2], argv[1]);
        read_input_file(argv[2], ' ');
    }
    else
    {
        cout << "Wrong type of input parameters!" << endl;
        input_format();
        return 1;
    }

    // print_tokens();
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
            tokens.push_back(token);

        myfile.close();
    }
    else
        cout << "Unable to open file" << endl;
}

void print_tokens()
{
    cout << "\n----- TOKENS: -----\n"
         << endl;
    // for (auto i : tokens)
    //     cout << i << endl; // this will print all the tokens of the program

    // another print way
    for (iter = tokens_after_clean.begin(); iter != tokens_after_clean.end(); ++iter)
        cout << *iter << endl;
}

void clean_tokens()
{   // Accessing the elements using iterators
    for (iter = tokens.begin(); iter != tokens.end(); ++iter)
    {
        string str = *iter;
        int index = str.length() - 1;
        // cout << *iter << " ";
        if (str.back() == ':')
            str.replace(index, 1, "");
        if (str.back() == ',')
            str.replace(index, 1, "");
        tokens_after_clean.push_back(str);
    }
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

void change_extension(string fileName, string option)
{
    ofstream outFile;      // object for writing to a file
    string str = fileName; // aux string
    int fileLength = str.length();
    int index = fileLength - 4;

    if (option == "-p")
        str.replace(index, 4, ".pre");
    if (option == "-o")
        str.replace(index, 4, ".obj");

    outFile.open(str);
}

void preprocess(string fileName, string action)
{
    cout << "Preprocessing file!\n"
         << endl;

    change_extension(fileName, action); // extension .pre
}

void assemble(string fileName, string action)
{
    cout << "Assembling file!\n"
         << endl;

    change_extension(fileName, action); // extension .obj
}