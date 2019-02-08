#include <iostream>
#include <string>
#include <vector>



std::vector <std::string> split(std::string line, char separator, bool asd = false)
{
    std::vector< std::string > a;
    std::string helper = "";
    if (asd)
    {

        for (unsigned int i = 0; i < line.size(); ++i)
        {
            if (line[i]==separator)
            {
                    if (helper != "")
                    {
                    a.push_back(helper);
                    helper = "";
                    }
            }
            else
            {
                helper += line[i];
            }
        }
        if (helper != "")
        {
            a.push_back(helper);
        }
        return a;}
    else
    {
    for (unsigned int i = 0; i < line.size(); ++i)
    {
        if (line[i]==separator)
        {
            {
                a.push_back(helper);
                helper = "";
            }
        }
        else
        {
            helper += line[i];
        }
    }

        a.push_back(helper);

    return a;
    }
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto o : parts ) {
        std::cout << o << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto o : parts_no_empty ) {
        std::cout << o << std::endl;
    }
}
