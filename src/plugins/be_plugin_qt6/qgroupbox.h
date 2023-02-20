#ifndef QGROUPBOX_H_INCLUDED
#define QGROUPBOX_H_INCLUDED

#include "kernel/be_entity_interface.h"
#include <QGroupBox>

		class BQGroupBox : public QGroupBox, public BEntity
		{
			Q_OBJECT
			public:
				BQGroupBox();
				virtual ~BQGroupBox() {};
				const char* class_id() const { return "QGroupBox"; }

			virtual bool set( const Bstring& id, const char* value );
			virtual Bbool onAddChild( BEntity* entity );
		};

#endif
