#include "qwindow.h"
// #include "kernel/be_plugin_base_entity_types.h"
#include "kernel/be_entity_core_types.h"
#include "qboxlayouts.h"
// #include "qmdiarea.h"

#include <iostream>
#include <QCloseEvent>

	// QWINDOW
		BQWindow::BQWindow()
		: QWidget()
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
		{
			setWindowTitle("Engine Qt6 ");
			QWidget::setVisible(true);

			// FIXME DISABLED FOR NOW BECAUSE WARNING
// 			if ( layout() )
// 				delete layout();
		}

	// PROPERTIES
		bool BQWindow::set( const Bstring& id, const Buint& value )
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

		Buint BQWindow::get_uint( const Bstring& id )
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
		bool BQWindow::set( const Bstring& id, BEntity* value )
		{
// 			std::cout << "BQWindow::set " << id << " " << value->id() << std::endl;
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

		BEntity* BQWindow::get_reference( const Bstring& id )
		{
			if ( id == "on_close_destroy_entity" )
			{
				return m_destroy_entity_on_close;
			}

			return 0;
		}
		
		bool BQWindow::set( const Bstring& id, const char* value )
		{
			if ( id == "title" )
			{
				QString s(value);
				if ( s != windowTitle() )
				{
					setWindowTitle(s);
					return true;
				}
			}

			return false;
		}

		void BQWindow::moveEvent(QMoveEvent *event)
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

		void BQWindow::resizeEvent(QResizeEvent *event)
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

		void BQWindow::changeEvent(QEvent *event)
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
		
// 		void BQWindow::hideEvent(QHideEvent *event)
// 		{
// // 			// FIXME SEND SIGNALS
// // 			if ( compareAndSetValue( m_isMinimized, isMinimized() ) )
// // 			{
// // 				std::cout << "minimized: " << m_isMinimized << std::endl;
// // 			}
// 		}
// 
// 		void BQWindow::showEvent(QShowEvent *event)
// 		{
// 		}
		
		void BQWindow::dragEnterEvent(QDragEnterEvent *event)
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

		Bbool BQWindow::onAddChild( BEntity* entity )
		{ 
// 			std::cout << "BQWindow::onAddChild" << std::endl;

			BQHBoxLayout* hlayout_entity = dynamic_cast<BQHBoxLayout*>(entity);
			if ( hlayout_entity )
			{
// 				std::cout << "BQWindow::onAddChild : is QHBoxLayout" << std::endl;
				if ( !layout() )
				{
					setLayout(hlayout_entity);
					hlayout_entity->setAlignment(Qt::AlignTop | Qt::AlignLeft);
					return true;
				}
			}

			BQVBoxLayout* vlayout_entity = dynamic_cast<BQVBoxLayout*>(entity);
			if ( vlayout_entity )
			{
// 				std::cout << "BQWindow::onAddChild : is QVBoxLayout" << std::endl;
				if ( !layout() )
				{
					setLayout(vlayout_entity);
					vlayout_entity->setAlignment(Qt::AlignTop | Qt::AlignLeft);
					return true;
				}
			}

			// try adding widgets only when there is a layout present
			if ( layout() )
			{
// 				std::cout << "BQWindow::onAddChild : is QWidget" << std::endl;
				QWidget* qwidget_entity = dynamic_cast<QWidget*>(entity);
				if ( qwidget_entity )
				{
					layout()->addWidget(qwidget_entity);
					layout()->setAlignment(qwidget_entity, Qt::AlignTop | Qt::AlignLeft);
					qwidget_entity->show();
					return true;
				}
			}

			return false;
		}

		void BQWindow::closeEvent(QCloseEvent *event)
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

