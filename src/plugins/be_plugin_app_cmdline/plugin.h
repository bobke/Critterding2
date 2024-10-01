#pragma once
#include "kernel/be_plugin_interface.h"
#include "kernel/be_entity_core_types.h"
#include "be_parser.h"
#include <chrono>
#include <signal.h>

// SCENE
	class Scene: public BEntity
	{
		public:
			Scene() : BEntity() {};
			virtual ~Scene() {};
			virtual void construct();
	};

// BROWSER
	class BEntityBrowser: public BEntity_string
	{
		public:
			BEntityBrowser() : m_pipeR(0), m_ai_runs(false) { setProcessing(); }
			virtual ~BEntityBrowser()
			{
				kill( m_pid, SIGINT);
			};
			void construct();
			virtual void process();
			bool set( const char* value );

		private:
			std::string launchAI(const char* cmd);
			std::string execAI();
			std::string print_entityLine( BEntity* e, bool main=false );
			std::string print_entity( BEntity* e );
			std::string print_value( BEntity* e );
			bool set_value( BEntity* e, const std::string& value );
			BEntity* getFinalChild( const std::string& arg );
			BEntity* current_position;
			BeParser parseH;
			bool m_search_from_root;
			std::string textbox_last;
			
			FILE* m_pipeR;
			int in_pipe[2];    // This pipe is for sending input to the command
			int out_pipe[2];   // This pipe is for reading output from the command
			pid_t m_pid;
			bool m_ai_runs;
		std::chrono::steady_clock::time_point begin;
		std::chrono::steady_clock::time_point end;

		BEntity* textbox;
		
		bool stop;
		bool started;
		// bool unqueried = true;
		bool after_first_command;
		// Read output from the command while it's running
		char buffer[128];
		ssize_t count;
		std::stringstream output;
		std::stringstream session_output;
		
		BEntity* llama_location;
		BEntity* layers_on_gpu;
		BEntity* model_location;
		BEntity* ctx_size;
		BEntity* repeat_penalty;
		BEntity* prompt_assistant;
		BEntity* session_name;
		
	};

// // COMMANDS
// 	class cmd_runquery: public BEntity_trigger
// 	{
// 		public:
// 			cmd_runquery() { };
// 			virtual ~cmd_runquery() {};
// 			bool set();
// 	};
