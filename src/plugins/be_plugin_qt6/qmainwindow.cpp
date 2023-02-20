#include "qmainwindow.h"
// #include "kernel/be_plugin_base_entity_types.h"
#include "kernel/be_entity_core_types.h"
#include "qboxlayouts.h"
#include "qmenu.h"

#include <iostream>
#include <QCloseEvent>
#include <QMenuBar>

	// QWINDOW
		BQMainWindow::BQMainWindow()
		: QMainWindow()
		, m_destroy_entity_on_close(this)
		, m_x(0)
		, m_y(0)
		, m_width(0)
		, m_height(0)
		, m_isFullscreen(false)
		, m_isMaximized(false)
		, m_isMinimized(false)
		, m_isActiveWindow(false)
		, m_isVisible(false)
		, m_isHidden(false)
		, m_isEnabled(false)
		, m_title_value(0)
		{
			setWindowTitle("Engine Qt6");	// FIXME remove or even just alter this and it no longer spawns window in the foreground?
			QWidget::setVisible(true);

			m_central_widget = new QWidget;
			setCentralWidget(m_central_widget);

			setMinimumSize(160, 160);
			resize(480, 320);
			
			// FIXME DISABLED FOR NOW BECAUSE WARNING
// 			if ( layout() )
// 				delete layout();
		}

		BQMainWindow::~BQMainWindow()
		{
			if ( m_title_value )
			{
				free(m_title_value);
			}
		};

		
// 		void BQMainWindow::contextMenuEvent(QContextMenuEvent *event)
// 		{
// 			QMenu menu(this);
// 			menu.addAction(cutAct);
// 			menu.addAction(copyAct);
// 			menu.addAction(pasteAct);
// 			menu.exec(event->globalPos());
// 		}
		
		
	// PROPERTIES
		bool BQMainWindow::set( const Bstring& id, const Buint& value )
		{
			if ( id == "x" )
			{
				if ( compareAndSetValue( m_x, value ) )
				{
					move(value, y());
					return true;
				}
			}

			else if ( id == "y" )
			{
				if ( compareAndSetValue( m_y, value ) )
				{
					move(x(), value);
					return true;
				}
			}

			else if ( id == "width" )
			{
				if ( compareAndSetValue( m_width, value ) )
				{
					resize(value, height());
					return true;
				}
			}

			else if ( id == "height" )
			{
				if ( compareAndSetValue( m_height, value ) )
				{
					resize(width(), value);
					return true;
				}
			}

			return false;
		}

		Buint BQMainWindow::get_uint( const Bstring& id )
		{
			if ( id == "x" )
			{
				return x();
			}
			if ( id == "y" )
			{
				return y();
			}
			if ( id == "width" )
			{
				return width();
			}
			if ( id == "height" )
			{
				return height();
			}

			return 0;
		}
		
	// PROPERTIES
		bool BQMainWindow::set( const Bstring& id, BEntity* value )
		{
// 			std::cout << "BQMainWindow::set " << id << " " << value->id() << std::endl;
			if ( id == "on_close_destroy_entity" )
			{
				if ( compareAndSetValue( m_destroy_entity_on_close, value ) )
				{
// 					std::cout << " is now " << m_destroy_entity_on_close->id() << std::endl;
					return true;
				}
			}

			return false;
		}

		BEntity* BQMainWindow::get_reference( const Bstring& id )
		{
			if ( id == "on_close_destroy_entity" )
			{
				return m_destroy_entity_on_close;
			}

			return 0;
		}
		
		bool BQMainWindow::set( const Bstring& id, const char* value )
		{
			if ( id == "title" )
			{
				QString s(value);
				if ( s != windowTitle() )
				{
					setWindowTitle(s);
					m_title_value = strdup(value);
					return true;
				}
			}

			return false;
		}
		const char* BQMainWindow::get_string( const Bstring& id )
		{
			if ( id == "title" )
			{
				return m_title_value;
			}

			return "";
		}


		void BQMainWindow::moveEvent(QMoveEvent *event)
		{
			// FIXME SEND SIGNALS
			if ( compareAndSetValue( m_x, (Buint)event->pos().x() ) )
			{
// 				std::cout << id() << " x: " << m_x << std::endl;
			}
			if ( compareAndSetValue( m_y, (Buint)event->pos().y() ) )
			{
// 				std::cout << id() << " y: " << m_y << std::endl;
			}
			(void)event;
		}

		void BQMainWindow::resizeEvent(QResizeEvent *event)
		{
			// FIXME SEND SIGNALS
			if ( compareAndSetValue( m_width, (Buint)event->size().width() ) )
			{
// 				std::cout << "width: " << m_width << std::endl;
			}
			if ( compareAndSetValue( m_height, (Buint)event->size().height() ) )
			{
// 				std::cout << "height: " << m_height << std::endl;
			}
			if ( compareAndSetValue( m_isFullscreen, isFullScreen() ) )
			{
// 				std::cout << "fullscreen: " << m_isFullscreen << std::endl;
			}
			if ( compareAndSetValue( m_isMaximized, isMaximized() ) )
			{
// 				std::cout << "maximized: " << m_isMaximized << std::endl;
			}
			(void)event;
		}

		void BQMainWindow::changeEvent(QEvent *event)
		{
			if ( compareAndSetValue( m_isMinimized, isMinimized() ) )
			{
// 				std::cout << "minimized: " << m_isMinimized << std::endl;
			}
			if ( compareAndSetValue( m_isActiveWindow, isActiveWindow() ) )
			{
// 				std::cout << "active window: " << m_isActiveWindow << std::endl;
			}
			if ( compareAndSetValue( m_isVisible, isVisible() ) )
			{
// 				std::cout << "visible: " << m_isVisible << std::endl;
			}
			if ( compareAndSetValue( m_isHidden, isHidden() ) )
			{
// 				std::cout << "hidden: " << m_isHidden << std::endl;
			}
			if ( compareAndSetValue( m_isEnabled, isEnabled() ) )
			{
// 				std::cout << "enabled: " << m_isEnabled << std::endl;
			}
			(void)event;
		}
		
// 		void BQMainWindow::hideEvent(QHideEvent *event)
// 		{
// // 			// FIXME SEND SIGNALS
// // 			if ( compareAndSetValue( m_isMinimized, isMinimized() ) )
// // 			{
// // 				std::cout << "minimized: " << m_isMinimized << std::endl;
// // 			}
// 		}
// 
// 		void BQMainWindow::showEvent(QShowEvent *event)
// 		{
// 		}
		
		void BQMainWindow::dragEnterEvent(QDragEnterEvent *event)
		{
			(void)event;
// 			std::cout << "drag event" << std::endl;
// 			if (event->mimeData()->hasText()) {
// 				if (event->source() == this) {
// 					event->setDropAction(Qt::MoveAction);
// 					event->accept();
// 				} else {
// 					event->acceptProposedAction();
// 				}
// 			} else {
// 				event->ignore();
// 			}
		}

		Bbool BQMainWindow::onAddChild( BEntity* entity )
		{ 
			// std::cout << "BQMainWindow::onAddChild" << std::endl;

			BQHBoxLayout* hlayout_entity = dynamic_cast<BQHBoxLayout*>(entity);
			if ( hlayout_entity )
			{
// 				std::cout << "BQMainWindow::onAddChild : is QHBoxLayout" << std::endl;
				if ( !m_central_widget->layout() )
				{
					m_central_widget->setLayout(hlayout_entity);
					hlayout_entity->setAlignment(Qt::AlignTop | Qt::AlignLeft);
					return true;
				}
			}

			BQVBoxLayout* vlayout_entity = dynamic_cast<BQVBoxLayout*>(entity);
			if ( vlayout_entity )
			{
// 				std::cout << "BQMainWindow::onAddChild : is QVBoxLayout" << std::endl;
				if ( !m_central_widget->layout() )
				{
					m_central_widget->setLayout(vlayout_entity);
					vlayout_entity->setAlignment(Qt::AlignTop | Qt::AlignLeft);
					return true;
				}
			}

			BQMenu* menu = dynamic_cast<BQMenu*>(entity);
			if ( menu )
			{
				// std::cout << "BQMainWindow::onAddChild : is QMenu" << std::endl;
// 				if ( !m_central_widget->layout() )
				{
// 					menuBar()->addMenu(tr("&File"));
// 					menuBar()->addWidget(menu);
					menuBar()->addMenu(menu);

// 					m_central_widget->setLayout(vlayout_entity);
// 					vlayout_entity->setAlignment(Qt::AlignTop | Qt::AlignLeft);
					return true;
				}
			}
			
			// try adding widgets only when there is a layout present
			if ( m_central_widget->layout() )
			{
// 				std::cout << "BQMainWindow::onAddChild : is QWidget" << std::endl;
				QWidget* qwidget_entity = dynamic_cast<QWidget*>(entity);
				if ( qwidget_entity )
				{
					m_central_widget->layout()->addWidget(qwidget_entity);
					m_central_widget->layout()->setAlignment(qwidget_entity, Qt::AlignTop | Qt::AlignLeft);
					qwidget_entity->show();
					return true;
				}
			}

			return false;
		}

		void BQMainWindow::closeEvent(QCloseEvent *event)
		{
			if ( event )
			{
				// add remove command to the command buffer
				BEntity* cmdbuffer = topParent()->getChild("_command_buffer");
				if ( cmdbuffer )
				{
					cmdbuffer->addChild("remove", new BEntity_reference() )->set( m_destroy_entity_on_close );
				}

				event->ignore();
			}
		}

