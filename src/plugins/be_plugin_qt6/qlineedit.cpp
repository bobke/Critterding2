// #include "kernel/be_entity_io_handler.h"
#include "qlineedit.h"
#include <iostream>
// #include <sstream>
// #include <algorithm>

	// QLINEEDIT
		BQLineEdit::BQLineEdit()
		: QLineEdit()
		, m_width(0)
		, m_height(0)
		{
			connect(this, SIGNAL(editingFinished()), SLOT(onChange()));
// 			connect(this, SIGNAL(textChanged(const QString&)), SLOT(onChange()));
		}

		bool BQLineEdit::set( const char* value )
		{
			QString s(value);
			if ( s != text() )
			{
				setText(s);
				BEntity_string::set( value );
				onUpdate();
				return true;
			}
			return false;
		}


		bool BQLineEdit::set( const Bstring& id, const char* value )
		{
			if ( id == "value" )
			{
				QString s(value);
				if ( s != text() )
				{
					setText(s);
					BEntity_string::set( value );
					onUpdate();
					return true;
				}
				return false;
				
				// if ( m_value != std::string(value) )
				// {
				// 	QString s(value);
				// 	setText(s);
				// 	strcpy( m_value, value );
				// 	onUpdate();
				// 	return true;
				// }
			}
			return false;
		}

		bool BQLineEdit::set( const Bstring& id, const Buint& value )
		{
			if ( id == "width" )
			{
				if ( compareAndSetValue( m_width, value ) )
				{
					setFixedSize(QSize(value, height()));  //HACK
					return true;
				}
			}

			else if ( id == "height" )
			{
				if ( compareAndSetValue( m_height, value ) )
				{
					setFixedSize(QSize(width(), value));  //HACK
					return true;
				}
			}
			
			return false;
		}

		void BQLineEdit::onChange()
		{
			BEntity_string::set( text().toStdString().c_str() );
		}
		
		
	// QLINEEDIT_uint
		BQLineEdit_uint::BQLineEdit_uint()
		: QLineEdit()
		, m_width(0)
		, m_height(0)
		{
			connect(this, SIGNAL(editingFinished()), SLOT(onChange()));
// 			connect(this, SIGNAL(textChanged(const QString&)), SLOT(onChange()));
		}

		bool BQLineEdit_uint::set( BEntity* entity )
		{
			QString s;
			s.setNum( entity->get_int() );
			if ( m_value != entity->get_int() )
			{
// 				std::cout << "BQLineEdit_uint::set( BEntity* entity ): " << " changing " << text().toStdString() << " to " << entity->get_uint() << std::endl;
				m_value = entity->get_int();
				setText(s);
				onUpdate();
				return true;
			}
			return false;
		}

		bool BQLineEdit_uint::set( const char* value )
		{
			QString s(value);
			if ( s != text() )
			{
				setText(s);
				onUpdate();
				return true;
			}
			return false;
		}

		bool BQLineEdit_uint::set( const Buint& value )
		{
			
			if ( m_value != value )
			{
// 				std::cout << "BQLineEdit::set( const Buint& value ): " << " changing " << text().toStdString() << " to " << value << std::endl;
				m_value = value;
				QString s;
				s.setNum(value);
				setText(s);
				onUpdate();

				return true;
			}
			return false;
		}

		bool BQLineEdit_uint::set( const Bint& value )
		{
			if ( m_value != value )
			{
// 				std::cout << "BQLineEdit_uint::set( const Buint& value ): " << " changing " << text().toStdString() << " to " << value << std::endl;
				m_value = value;
				QString s;
				s.setNum(value);
				setText(s);
				onUpdate();

				return true;
			}
			return false;
		}

// 		bool BQLineEdit_uint::set( const Bstring& id, const Bint& value )
// 		{
// 			if ( id == "value" )
// 			{
// 				if ( compareAndSetValue( m_value, value ) )
// 				{
// // 					std::cout << "BQLineEdit_uint::set( const Bstring& id, const Buint& value ): " << " changing " << text().toStdString() << " to " << value << std::endl;
// 					QString s;
// 					s.setNum(value);
// 					setText(s);
// 					onUpdate();
// 					return true;
// 				}
// 			}
// 			return false;
// 		}

		bool BQLineEdit_uint::set( const Bstring& id, const Buint& value )
		{
			if ( id == "width" )
			{
				if ( compareAndSetValue( m_width, value ) )
				{
					setFixedSize(QSize(value, height()));  //HACK
					return true;
				}
			}

			else if ( id == "height" )
			{
				if ( compareAndSetValue( m_height, value ) )
				{
					setFixedSize(QSize(width(), value));  //HACK
					return true;
				}
			}
			
			return false;
		}
		
		void BQLineEdit_uint::onChange()
		{
			auto v = text().toUInt();
			if ( m_value != v )
			{
				m_value = v;
// 				std::cout << "2BQLineEdit_float::onChange(): " << id() << name() << " " << m_value << " STRING: " << text().toStdString() << " UINT: " << text().toUInt() << std::endl;
				onUpdate();
			}
		}
				
		
		
		

	// QLINEEDIT_int
		BQLineEdit_int::BQLineEdit_int()
		: QLineEdit()
		, m_width(0)
		, m_height(0)
		{
			connect(this, SIGNAL(editingFinished()), SLOT(onChange()));
// 			connect(this, SIGNAL(textChanged(const QString&)), SLOT(onChange()));
		}

		bool BQLineEdit_int::set( BEntity* entity )
		{
			QString s;
			s.setNum( entity->get_int() );
			if ( m_value != entity->get_int() )
			{
// 				std::cout << "BQLineEdit_int::set( BEntity* entity ): " << " changing " << text().toStdString() << " to " << entity->get_uint() << std::endl;
				m_value = entity->get_int();
				setText(s);
				onUpdate();
				return true;
			}
			return false;
		}

		bool BQLineEdit_int::set( const char* value )
		{
			QString s(value);
			if ( s != text() )
			{
				setText(s);
				onUpdate();
				return true;
			}
			return false;
		}

		bool BQLineEdit_int::set( const Buint& value )
		{
			
			if ( m_value != value )
			{
// 				std::cout << "BQLineEdit::set( const Buint& value ): " << " changing " << text().toStdString() << " to " << value << std::endl;
				m_value = value;
				QString s;
				s.setNum(value);
				setText(s);
				onUpdate();

				return true;
			}
			return false;
		}

		bool BQLineEdit_int::set( const Bint& value )
		{
			if ( m_value != value )
			{
// 				std::cout << "BQLineEdit_int::set( const Buint& value ): " << " changing " << text().toStdString() << " to " << value << std::endl;
				m_value = value;
				QString s;
				s.setNum(value);
				setText(s);
				onUpdate();

				return true;
			}
			return false;
		}

		bool BQLineEdit_int::set( const Bstring& id, const Bint& value )
		{
			if ( id == "value" )
			{
				if ( compareAndSetValue( m_value, value ) )
				{
// 					std::cout << "BQLineEdit_int::set( const Bstring& id, const Buint& value ): " << " changing " << text().toStdString() << " to " << value << std::endl;
					QString s;
					s.setNum(value);
					setText(s);
					onUpdate();
					return true;
				}
			}
			return false;
		}

		bool BQLineEdit_int::set( const Bstring& id, const Buint& value )
		{
			if ( id == "width" )
			{
				if ( compareAndSetValue( m_width, value ) )
				{
					setFixedSize(QSize(value, height()));  //HACK
					return true;
				}
			}

			else if ( id == "height" )
			{
				if ( compareAndSetValue( m_height, value ) )
				{
					setFixedSize(QSize(width(), value));  //HACK
					return true;
				}
			}
			
			return false;
		}
		
		void BQLineEdit_int::onChange()
		{
			auto v = text().toInt();
			if ( m_value != v )
			{
				m_value = v;
// 				std::cout << "2BQLineEdit_float::onChange(): " << id() << name() << " " << m_value << " STRING: " << text().toStdString() << " UINT: " << text().toUInt() << std::endl;
				onUpdate();
			}
		}
		
		
		
		
		
		
		
		
		
		
		
		
	// QLINEEDIT_float
		BQLineEdit_float::BQLineEdit_float()
		: QLineEdit()
		, m_width(0)
		, m_height(0)
		{
			connect(this, SIGNAL(editingFinished()), SLOT(onChange()));
// 			connect(this, SIGNAL(textChanged(const QString&)), SLOT(onChange()));
		}

		bool BQLineEdit_float::set( BEntity* entity )
		{
			QString s;
			s.setNum( entity->get_uint() );
			if ( m_value != entity->get_uint() )
			{
// 				std::cout << "BQLineEdit_float::set( BEntity* entity ): " << " changing " << text().toStdString() << " to " << entity->get_uint() << std::endl;
				m_value = entity->get_uint();
				setText(s);
				onUpdate();
				return true;
			}
			return false;
		}

		bool BQLineEdit_float::set( const char* value )
		{
			QString s(value);
			if ( s != text() )
			{
				setText(s);
				onUpdate();
				return true;
			}
			return false;
		}

		
		bool BQLineEdit_float::set( const Bfloat& value )
		{
			if ( m_value != value )
			{
// 				std::cout << "BQLineEdit_float::set( const Buint& value ): " << " changing " << text().toStdString() << " to " << value << std::endl;
				m_value = value;
				QString s;
				s.setNum(value);
				setText(s);
				onUpdate();

				return true;
			}

			return false;
		}

		bool BQLineEdit_float::set( const Bstring& id, const Bfloat& value )
		{
			if ( id == "value" )
			{
				if ( compareAndSetValue( m_value, value ) )
				{
// 					std::cout << "BQLineEdit_float::set( const Bstring& id, const Buint& value ): " << " changing " << text().toStdString() << " to " << value << std::endl;
					QString s;
					s.setNum(value);
					setText(s);
					onUpdate();
					return true;
				}
			}

			return false;
		}

		bool BQLineEdit_float::set( const Bstring& id, const Buint& value )
		{
			if ( id == "width" )
			{
				if ( compareAndSetValue( m_width, value ) )
				{
					setFixedSize(QSize(value, height()));  //HACK
					return true;
				}
			}

			else if ( id == "height" )
			{
				if ( compareAndSetValue( m_height, value ) )
				{
					setFixedSize(QSize(width(), value));  //HACK
					return true;
				}
			}
			
			return false;
		}
		
		void BQLineEdit_float::onChange()
		{
			auto v = text().toFloat();
			if ( m_value != v )
			{
				m_value = v;
// 				std::cout << "2BQLineEdit_float::onChange(): " << id() << name() << " " << m_value << " STRING: " << text().toStdString() << " UINT: " << text().toUInt() << std::endl;
				onUpdate();
			}
		}

	// QLINEEDIT_double
		BQLineEdit_double::BQLineEdit_double()
		: QLineEdit()
		, m_width(0)
		, m_height(0)
		{
			connect(this, SIGNAL(editingFinished()), SLOT(onChange()));
// 			connect(this, SIGNAL(textChanged(const QString&)), SLOT(onChange()));
		}

		bool BQLineEdit_double::set( BEntity* entity )
		{
			QString s;
			s.setNum( entity->get_double() );
			if ( m_value != entity->get_double() )
			{
// 				std::cout << "BQLineEdit_float::set( BEntity* entity ): " << " changing " << text().toStdString() << " to " << entity->get_uint() << std::endl;
				m_value = entity->get_double();
				setText(s);
				onUpdate();
				return true;
			}
			return false;
		}

		bool BQLineEdit_double::set( const char* value )
		{
			QString s(value);
			if ( s != text() )
			{
				setText(s);
				onUpdate();
				return true;
			}
			return false;
		}

		
		bool BQLineEdit_double::set( const Bdouble& value )
		{
			if ( m_value != value )
			{
// 				std::cout << "BQLineEdit_float::set( const Buint& value ): " << " changing " << text().toStdString() << " to " << value << std::endl;
				m_value = value;
				QString s;
				s.setNum(value);
				setText(s);
				onUpdate();

				return true;
			}
			return false;
		}

		bool BQLineEdit_double::set( const Bstring& id, const Bdouble& value )
		{
			if ( id == "value" )
			{
				if ( compareAndSetValue( m_value, value ) )
				{
// 					std::cout << "BQLineEdit_float::set( const Bstring& id, const Buint& value ): " << " changing " << text().toStdString() << " to " << value << std::endl;
					QString s;
					s.setNum(value);
					setText(s);
					onUpdate();
					return true;
				}
			}

			return false;
		}

		bool BQLineEdit_double::set( const Bstring& id, const Buint& value )
		{
			if ( id == "width" )
			{
				if ( compareAndSetValue( m_width, value ) )
				{
					setFixedSize(QSize(value, height()));  //HACK
					return true;
				}
			}

			else if ( id == "height" )
			{
				if ( compareAndSetValue( m_height, value ) )
				{
					setFixedSize(QSize(width(), value));  //HACK
					return true;
				}
			}

			return false;
		}
		
		void BQLineEdit_double::onChange()
		{
			auto v = text().toDouble();
			if ( m_value != v )
			{
				m_value = v;
// 				std::cout << "2BQLineEdit_float::onChange(): " << id() << name() << " " << m_value << " STRING: " << text().toStdString() << " UINT: " << text().toUInt() << std::endl;
				onUpdate();
			}
		}







