#include "rasterwindow.h"
#include "kernel/be_plugin_base_entity_types.h"

		RasterWindow::RasterWindow()
		{
		}

		void RasterWindow::construct()
		{
			// CREATE A RASTER WINDOW
	// 		if (false)
			{
				BEntity* qrasterwindow = addChild( "QT RasterWindow", "QRasterWindow" );
				qrasterwindow->setFps(8);

				// SETUP WINDOW
					qrasterwindow->set("on_close_destroy_entity", qrasterwindow);
					qrasterwindow->set("x", Buint(1200));
					qrasterwindow->set("y", Buint(50));
					qrasterwindow->set("width", Buint(705));
					qrasterwindow->set("height", Buint(101));
					
				// COMPOSITE && FOR EACH CPU
					for_all_children_of( topParent()->getChild("CPU Info", 10) )
					{
						// FREQUENCY
							BEntity* mhz = (*child)->getChild("mhz");
							if ( mhz )
							{
								BEntity* mhz_uint = qrasterwindow->addChild( "mhz", new BEntity_uint() );
		//							line_edit->set( (*child3)->get_float() );
								mhz->connectServerServer(mhz_uint);
							}

						// HIGHEST FREQUENCY
							BEntity* mhz_highest = (*child)->getChild("mhz_highest");
							if ( mhz_highest )
							{
								BEntity* mhz_uint_highest = qrasterwindow->addChild( "mhz_highest", new BEntity_uint() );
		//							line_edit->set( (*child3)->get_float() );
								mhz_highest->connectServerServer(mhz_uint_highest);
							}

						// PERCENT
							BEntity* percent_idle = (*child)->getChild("workload_percent")->getChild("perc_idle");
							if ( percent_idle )
							{
								BEntity* perc_float = qrasterwindow->addChild( percent_idle->name(), new BEntity_float() );
		//							line_edit->set( (*child3)->get_float() );
								percent_idle->connectServerServer(perc_float);
							}
					}
			}
		}
