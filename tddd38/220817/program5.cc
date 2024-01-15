#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

// TODO: Figure out what containers to use

auto read_table(std::istream& is)
{
    /* appropriate associative container */ result { };
    
    std::string line;
    while (std::getline(is, line))
    {
	std::istringstream iss { line };
	std::string entry { };
	std::string tag   { };

        /* appropriate container */ tags { };
	
	iss >> entry;
	while (iss >> tag)
	    /* insert 'tag' into 'tags' */;

	/* store an association between 'entry' and 'tags' into 'result' */
    }

    return result;
}

/* Expected output:

$ ./a.out names.txt Male Female
Alex
Austin
Avery
Blake
Brooklyn
Charlie
Drew
Jordan
Kennedy
Parker
Taylor

$ ./a.out names.txt Female
Abigail
Alex
Amelia
Austin
Ava
Avery
Blake
Brooklyn
Camila
Charlie
Charlotte
Drew
Eleanor
Elizabeth
Ella
Emma
Evelyn
Gianna
Harper
Isabella
Jordan
Kennedy
Luna
Mia
Olivia
Parker
Scarlett
Sofia
Sophia
Taylor

 */

int main(int argc, char* argv[])
{
    if (argc <= 2)
    {
	std::cerr << "Usage: " << argv[0] << " FILE [TAGS...]" << std::endl;
	return 1;
    }
    
    std::ifstream ifs { argv[1] };
    /* appropriate container */ tags { &argv[2], &argv[argc] };

    auto table = read_table(ifs);

    /* implement the program here */
}
