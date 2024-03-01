#include "checkbox.h"
#include "imgui/imgui.h"

	BImGuiCheckBox::BImGuiCheckBox()
	: BEntity_bool()
	, m_width(20)
	, m_height(18)
	{
		setProcessing();
	}

	void BImGuiCheckBox::process()
	{
		if ( parent()->class_id() == "ImGuiHBoxLayout" && parent()->children()[0] != this )
			ImGui::SameLine();

		ImGui::PushID( id() );

		if ( ImGui::Checkbox( name().c_str(), &m_value ) )
		{
			onUpdate();
		}

		ImGui::PopID();
	}

	bool BImGuiCheckBox::set( const Bstring& id, const Buint& value )
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

	bool BImGuiCheckBox::set( const Bstring& id, const char* value )
	{
		if ( id == "text" )
		{
			m_text = value;
		}
		else
			return false;
		return true;
	}	
