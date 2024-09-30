#include "llama_gui.h"
#include "kernel/be_lib_handler.h"

	void LLama_GUI::construct()
	{
		setName( "llama.cpp GUI" );

		auto bin = topParent()->getChild( "bin", 1 );
		auto qt_app = bin->getChild( "QT Application", 2 );

		// 	COMMANDS
			// auto commands = addChild( "commands", "entity" );
			// auto cmd_calcEntity = commands->addChild( "calc", new cmd_calc() );

		// QWINDOW
			auto qwindow = qt_app->addChild( "llamacpp_window", "QMainWindow" );
			qwindow->addChild( "title", "string_property" )->set( name().c_str() );
			qwindow->addChild( "x", "uint_property" )->set(Buint(750));
			qwindow->addChild( "y", "uint_property" )->set(Buint(20));
			qwindow->addChild( "width", "uint_property" )->set(Buint(700));
			qwindow->addChild( "height", "uint_property" )->set(Buint(230));
			// qwindow->set("on_close_destroy_entity", this);

		// VERT LAYOUT
			auto vl = qwindow->addChild( "Vlayout", "QVBoxLayout" );

		// LLAMA LOCATION
		{
			auto hl = vl->addChild( "Hlayout", "QHBoxLayout" );
			auto llama_location_label = hl->addChild( "label_llama_location", "QLabel" );
			llama_location_label->set( "llama_location" );
			llama_location_label->set( "width", (Buint)130 );
			auto llama_location = hl->addChild( "llama_location", "QLineEdit_string" );
		}

		// LAYERS ON GPU
		{
			auto hl = vl->addChild( "Hlayout", "QHBoxLayout" );
			auto layers_on_gpu_label = hl->addChild( "label_layers_on_gpu", "QLabel" );
			layers_on_gpu_label->set( "layers_on_gpu" );
			layers_on_gpu_label->set( "width", (Buint)130 );
			auto layers_on_gpu = hl->addChild( "layers_on_gpu", "QLineEdit_uint" );
		}

		// MODEL LOCATION
		{
			auto hl = vl->addChild( "Hlayout", "QHBoxLayout" );
			auto model_location_label = hl->addChild( "label_model_location", "QLabel" );
			model_location_label->set( "model_location" );
			model_location_label->set( "width", (Buint)130 );
			auto model_location = hl->addChild( "model_location", "QLineEdit_string" );
		}

		// CTX_SIZE
		{
			auto hl = vl->addChild( "Hlayout", "QHBoxLayout" );
			auto ctx_size_label = hl->addChild( "label_ctx_size", "QLabel" );
			ctx_size_label->set( "ctx_size" );
			ctx_size_label->set( "width", (Buint)130 );
			auto ctx_size = hl->addChild( "ctx_size", "QLineEdit_uint" );
		}

		// REPEAT PENALTY
		{
			auto hl = vl->addChild( "Hlayout", "QHBoxLayout" );
			auto repeat_penalty_label = hl->addChild( "label_repeat_penalty", "QLabel" );
			repeat_penalty_label->set( "repeat_penalty" );
			repeat_penalty_label->set( "width", (Buint)130 );
			auto repeat_penalty = hl->addChild( "repeat_penalty", "QLineEdit_float" );
		}

		// PROMPT ASSISTANT
		{
			auto hl = vl->addChild( "Hlayout", "QHBoxLayout" );
			auto prompt_assistant_label = hl->addChild( "label_prompt_assistant", "QLabel" );
			prompt_assistant_label->set( "prompt_assistant" );
			prompt_assistant_label->set( "width", (Buint)130 );
			auto prompt_assistant = hl->addChild( "prompt_assistant", "QLineEdit_string" );
		}
		
		// // SESSION NAME
		// {
		// 	auto hl = vl->addChild( "Hlayout", "QHBoxLayout" );
		// 	auto session_name_label = hl->addChild( "label_session_name", "QLabel" );
		// 	session_name_label->set( "session_name" );
		// 	session_name_label->set( "width", (Buint)130 );
		// 	auto session_name = hl->addChild( "session_name", "QLineEdit_string" );
		// }
		
	}
