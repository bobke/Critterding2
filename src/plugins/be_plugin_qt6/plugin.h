#ifndef PLUGIN_H_INCLUDED
#define PLUGIN_H_INCLUDED

#include "kernel/be_timer.h"
class QApplication;

#include "kernel/be_plugin_interface.h"

	// SCENE
		class Scene: public BEntity
		{
			public:
				Scene() : BEntity() {};
				virtual ~Scene() {};
			private:
		};
		
	// QAPPLICATION
		class BQApplicationWrapper: public BEntity
		{
			public:
				BQApplicationWrapper();
				virtual ~BQApplicationWrapper();
				int m_fakeargc = 1;
				char* m_fakeParam1 = 0;
				char** m_fakeParam = &m_fakeParam1;
				
				virtual void process();
			private:
				QApplication* m_qapp;
		};

	// QAPPLICATION SPAWNER
		class BQApplicationSpawner: public BEntity
		{
			public:
				BQApplicationSpawner() {};
				virtual ~BQApplicationSpawner() {};
				BEntity* getChildCustom( BEntity* parent, const char* name );
		};
		

#endif
