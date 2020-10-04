#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <iomanip>

using namespace std;
const int size = 100;

void inputFormat();
void readInputFile(string filePath, char delim);
void writeOutputFile(string inputFilePath, string outputFilePath);
void changeExtension(string fileName, string option);
void printTokens();
void cleanTokens();
void preprocess(string fileName, string action);
void assemble(string fileName, string action);

vector<string> tokens;             // input tokens
vector<string> tokens_after_clean; // tokens without special caracters
auto iter = tokens.begin();        // iterator
// auto iter = tokens_after_clean.begin();        // iterator

class Instruction
{
public:
    Instruction(string mnemonic, string opcode, int operands, int length);
    ~Instruction();

    string mnemonic, opcode;
    int operands, length;
};

Instruction::Instruction(string mnemonic, string opcode, int operands, int length)
{
    this->mnemonic = mnemonic;
    this->opcode = opcode;
    this->operands = operands;
    this->length = length;
}

Instruction::~Instruction()
{
}


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Input with the wrong amount of parameters!" << endl;
        inputFormat();
        return 1;
    }
    else if (strncmp(argv[1], "-p", 2) == 0)
    {
        preprocess(argv[2], argv[1]);
        readInputFile(argv[2], ' ');
        cleanTokens();
        cout << "\nafter clean\n"
             << endl;
        printTokens();
    }
    else if (strncmp(argv[1], "-o", 2) == 0)
    {
        assemble(argv[2], argv[1]);
        readInputFile(argv[2], ' ');
    }
    else
    {
        cout << "Wrong type of input parameters!" << endl;
        inputFormat();
        return 1;
    }

    // printTokens();
    // writeOutputFile("examples/bin.asm", "output.txt");

    return 0;
}

void inputFormat()
{
    cout << "\nRight input format:" << endl;
    cout << "./montador -p assemble_program.asm \n   or\n./montador -o preprocess_file.pre" << endl;
}

void readInputFile(string filePath, char delim = ' ')
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

void printTokens()
{
    cout << "\n----- TOKENS: -----\n"
         << endl;
    // for (auto i : tokens)
    //     cout << i << endl; // this will print all the tokens of the program

    // another print way
    for (iter = tokens_after_clean.begin(); iter != tokens_after_clean.end(); ++iter)
        cout << *iter << endl;
}

void cleanTokens()
{ // Accessing the elements using iterators
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

void writeOutputFile(string inputFilePath, string outputFilePath)
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

void changeExtension(string fileName, string option)
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

    changeExtension(fileName, action); // extension .pre
}

void assemble(string fileName, string action)
{
    cout << "Assembling file!\n"
         << endl;

    Instruction *inst[15];
    inst[1] = new Instruction("ADD", "01", 1, 2);
    inst[2] = new Instruction("SUB", "02", 1, 2);
    inst[3] = new Instruction("MULT", "03", 1, 2);
    inst[4] = new Instruction("DIV", "04", 1, 2);
    inst[5] = new Instruction("JMP", "05", 1, 2);
    inst[6] = new Instruction("JMPN", "06", 1, 2);
    inst[7] = new Instruction("JMPP", "07", 1, 2);
    inst[8] = new Instruction("JMPZ", "08", 1, 2);
    inst[9] = new Instruction("COPY", "09", 2, 3);
    inst[10] = new Instruction("LOAD", "10", 1, 2);
    inst[11] = new Instruction("STORE", "11", 1, 2);
    inst[12] = new Instruction("INPUT", "12", 1, 2);
    inst[13] = new Instruction("OUTPUT", "13", 1, 2);
    inst[14] = new Instruction("STOP", "14", 0, 1);

    for(auto i : inst)
        cout << i << endl;

    changeExtension(fileName, action); // extension .obj
}

