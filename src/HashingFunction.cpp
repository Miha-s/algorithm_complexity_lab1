#include "HashingFunction.hpp"
#include <gmpxx.h>



HashingFunction::HashingFunction( const long max_string_length )
    : m_max_string_length{ max_string_length }
    , m_m{ 999883 }
    , m_p{ 271 }  // must be bigger that string character code
{
    m_base_powers.push_back( 1 );
    m_base_powers.resize( m_max_string_length + 1 );
    m_inverse_powers.push_back( 1 );
    m_inverse_powers.resize( m_max_string_length + 1 );

    mpz_t p, m, k, inv, result;
    mpz_inits( p, m, k, inv, result, NULL );

    // Initialize values
    mpz_set_ui( p, m_p );
    mpz_set_ui( m, m_m );
    mpz_invert( inv, p, m );

    for ( int i = 1; i < m_max_string_length + 1; i++ )
    {
        m_base_powers[ i ] = ( m_base_powers[ i - 1 ] * m_p ) % m_m;
        mpz_set_ui( k, i );
        mpz_powm( result, inv, k, m );
        m_inverse_powers[ i ] = mpz_get_ui( result );
    }
}

std::vector< long >
HashingFunction::compute_prefix_hashes( const std::string& str ) const
{
    std::vector< long > prefix_hashes;
    prefix_hashes.resize( str.size( ) );
    long hash_value = 0;

    for ( int i = 0; i < str.size( ); i++ )
    {
        hash_value = ( hash_value + str[ i ] * m_base_powers[ i ] ) % m_m;
        prefix_hashes[ i ] = ( hash_value );
    }

    return prefix_hashes;
}

long
HashingFunction::compute_hash( const std::string& str ) const
{
    return compute_prefix_hashes( str ).back( );
}

long
HashingFunction::modulo( ) const
{
    return m_m;
}

const std::vector< long >
HashingFunction::base_powers( ) const
{
    return m_base_powers;
}

const std::vector< long >
HashingFunction::inverse_powers( ) const
{
    return m_inverse_powers;
}
