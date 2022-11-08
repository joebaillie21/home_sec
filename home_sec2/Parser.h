#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

class CSVParser
{
    public:
    CSVParser(string  _filePath);
    vector<string> ReadLines();
    vector<string> ParseString(string data);
    protected:
    string filePath;
    vector<string> Split(string s, char delimiter);

};