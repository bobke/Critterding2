#include "qgroupbox.h"
#include "qboxlayouts.h"
// #include "qaction.h"

	// QMENU
		BQGroupBox::BQGroupBox()
		: QGroupBox()
		{
// 			setSpacing(0);
// 			setMargin(0);
			setContentsMargins(10,0,0,0); // HACK
// 			setSizeConstraint(QLayout::SetMinimumSize);
			setAlignment(Qt::AlignTop | Qt::AlignLeft);
		
// 		    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		}

	// PROPERTIES
		bool BQGroupBox::set( const Bstring& id, const char* value )
		{
			if ( id == "title" )
			{
				QString s(value);
				if ( s != title() )
				{
					setTitle(tr(value));
					return true;
				}
			}
			return false;
		}

// 		Bbool BQGroupBox::onAddChild( BEntity* entity )
// 		{ 
// 			auto action = dynamic_cast<BQAction*>(entity);
// 			if ( action )
// 			{
// 				addAction(action);
// 				return true;
// 			}
// 			return false;
// 		}

		Bbool BQGroupBox::onAddChild( BEntity* entity )
		{ 
			auto HBoxLayout = dynamic_cast<BQHBoxLayout*>(entity);
			if ( HBoxLayout )
			{
// 				std::cout << "BeQtWindow::onAddChild : is VBoxLayout" << std::endl;
				if ( !layout() )
				{
					setLayout(HBoxLayout);
					HBoxLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
					
// 					hide();
// 					show();
// 					resize(size());
					return true;
				}
			}

			auto VBoxLayout = dynamic_cast<BQVBoxLayout*>(entity);
			if ( VBoxLayout )
			{
// 					std::cout << "BeQtWindow::onAddChild : is VBoxLayout" << std::endl;
				if ( !layout() )
				{
					setLayout(VBoxLayout);
					VBoxLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
// 					hide();
// 					show();
// 					resize(size());
					return true;
				}
			}

			if ( layout() )
			{
// 					BeQtMdiArea* mdi_area = dynamic_cast<BeQtMdiArea*>(entity);
// 					if ( mdi_area )
// 					{
// 						layout()->addWidget(mdi_area);
// 						return true;
// 					}

					QWidget* qwidget_entity = dynamic_cast<QWidget*>(entity);
					if ( qwidget_entity )
					{
						layout()->addWidget(qwidget_entity);
// 						qwidget_entity->hide();
// 						qwidget_entity->show();
// 						hide();
// 						show();
// 						resize(size());
// 						qwidget_entity->adjustSize();
// 						adjustSize();
						return true;
					}
				}

			return false;
		}
