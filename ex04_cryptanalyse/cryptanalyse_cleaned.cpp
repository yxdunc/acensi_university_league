#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>

using namespace std;

std::string to_lower(std::string str)
{
	for (int i = 0; i < str.length(); i++)
		str[i]=tolower(str[i]);
	return(str);
}

std::string  roseting(std::string line)
{ 
	char					max;
	std::string				rosetta;
	std::map< char, char >	trans;

	max = 65;
	rosetta = line;
	trans.clear();

	for (unsigned int i = 0; i < line.size(); i++)
	{
		if(trans.find(line[i]) == trans.end())
		{
			trans[line[i]] = max;
			max++;
		}
		rosetta[i] = trans[line[i]];
	}
	return (rosetta);
}

char	lookup_by_value(std::map< char, char > mp, char value)
{
	char key = -1;
	std::map<char, char>::const_iterator it;

	for (it = mp.begin(); it != mp.end(); ++it)
	{
		if (it->second == value)
		{
			key = it->first;
			break;
		}
	}
	return(key);
}

void	decrypte(map<string, vector<string> > dico, vector<string> input)
{
	std::map< char, char >		known;
	std::string					rosetta;
	std::string					bob;
	bool						is_the_one;

	for(unsigned int iter = 0; iter < 20; iter++) // subjective number of iterations of the decoding
	{
	for(unsigned int i = 0; i < input.size(); i++)
	{
		rosetta = roseting(input[i]);
		if(dico[rosetta].size() == 1)
		{
			for(unsigned int y = 0; y < dico[rosetta][0].size(); y++)
		 		known[dico[rosetta][0][y]] = input[i][y]; // adding all figured letters
		}
		else
		{
			for(unsigned int y = 0; y < dico[rosetta].size(); y++)
			{
				bob = dico[rosetta][y];
				for (unsigned int z = 0; z < bob.size(); z++)
				{
					if (known.find(bob[z]) != known.end())
					{
						if(input[i][z] == known[bob[z]])
							is_the_one = true;
						else
						{
							is_the_one = false;
							break;
						}
					}
					else
					{
						is_the_one = false;
						break ;
					}
				}
				if (is_the_one)
				{
					for(unsigned int y = 0; y < bob.size(); y++)
					{
						known[bob[y]] = input[i][y]; // adding all figured letters
					}
					break ;
				}
			}
		}
	}
	}
	for(unsigned int i = 0; i < input.size(); i++)
	{
		rosetta = roseting(input[i]);
		if (dico[rosetta].size() == 1)
			std::cout << dico[rosetta][0] << ' ';
		else
		{
			string bob;
			bool is_the_one;
			
			for(unsigned int y = 0; y < dico[rosetta].size(); y++)
			{
				bob = dico[rosetta][y];
				for (unsigned int z = 0; z < bob.size(); z++)
				{
					if (known.find(bob[z]) != known.end())
					{
						if(input[i][z] == known[bob[z]])
							is_the_one = true;
						else
						{
							is_the_one = false;
							break ;
						}
					}
				}
				if (is_the_one)
				{
					std::cout << bob << ' ';
					break ;
				}
			}
		}
	}
}

int main()
{
	std::map< std::string, std::vector< std::string > >	dico;
	std::map< char, char >		trans;
	std::vector< std::string >	input;
	std::string			line;
	char				word[200];

	/* create dictionary */
	std::ifstream myfile ("dictionary.lst");
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			line = to_lower(line);
			dico[roseting(line)].push_back(line); // dico represent an abstract temporary language
		}
		myfile.close();
	}
	else std::cout << "Unable to open file"; 
	/**/

	/* decrypte */
	while (std::cin>>word) input.push_back(word);
	decrypte(dico, input);
	/**/

	return (0);
}

