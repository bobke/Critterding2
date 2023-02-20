// #include "kernel/be_entity_io_handler.h"
#include "qcheckbox.h"
// #include <iostream>
// #include <sstream>
// #include <algorithm>


	// QLINEEDIT
		BQCheckBox::BQCheckBox()
		: QCheckBox()
		, m_width(0)
		, m_height(0)
		{
			connect(this, SIGNAL(stateChanged(int)), SLOT(onChange()));
		}

		bool BQCheckBox::set( BEntity* entity )
		{
			if ( QCheckBox::checkState() != entity->get_bool() )
			{
// 				std::cout << "BQCheckBox::set( BEntity* entity ): " << " changing " << text().toStdString() << " to " << entity->get_uint() << std::endl;
				if ( entity->get_bool() )
					setCheckState( Qt::Checked );
				else
					setCheckState( Qt::Unchecked );

				m_value = entity->get_bool();

				onUpdate();
				return true;
			}
			return false;
		}

		bool BQCheckBox::set( const Bbool& value )
		{
			if ( m_value != value )
			{
// 				std::cout << "BQCheckBox::set( const Buint& value ): " << " changing " << text().toStdString() << " to " << value << std::endl;
				if ( value )
					setCheckState( Qt::Checked );
				else
					setCheckState( Qt::Unchecked );

				m_value = value;

				onUpdate();
				return true;
			}
			return false;
		}

		void BQCheckBox::onChange()
		{
// 			std::cout << "BQLineEdit::onChange(): " << id() << name() << " " << m_value << " STRING: " << text().toStdString() << " UINT: " << text().toUInt() << std::endl;
// 			m_value = text().toUInt();
			auto v = QCheckBox::checkState();
			if ( m_value != v )
			{
				if ( v )
					m_value = true;
				else
					m_value = false;

				// std::cout << "BQCheckBox::onChange(): " << m_value << " " << std::endl;
				onUpdate();
			}
// 			auto property = getChild( "value", 1 );
// 			if ( property )
// 			{
// 				std::cout << "BQLineEdit::onChange(): " << id() << " " << text().toStdString() << std::endl;
// 				property->onUpdate();
// 			}
		}
