#ifndef QBOXLAYOUTS_H_INCLUDED
#define QBOXLAYOUTS_H_INCLUDED

#include "kernel/be_entity_interface.h"
#include <QVBoxLayout>

	// QVBOXLAYOUT
		class BQVBoxLayout : public QVBoxLayout, public BEntity
		{
			Q_OBJECT
			public:
				BQVBoxLayout();
				virtual ~BQVBoxLayout() {};
				const char* class_id() const { return "QVBoxLayout"; }
				
				virtual Bbool onAddChild( BEntity* entity );
// 				virtual Bbool onRemoveChild( BEntity* entity );
		};

	// QHBOXLAYOUT
		class BQHBoxLayout : public QHBoxLayout, public BEntity
		{
			Q_OBJECT
			public:
				BQHBoxLayout();
				virtual ~BQHBoxLayout() {};
				const char* class_id() const { return "QHBoxLayout"; }

				virtual Bbool onAddChild( BEntity* entity );
// 				virtual Bbool onRemoveChild( BEntity* entity );
		};
		
#endif
