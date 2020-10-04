#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <iomanip>

#define maxNumMacros 2
#define masArgsMacro 2

using namespace std;
const int size = 100;

void initDirectives();
void replacingEQU();
void initInstructions();
void inputFormat();
void readInputFile(string filePath);
void removeComments(string inputFilePath, string outputFilePath);
void writeOutputFile(string inputFilePath, string outputFilePath);
string changeExtension(string option, string fileName);
void printTokens();
void cleanTokens();
void preprocess(string fileName, string action);
void assemble(string fileName, string action);

vector<string> tokens;             // input tokens
vector<string> tokens_after_clean; // tokens without special caracters
auto iter = tokens.begin();        // iterator
// auto iter = tokens_after_clean.begin();        // iterator

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
        initDirectives();
        preprocess(argv[1], argv[2]);
        readInputFile(argv[2]);
        // cleanTokens();
    }
    else if (strncmp(argv[1], "-o", 2) == 0)
    {
        initInstructions();
        assemble(argv[1], argv[2]);
        readInputFile(argv[2]);
    }
    else
    {
        cout << "Wrong type of input parameters!" << endl;
        inputFormat();
        return 1;
    }

    return 0;
}

void initDirectives()
{
    typedef tuple<string, int, int> directive;
    vector<directive> libDirectives;
    // mnemonic, operands, length
    libDirectives.push_back(directive("SECTION", 1, 0));
    libDirectives.push_back(directive("SPACE", 0, 1));
    libDirectives.push_back(directive("CONST", 1, 1));
    libDirectives.push_back(directive("EQU", 1, 0));
    libDirectives.push_back(directive("IF", 1, 0));
    libDirectives.push_back(directive("MACRO", 0, 0));
    libDirectives.push_back(directive("ENDMACRO", 0, 0));

    for (directive d : libDirectives)
    {
        cout << get<0>(d) << ' ';
        cout << get<1>(d) << ' ';
        cout << get<2>(d) << '\n';
    };
}

void getLabelEQU()
{   
    int positionCount = 0;
    int labelSize = 0;
    string label = "";
    
    for (iter = tokens.begin(); iter != tokens.end(); ++iter)
    {
        label = *iter;
        int length = label.length();

        for (int i = 0; i < length; i++)
        {
            positionCount += 1;
            if (iter->find(":")){
                labelSize = iter->size()-1;
                break;
            }
        }
        // str.replace(labelSize, 1, "");
    }
    cout << "EQU Position Count = " << positionCount << endl;  
    cout << "Label Size = " << labelSize << endl;   
    cout << "Label = " << label << endl;  
}

void initInstructions()
{
    typedef tuple<string, string, int, int> instruction;
    vector<instruction> libInstructions;
    // mnemonic, opcode, operands, length
    libInstructions.push_back(instruction("ADD", "01", 1, 2));
    libInstructions.push_back(instruction("SUB", "02", 1, 2));
    libInstructions.push_back(instruction("MULT", "03", 1, 2));
    libInstructions.push_back(instruction("DIV", "04", 1, 2));
    libInstructions.push_back(instruction("JMP", "05", 1, 2));
    libInstructions.push_back(instruction("JMPN", "06", 1, 2));
    libInstructions.push_back(instruction("JMPP", "07", 1, 2));
    libInstructions.push_back(instruction("JMPZ", "08", 1, 2));
    libInstructions.push_back(instruction("COPY", "09", 2, 3));
    libInstructions.push_back(instruction("LOAD", "10", 1, 2));
    libInstructions.push_back(instruction("STORE", "11", 1, 2));
    libInstructions.push_back(instruction("INPUT", "12", 1, 2));
    libInstructions.push_back(instruction("OUTPUT", "13", 1, 2));
    libInstructions.push_back(instruction("STOP", "14", 0, 1));

    for (instruction i : libInstructions)
    {
        cout << get<0>(i) << ' ';
        cout << get<1>(i) << ' ';
        cout << get<2>(i) << '\n';
    };
}

void inputFormat()
{
    cout << "\nRight input format:" << endl;
    cout << "./montador -p assemble_program.asm \n   or\n./montador -o preprocess_file.pre" << endl;
}

void readInputFile(string filePath)
{
    char delim = ' ';
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

// removes comments declared with ';'
void removeComments(string inputFilePath, string outputFilePath)
{
    ifstream inputFile(inputFilePath);
    ofstream outputFile(outputFilePath);
    string line;

    int numComment = 0;
    int positionComment;

    if (outputFile.is_open())
    {
        while (getline(inputFile, line))
        {
            if (line.find(";"))
            {
                positionComment = line.find(";");

                if (positionComment != -1)
                {
                    line.erase(positionComment, line.size());
                    numComment += 1;
                }
            }
            outputFile << line << endl;
        }
        outputFile.close();
    }
    else
        cout << "Unable to open file" << endl;

    cout << "Number of Comments = " << numComment << endl;
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

string changeExtension(string option, string fileNameInput)
{
    ofstream outFile;           // object for writing to a file
    string str = fileNameInput; // aux string
    int fileLength = str.length();
    int index = fileLength - 4;

    if (option == "-p")
        str.replace(index, 4, ".pre");
    if (option == "-o")
        str.replace(index, 4, ".obj");

    outFile.open(str);

    return str;
}

void preprocess(string action, string inputFile)
{
    cout << "Preprocessing file!\n"
         << endl;

    string outputFile = changeExtension(action, inputFile); // extension .pre

    removeComments(inputFile, outputFile);
    cout << "\nReplacing EQU\n" << endl;
    readInputFile(inputFile);
    getLabelEQU();
    // writeOutputFile(inputFile, outputFile);
}

void assemble(string action, string fileName)
{
    cout << "Assembling file!\n"
         << endl;

    changeExtension(action, fileName); // extension .obj
}
