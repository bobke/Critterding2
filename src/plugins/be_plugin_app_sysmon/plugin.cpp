#include "plugin.h"
#include "kernel/be_lib_handler.h"
#include "kernel/be_timer.h"
// #include "kernel/be_profiler.h"
#include "kernel/be_entity_children_handler.h"
#include "kernel/be_entity_id_handler.h"
#include <iostream>
#include <sstream>
#include <fstream>
// #include <chrono>
// #include <thread>

#include "rasterwindow.h"


// ---- FACTORIES
	enum CLASS
	{
		  PLUGIN_INFO
		, SCENE
		, SYSMON
		// , GLWIN
	};

	extern "C" BEntity* create( BEntity* parent, const Buint type )
	{
// 		std::cout << "LIB CREATE:: type: " << type  << std::endl;
		// PLUGIN DESCRIPTION ENTITY
			if ( type == PLUGIN_INFO )
			{
				BClassesHelper i;
					i.addClass( parent, CLASS::SCENE, "Scene" );
					i.addClass( parent, CLASS::SYSMON, "SystemMonitor" );
					// i.addClass( parent, CLASS::GLWIN, "GlWindow" );
				return 0;
			}

		// ENTITIES
			else
			{
				BEntity* i(0);
				
				if ( type == CLASS::SCENE )
					i = new Scene();
				else if ( type == CLASS::SYSMON )
					i = new BSystemMonitor();
				// else if ( type == CLASS::GLWIN )
					// i = new BGLApp();

				return i;
			}
	}

	extern "C" void destroy(BEntity* p)
	{
// 		std::cout << "LIB DESTROY:: " << p->id() << std::endl;
		delete p;
	}

	void Scene::construct()
	{
		// FIXME this is the same in app_admin_window -> make this a function
		std::cout << "Scene::construct()" << std::endl;

		// LOAD QT APP
			pluginManager()->load( "qt6", "src/plugins/be_plugin_qt6", "be_plugin_qt6" );
			auto spawner = addChild( "spawner", "QApplicationSpawner" );
			auto t_parent_to_add_to = spawner->getChildCustom( this );
			removeChild( spawner );

		// load admin window
		auto admin_window = t_parent_to_add_to->addChild("SystemMonitor App", new BSystemMonitor());

		// kill the scene when the main window is closed
		auto qmainwindow = admin_window->getChild("QT MainWindow");
		qmainwindow->set("on_close_destroy_entity", this);

		// load a opengltest
		auto glApp = t_parent_to_add_to->addChild("GLAppApp", new BGLApp());
// 		auto sdlwin = glApp->getChild("GLWindow");
// 		sdlwin->set("on_close_destroy_entity", this);
	}

	void BSystemMonitor::construct()
	{
		// std::cout << "BSystemMonitor::construct()" << std::endl;

		// THREADS
// 			pluginManager()->load( "thread", "src/plugins/be_plugin_thread", "be_plugin_thread" );

		// M_TIMER
			if ( m_timer_s_total == 0 )
			{
				auto found_sys = topParent()->getChild("sys", 1);
				if ( !found_sys )
				{
					found_sys = topParent()->addChild( "sys", new BEntity() );
				}
				auto timer = found_sys->getChild("timer", 1);
				if ( !timer )
				{
					timer = found_sys->addChild( "timer", new BTimer() );
				}
				m_timer_s_total = timer->getChild("s_total", 1);
				m_timer_frame = timer->getChild("frame", 1);
			}

		// BASE TYPES
			pluginManager()->load( "basetypes", "src/kernel", "be_base_entity_types" );
			
		// GUI
			pluginManager()->load( "qt6", "src/plugins/be_plugin_qt6", "be_plugin_qt6" );

		// QWINDOW
			auto qwindow = addChild( "QT MainWindow", "QMainWindow" );
			qwindow->addChild( "title", "string_property" )->set("System Monitor");
			qwindow->addChild( "x", "uint_property" )->set(Buint(2250));
			qwindow->addChild( "y", "uint_property" )->set(Buint(40));
			qwindow->addChild( "width", "uint_property" )->set(Buint(300));
			qwindow->addChild( "height", "uint_property" )->set(Buint(226));
			qwindow->set("on_close_destroy_entity", this);

// 				qwindow->set("x", Buint(1200));
// 				qwindow->set("y", Buint(180));
// 				qwindow->set("width", Buint(705));
// 				qwindow->set("height", Buint(150));
			
// 		// LAUNCH ON THREAD1
// // 			BEntity* t_thread1 = addChild( "Thread 1", "thread" );
// // 			BEntity* t_qtapp = t_thread1->addChild( "QT Application", "QApplication" );
// 			BEntity* t_qtapp = addChild( "QT Application", "QApplication" );
// 			BEntity* qwindow;


			BEntity* general_layout_V;
			
// 		// CREATE A WINDOW
// 			qwindow = t_qtapp->addChild( "QT Window", "QWindow" );
// 			
// 			// SETUP WINDOW
// 				qwindow->set("on_close_destroy_entity", this);
// 				qwindow->set("x", Buint(1200));
// 				qwindow->set("y", Buint(180));
// 				qwindow->set("width", Buint(705));
// 				qwindow->set("height", Buint(150));

		// GENERAL V LAYOUT
			general_layout_V = qwindow->addChild( "QT VBoxlayout", "QVBoxLayout" );
			
		// GENERAL V LAYOUT
			BEntity* general_layout_H = general_layout_V->addChild( "QT VBoxlayout", "QVBoxLayout" );

// 			// PROGRAM SETTINGS
// 			{
// 				// V LAYOUT
// 					BEntity* settings_layout_V = general_layout_H->addChild( "QT VBoxlayout for settings", "QVBoxLayout" );
// 				
// 					BEntity* layout_H = settings_layout_V->addChild( "HBox", "QHBoxLayout" );
// 					{
// 						// BACKGROUND FPS
// 							BEntity* text_background_fps = layout_H->addChild( "text_background_fps", "QLabel" );
// 							text_background_fps->set("text", "strive fps");
// 							m_line_edit_fps_background = layout_H->addChild( "fps_background", "QLineEdit" );
// 							m_line_edit_fps_background->set("width", Buint(164));
// 							m_line_edit_fps_background->set("height", Buint(28));
// 					}
// 
// 					BEntity* layout_H2 = settings_layout_V->addChild( "HBox", "QHBoxLayout" );
// 					{
// 						// VULKAN SCENE LOADMODEL FPS
// 							BEntity* vk_loadmodel_fps = layout_H2->addChild( "vk_loadmodel_fps", "QLineEdit" );
// 							vk_loadmodel_fps->set("vulkan scene fps");
// 							m_line_edit_vk_loadmodel_fps = layout_H2->addChild( "vk_loadmodel_fps", "QLineEdit" );
// 							m_line_edit_vk_loadmodel_fps->set("width", Buint(164));
// 
// 					}
// 			}
			
			// STATS V LAYOUT
				BEntity* layout_V = general_layout_H->addChild( "QT VBoxlayout for stats", "QVBoxLayout" );

				// LINE EDITS
					BEntity* layout_H = layout_V->addChild( "frame_counter", "QHBoxLayout" );
					{
						BEntity* text_frame_counter = layout_H->addChild( "text_frame_counter", "QLabel" );
						text_frame_counter->set("text", "current frame");
						text_frame_counter->set("width", Buint(164));
						m_line_edit_frame_counter = layout_H->addChild( "Frames", "QLineEdit" );
						m_line_edit_frame_counter->set("frames");
						m_line_edit_frame_counter->set("width", Buint(164));
						m_line_edit_frame_counter->set("height", Buint(28));
					}

					layout_H = layout_V->addChild( "current fps", "QHBoxLayout" );
					{
						BEntity* text_current_fps = layout_H->addChild( "text_current_fps", "QLabel" );
						text_current_fps->set("text", "current fps");
						text_current_fps->set("width", Buint(164));
						m_line_edit_fps_cur = layout_H->addChild( "Current FPS", "QLineEdit" );
						m_line_edit_fps_cur->set("current fps");
						m_line_edit_fps_cur->set("width", Buint(164));
						m_line_edit_fps_cur->set("height", Buint(28));
					}

					layout_H = layout_V->addChild( "average fps", "QHBoxLayout" );
					{
						BEntity* text_average_fps = layout_H->addChild( "text_average_fps", "QLabel" );
						text_average_fps->set("text", "average fps");
						text_average_fps->set("width", Buint(164));
						m_line_edit_fps_avg = layout_H->addChild( "Average FPS", "QLineEdit" );
						m_line_edit_fps_avg->set("average fps");
						m_line_edit_fps_avg->set("width", Buint(164));
						m_line_edit_fps_avg->set("height", Buint(28));
					}
					
					layout_H = layout_V->addChild( "entities", "QHBoxLayout" );
					{
						BEntity* text_entities = layout_H->addChild( "text_entities", "QLabel" );
						text_entities->set("text", "entities");
						text_entities->set("width", Buint(164));
						m_line_edit_entities = layout_H->addChild( "Entities", "QLineEdit" );
						m_line_edit_entities->set("entities");
						m_line_edit_entities->set("width", Buint(164));
						m_line_edit_entities->set("height", Buint(28));
					}

					layout_H = layout_V->addChild( "last entity id", "QHBoxLayout" );
					{
						BEntity* text_last_entity_id = layout_H->addChild( "text_last_entity_id", "QLabel" );
						text_last_entity_id->set("text", "last entity id");
						text_last_entity_id->set("width", Buint(164));
						m_line_edit_last_entity_id = layout_H->addChild( "Last Entity ID", "QLineEdit" );
						m_line_edit_last_entity_id->set("last entity id");
						m_line_edit_last_entity_id->set("width", Buint(164));
						m_line_edit_last_entity_id->set("height", Buint(28));
					}
					
					layout_H = layout_V->addChild( "uptime", "QHBoxLayout" );
					{
						BEntity* text_uptime = layout_H->addChild( "text_uptime", "QLabel" );
						text_uptime->set("text", "uptime");
						text_uptime->set("width", Buint(164));
						m_line_edit_uptime = layout_H->addChild( "Uptime", "QLineEdit_float" );
						m_line_edit_uptime->set("uptime");
						m_line_edit_uptime->set("width", Buint(164));
						m_line_edit_uptime->set("height", Buint(28));
					}

					layout_H = layout_V->addChild( "memory", "QHBoxLayout" );
					{
						BEntity* text_memory = layout_H->addChild( "text_memory", "QLabel" );
						text_memory->set("text", "memory");
						text_memory->set("width", Buint(164));
						m_line_edit_memory = layout_H->addChild( "Memory", "QLineEdit_string" );
						m_line_edit_memory->set("memory");
						m_line_edit_memory->set("width", Buint(165));
						m_line_edit_memory->set("height", Buint(28));
					}

			if ( false )
			{
				// SYSTEM OBJECTS
					pluginManager()->load( "system", "src/plugins/be_plugin_system", "be_plugin_system" );
					
					BEntity* system_objects = addChild( "System Objects", new BEntity() );
					
						BEntity* t_CPUInfo = system_objects->addChild( "CPU Info", "CPUInfo" );
						t_CPUInfo->setFps(8);

					// CREATE A RASTER WINDOW
					auto rasterWindow = system_objects->addChild( "RasterWindow", new RasterWindow() );
					// auto rasterWindow = t_qtapp->addChild( "RasterWindow", new RasterWindow() );
					rasterWindow->set("title", "CPU logical cores"); // FIXME
					rasterWindow->getChild("QT RasterWindow", 1)->set("on_close_destroy_entity", system_objects);

						
				// CPU FREQUENCY LINEEDITS
					// V LAYOUT
					if ( false )
					{
						BEntity* mhz_layout_V = general_layout_H->addChild( "QT VBoxlayout for mhz", "QVBoxLayout" );
						BEntity* mhz_highest_layout_V = general_layout_H->addChild( "QT VBoxlayout for mhz-highest", "QVBoxLayout" );

						// BEntity* freq = t_CPUInfo->getChild(t_CPUInfo, "frequencies", 3);
						bool first(true);
						// for_all_children_of(freq)
						for_all_children_of(t_CPUInfo)
						{
							// std::cout << "*** " << (*child)->name() << std::endl;
							
							BEntity* line_edit = mhz_layout_V->addChild( (*child)->name(), "QLineEdit" );
							line_edit->set("width", Buint(40));

							BEntity* line_edit_highest = mhz_highest_layout_V->addChild( (*child)->name(), "QLineEdit" );
							line_edit_highest->set("width", Buint(40));

							if ( first )
							{
								first=false;
								line_edit->set("composite");
							}
							else
							{
								BEntity* mhz = (*child)->getChild("mhz");
								line_edit->set( mhz->get_uint() );
								mhz->connectServerServer(line_edit);
								
								BEntity* mhz_highest = (*child)->getChild("mhz_highest");
								line_edit_highest->set( mhz_highest->get_uint() );
								mhz_highest->connectServerServer(line_edit_highest);
								
							}
						}
					}


			// CPU STATS LINEEDITS
				// V LAYOUT
				if ( false )
				{
					BEntity* deco_layout_V = general_layout_H->addChild( "QT VBoxlayout for decorations", "QVBoxLayout" );

					for_all_children_of(t_CPUInfo)
					{
						// HLAYOUT
							BEntity* layout_H2 = deco_layout_V->addChild( (*child)->name(), "QHBoxLayout" );
							
							// PERCENT
								BEntity* percent = (*child)->getChild("workload_percent");
								for_all_children_of3( percent )
								{
									BEntity* line_edit = layout_H2->addChild( (*child3)->name(), "QLineEdit" );
									line_edit->set( (*child3)->get_float() );
									(*child3)->connectServerServer(line_edit);
								}

	// 						// RAW
	// 							BEntity* raw = (*child)->getChild("workload_raw");
	// 							for_all_children_of2( raw )
	// 							{
	// 								BEntity* line_edit = layout_H2->addChild( (*child2)->name(), "QLineEdit" );
	// 								line_edit->set( (*child2)->get_uint() );
	// 								(*child2)->connectServerServer(line_edit);
	// 							}
					}
				}
			}

		// TESTGRAPHICS VIEW AND SCENE
// 			if (false)
			{
				if (false)
				{
					BEntity* t_window = addChild( "QT Window", "QWindow" );
					t_window->set("on_close_destroy_entity", t_window);
					t_window->set("x", Buint(1200));
					t_window->set("y", Buint(500));
					t_window->set("width", Buint(200));
					t_window->set("height", Buint(200));
					
						BEntity* t_vlayout = t_window->addChild( "QT VBoxlayout", "QVBoxLayout" );
							BEntity* t_graphicsview = t_vlayout->addChild( "QT GraphicsView", "QGraphicsView" );
								t_graphicsview->setFps(60);

								// SCENE
								{
									BEntity* t_graphicsscene = t_graphicsview->addChild( "QT GraphicsScene", "QGraphicsScene" );

									// MDI AREA & MDI WINDOW TEST
										if ( true )
										{
											BEntity* t_proxywidget = t_graphicsscene->addChild( "QT GraphicsProxyWidget", "QGraphicsProxyWidget" );
											BEntity* t_mdiarea = t_proxywidget->addChild( "QT MDIArea", "QMdiArea" );
												BEntity* t_glwin = t_mdiarea->addChild( "QT MdiWindow", "QMdiWindow" );
													BEntity* t_vlayout01 = t_glwin->addChild( "QT VBoxlayout", "QVBoxLayout" );
													t_vlayout01->addChild( "QT LineEdit", "QLineEdit" );
										}
								}
				}

				if (false)
				{
					BEntity* t_window = addChild( "QT Window", "QWindow" );
					t_window->set("on_close_destroy_entity", t_window);
					t_window->set("x", Buint(1405));
					t_window->set("y", Buint(500));
					t_window->set("width", Buint(200));
					t_window->set("height", Buint(200));
					
						BEntity* t_vlayout = t_window->addChild( "QT VBoxlayout", "QVBoxLayout" );
							BEntity* t_graphicsview = t_vlayout->addChild( "QT OpenGL GraphicsView", "QGraphicsView" );
								t_graphicsview->setFps(0);

								// OPENGL WIDGET
								{
									BEntity* t_openglwidget = t_graphicsview->addChild( "QT GLWidget", "QOpenGLWidget" );
									
									// SCENE
										BEntity* t_graphicsscene = t_openglwidget->addChild( "QT GraphicsScene", "QGraphicsScene" );
										
										// MDI AREA & MDI WINDOW TEST
											if ( true )
											{
												
												BEntity* t_proxywidget = t_graphicsscene->addChild( "QT GraphicsProxyWidget", "QGraphicsProxyWidget" );
												BEntity* t_mdiarea = t_proxywidget->addChild( "QT MDIArea", "QMdiArea" );
													BEntity* t_glwin = t_mdiarea->addChild( "QT MdiWindow", "QMdiWindow" );
														BEntity* t_vlayout01 = t_glwin->addChild( "QT VBoxlayout", "QVBoxLayout" );
														t_vlayout01->addChild( "QT LineEdit", "QLineEdit" );
											}
										
										// OPENGL
											pluginManager()->load( "opengl", "src/plugins/be_plugin_opengl", "be_plugin_opengl" );

											// 6 RED CUBES IN BACKGROUND
											{
												BEntity* t_bg = t_graphicsscene->addChild("background", new BEntity());

												// GraphicsModelSystem
												BEntity* t_graphicsModelSystem = t_bg->addChild("GraphicsModelSystem", "GraphicsModelSystem");
												BEntity* t_graphicsModel = t_graphicsModelSystem->addChild("GraphicsModel", "GraphicsModel");
// 												t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/cube-floor/cube-floor-100-1.obj");
// 												t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/Medieval/Medieval_City3.obj");
// 												t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/e-road/e-road.obj");
												t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/alpine-2/alpine-2.obj");
												
												
												
												
												
// 												// something in between
// 												t_bg->addChild("BglQuads", "BglQuads");
// // 												t_graphicsscene->addChild("BglQuads", "BglQuads");
// 
// 												BEntity* color = t_bg->addChild("BglColor3f", "BglColor3f");
// 													color->set("R", 1.0f);
// 													color->set("G", 0.0f);
// 													color->set("B", 0.0f);
// 
// 												do_times(6)
// 												{
// 													int offset = dtc * 30 - 25;
// 														BEntity* vertex1 = t_bg->addChild("Vertex1", "BglVertex2f");
// 															vertex1->set("X", -10.5f+offset);
// 															vertex1->set("Y", -10.5f);
// 															
// 														BEntity* vertex2 = t_bg->addChild("Vertex2", "BglVertex2f");
// 															vertex2->set("X", 10.5f+offset);
// 															vertex2->set("Y", -10.5f);
// 															
// 														BEntity* vertex3 = t_bg->addChild("Vertex3", "BglVertex2f");
// 															vertex3->set("X", 10.5f+offset);
// 															vertex3->set("Y", 10.5f);
// 															
// 														BEntity* vertex4 = t_bg->addChild("Vertex4", "BglVertex2f");
// 															vertex4->set("X", -10.5f+offset);
// 															vertex4->set("Y", 10.5f);
// 												}
// 												t_bg->addChild("BglEnd", "BglEnd");
											}
											
// 											// 6 blue CUBES IN FOREGROUND
// 											{
// 												// something in between
// 												BEntity* t_bg = t_graphicsscene->addChild("foreground", new BEntity());
// 												t_bg->addChild("BglQuads", "BglQuads");
// // 												t_graphicsscene->addChild("BglQuads", "BglQuads");
// 
// 												BEntity* color = t_bg->addChild("BglColor3f", "BglColor3f");
// 													color->set("R", 0.0f);
// 													color->set("G", 0.0f);
// 													color->set("B", 1.0f);
// 
// 												do_times(6)
// 												{
// 													int offset = dtc * 30 - 25;
// 														BEntity* vertex1 = t_bg->addChild("Vertex1", "BglVertex2f");
// 															vertex1->set("X", -10.5f+offset);
// 															vertex1->set("Y", -10.5f + 50);
// 															
// 														BEntity* vertex2 = t_bg->addChild("Vertex2", "BglVertex2f");
// 															vertex2->set("X", 10.5f+offset);
// 															vertex2->set("Y", -10.5f + 50);
// 															
// 														BEntity* vertex3 = t_bg->addChild("Vertex3", "BglVertex2f");
// 															vertex3->set("X", 10.5f+offset);
// 															vertex3->set("Y", 10.5f + 50);
// 															
// 														BEntity* vertex4 = t_bg->addChild("Vertex4", "BglVertex2f");
// 															vertex4->set("X", -10.5f+offset);
// 															vertex4->set("Y", 10.5f + 50);
// 												}
// 												t_bg->addChild("BglEnd", "BglEnd");
// 											}
											
								}
				}
				
				// ARCHER WITH SKYDOME
				if (false)
				{
					BEntity* t_window = addChild( "QT Window", "QWindow" );
					t_window->set("on_close_destroy_entity", t_window);
					t_window->set("x", Buint(1620));
					t_window->set("y", Buint(720));
					t_window->set("width", Buint(200));
					t_window->set("height", Buint(200));
// 					t_window->set("x", Buint(1100));
// 					t_window->set("y", Buint(500));
// 					t_window->set("width", Buint(800));
// 					t_window->set("height", Buint(500));
					
						BEntity* t_vlayout = t_window->addChild( "QT VBoxlayout", "QVBoxLayout" );
							BEntity* t_graphicsview = t_vlayout->addChild( "QT OpenGL GraphicsView", "QGraphicsView" );
								t_graphicsview->setFps(60);

								// OPENGL WIDGET
								{
									BEntity* t_openglwidget = t_graphicsview->addChild( "QT GLWidget", "QOpenGLWidget" );
									
									// SCENE
										BEntity* t_graphicsscene = t_openglwidget->addChild( "QT GraphicsScene", "QGraphicsScene" );
										
									// MDI AREA & MDI WINDOW TEST WELL THIS GIVES A HANDY OFFSET TOO :/
// 										if ( false )
										{
											BEntity* t_proxywidget = t_graphicsscene->addChild( "QT GraphicsProxyWidget", "QGraphicsProxyWidget" );
												BEntity* t_mdiarea = t_proxywidget->addChild( "QT MDIArea", "QMdiArea" );
													BEntity* t_glwin = t_mdiarea->addChild( "QT MdiWindow", "QMdiWindow" );
														BEntity* t_vlayout01 = t_glwin->addChild( "QT VBoxlayout", "QVBoxLayout" );
															t_vlayout01->addChild( "QT LineEdit", "QLineEdit" );
										}

									// OPENGL
										pluginManager()->load( "opengl", "src/plugins/be_plugin_opengl", "be_plugin_opengl" );

										// 6 RED CUBES IN BACKGROUND
										{
											BEntity* t_bg = t_graphicsscene->addChild("background", new BEntity());

											// GraphicsModelSystem
												BEntity* t_graphicsModelSystem = t_bg->addChild("GraphicsModelSystem", "GraphicsModelSystem");
											
											// CAMERA
												t_graphicsModelSystem->addChild("Camera", "Camera");
												
											// MODELS
												BEntity* t_graphicsModel = t_graphicsModelSystem->addChild("GraphicsModel_base", "GraphicsModel");
													t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/Medieval/Medieval_City3.obj");

// 													t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/cube-floor/cube-floor-100-1.obj");
// 													t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/toro/body.obj");
// 													t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/archer/body.obj");
// 													t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/sirius5/sirus_city.obj");
// 													t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/e-road/e-road.obj");
// 													t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/alpine-2/alpine-2.obj");
// 													t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/Paris/Paris2010_0.obj");
// 													t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/scifi/Center City Sci-Fi.obj");
													

													
												BEntity* t_graphicsModelSkyDome = t_graphicsModelSystem->addChild("GraphicsModel_SkyDome", "GraphicsModel");
													t_graphicsModelSkyDome->set("filename", "/projects/critterding-beta14/share/critterding/skies/round/skydome3.obj");
// 													t_graphicsModelSkyDome->set("filename", "/projects/critterding-beta14/share/critterding/skies/default/skydome3.obj");
// 													t_graphicsModelSkyDome->set("filename", "/projects/critterding-beta14/share/critterding/skies/night-day/skydome3.obj");
													
													
													
													
													

										}
								}
				}
				
				
				// MEDIEVAL CITY
				if (false)
				{
					BEntity* t_window = addChild( "QT Window", "QWindow" );
					t_window->set("on_close_destroy_entity", t_window);
					t_window->set("x", Buint(1620));
					t_window->set("y", Buint(1000));
					t_window->set("width", Buint(200));
					t_window->set("height", Buint(200));
					
						BEntity* t_vlayout = t_window->addChild( "QT VBoxlayout", "QVBoxLayout" );
							BEntity* t_graphicsview = t_vlayout->addChild( "QT OpenGL GraphicsView", "QGraphicsView" );
								t_graphicsview->setFps(0);

								// OPENGL WIDGET
								{
									BEntity* t_openglwidget = t_graphicsview->addChild( "QT GLWidget", "QOpenGLWidget" );
									
									// SCENE
										BEntity* t_graphicsscene = t_openglwidget->addChild( "QT GraphicsScene", "QGraphicsScene" );
										
									// MDI AREA & MDI WINDOW TEST WELL THIS GIVES A HANDY OFFSET TOO :/
										if ( true )
										{
											BEntity* t_proxywidget = t_graphicsscene->addChild( "QT GraphicsProxyWidget", "QGraphicsProxyWidget" );
												BEntity* t_mdiarea = t_proxywidget->addChild( "QT MDIArea", "QMdiArea" );
													BEntity* t_glwin = t_mdiarea->addChild( "QT MdiWindow", "QMdiWindow" );
														BEntity* t_vlayout01 = t_glwin->addChild( "QT VBoxlayout", "QVBoxLayout" );
															t_vlayout01->addChild( "QT LineEdit", "QLineEdit" );
										}

									// OPENGL
										pluginManager()->load( "opengl", "src/plugins/be_plugin_opengl", "be_plugin_opengl" );

										// 6 RED CUBES IN BACKGROUND
										{
											BEntity* t_bg = t_graphicsscene->addChild("background", new BEntity());

											// GraphicsModelSystem
											BEntity* t_graphicsModelSystem = t_bg->addChild("GraphicsModelSystem", "GraphicsModelSystem");
											// CAMERA
												t_graphicsModelSystem->addChild("Camera", "Camera");
												BEntity* t_graphicsModel = t_graphicsModelSystem->addChild("GraphicsModel", "GraphicsModel");
// 													t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/alpine-2/alpine-2.obj");
													t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/Medieval/Medieval_City3.obj");
// 													t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/Paris/Paris2010_0.obj");
// 													t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/archer/body.obj");
										}
								}
				}
				
			}

		// VULKAN TEST
			if (false)
			{
// 				pluginManager()->load( "vulkan", "src/plugins/be_plugin_vulkan_old", "be_plugin_vulkan_old" );
// 				BEntity* vk = addChild( "VulkanScene Raycast", "VulkanRayScene2" );
// 				vk->setFps(24);

				pluginManager()->load( "vulkan", "src/plugins/be_plugin_vulkan", "be_plugin_vulkan" );
// 				BEntity* vk = addChild( "VulkanScene LoadModel", "VulkanSceneLoadModel" );
// 				vk->setFps(144);

			//	LAUNCH ON THREADS
// 				do_times (2)
// 				{
// 					BEntity* t_thread2 = addChild( "Thread", "thread" );
// 						BEntity* vk1 = t_thread2->addChild( "VulkanScene LoadModel", "VulkanSceneLoadModel" );
// 						vk1->setFps(144);
// 				}
// 				addChild( "ThreadFinish", "threads_finish" );

				do_times(1)
				{
					auto vk2 = addChild( "VulkanScene LoadModel", "VulkanSceneLoadModel" );
// 					vk2->setFps(144);
				}

// 				// INSTANCE
// 					BEntity* vulkan_instance = t_qtapp->addChild( "Vulkan Instance", "VulkanInstance" );
// 				
// 				// GIVE EACH CHILD OF INSTANCE (PHYSICAL DEVICE) A VULKAN DEVICE
// 					for_all_children_of2( vulkan_instance )
// 					{
// 						BEntity* device = (*child2)->addChild( "Vulkan Device", "VulkanDevice" );
// 						
// 						// ADD A BUFFER TOT THE DEVICE
// 							BEntity* buffer = device->addChild( "Vulkan Buffer", "VulkanBuffer" );
// 							
// 						BEntity* scene = (*child2)->addChild( "Raycast Scene", "VulkanRayScene2" );
// 						
// 					}
			}

		// TIMER & FRAME COUNTER
			m_last_updated = 0.0f;
			m_frame_counter_last = 0;
			m_last_processed_qapp = 0;

		// sleeper fps
			// m_line_edit_fps_background->set( Buint( 0 ) );

// 		m_line_edit_fps_background->set(Buint(10000));
		setFps(0);

// 		m_line_edit_vk_loadmodel_fps // FIXME, WE NEED QT INPUT FOR MODEL FPS.   BEST IS WE HAVE THE ADMIN WINDOW THOUGH


		// PHYSICS WORLD
		if (false)
		{
			pluginManager()->load( "bullet", "src/plugins/be_plugin_bullet", "be_plugin_bullet" );
			addChild( "Physics World", "PhysicsWorld" );
		}

		// THREAD
		if (false)
		{
			pluginManager()->load( "thread", "src/plugins/be_plugin_thread", "be_plugin_thread" );
			addChild( "Thread Test 1", "thread" );
			addChild( "Thread Test 2", "thread" );
			addChild( "Thread Test 3", "thread" );
			addChild( "ThreadsFinish", "threads_finish" );
		}

		// PHYSICS ON A THREAD
		if (false)
		{
			pluginManager()->load( "thread", "src/plugins/be_plugin_thread", "be_plugin_thread" );
			pluginManager()->load( "bullet", "src/plugins/be_plugin_bullet", "be_plugin_bullet" );
			
			BEntity* t_thread_test_1 = addChild( "Thread Test 1", "thread" );
				t_thread_test_1->addChild( "Physics World", "PhysicsWorld" );

			// BEntity* t_thread_test_2 = addChild( "Thread Test 2", "thread" );
			// BEntity* t_thread_test_3 = addChild( "Thread Test 3", "thread" );
			
			addChild( "ThreadsFinish", "threads_finish" );
		}

	}

	void BGLApp::construct()
	{
		pluginManager()->load( "sdl", "src/plugins/be_plugin_sdl", "be_plugin_sdl" );
		pluginManager()->load( "opengl", "src/plugins/be_plugin_opengl", "be_plugin_opengl" );
		pluginManager()->load( "bullet", "src/plugins/be_plugin_bullet", "be_plugin_bullet" );

		{
			// BULLET
				auto physics_world = addChild( "physicsworld", "PhysicsWorld" );
				physics_world->setFps(35);
				auto physics_entity = physics_world->addChild( "physics entity", "PhysicsEntity" );
					physics_entity->set("filename", "/projects/bengine-new/share/sandbox/models/Paris/Paris2010_0.obj");
					physics_entity->set("weight", 0.01f);
				auto physics_entity_transform = physics_entity->getChild("transform");
			// OPENGL
				BEntity* glscene;
				glscene = addChild( "GLWindow", "SDLWindow" );
				BEntity* t_graphicsModelSystem = glscene->addChild("GraphicsModelSystem", "GraphicsModelSystem");
				t_graphicsModelSystem->addChild("Camera", "Camera");
				BEntity* t_graphicsModel = t_graphicsModelSystem->addChild("GraphicsModel", "GraphicsModel");
				t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/Paris/Paris2010_0.obj");
				auto t1 = t_graphicsModel->addChild("transform", "Transform");
				BEntity* t_graphicsModelSkyDome = t_graphicsModelSystem->addChild("GraphicsModel_SkyDome", "GraphicsModel");
				t_graphicsModelSkyDome->set("filename", "/projects/critterding-beta14/share/critterding/skies/round/skydome3.obj");
				glscene->addChild("SDLSwapBuffers", "SDLSwapBuffers");
				
// 			// connect
			if ( physics_entity_transform )
				physics_entity_transform->connectServerServer(t1);
		}
		
// 		// UNTHREADED
// 		{
// 			// BULLET
// 				auto physics_world = addChild( "physicsworld", "PhysicsWorld" );
// 				physics_world->setFps(5);
// 				auto physics_entity = physics_world->addChild( "physics entity", "PhysicsEntity" );
// 					physics_entity->set("filename", "/projects/bengine-new/share/sandbox/models/Paris/Paris2010_0.obj");
// 	// 				physics_entity->set("filename", "/projects/bengine-new/share/sandbox/models/Medieval/Medieval_City3.obj");
// 	// 				physics_entity->set("filename", "/projects/bengine-new/share/sandbox/models/archer/body.obj");
// 					
// 					physics_entity->set("weight", 0.01f);
// 					auto physics_entity_transform = physics_entity->getChild("transform");
// 
// 				// OPENGL
// 
// 					BEntity* glscene;
// 					
// 					// SDL
// 					glscene = addChild( "GLWindow", "SDLWindow" );
// 	// 				glscene->setFps(165);
// 
// 	// 				// QT
// 	// 				BEntity* t_window = addChild( "QT Window", "QWindow" );
// 	// 				t_window->set("on_close_destroy_entity", t_window);
// 	// 				t_window->set("x", Buint(1620));
// 	// 				t_window->set("y", Buint(720));
// 	// 				t_window->set("width", Buint(200));
// 	// 				t_window->set("height", Buint(200));
// 	// 				BEntity* t_vlayout = t_window->addChild( "QT VBoxlayout", "QVBoxLayout" );
// 	// 				BEntity* t_graphicsview = t_vlayout->addChild( "QT OpenGL GraphicsView", "QGraphicsView" );
// 	// 				BEntity* t_openglwidget = t_graphicsview->addChild( "QT GLWidget", "QOpenGLWidget" );
// 	// 				BEntity* t_graphicsscene = t_openglwidget->addChild( "QT GraphicsScene", "QGraphicsScene" );
// 	// 				glscene = t_graphicsscene->addChild("background", new BEntity());
// 	// // 					t_graphicsview->setFps(0);
// 					
// 	// 				glwindow->setFps(60);
// 					
// 						// GraphicsModelSystem
// 						BEntity* t_graphicsModelSystem = glscene->addChild("GraphicsModelSystem", "GraphicsModelSystem");
// 						// CAMERA
// 							t_graphicsModelSystem->addChild("Camera", "Camera");
// 							BEntity* t_graphicsModel = t_graphicsModelSystem->addChild("GraphicsModel", "GraphicsModel");
// 	// 							t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/Medieval/Medieval_City3.obj");
// 	// 							t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/alpine-2/alpine-2.obj");
// 								t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/Paris/Paris2010_0.obj");
// 	// 							t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/archer/body.obj");
// 							
// 	// 							t_graphicsModel->set("filename", "/projects/ethical/critterthing/share/critterding/maps/MarsPlanet3/MarsPlanet2.obj");
// 	// 							t_graphicsModel->set("filename", "/projects/ethical/critterthing/share/critterding/maps/penrose/penrose.obj");
// 	// 							t_graphicsModel->set("filename", "/projects/ethical/critterthing/share/critterding/maps/hard/easy3.obj");
// 	// 							t_graphicsModel->set("filename", "/projects/bengine-new/share/stuntcoureur/cars/f360/f360.obj");
// 	// 							t_graphicsModel->set("filename", "/projects/bengine-new/share/sandbox/models/uss-tomcat/tomcat.obj");
// 	// 							t_graphicsModel->set("filename", "/projects/critterding-beta14/share/critterding/food/cube-food2.obj");
// 								
// 								auto t1 = t_graphicsModel->addChild("transform", "Transform");
// // 								t1->set("0000000000000000000000000001000000000000000000000000000000000000");
// 	// 							std::cout << "t1: " << t1->get_string() << std::endl;
// 	// 							auto t2 = t_graphicsModel->addChild("transform", "Transform");
// 	// 							t2->set("000000000000000000000000000000ekrjhtnxc;,bnlk000sdfgsdfgsdfg0001");
// 	// 							std::cout << "t2: " << t2->get_string() << std::endl;
// 								
// 							BEntity* t_graphicsModelSkyDome = t_graphicsModelSystem->addChild("GraphicsModel_SkyDome", "GraphicsModel");
// 								t_graphicsModelSkyDome->set("filename", "/projects/critterding-beta14/share/critterding/skies/round/skydome3.obj");
// 						
// 
// 						glscene->addChild("SDLSwapBuffers", "SDLSwapBuffers");
// 					
// 
// 			// connect
// 			if ( physics_entity_transform )
// 				physics_entity_transform->connectServerServer(t1);
// 		}

	}

	void BSystemMonitor::process()
	{
		// FIXME timer shit isn't worked out yet has it???
		// timer stuff doesn't need to be here needs to be handled by be_processor
		
		
// 		BE_FUNCTION_PROFILER;
		
		// MARK TIMER
			// m_timer.mark(); // FIXME create a m_timer.elapsedInFrame
							// rename mark() resetFrame()
							// add timer.update()


		// ALL DONE IN PROCESSOR NOW

// 		// FAST ROUTINE we know for now only these entities need processing
// 			// FIXME OUT OF PLACE
// 
// 			// PROCESS RAYCAST SCENE
// 				m_raycast_scene->process();
// 
// 			// PROCESS CPU INFO, has own timer
// 				t_CPUInfo->process();
// 		
// 			// Qt app // FIXME COMBINE PROCESS AND TIMER
// 				if ( m_timer.getTotalMilliSeconds() - m_last_processed_qapp >= 16 )
// 				{
// 					// PROCESS
// 						
// 						t_qtapp->process();
// 						
// 						// FIXME CHECK IF WE AREN'T ONE FRAME BEHIND, I THINK IT'S FINE
// 						BEntity* qt_rasterwindow = t_qtapp->getChild(t_qtapp, "QT RasterWindow", 3);
// 						if ( qt_rasterwindow )
// 							qt_rasterwindow->process();
// 
// 					// UPDATE LAST_PROCESSED
// 						m_last_processed_qapp = m_timer.getTotalMilliSeconds();
// 				}



		// UPDATE GUI
			const float elapsed_seconds = m_timer_s_total->get_float() - m_last_updated;
			const Buint elapsed_frames = m_timer_frame->get_uint() - m_frame_counter_last;
			const Bfloat current_fps = (Bfloat)elapsed_frames / elapsed_seconds;
			
			if ( elapsed_seconds >= 0.5f ) //FIXME an line edit input for this
			{
				// FRAMES
					m_line_edit_frame_counter->set( std::to_string(m_timer_frame->get_uint()).c_str() );

				// CURRENT FPS
					m_line_edit_fps_cur->set( std::to_string(current_fps).c_str() );
				
				// AVERAGE FPS
					m_line_edit_fps_avg->set( std::to_string((Bfloat)m_timer_frame->get_uint() / m_timer_s_total->get_float()).c_str() );
					// m_line_edit_fps_avg->set( "disabled" );

				// ENTITIES
					m_line_edit_entities->set( topParent()->numTotalChildren() );
					
				// LAST ENTITY ID
					auto id_handler = topParent()->childHandler()->m_id_handler;
					m_line_edit_last_entity_id->set( Buint(id_handler->lastID()) );
					
				// UPTIME
					m_line_edit_uptime->set(m_timer_s_total->get_float());
					
				// MEMORY // FIXME MOVE THIS TO SYSTEM
					std::ostringstream mem;
					std::ifstream proc("/proc/self/status");
					std::string s;
					while(getline(proc, s), !proc.fail())
					{
						if(s.substr(0, 6) == "VmSize")
						{
							mem << s;
							m_line_edit_memory->set( mem.str().c_str() );
// 							return mem.str();
							break;
						}
					}

				// SET VALUES NEEDED FOR NEXT UPDATE
					m_last_updated = m_timer_s_total->get_float();
					m_frame_counter_last = m_timer_frame->get_uint();
			}

// 		// SLEEPER, FIXME WHEN LOWER THAN 1K FPS, INCREASE VALUE
// 			m_background_strive_fps = m_line_edit_fps_background->get_uint();
// 
// 			if ( m_background_strive_fps > 0 )
// 			{
// 				// FIXME THIS IS A FUCKING SLEEPER OBJECT
// // 				std::cout << "current_fps " << current_fps << std::endl;
// // 				if ( current_fps > m_background_strive_fps )
// 				{
// 					// FIXME ALL of this should be float
// 					Buint sleep_ms(1);
// 
// 					if ( current_fps < 1000.0f )
// 						sleep_ms = 1000.0f / m_background_strive_fps;
// 
// // 					sleep_ms += 1;
// // 					std::cout << "elapsed_seconds " << elapsed_seconds << std::endl;
// // 					std::cout << "sleep_ms " << sleep_ms << std::endl;
// 					
// 					
// 					
// 					std::this_thread::sleep_for(std::chrono::milliseconds( sleep_ms ));
// 				}
// 			}

			

		// UPDATE UPTIME
// 			m_line_edit_fps_avg->set(m_timer.getTotalSeconds());
	}

