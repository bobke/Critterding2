#include "qmdiwindow.h"
#include "qboxlayouts.h"
// #include "kernel/be_plugin_base_entity_types.h"
#include "kernel/be_entity_core_types.h"

		BQMdiWindow::BQMdiWindow()
		: QMdiSubWindow()
		{
			show();
			resize(10,10);
		}
		
		void BQMdiWindow::closeEvent(QCloseEvent *event)
		{
			if ( event )
			{
				windowClosed();
				event->ignore();
			}
		}

		void BQMdiWindow::windowClosed()
		{
			// add remove command to the command buffer
			BEntity* cmdbuffer = topParent()->getChild("_command_buffer", 1);
			if ( cmdbuffer )
			{
				cmdbuffer->addChild("remove", new BEntity_reference() )->set(this);
			}
// // 			std::cout << "BeQtWindow::windowClosed()" << std::endl;
// 			BEntity* cmd_remove = topParent()->get("_command_buffer", 1)->addChild("cmd_remove", new CMD_remove() );
// 			cmd_remove->set(this);
		}
		
		Bbool BQMdiWindow::onAddChild( BEntity* entity )
		{ 
// 			QLayout* qlayout_entity = dynamic_cast<QLayout*>(entity);
// 			if ( qlayout_entity )
// 			{
// // 				setAlignment(qlayout_entity, Qt::AlignTop);
// // 				setAlignment(qlayout_entity, Qt::AlignLeft);
// 				
// // 				setLayout(qlayout_entity);
// 
// 				// INSERT A QWIDGET IN BETWEEN MDISUBWINDOW and LAYOUT
// 				auto central = new QWidget;
// 				central->setLayout(qlayout_entity);
// 				setWidget(central);
// 				
// // 				QWidget* qwidget_entity = dynamic_cast<QWidget*>(qlayout_entity);
// // 				setWidget(qwidget_entity);
// 				return true;
// 			}
// 			else
// 			{
// 				QWidget* qwidget_entity = dynamic_cast<QWidget*>(entity);
// 				if ( qwidget_entity )
// 				{
// // 					setAlignment(qwidget_entity, Qt::AlignTop);
// // 					setAlignment(qwidget_entity, Qt::AlignLeft);
// // 					addWidget(qwidget_entity);
// 					setWidget(qwidget_entity);
// 					return true;
// 				}
// 			}

			QLayout* qlayout_entity = dynamic_cast<QLayout*>(entity);
			if ( qlayout_entity )
			{
				if ( layout() )
				{
					QBoxLayout* present_layout = dynamic_cast<QBoxLayout*>(layout());
					if ( present_layout )
					{
						present_layout->setAlignment(qlayout_entity, Qt::AlignTop | Qt::AlignLeft);
						present_layout->addLayout(qlayout_entity);
						return true;
					}
				}
				else
				{
					// INSERT A QWIDGET IN BETWEEN MDISUBWINDOW and LAYOUT
					auto central = new QWidget;
					central->setLayout(qlayout_entity);
					setWidget(central);
					return true;
				}
			}


			if ( layout() )
			{
				QWidget* qwidget_entity = dynamic_cast<QWidget*>(entity);
				if ( qwidget_entity )
				{
// 					std::cout << "BQMdiWindow::onAddChild : has layout" << std::endl;
					layout()->addWidget(qwidget_entity);
// 					qwidget_entity->show();
// 					qwidget_entity->showMinimized();
// 					qwidget_entity->showNormal();
// 					qwidget_entity->adjustSize();
					return true;
				}
			}
			return false;
		} 
