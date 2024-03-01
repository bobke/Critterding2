#include "groupbox.h"
#include "imgui/imgui.h"
#include <sstream>

	void BImGuiGroupBox::process()
	{
		if ( parent()->class_id() == "ImGuiHBoxLayout" && parent()->children()[0] != this )
			ImGui::SameLine();

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;

		const bool disable_mouse_wheel = false;
		if ( disable_mouse_wheel )
			window_flags |= ImGuiWindowFlags_NoScrollWithMouse;
		
		const bool disable_menu = true;
		if ( !disable_menu )
			window_flags |= ImGuiWindowFlags_MenuBar;

		// std::stringstream s;
		// s << "##groupbox" << id();
		// ImGui::BeginChild( s.str().c_str(), ImVec2(300, 260), ImGuiChildFlags_Border, window_flags);

		ImGui::PushID( id() );
		// ImGui::BeginChild( "groupbox", ImVec2(400, 560), ImGuiChildFlags_Border, window_flags);
		
		
		// ImGui::BeginChild( "groupbox", ImVec2(m_width, m_height), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeY | ImGuiChildFlags_ResizeX, window_flags);
		ImGui::BeginChild( "groupbox", ImVec2(0, 0), ImGuiChildFlags_Border | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AutoResizeX, window_flags);
		
	}

	bool BImGuiGroupBox::set( const Bstring& id, const Buint& value )
	{
		if ( id == "title" )
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

	bool BImGuiGroupBox::set( const Bstring& id, const char* value )
	{
		if ( id == "text" )
		{
			m_text = value;
		}
		else
			return false;
		return true;
	}

	void BImGuiGroupBox_end::process()
	{
		ImGui::EndChild();
		ImGui::PopID();
	}
