#ifndef STRINGHASHTABLE_HPP
#define STRINGHASHTABLE_HPP
#include <string>
#include <vector>
#include <list>
#include "./HashingFunction.hpp"

class StringHashTable
{
    const long int m_max_string_length;
    std::vector< std::list< std::string > > m_hash_table;
    const HashingFunction& m_hash_func;

public:
    StringHashTable( const long int max_string_length, const HashingFunction& func );
    void insert( const std::string& str );
    void remove( const std::string& str );
    bool is_present( const std::string& str);

    long substring_hash( const std::vector< long int >& prefix_hashes,
                         long left_index,
                         long right_index ) const;

    std::vector< std::string > find_all_palindromes( ) const;
    std::vector< std::string > find_palindromes( const std::string& str ) const;

    const std::vector< std::string > get_all_strings( ) const;
};


#endif  // STRINGHASHTABLE_HPP
