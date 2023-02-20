#ifndef QMENU_H_INCLUDED
#define QMENU_H_INCLUDED

#include "kernel/be_entity_interface.h"
#include <QMenu>

		class BQMenu : public QMenu, public BEntity
		{
			Q_OBJECT
			public:
				BQMenu();
				virtual ~BQMenu() {};
				const char* class_id() const { return "QMenu"; }

			virtual bool set( const Bstring& id, const char* value );
			virtual Bbool onAddChild( BEntity* entity );
		};

#endif
