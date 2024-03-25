#include "plugin.h"
#include "plugins/be_plugin_glfw/plugin.h"
#include "imgui/imgui.h"
// #include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "lineedit.h"
#include "pushbutton.h"
#include "groupbox.h"
#include "boxlayouts.h"
#include "checkbox.h"
#include "label.h"
#include "graph.h"
#include <iostream>
#include <sstream>

	void BImGuiContext::construct()
	{
		m_capture_keyboard = addChild("capture_keyboard", "bool");
		m_capture_mouse = addChild("capture_mouse", "bool");
		
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch
		// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	}

	bool BImGuiContext::set( const Bstring& id, BEntity* value )
	{
		if ( id == "init_glfw" )
		{
			// Setup Platform/Renderer backends
				auto glwindow = dynamic_cast<BGLWindow*>( value );
				ImGui_ImplGlfw_InitForOpenGL( glwindow->m_window, true );          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
				// ImGui_ImplGlfw_SetCallbacksChainForAllWindows(false);
				ImGui_ImplOpenGL3_Init();
		}
		else if ( id == "init_sdl2" )
		{
		}
		else
		{
			return false;
		}
		return true;
	}

	void BImGuiContext::process()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		m_capture_keyboard->set( ImGui::GetIO().WantCaptureKeyboard );
		m_capture_mouse->set( ImGui::GetIO().WantCaptureMouse );
	}

	BImGuiContext::~BImGuiContext()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	
	void BImGuiWindow::construct()
	{
		m_destroy_entity_on_close = this;

		m_color[0] = 0.5f;
		m_color[1] = 0.5f;
		m_color[2] = 0.5f;
		m_color[3] = 1.0f;
	}

	void BImGuiWindow::process()
	{
		ImGui::PushID( id() );
		// ImGui::SetNextWindowContentSize(ImVec2(0,0));
		ImGui::Begin(m_text.c_str(), &m_tool_active, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize);
		
		if ( !m_tool_active )
		{
			// add remove command to the command buffer
			BEntity* cmdbuffer = topParent()->getChild("_command_buffer");
			if ( cmdbuffer )
			{
				cmdbuffer->addChild("remove", new BEntity_reference() )->set( m_destroy_entity_on_close );
			}
		}
		
		// if (ImGui::BeginMenuBar())
		// {
		// 	if (ImGui::BeginMenu("File"))
		// 	{
		// 		if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
		// 		if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
		// 		if (ImGui::MenuItem("Close", "Ctrl+W"))  { m_tool_active = false; }
		// 		ImGui::EndMenu();
		// 	}
		// 	ImGui::EndMenuBar();
		// }

// 		// some text
// 			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Hello There");
// 			ImGui::Text("Hello, world %d", 123);
// 			
// 		// a button
// 			if (ImGui::Button("Save"))
// 			{
// 				/*MySaveFunction()*/;
// 			}
		
		// // some text
		// 	static char buf[20];
		// 	ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
		// 	if (ImGui::IsItemDeactivatedAfterEdit() )
		// 	// if (ImGui::IsItemEdited() )
		// 	{
		// 		std::cout << "edited" << std::endl;
		// 	}
		
		// // a slider
		// 	static float f;
		// 	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
  // 
		// // checkboxes
		// 	ImGui::Checkbox("capturekeyboard", &ImGui::GetIO().WantCaptureKeyboard);
		// 	ImGui::Checkbox("capturemouse", &ImGui::GetIO().WantCaptureMouse);
  // 
		// // Edit a color stored as 4 floats
		// 	ImGui::ColorEdit4("Color", m_color);
  // 
		// // Generate samples and plot them
		// 	float samples[100];
		// 	for (int n = 0; n < 100; n++)
		// 		samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
		// 	ImGui::PlotLines("Samples", samples, 100);

		// // Display contents in a scrolling region
		// 	ImGui::TextColored(ImVec4(1,1,0,1), "Important Stuff");
		// 	ImGui::BeginChild("Scrolling");
		// 	for (int n = 0; n < 50; n++)
		// 		ImGui::Text("%04d: Some text", n);
		// 	ImGui::EndChild();
		// 	ImGui::End();
	}

	// PROPERTIES
		bool BImGuiWindow::set( const Bstring& id, BEntity* value )
		{
			if ( id == "on_close_destroy_entity" )
			{
				compareAndSetValue( m_destroy_entity_on_close, value );
				return true;
			}
			return false;
		}
		
		bool BImGuiWindow::set( const Bstring& id, const Buint& value )
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

		bool BImGuiWindow::set( const Bstring& id, const char* value )
		{
			if ( id == "title" )
			{
				m_text = value;
			}
			else
				return false;
			return true;
		}

	void BImGuiWindow_end::process()
	{
		ImGui::End();
		ImGui::PopID();
	}
	
	void BImGuiRender::process()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// FIXME DOESN'T WORK
		// Update and Render additional Platform Windows 
		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}

	void BImGuiDemoWindow::process()
	{
		ImGui::ShowDemoWindow();
	}
	
	void BTranslate_QT_IMGUI::construct()
	{
		// COMMENTING SWITCHES FROM IMGUI TO QT
		add( "QMainWindow", 				"ImGuiWindow" );
		add( "QMainWindow_end",				"ImGuiWindow_end" );
		add( "QLineEdit",					"ImGuiLineEdit_uint" );
		add( "QLineEdit_float",				"ImGuiLineEdit_float" );
		add( "QLineEdit_int",				"ImGuiLineEdit_int" );
		add( "QLineEdit_uint",				"ImGuiLineEdit_uint" );
		add( "QLineEdit_string",			"ImGuiLineEdit" );
		// add( "QLabel", 						"ImGuiPushButton" );
		add( "QLabel", 						"ImGuiLabel" );
		add( "QCheckBox",					"ImGuiCheckBox" );
		add( "QPushButton",					"ImGuiPushButton" );
		add( "QPushButtonDraggable",		"ImGuiPushButton" );
		add( "QPushButtonDragAndDroppable",	"ImGuiPushButton" );
		add( "QVBoxLayout",					"ImGuiVBoxLayout" );
		add( "QHBoxLayout",					"ImGuiHBoxLayout" );
		add( "QGroupBox",					"ImGuiGroupBox" );
		add( "QGroupBox_end",				"ImGuiGroupBox_end" );
		add( "QwtPlot",						"entity" );
		add( "QwtCurve",					"ImGuiGraph" );
		add( "QwtCurve_Poll",				"ImGuiGraph_Float_Poll" );
		add( "QPen",						"ImGuiPen" );
		
		
	}
	
	// const char* BTranslate_QT_IMGUI::get_string( const Bstring& id )
	// {
	// 	return get( id.c_str() );
	// }
	

// ---- FACTORIES
	enum CLASS
	{
		  PLUGIN_INFO
		// , SCENE
		, IMGUI_CONTEXT
		, IMGUI_TRANSLATE_QT_IMGUI
		, IMGUI_WINDOW
		, IMGUI_WINDOW_END
		, IMGUI_LINEEDIT
		, IMGUI_LINEEDIT_INT
		, IMGUI_LINEEDIT_UINT
		, IMGUI_LINEEDIT_FLOAT
		, IMGUI_PUSHBUTTON
		, IMGUI_LABEL
		, IMGUI_VBOXLAYOUT
		, IMGUI_HBOXLAYOUT
		, IMGUI_GROUPBOX
		, IMGUI_GROUPBOX_END
		, IMGUI_CHECKBOX
		, IMGUI_RENDER
		, IMGUI_GRAPH
		, IMGUI_GRAPH_FLOAT_POLL
		, IMGUI_PEN
		, IMGUI_DEMOWINDOW
	};

	extern "C" BEntity* create( BEntity* parent, const Buint type )
	{
		// PLUGIN DESCRIPTION ENTITY
			if ( type == PLUGIN_INFO )
			{
				BClassesHelper i;
					// i.addClass( parent, CLASS::SCENE, "Scene" );
					i.addClass( parent, CLASS::IMGUI_CONTEXT, "ImGuiContext" );
					i.addClass( parent, CLASS::IMGUI_TRANSLATE_QT_IMGUI, "Translate_QT_IMGUI" );
					i.addClass( parent, CLASS::IMGUI_WINDOW, "ImGuiWindow" );
					i.addClass( parent, CLASS::IMGUI_WINDOW_END, "ImGuiWindow_end" );
					i.addClass( parent, CLASS::IMGUI_LINEEDIT, "ImGuiLineEdit" );
					i.addClass( parent, CLASS::IMGUI_LINEEDIT_UINT, "ImGuiLineEdit_int" );
					i.addClass( parent, CLASS::IMGUI_LINEEDIT_UINT, "ImGuiLineEdit_uint" );
					i.addClass( parent, CLASS::IMGUI_LINEEDIT_FLOAT, "ImGuiLineEdit_float" );
					i.addClass( parent, CLASS::IMGUI_PUSHBUTTON, "ImGuiPushButton" );
					i.addClass( parent, CLASS::IMGUI_LABEL, "ImGuiLabel" );
					i.addClass( parent, CLASS::IMGUI_VBOXLAYOUT, "ImGuiVBoxLayout" );
					i.addClass( parent, CLASS::IMGUI_HBOXLAYOUT, "ImGuiHBoxLayout" );
					i.addClass( parent, CLASS::IMGUI_GROUPBOX, "ImGuiGroupBox" );
					i.addClass( parent, CLASS::IMGUI_GROUPBOX_END, "ImGuiGroupBox_end" );
					i.addClass( parent, CLASS::IMGUI_CHECKBOX, "ImGuiCheckBox" );
					i.addClass( parent, CLASS::IMGUI_RENDER, "ImGuiRender" );
					i.addClass( parent, CLASS::IMGUI_GRAPH, "ImGuiGraph" );
					i.addClass( parent, CLASS::IMGUI_GRAPH_FLOAT_POLL, "ImGuiGraph_Float_Poll" );
					i.addClass( parent, CLASS::IMGUI_PEN, "ImGuiPen" );
					i.addClass( parent, CLASS::IMGUI_DEMOWINDOW, "ImGuiDemoWindow" );
				return 0;
			}

		// ENTITIES
			else
			{
				BEntity* i(0);
				
				/*if ( type == CLASS::SCENE )
					i = new Scene();
				else */if ( type == CLASS::IMGUI_CONTEXT )
					i = new BImGuiContext();
				else if ( type == CLASS::IMGUI_TRANSLATE_QT_IMGUI )
					i = new BTranslate_QT_IMGUI();
				else if ( type == CLASS::IMGUI_WINDOW )
					i = new BImGuiWindow();
				else if ( type == CLASS::IMGUI_WINDOW_END )
					i = new BImGuiWindow_end();
				else if ( type == CLASS::IMGUI_LINEEDIT )
					i = new BImGuiLineEdit();
				else if ( type == CLASS::IMGUI_LINEEDIT_INT )
					i = new BImGuiLineEdit_int();
				else if ( type == CLASS::IMGUI_LINEEDIT_UINT )
					i = new BImGuiLineEdit_uint();
				else if ( type == CLASS::IMGUI_LINEEDIT_FLOAT )
					i = new BImGuiLineEdit_float();
				else if ( type == CLASS::IMGUI_PUSHBUTTON )
					i = new BImGuiPushButton;
				else if ( type == CLASS::IMGUI_LABEL )
					i = new BImGuiLabel;
				else if ( type == CLASS::IMGUI_VBOXLAYOUT )
					i = new BImGuiVBoxLayout;
				else if ( type == CLASS::IMGUI_HBOXLAYOUT )
					i = new BImGuiHBoxLayout;
				else if ( type == CLASS::IMGUI_GROUPBOX )
					i = new BImGuiGroupBox;
				else if ( type == CLASS::IMGUI_GROUPBOX_END )
					i = new BImGuiGroupBox_end;
				else if ( type == CLASS::IMGUI_CHECKBOX )
					i = new BImGuiCheckBox;
				else if ( type == CLASS::IMGUI_RENDER )
					i = new BImGuiRender();
				else if ( type == CLASS::IMGUI_GRAPH )
					i = new BImGuiGraph();
				else if ( type == CLASS::IMGUI_GRAPH_FLOAT_POLL )
					i = new BImGuiGraph_Float_Poll();
				else if ( type == CLASS::IMGUI_PEN )
					i = new BImGuiPen();
				else if ( type == CLASS::IMGUI_DEMOWINDOW )
					i = new BImGuiDemoWindow();
					

				return i;
			}
	}

	extern "C" void destroy( BEntity* p )
	{
		delete p;
	}

