#include "pushbutton.h"
#include <iostream>
#include <sstream>
#include "imgui/imgui.h"

	BImGuiPushButton::BImGuiPushButton()
	: BEntity_trigger()
	, m_width(20)
	, m_height(18)
	{
		setProcessing();
	}

	void BImGuiPushButton::process()
	{
		if ( parent()->class_id() == "ImGuiHBoxLayout" && parent()->children()[0] != this )
			ImGui::SameLine();

		ImGui::PushID( id() );

		if ( ImGui::Button( m_text.c_str(), ImVec2(m_width, m_height) ) )
		{
			auto actions = getChild("_commands", 1);
			if ( actions )
			{
				auto cmdbuffer = topParent()->getChild("_command_buffer", 1);
				if ( cmdbuffer )
				{
					for_all_children_of(actions)
					{
						cmdbuffer->addChild("reference", new BEntity_reference() )->set( *child );
					}
				}
			}
			onUpdate();
		}
		
		ImGui::PopID();
	}

	bool BImGuiPushButton::set( const Bstring& id, const Buint& value )
	{
		if ( id == "value" )
		{
			std::stringstream s;
			s << value;
			m_text = s.str();
		}
		
		else if ( id == "width" )
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

	bool BImGuiPushButton::set( const Bstring& id, const char* value )
	{
		if ( id == "text" )
		{
			m_text = value;
		}
		else
			return false;
		return true;
	}
