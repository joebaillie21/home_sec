#include "Parser.h"
#include <vector>
#include <sstream>

CSVParser::CSVParser(string file)
{
    filePath = file;
};

vector<string> CSVParser::ReadLines()
{
    vector<string> lines;
    ifstream inputStream(filePath);
    if (inputStream.is_open() == false)
        return lines;
    string line;
    while ( getline(inputStream,line))
    {
        lines.push_back(line);
    }
    inputStream.close();
    return lines;
};

vector<string> CSVParser::ParseString(string s)
{
    vector<string> fields;
    fields = Split(s, ',');
    return fields;
}

//Split based on delimiter.  Return a standard vector of strings
std::vector<std::string> CSVParser::Split(std::string line, char delimiter)                                                                                                                          
{                                                                                                                                                                                             
   std::vector<std::string> splits;                                                                                                                                                           
   std::string field;                                                                                                                                                                         
   std::stringstream s_stream(line);                                                                                                                                                                  
   while (std::getline(s_stream, field, delimiter))                                                                                                                                                 
   {                                                                                                                                                                                          
      splits.push_back(field);                                                                                                                                                                
   }                                                                                                                                                                                          
   return splits;                                                                                                                                                                             
}