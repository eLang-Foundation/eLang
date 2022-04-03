#include "headers.h"

string FILENAME;
ifstream SRC_FILE;
string SRC_CODE;

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



	cleanup();
	return 0;
}
