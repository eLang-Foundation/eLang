#include "headers.h"


string FILENAME;
ifstream SRC_FILE;
string SRC_CODE;

vector<string> instructions;
vector<string> names;


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "Usage: " << argv[0] << " <filename>" << endl;
		return 1;
	}

	
	FILENAME = string(argv[1]); 

	SRC_FILE.open(FILENAME);


	// reading the file
	string tmp;
	while (getline(SRC_FILE, tmp)) SRC_CODE += tmp + "\n";


	// splitting the code into lines
	vector<string> lines;
	stringstream s_stream(SRC_CODE);
	string line;
	while (getline(s_stream, line))
	{
		// remove whitespace around the line
		line.erase(0, line.find_first_not_of(" \t"));
		reverse(line.begin(), line.end());
		line.erase(0, line.find_first_not_of(" \t"));
		reverse(line.begin(), line.end());

		if (line[0] == ';') lines.push_back("");
		else lines.push_back(line);
	}


	vector<char> VAR_CHARS = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
								'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
								'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	vector<string> KEYWORDS = {"fun", "if", "else", "elif", "while", "for", "repeat", "return", "end"};

	// parsing the code
	tmp = "";
	for (auto line: lines)
	{
		for (auto c: line)
		{
			if (c != ' ')
				tmp += c;
			else
			{
				if (find(KEYWORDS.begin(), KEYWORDS.end(), tmp) == KEYWORDS.end()) names.push_back(tmp);
				else instructions.push_back(tmp);
				tmp = c;
			}
		}
	}


	cout << "INSTRUCTIONS" << endl;
	for (auto i: instructions) cout << i << endl;
	cout << "NAMES" << endl;
	for (auto i: names) cout << i << endl;


	cleanup();
	return 0;
}
