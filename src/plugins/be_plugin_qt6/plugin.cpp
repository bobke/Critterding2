#include "plugin.h"
// #include "kernel/be_plugin_base_entity_types.h"

#include "qwindow.h"
#include "qrasterwindow.h"
#include "qboxlayouts.h"
#include "qmdiarea.h"
#include "qlineedit.h"
#include "qgraphicsscene.h"
#include "qgraphicsview.h"
#include "qopenglwidget.h"
#include "qgraphicsproxywidget.h"
#include "qmdiwindow.h"
#include "qmainwindow.h"
#include "qmenu.h"
#include "qaction.h"
#include "qwidget.h"
#include "qgroupbox.h"
#include "qpushbutton.h"
#include "qlabel.h"
#include "qcheckbox.h"
#include "qpen.h"

#include <iostream>
#include <QApplication>
// #include <sstream>
// #include <fstream>

// ---- FACTORIES
	enum CLASS
	{
		  PLUGIN_INFO
		, SCENE
		, QAPPLICATION
		, QAPPLICATIONSPAWNER
		, QWIDGET
		, QMENU
		, QACTION
		, QWINDOW
		, QRASTERWINDOW
		, QHBOXLAYOUT
		, QVBOXLAYOUT
		, QMDIAREA
		, QLINEEDIT
// 		, QLINEEDIT_UINT
		, QLINEEDIT_INT
		, QLINEEDIT_FLOAT
		, QLINEEDIT_DOUBLE
		, QLINEEDIT_STRING
		, QGRAPHICSVIEW
		, QGRAPHICSSCENE
		, QOPENGLWIDGET
		, QGRAPHICSPROXYWIDGET
		, QMDIWINDOW
		, QMAINWINDOW
		, QGROUPBOX
		, QPUSHBUTTON
		, QPUSHBUTTON_DRAGGABLE
		, QPUSHBUTTON_DROPPABLE
		, QPUSHBUTTON_DRAGANDDROPPABLE
		, QLABEL
		, QLABEL_DROPPABLE
		, QCHECKBOX
		, QPEN
	};

	extern "C" BEntity* create( BEntity* parent, const Buint type )
	{
// 		std::cout << "LIB CREATE:: type: " << type  << std::endl;
		// PLUGIN DESCRIPTION ENTITY
			if ( type == PLUGIN_INFO )
			{
				BClassesHelper i;
					i.addClass( parent, CLASS::SCENE, "Scene" );
					i.addClass( parent, CLASS::QAPPLICATION, "QApplication" );
					i.addClass( parent, CLASS::QAPPLICATIONSPAWNER, "QApplicationSpawner" );
					i.addClass( parent, CLASS::QWIDGET, "QWidget" );
					i.addClass( parent, CLASS::QMENU, "QMenu" );
					i.addClass( parent, CLASS::QACTION, "QAction" );
					i.addClass( parent, CLASS::QWINDOW, "QWindow" );
					i.addClass( parent, CLASS::QRASTERWINDOW, "QRasterWindow" );
					i.addClass( parent, CLASS::QHBOXLAYOUT, "QHBoxLayout" );
					i.addClass( parent, CLASS::QVBOXLAYOUT, "QVBoxLayout" );
					i.addClass( parent, CLASS::QMDIAREA, "QMdiArea" );
					i.addClass( parent, CLASS::QLINEEDIT, "QLineEdit" );
// 					i.addClass( parent, CLASS::QLINEEDIT_UINT, "QLineEdit_uint" );
					i.addClass( parent, CLASS::QLINEEDIT_INT, "QLineEdit_int" );
					i.addClass( parent, CLASS::QLINEEDIT_FLOAT, "QLineEdit_float" );
					i.addClass( parent, CLASS::QLINEEDIT_DOUBLE, "QLineEdit_double" );
					i.addClass( parent, CLASS::QLINEEDIT_STRING, "QLineEdit_string" );
					i.addClass( parent, CLASS::QGRAPHICSVIEW, "QGraphicsView" );
					i.addClass( parent, CLASS::QGRAPHICSSCENE, "QGraphicsScene" );
					i.addClass( parent, CLASS::QOPENGLWIDGET, "QOpenGLWidget" );
					i.addClass( parent, CLASS::QGRAPHICSPROXYWIDGET, "QGraphicsProxyWidget" );
					i.addClass( parent, CLASS::QMDIWINDOW, "QMdiWindow" );
					i.addClass( parent, CLASS::QMAINWINDOW, "QMainWindow" );
					i.addClass( parent, CLASS::QGROUPBOX, "QGroupBox" );
					i.addClass( parent, CLASS::QPUSHBUTTON, "QPushButton" );
					i.addClass( parent, CLASS::QPUSHBUTTON_DRAGGABLE, "QPushButtonDraggable" );
					i.addClass( parent, CLASS::QPUSHBUTTON_DROPPABLE, "QPushButtonDroppable" );
					i.addClass( parent, CLASS::QPUSHBUTTON_DRAGANDDROPPABLE, "QPushButtonDragAndDroppable" );
					i.addClass( parent, CLASS::QLABEL, "QLabel" );
					i.addClass( parent, CLASS::QLABEL_DROPPABLE, "QLabelDroppable" );
					i.addClass( parent, CLASS::QCHECKBOX, "QCheckBox" );
					i.addClass( parent, CLASS::QPEN, "QPen" );
				return 0;
			}

		// ENTITIES
			else
			{
				BEntity* i(0);
				
				if ( type == CLASS::SCENE )
					i = new Scene();
				else if ( type == CLASS::QAPPLICATION )
					i = new BQApplicationWrapper();
				else if ( type == CLASS::QAPPLICATIONSPAWNER )
					i = new BQApplicationSpawner();
				else if ( type == CLASS::QWINDOW )
					i = new BQWindow();
				else if ( type == CLASS::QWIDGET )
					i = new BQWidget();
				else if ( type == CLASS::QMENU )
					i = new BQMenu();
				else if ( type == CLASS::QACTION )
					i = new BQAction();
				else if ( type == CLASS::QRASTERWINDOW )
					i = new BQRasterWindow();
				else if ( type == CLASS::QHBOXLAYOUT )
					i = new BQHBoxLayout();
				else if ( type == CLASS::QVBOXLAYOUT )
					i = new BQVBoxLayout();
				else if ( type == CLASS::QMDIAREA )
					i = new BQMdiArea();
				else if ( type == CLASS::QLINEEDIT )
					i = new BQLineEdit();
// 				else if ( type == CLASS::QLINEEDIT_UINT )
// 					i = new BQLineEdit_uint();
				else if ( type == CLASS::QLINEEDIT_INT )
					i = new BQLineEdit_int();
				else if ( type == CLASS::QLINEEDIT_FLOAT )
					i = new BQLineEdit_float();
				else if ( type == CLASS::QLINEEDIT_DOUBLE )
					i = new BQLineEdit_double();
				else if ( type == CLASS::QLINEEDIT_STRING )
					i = new BQLineEdit_string();
				else if ( type == CLASS::QGRAPHICSVIEW )
					i = new BQGraphicsView();
				else if ( type == CLASS::QGRAPHICSSCENE )
					i = new BQGraphicsScene();
				else if ( type == CLASS::QOPENGLWIDGET )
					i = new BQOpenGLWidget();
				else if ( type == CLASS::QGRAPHICSPROXYWIDGET )
					i = new BQGraphicsProxyWidget();
				else if ( type == CLASS::QMDIWINDOW )
					i = new BQMdiWindow();
				else if ( type == CLASS::QMAINWINDOW )
					i = new BQMainWindow();
				else if ( type == CLASS::QGROUPBOX )
					i = new BQGroupBox();
				else if ( type == CLASS::QPUSHBUTTON )
					i = new BQPushButton();
				else if ( type == CLASS::QPUSHBUTTON_DRAGGABLE )
					i = new BQPushButtonDraggable();
				else if ( type == CLASS::QPUSHBUTTON_DROPPABLE )
					i = new BQPushButtonDroppable();
				else if ( type == CLASS::QPUSHBUTTON_DRAGANDDROPPABLE )
					i = new BQPushButtonDragAndDroppable();
				else if ( type == CLASS::QLABEL )
					i = new BQLabel();
				else if ( type == CLASS::QLABEL_DROPPABLE )
					i = new BQLabelDroppable();
				else if ( type == CLASS::QCHECKBOX )
					i = new BQCheckBox();
				else if ( type == CLASS::QPEN )
					i = new BQPen();
				
				

				return i;
			}
	}

	extern "C" void destroy(BEntity* p)
	{
// 		std::cout << "LIB DESTROY:: " << p->id() << std::endl;
		delete p;
	}

	BQApplicationWrapper::BQApplicationWrapper()
	{
		// SET PROCESSING BIT, deferred, meaning process children first
		// ACTUALLY NO NEED TO DO DEFERRED BECAUSE QT DOES IT BY ITSELF
// 			m_flags.m_has_deferred_processing = true;
			setProcessing();
// 			m_flags.m_has_processing = true;
		
		m_qapp = new QApplication(m_fakeargc, m_fakeParam);

// 		// PUSHBUTTON
// 			QPushButton hello( "Hello world!", 0 );
// 			hello.resize( 100, 30 );
// 			hello.show();
// 			
// 		m_qapp->exec();
	}
	
	void BQApplicationWrapper::process()
	{
// 		std::cout << "BQApplicationWrapper::process() " << id() << std::endl;
		m_qapp->processEvents();
// 		m_qapp->processEvents(QEventLoop::AllEvents, 5);

		// NOTE: FORCE THIS TO PREVENT ADMIN MEMLEAK
		m_qapp->sendPostedEvents(0, QEvent::DeferredDelete);
	}

	BQApplicationWrapper::~BQApplicationWrapper()
	{
// 		std::cout << "BQApplication::~BQApplication()" << std::endl;
		m_qapp->closeAllWindows();
		m_qapp->quit();
		m_qapp->exit();

		delete m_qapp;
	}
		

	BEntity* BQApplicationSpawner::getChildCustom( BEntity* parent, const char* name )
	{
		// FIXME avoid warning
		(void)name;

		// "BAdminWindow QT Application"
		// LOAD QT APP
		BEntity* qt_app = topParent()->getChild( "QT Application" ); // FIXME THIS HAS TO WORK
		if ( qt_app )
		{
			return qt_app;
		}

		return parent->addChild( "QT Application", new BQApplicationWrapper() );
		
	}
