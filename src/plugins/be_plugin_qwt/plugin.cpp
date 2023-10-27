#include "plugin.h"
#include "kernel/be_plugin_interface.h"
#include <QPen>
#include <iostream>

	// PLOT
		BeEntityQwtPlot::BeEntityQwtPlot()
		 : QwtPlot()
		{
			QWidget::setVisible( true );
			// setAutoReplot(true);
			// resize ( 100, 100 );
		}

		Bbool BeEntityQwtPlot::onAddChild( BEntity* entity )
		{ 
			// std::cout << "BeEntityQwtPlot::onAddChild" << std::endl;

			auto qwtplotcurve = dynamic_cast<BeEntityQwtPlotCurve*>(entity);
			if ( qwtplotcurve )
			{
				qwtplotcurve->attach(this);
				replot();
				return true;
			}

			return false;
		}

	// CURVE
		BeEntityQwtPlotCurve::BeEntityQwtPlotCurve()
		 : QwtPlotCurve()
		 , m_count(0)
		 , m_size_max(0)
		{
			setPaintAttribute(ClipPolygons, true);
			setPaintAttribute(FilterPoints, true);
			setPaintAttribute(MinimizeMemory, true);
			setPaintAttribute(ImageBuffer, true);

			setStyle( Lines ); // NoCurve, Lines , Sticks , Steps , Dots , UserCurve
		}
		
		void BeEntityQwtPlotCurve::construct()
		{
			m_size_max = addChild("size_max", new BEntity_uint());
			m_size_max->set( (Buint)7200 ); // FIXME   parent -> setAxisScale( Position::yRight, min, max, stepsize )
		}

		bool BeEntityQwtPlotCurve::set()
		{
			// REPLOT
			auto plot = dynamic_cast<QwtPlot*>(parent());
			QwtPlotCurve::setSamples( m_list );
			plot->replot();
			return true;
		}
		
		
		Bbool BeEntityQwtPlotCurve::onAddChild( BEntity* entity )
		{ 
			auto qpen = dynamic_cast<QPen*>(entity);
			if ( qpen )
			{
				setPen(*qpen);
				return true;
			}

			return false;
		}
		
		void BeEntityQwtPlotCurve::resizeList()
		{
			// if ( m_count >= m_size_max->get_uint() )
			// {
			// 	while ( m_list.size() > (int)m_count )
			// 	{
			// 		m_list.erase(m_list.begin());
			// 		m_count--;
			// 	}
			// }

			if ( m_count >= m_size_max->get_uint() )
			{
				const auto& it(m_list.begin()+m_count);
				while ( m_list.size() > (int)m_count )
					m_list.erase(it);
				m_count=0;
			}
		}

		void BeEntityQwtPlotCurve::addValue( float value )
		{
			if ( (int)m_count >= m_list.size() )
			{
				m_list.insert( m_count, value );
			}
			else
			{
				m_list[m_count] = value;

				// CLEAR DISTANCE
				const unsigned int clear_distance(120);
				for ( unsigned int i(1); i <= clear_distance; ++i )
				{
					if ( m_count+i < (unsigned int)m_list.size() )
						// m_list[m_count+i] = value; // it's really not that clear
						m_list[m_count+i] = 0.0;
				}
			}
			++m_count;
			resizeList();
			set();
		}
		

	// CURVE_FLOAT
		bool BeEntityQwtPlotCurve_Float::set( const Bfloat& value )
		{
			addValue( value );
			return true;
		}

		bool BeEntityQwtPlotCurve_Float::set( const Buint& value )
		{
			addValue( value );
			return true;
		}

	// CURVE_FLOAT_POLL
		BeEntityQwtPlotCurve_Float_Poll::BeEntityQwtPlotCurve_Float_Poll()
		: BeEntityQwtPlotCurve()
		, m_entity_to_poll(0)
		{
			setProcessing();
		}
		
		bool BeEntityQwtPlotCurve_Float_Poll::set( const Bstring& id, BEntity* value )
		{
			if ( id == "poll_entity" )
			{
				m_entity_to_poll = addChild( "poll_entity", new BEntity_reference() );
				m_entity_to_poll->set( value );
				return true;
			}
			return false;
		}
		
		void BeEntityQwtPlotCurve_Float_Poll::process()
		{
			if ( m_entity_to_poll != 0 )
			{
				addValue( m_entity_to_poll->get_reference()->get_float() );
			}
		}



// ---- FACTORIES
	enum CLASS
	{
		  PLUGIN_INFO
		, PLOT
		, CURVE
		, CURVE_POLL
	};

	extern "C" BEntity* create( BEntity* parent, const Buint type )
	{
// 		std::cout << "LIB CREATE:: type: " << type  << std::endl;
		// PLUGIN DESCRIPTION ENTITY
			if ( type == PLUGIN_INFO )
			{
				BClassesHelper i;
					i.addClass( parent, CLASS::PLOT, "QwtPlot" );
					i.addClass( parent, CLASS::CURVE, "QwtCurve" );
					i.addClass( parent, CLASS::CURVE_POLL, "QwtCurve_Poll" );
				return 0;
			}

		// ENTITIES
			else
			{
				BEntity* i(0);
				
				if ( type == CLASS::PLOT )
					i = new BeEntityQwtPlot();

				else if ( type == CLASS::CURVE )
					i = new BeEntityQwtPlotCurve_Float();
				
				else if ( type == CLASS::CURVE_POLL )
					i = new BeEntityQwtPlotCurve_Float_Poll();

				return i;
			}
	}

	extern "C" void destroy(BEntity* p)
	{
// 		std::cout << "LIB DESTROY:: " << p->id() << std::endl;
		delete p;
	}
