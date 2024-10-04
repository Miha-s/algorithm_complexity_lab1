#include "StringHashTable.hpp"
#include <algorithm>
#include <vector>

StringHashTable::StringHashTable( const long int max_string_length, const HashingFunction& func )
    : m_max_string_length{ max_string_length }
    , m_hash_func{ func }
{
    m_hash_table.resize( 1000000 );
}

void
StringHashTable::insert( const std::string& str )
{
    m_hash_table[ m_hash_func.compute_hash( str ) ].push_back( str );
}

void
StringHashTable::remove( const std::string& str )
{
    auto& list = m_hash_table[ m_hash_func.compute_hash( str ) ];
    auto it = std::find( list.begin( ), list.end( ), str );
    if ( it != list.end( ) )
    {
        list.erase( it );
    }
}

bool
StringHashTable::is_present( const std::string& str )
{
    auto& list = m_hash_table[ m_hash_func.compute_hash( str ) ];
    auto it = std::find( list.begin( ), list.end( ), str );
    if ( it != list.end( ) )
    {
        return true;
    }
    return false;
}

long
StringHashTable::substring_hash( const std::vector< long >& prefix_hashes,
                                 long left_index,
                                 long right_index ) const
{
    auto right_hash = prefix_hashes[ right_index ];
    auto left_hash_minus_1 = left_index > 0 ? prefix_hashes[ left_index - 1 ] : 0;
    auto left_right_hash = ( right_hash - left_hash_minus_1 ) % m_hash_func.modulo( );
    while ( left_right_hash < 0 )
    {
        left_right_hash += m_hash_func.modulo( );
    }

    left_right_hash = ( left_right_hash * m_hash_func.inverse_powers( )[ left_index ] )
                      % m_hash_func.modulo( );

    return left_right_hash;
}

std::vector< std::string >
StringHashTable::find_all_palindromes( ) const
{
    std::vector< std::string > palindromes;
    for ( const auto& str : get_all_strings( ) )
    {
        auto new_palindromes = find_palindromes( str );
        std::copy( new_palindromes.begin( ),
                   new_palindromes.end( ),
                   std::back_inserter( palindromes ) );
    }

    return palindromes;
}

std::vector< std::string >
StringHashTable::find_palindromes( const std::string& str ) const
{
    std::vector< std::string > palindromes;

    auto length = str.size( );
    auto prefix_hashes = m_hash_func.compute_prefix_hashes( str );
    auto reversed_str = str;
    std::reverse( reversed_str.begin( ), reversed_str.end( ) );
    auto prefix_hashes_reverse = m_hash_func.compute_prefix_hashes( reversed_str );

    for ( int center = 0; center < length; center++ )
    {
        auto low = center - 1;
        auto high = center+1;
        while ( low >= 0 && high < length )
        {
            auto substr_hash = substring_hash( prefix_hashes, low, high );
            auto low_reverse = length - high - 1;
            auto high_reverse = length - low - 1;
            auto substr_reverse_hash =
                    substring_hash( prefix_hashes_reverse, low_reverse, high_reverse );
            if ( substr_hash == substr_reverse_hash )
            {
                palindromes.push_back( str.substr( low, high - low + 1 ) );
            }
            else
            {
                break;
            }

            low--;
            high++;
        }
    }

    for ( int low_ = 0; low_ < length; low_++ )
    {
        auto low = low_;
        auto high = low + 1;
        while ( low >= 0 && high < length )
        {
            auto substr_hash = substring_hash( prefix_hashes, low, high );
            auto low_reverse = length - high - 1;
            auto high_reverse = length - low - 1;
            auto substr_reverse_hash =
                    substring_hash( prefix_hashes_reverse, low_reverse, high_reverse );
            if ( substr_hash == substr_reverse_hash )
            {
                palindromes.push_back( str.substr( low, high - low + 1 ) );
            }
            low--;
            high++;
        }
    }

    return palindromes;
}

const std::vector< std::string >
StringHashTable::get_all_strings( ) const
{
    std::vector< std::string > all_strings;
    for ( const auto& bucket : m_hash_table )
    {
        if ( bucket.empty( ) )
        {
            continue;
        }
        for ( const auto& str : bucket )
        {
            all_strings.push_back( str );
        }
    }

    return all_strings;
}
