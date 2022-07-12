
#include <iostream>
#include <fstream>

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;


extern string FILENAME;
extern ifstream SRC_FILE;
extern string SRC_CODE;


extern vector<string> instructions;
extern vector<string> names;


#include "cleanup.cpp"
#include "execute.cpp"

