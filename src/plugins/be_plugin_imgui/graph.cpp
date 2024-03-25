#include "graph.h"
#include "kernel/be_entity_core_types.h"
// #include "groupbox.h"
#include <iostream>
// #include <sstream>
#include "imgui/imgui.h"

		BImGuiGraph::BImGuiGraph()
		: m_count(0)
		, m_size_max(0)
		, m_pen(0)
		{
			setProcessing();
		}

		void BImGuiGraph::construct()
		{
			m_size_max = addChild("size_max", new BEntity_uint());
			m_size_max->set( (Buint)7200 ); // FIXME   parent -> setAxisScale( Position::yRight, min, max, stepsize )
		}
		
		Bbool BImGuiGraph::onAddChild( BEntity* entity )
		{ 
			auto pen = dynamic_cast<BImGuiPen*>(entity);
			if ( pen )
			{
				m_pen = pen;
				return true;
			}
			return false;
		}

		void BImGuiGraph::resizeList()
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

		void BImGuiGraph::addValue( float value )
		{
			if ( (int)m_count >= m_list.size() )
			{
				m_list.insert( m_list.begin()+m_count, value );
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
			// set();
		}		
		
		void BImGuiGraph::process()
		{
			if ( parent()->class_id() == "ImGuiHBoxLayout" && parent()->children()[0] != this )
				ImGui::SameLine();

			ImGui::PushID( id() );

				ImVec4 color;
				if ( m_pen )
				{
					color = ImVec4( 0.00390625*m_pen->m_r, 0.00390625*m_pen->m_g, 0.00390625*m_pen->m_b, 1.0f );
				}
				else
				{
					color = ImVec4( 0.8f, 0.8f, 0.8f, 1.0f );
				}

				ImGui::PushStyleColor(ImGuiCol_PlotLines, color);

					ImGui::PlotLines(m_title.c_str(), &m_list[0], m_list.size(), 0, NULL, FLT_MAX, FLT_MAX, ImVec2(350, 140) );

				ImGui::PopStyleColor();
		
			ImGui::PopID();
		}

	// CURVE_FLOAT
		bool BImGuiGraph::set( const Bfloat& value )
		{
			addValue( value );
			return true;
		}

		bool BImGuiGraph::set( const Buint& value )
		{
			addValue( value );
			return true;
		}

	// CURVE_FLOAT_POLL
		BImGuiGraph_Float_Poll::BImGuiGraph_Float_Poll()
		: BImGuiGraph()
		, m_entity_to_poll(0)
		{
			setProcessing();
		}
		
		bool BImGuiGraph_Float_Poll::set( const Bstring& id, BEntity* value )
		{
			if ( id == "poll_entity" )
			{
				m_entity_to_poll = addChild( "poll_entity", new BEntity_reference() );
				m_entity_to_poll->set( value );
				return true;
			}
			return false;
		}
		
		void BImGuiGraph_Float_Poll::process()
		{
			if ( m_entity_to_poll != 0 )
			{
				addValue( m_entity_to_poll->get_reference()->get_float() );
			}
		}

		bool BImGuiGraph::set( const char* value )
		{
			// std::cout << "set title to " << value << std::endl;
			if ( m_title != value )
			{
				// free(m_value);
				// m_value = strdup(value);
				m_title = value;
				onUpdate();
				return true;
			}
			return false;
		}
		
		bool BImGuiGraph::set( const Bstring& id, const char* value )
		{
			if ( id == "text" )
			{
				// std::cout << "set title to " << value << std::endl;
				if ( m_title != value )
				{
					m_title = value;
					onUpdate();
					return true;
				}
			}
			return false;
		}
		
	
		bool BImGuiGraph::set( const Bstring& id, const Buint& value )
		{
			if ( id == "width" )
			{
				m_width = value;
			}

			else if ( id == "height" )
			{
				m_height = value;
			}
			else
				return false;
			return true;
		}
	
 		BImGuiPen::BImGuiPen()
		: m_r(0)
		, m_g(0)
		, m_b(0)
		{
		}

		void BImGuiPen::construct()
		{
			// auto color = addChild( "color", new BEntity() );
			addChild( "color_r", new BEntity_uint_property() );
			addChild( "color_g", new BEntity_uint_property() );
			addChild( "color_b", new BEntity_uint_property() );
		}

		bool BImGuiPen::set( const Bstring& id, const Buint& value )
		{
			if ( id == "color_r" )
			{
				if ( m_r != value )
				{
					m_r = value;
					// setColor( QColor( m_r, m_g, m_b ) );
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
					// setColor( QColor( m_r, m_g, m_b ) );
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
					// setColor( QColor( m_r, m_g, m_b ) );
					parent()->onAddChild( this );
					onUpdate();
					return true;
				}
			}

			return false;
		}

