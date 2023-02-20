#include "qpen.h"
#include "kernel/be_entity_core_types.h"
 
		BQPen::BQPen()
		: QPen()
		, m_r(0)
		, m_g(0)
		, m_b(0)
		{
			setColor( QColor(0, 0, 0) );
		}

		void BQPen::construct()
		{
			// auto color = addChild( "color", new BEntity() );
			addChild( "color_r", new BEntity_uint_property() );
			addChild( "color_g", new BEntity_uint_property() );
			addChild( "color_b", new BEntity_uint_property() );
		}

		bool BQPen::set( const Bstring& id, const Buint& value )
		{
			if ( id == "color_r" )
			{
				if ( m_r != value )
				{
					m_r = value;
					setColor( QColor( m_r, m_g, m_b ) );
					parent()->onAddChild( this );
					onUpdate();
					return true;
				}
			}
			else if ( id == "color_g" )
			{
				if ( m_g != value )
				{
					m_g = value;
					setColor( QColor( m_r, m_g, m_b ) );
					parent()->onAddChild( this );
					onUpdate();
					return true;
				}
			}
			else if ( id == "color_b" )
			{
				if ( m_b != value )
				{
					m_b = value;
					setColor( QColor( m_r, m_g, m_b ) );
					parent()->onAddChild( this );
					onUpdate();
					return true;
				}
			}

			return false;
		}
