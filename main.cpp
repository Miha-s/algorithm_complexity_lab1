#include <iostream>
#include <fstream>

#include "HashingFunction.hpp"
#include "StringHashTable.hpp"

void
process_strings( const std::string& file_path, StringHashTable& table )
{
    std::fstream s{ file_path, std::ios::in };

    if ( !s.is_open( ) )
    {
        std::cerr << "Error: Could not open the file: " << file_path << std::endl;
        return;
    }

    std::string new_line;

    while ( std::getline( s, new_line ) )
    {
        const char operation = new_line[ 0 ];
        new_line = new_line.substr( 2 );

        if ( operation == '+' )
        {
            table.insert( new_line );
        }
        else if ( operation == '-' )
        {
            table.remove( new_line );
        }
        else
        {
            if ( table.is_present( new_line ) )
            {
                std::cout << new_line << " - yes" << std::endl;
            }
            else
            {
                std::cout << new_line << " - no" << std::endl;
            }
        }
    }
}

int
main( int argc, char* argv[] )
{
    const long max_string_length = 15;
    HashingFunction hash_func{ max_string_length };
    StringHashTable strings_table{ max_string_length, hash_func };

    std::string file_path = argv[1];

    process_strings( file_path, strings_table );

    const auto palindromes = strings_table.find_all_palindromes( );

    for ( const auto& palindrome : palindromes )
    {
        std::cout << palindrome << std::endl;
    }

    return 0;
}
