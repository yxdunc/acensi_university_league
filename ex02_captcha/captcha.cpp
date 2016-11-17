#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

#define BEGIN_X 11
#define BEGIN_Y 4
#define WIDTH 8
#define HEIGHT 10
#define SPACING 1

/* bin image log */
void	print_image(std::string image)
{
	for (int x = 0; x < 30; x++)
	{
		for (int y = 0; y < 60; y++)
			std::cout << image[x * 60 + y];
		std::cout << std::endl;
	}
}
void	print_image(std::string image, int width, int height)
{
	for (int x = 0; x < height; x++)
	{
		for (int y = 0; y < width; y++)
			std::cout << image[x * width + y];
		std::cout << std::endl;
	}
}
/**/

/* utils */
void split(const std::string &s, char delim, std::vector< std::string > &elems)
{
    std::stringstream	ss;
    std::string			item;

    ss.str(s);
	elems.clear();
    while (std::getline(ss, item, delim))
	{
        elems.push_back(item);
    }
}
void split_white(const std::string &s, std::vector< std::string > &elems)
{
	std::string	buf;

	elems.clear();
    for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == ' ' || s[i] == '\n')
		{
        	elems.push_back(buf);
			buf.clear();
			i++;
		}
		buf += s[i];
    }
}
/**/

/* image processing */
std::string		binarize(std::string image)
{
	std::vector< std::string >		tokens;
	std::vector< std::string >		temp;
	std::string			   			final;

	split_white(image, tokens);
	
	
	temp.clear();
	for(unsigned int i = 0; i < tokens.size(); i++)
	{
		split(tokens[i], ',', temp);
		if(stoi(temp[0]) + stoi(temp[1]) + stoi(temp[2]) < 100)
			final += "1";
		else
			final += "0";
	}
	return(final);
}
std::string focus_on_letter(int index, std::string image)
{
	std::string		result;
	int				y_start;
	int				y_end;

	y_start = BEGIN_Y + (WIDTH + SPACING) * index;
	y_end = BEGIN_Y + (WIDTH + SPACING) * index + WIDTH;
	
	for (unsigned int x = BEGIN_X; x < 30; x++) // ligne/raw
	{
		for (unsigned int y = BEGIN_Y; y < 60; y++) // colonne/column
		{
			if(x <= (BEGIN_X + HEIGHT) && y <= y_end && y > y_start)
			{
				result += image[x * 60 + y];
			}
		}
	}
	return (result);
}	
/**/

/* file IO */
std::string		get_image(int i)
{
	std::string	image;
	std::string	base_name = "/Users/robin/Downloads/sampleCaptchas/input/input";
	std::string	fname;
	std::string	line;

	if (i < 10)
		fname = (base_name + "0" + std::to_string(i));
	else
		fname = (base_name + std::to_string(i));
	std::ifstream image_file(fname + ".txt");
	if (image_file.is_open())
	{
		getline(image_file, line); // throwing away first line
		while ( getline(image_file, line) )
		{
			if (image.size())
				line = ' ' + line;
			image += line;
		}
		image_file.close();
	}
	else std::cout << "[ERROR FILE]" << fname << std::endl;
	return (image);
}
std::string		get_label(int i)
{
	std::string	label;
	std::string	fname;
	std::string	line;
	std::string	base_name = "/Users/robin/Downloads/sampleCaptchas/output/output";

	if (i < 10)
		fname = (base_name + "0" + std::to_string(i));
	else
		fname = (base_name + std::to_string(i));
	std::ifstream label_file(fname + ".txt");
	if (label_file.is_open())
	{
		getline(label_file, label);
		label_file.close();
	}
	else std::cout << "[ERROR FILE]" << fname << std::endl;
	return(label);
}
/**/

void	print_result(std::string image, std::string answer)
{
	std::string focused;
    for(unsigned int i = 0; i < 5; i++)
    {
        focused = focus_on_letter(i, image);
//		print_image(focused, WIDTH, HEIGHT);
		std::cout << "recognizer[\"" << focused << "\"] = \"" << answer[i] << "\";" << std::endl;
    }
}

int main( void ) {
	std::string	image;
	std::string	label;

	for (int i = 0; i <= 24; i++)
	{
		image = get_image(i);
		label = get_label(i);
    	image = binarize(image);	// black and !blacks
//		print_image(image);
		print_result(image, label);
	}
    return 0;
}
