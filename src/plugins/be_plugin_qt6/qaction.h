#ifndef QACTION_H_INCLUDED
#define QACTION_H_INCLUDED

#include "kernel/be_entity_interface.h"
#include "kernel/be_plugin_base_entity_types.h"
#include <QAction>

		class BQAction : public QAction, public BEntity_trigger
		{
			Q_OBJECT
			public:
				BQAction();
				virtual ~BQAction() {};
				const char* class_id() const { return "QAction"; }

			virtual bool set( const Bstring& id, const char* value );
			void commit();
		};

#endif
