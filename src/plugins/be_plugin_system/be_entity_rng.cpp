#include "be_entity_rng.h"

	bool Brng::set( const Bstring& id, const Bint& value )
	{
		if ( id == "seed" )
		{
			srand ( value );
			return true;
		}
		else if ( id == "min" )
		{
			m_min = value;
			return true;
		}
		else if ( id == "max" )
		{
			m_max = value;
			return true;
		}
		return false;
	}

	Bint Brng::get_int()
	{
		if ( m_max > m_min )
		{
			return (rand() % ( m_max - m_min + 1 )) + m_min;
		}
		else
		{
			return m_min;
		}
	} 
