#ifndef HASHINGFUNCTION_HPP
#define HASHINGFUNCTION_HPP
#include <string>
#include <vector>

class HashingFunction
{
    const long int m_max_string_length;
    const long int m_p;
    const long int m_m;

    std::vector< long int > m_base_powers;
    std::vector< long int > m_inverse_powers;

public:
    HashingFunction( const long int max_string_length );

    std::vector< long int > compute_prefix_hashes( const std::string& str ) const;
    long int compute_hash( const std::string& str ) const;
    long int substring_hash( const std::string& str ) const;
    long int modulo( ) const;

    const std::vector< long int > base_powers( ) const;
    const std::vector< long int > inverse_powers( ) const;
};

#endif // HASHINGFUNCTION_HPP
