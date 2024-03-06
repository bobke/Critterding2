#include "label.h"
#include "groupbox.h"
#include <iostream>
// #include <sstream>
#include "imgui/imgui.h"

	// STRING
		void BImGuiLabel::process()
		{
			if ( parent()->class_id() == "ImGuiHBoxLayout" && parent()->children()[0] != this )
				ImGui::SameLine();

			ImGui::PushID( id() );
			// ImGui::PushItemWidth(m_width);

		// some text
			// ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Hello There");
			// ImGui::Text("Hello, world %d", 123);
			// ImGui::TextColored( ImVec4(1.0f, 1.0f, 1.0f, 1.0f), m_value );
			ImGui::Text( "%s", m_value );
			// ImGui::SameLine(m_width); ImGui::Text("");
		// ImGui::InpuText( m_value, &s );
			
			
			// ImGui::PopItemWidth();
			ImGui::PopID();
		}

		bool BImGuiLabel::set( const char* value )
		{
			if (m_value)
			{
				if ( m_value != value )
				{
					free(m_value);
					m_value = strdup(value);
					onUpdate();
					return true;
				}
			}
			else
			{
				m_value = strdup(value);
					onUpdate();
				return true;
			}
			return false;
		}
		
		bool BImGuiLabel::set( const Bstring& id, const char* value )
		{
			if ( id == "text" )
			{
				if ( m_value != value )
				{
					free(m_value);
					m_value = strdup(value);
					onUpdate();
					return true;
				}
			}
			return false;
		}
		
	
		bool BImGuiLabel::set( const Bstring& id, const Buint& value )
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
	
