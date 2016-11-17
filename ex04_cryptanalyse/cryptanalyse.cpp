#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>

using namespace std;


string to_lower(string str)
{
        for (int i=0;i<str.length();i++){ // input.length() gets the length of the string
         str[i]=tolower(str[i]);
        }
    return(str);
}

string  roseting(string line)
{ 
     char max = 65;
     string rosetta = line;
     map<char, char> trans;
    
     trans.clear();
     for (unsigned int i = 0; i<line.size(); i++)
     {
         if(trans.find(line[i]) == trans.end())
         {
             trans[line[i]] = max;
             max++;
         }
         rosetta[i] = trans[line[i]];//error pron
     }
    return (rosetta);
}

char lookup_by_value(map<char,char> mp, char value)
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

void    decrypte(map<string, vector<string> > dico, vector<string> input)
{
    map<char, char>     known;
    string              rosetta;
    for(unsigned int plouf = 0; plouf < 20; plouf++){
    for(unsigned int i = 0; i < input.size(); i++)
    {
        rosetta = roseting(input[i]);
        if (dico[rosetta].size() == 1)
        {
            for(unsigned int y = 0; y < dico[rosetta][0].size(); y++)
            {
                //known[input[i][y]] = dico[rosetta][0][y]; // adding all figured letters
                      known[dico[rosetta][0][y]] = input[i][y]; // adding all figured letters
            }
        }
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
                     // known[input[i][y]] = bob[y]; // adding all figured letters
                      known[bob[y]] = input[i][y]; // adding all figured letters
                   }
                   break ;
                }
            }
        }
            
    }}
                 
    for(unsigned int i = 0; i < input.size(); i++)
    {
        rosetta = roseting(input[i]);
        if (dico[rosetta].size() == 1)
        {
            std::cout << dico[rosetta][0] << ' ';
        }    
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

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    string line;
    map<string, vector<string> > dico;
    map<char, char>     trans;
    string rosetta;
    char max;
    
    ifstream myfile ("dictionary.lst");
    if (myfile.is_open())
    {
      while ( getline (myfile,line) )
      {
        max = 65;
        line = to_lower(line);
        rosetta = line;
        trans.clear();
        for (unsigned int i = 0; i<line.size(); i++)
        {
            if(trans.find(line[i]) == trans.end())
            {
                trans[line[i]] = max;
                max++;
            }
            rosetta[i] = trans[line[i]];//error pron
        }
        dico[rosetta].push_back(line);
      }
      myfile.close();
    }
    else cout << "Unable to open file"; 
    
    char word[200];
    vector<string> input;
    
    while (cin>>word)
    {
        input.push_back(word);
    }
    decrypte(dico, input);
    return 0;
}

