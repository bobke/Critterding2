#ifndef RASTERWINDOW_H_INCLUDED
#define RASTERWINDOW_H_INCLUDED

#include "kernel/be_entity_interface.h"

	class RasterWindow : public BEntity
	{
		public:
			RasterWindow();
			virtual ~RasterWindow() {};
			virtual void construct();
	};

#endif
