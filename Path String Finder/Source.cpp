//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>

typedef std::vector<int> int_vec;
//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************
class string_search
{
	int_vec shifts;
	void compute_shifts(const std::string &pattern);
public:
	int find_first(const std::string &text, const std::string &pattern);
	int_vec find_all(const std::string &text, const std::string &pattern);

};
//***************************************************************
//    	function declaration
//****************************************************************

// create the shift-lookup-table
void string_search::compute_shifts(const std::string &pattern)
{
	int next_shift = 0;
	shifts.clear();
	shifts.push_back(0); // shift to the first character

						 // start with the second character, since the shift to the first is always 0
	for (int i = 1; i < pattern.length(); i++)
	{
		while (next_shift > 0 && pattern[next_shift] != pattern[i])
			next_shift = shifts[next_shift];

		if (pattern[next_shift] == pattern[i])
			next_shift++;

		shifts.push_back(next_shift);
	}
}

// search the string and return when the first occurrence is found
int
string_search::find_first(const std::string &text, const std::string &pattern)
{
	int next_shift = 0;
	compute_shifts(pattern);
	for (int i = 0; i < text.length(); i++)
	{
		while (next_shift > 0 && pattern[next_shift] != text[i])
			next_shift = shifts[next_shift - 1];

		if (pattern[next_shift] == text[i])
			next_shift++;

		if (next_shift == pattern.length())
			return i - (pattern.length() - 1); // found the first so return
	}
	return -1;
}

// search the string and put every occurence in a vector
int_vec
string_search::find_all(const std::string &text, const std::string &pattern)
{
	int next_shift = 0;
	int_vec positions;
	compute_shifts(pattern);
	for (int i = 0; i < text.length(); i++)
	{
		while (next_shift > 0 && pattern[next_shift] != text[i])
			next_shift = shifts[next_shift - 1];

		if (pattern[next_shift] == text[i])
			next_shift++;

		if (next_shift == pattern.length())
		{
			positions.push_back(i - (pattern.length() - 1)); // found one, put in list
			next_shift = shifts[next_shift - 1]; // restart pattern with last shift
		}
	}
	return positions;
}
//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************

int main(int argc, char **argv)
{	
	std::cout << "\n\n";
	std::string myName = " \
  \t      _______________________               ____                ___\n\
  \t     /                      /              /   /               /  / ___ \n\
  \t    /     ___      ___     /  _______     /   /          _____/  / /__/\n\
  \t   /    /   /    /   /    /  / __    /   /   /_______  / ___    / ___ \n\
  \t  /    /   /    /   /    /  / /   / /   /   _____   / /  /  /  / /  /\n\
  \t /    /   /    /   /    /  / /__ / \\_  /   /    /  / /  /__/  / /  /\n\
\t/____/   /____/   /____/  /_________/ /___/    /__/ /________/ /__/\n\ ";

	std::cout << "\n By \n\n" << myName << "\n\n";
	if (argc <= 2) {
		std::cout << "Usage of \n" << argv[0] << "\nis showing filename search-pattern!" << std::endl;
		if (_getch()) {
			return 0;
		}
	}
	std::string pattern = argv[2];

	// read the file. Since the file is read like this all white-characters
	// are eaten, so a search including white-characters will fail...
	std::fstream fs;
	std::string text, temp;
	fs.open(argv[1], std::ios::in);
	while (!fs.eof()) {
		fs >> temp;
		text += temp;
	}
	fs.close();

	// search the file
	string_search search;
	int_vec pos_list = search.find_all(text, pattern);

	// print out result
	std::vector<int>::iterator it;
	std::cout << "Found " << pos_list.size() << " occurrences" << std::endl;
	for (it = pos_list.begin(); it != pos_list.end(); it++) {
		temp = text.substr(*it, pattern.length());
		std::cout << "Pos=" << *it << " == " << temp << std::endl;
	}

	if (_getch()) {
		return 0;
	}
}
//***************************************************************
//    			END OF PROJECT
//***************************************************************