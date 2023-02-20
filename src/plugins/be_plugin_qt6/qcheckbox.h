#ifndef QCHECKBOX_H_INCLUDED
#define QCHECKBOX_H_INCLUDED

#include "kernel/be_entity_interface.h"
#include "kernel/be_entity_core_types.h"
#include <QCheckBox>

	// QLINEEDIT
		class BQCheckBox : public QCheckBox, public BEntity_bool
		{
			Q_OBJECT
			public:
				BQCheckBox();
				virtual ~BQCheckBox() {};
				const char* class_id() const { return "QCheckBox"; }
				bool set( BEntity* entity );
				bool set( const Bbool& value );

			private Q_SLOTS:
				void onChange();
			private:
// 				Bfloat m_float; // HACK
				Buint m_width;
				Buint m_height;
		};

#endif
