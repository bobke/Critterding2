#include "lineedit.h"
#include "groupbox.h"
#include <iostream>
#include <sstream>
#include "imgui/imgui.h"

	// STRING
		void BImGuiLineEdit::process()
		{
			if ( parent()->class_id() == "ImGuiHBoxLayout" && parent()->children()[0] != this )
				ImGui::SameLine();

			ImGui::PushID( id() );
			ImGui::PushItemWidth(m_width);
			
			ImGui::InputText( "", m_value, IM_ARRAYSIZE(m_value), ImGuiInputTextFlags_None );
			if (ImGui::IsItemDeactivatedAfterEdit() )
			{
				// set ( m_buf );
				std::cout << "edited to '" << m_value << "'" << std::endl;
			}

			ImGui::PopItemWidth();
			ImGui::PopID();
		}

		bool BImGuiLineEdit::set( const char* value )
		{
			if (m_value)
			{
				if ( m_value != value )
				{
					free(m_value);
					m_value = strdup(value);
					// std::cout << "setting '" << value << "'" << std::endl;
					// strcpy(m_buf, value);
					// std::cout << "setting '" << value << "' done" << std::endl;
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
		
		bool BImGuiLineEdit::set( const Buint& value )
		{
			std::stringstream s;
			s << value;

			if ( m_value != s.str() )
			{
				// m_value = s.str();
				strcpy(m_value, s.str().c_str());
				onUpdate();
				return true;
			}
			return false;
		}
		
		bool BImGuiLineEdit::set( const Bstring& id, const Buint& value )
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
	
	// UNSIGNED INT
		void BImGuiLineEdit_uint::process()
		{
			if ( parent()->class_id() == "ImGuiHBoxLayout" && parent()->children()[0] != this )
				ImGui::SameLine();

			ImGui::PushID( id() );
			ImGui::PushItemWidth(m_width);
			
			ImGui::InputText( "", m_buf, IM_ARRAYSIZE(m_buf), ImGuiInputTextFlags_CharsDecimal );
			if (ImGui::IsItemDeactivatedAfterEdit() )
			{
				uint num = std::stoul(m_buf);
				set ( num );
			}

			ImGui::PopItemWidth();
			ImGui::PopID();
		}

		bool BImGuiLineEdit_uint::set( const Bstring& id, const Buint& value )
		{
			if ( id == "width" )
			{
				m_width = value;
				std::cout << name() << ": " << m_width << std::endl;
			}
			else if ( id == "height" )
			{
				m_height = value;
			}
			else
				return false;
			return true;
		}

		bool BImGuiLineEdit_uint::set( const Buint& value )
		{
			if ( m_value != value )
			{
				m_value = value;
				std::stringstream s;
				s << value;
				strcpy(m_buf, s.str().c_str());
				onUpdate();
				return true;
			}
			return false;
		}

		bool BImGuiLineEdit_uint::set( const char* value )
		{
			if (m_value)
			{
				unsigned int ui = std::stoul(value);
				if ( m_value != ui )
				{
					m_value = ui;
					// m_value = strdup(value);
					// std::cout << "setting '" << value << "'" << std::endl;
					strcpy(m_buf, value);
					// std::cout << "setting '" << value << "' done" << std::endl;
					onUpdate();
					return true;
				}
			}
			else
			{
				strcpy(m_buf, value);
					onUpdate();
				return true;
			}
			return false;
		}

		bool BImGuiLineEdit_uint::set( const Bint& value )
		{
			if ( m_value != (unsigned int)value )
			{
				m_value = (unsigned int)value;
				std::stringstream s;
				s << value;
				strcpy(m_buf, s.str().c_str());
				onUpdate();
				return true;
			}
			return false;
		}

		bool BImGuiLineEdit_uint::set( const Bfloat& value )
		{
			if ( m_value != (unsigned int)value )
			{
				m_value = (unsigned int)value;
				std::stringstream s;
				s << value;
				strcpy(m_buf, s.str().c_str());
				onUpdate();
				return true;
			}
			return false;
		}

		
	// INT
		void BImGuiLineEdit_int::process()
		{
			if ( parent()->class_id() == "ImGuiHBoxLayout" && parent()->children()[0] != this )
				ImGui::SameLine();

			ImGui::PushID( id() );
			ImGui::PushItemWidth(m_width);
			
			ImGui::InputText( "", m_buf, IM_ARRAYSIZE(m_buf), ImGuiInputTextFlags_CharsDecimal );
			if (ImGui::IsItemDeactivatedAfterEdit() )
			{
				int num = std::stol(m_buf);
				set ( num );
			}

			ImGui::PopItemWidth();
			ImGui::PopID();
		}

		bool BImGuiLineEdit_int::set( const Bint& value )
		{
			if ( m_value != value )
			{
				m_value = value;
				std::stringstream s;
				s << value;
				strcpy(m_buf, s.str().c_str());
				onUpdate();
				return true;
			}
			return false;
		}

		bool BImGuiLineEdit_int::set( const Bstring& id, const Buint& value )
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


	// FLOAT
		void BImGuiLineEdit_float::process()
		{
			if ( parent()->class_id() == "ImGuiHBoxLayout" && parent()->children()[0] != this )
				ImGui::SameLine();

			ImGui::PushID( id() );
			ImGui::PushItemWidth(m_width);
			
			ImGui::InputText( "", m_buf, IM_ARRAYSIZE(m_buf), ImGuiInputTextFlags_CharsDecimal );
			if (ImGui::IsItemDeactivatedAfterEdit() )
			{
				float num = std::stof(m_buf);
				set ( num );
				std::cout << "edited to '" << m_buf << "'" << std::endl;
			}

			ImGui::PopItemWidth();
			ImGui::PopID();
		}

		bool BImGuiLineEdit_float::set( const Bfloat& value )
		{
			if ( m_value != value )
			{
				m_value = value;
				std::stringstream s;
				s << value;
				strcpy(m_buf, s.str().c_str());
				onUpdate();
				return true;
			}
			return false;
		}

		bool BImGuiLineEdit_float::set( const Bstring& id, const Buint& value )
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

