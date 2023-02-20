#ifndef RASTERWINDOW_H_INCLUDED
#define RASTERWINDOW_H_INCLUDED

#include "kernel/be_entity_interface.h"

		class RasterWindow : public QAction, public BEntity_trigger
		{
			Q_OBJECT
			public:
				BQAction();
				virtual ~BQAction() {};

			virtual bool set( const Bstring& id, const char* value );
			void commit();
		};

#endif
