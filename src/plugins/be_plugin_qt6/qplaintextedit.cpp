// #include "kernel/be_entity_io_handler.h"
#include "qplaintextedit.h"
#include <iostream>

	// QLINEEDIT_string
		BQPlainTextEdit::BQPlainTextEdit()
		: QPlainTextEdit()
		, m_width(0)
		, m_height(0)
		{
			// connect(this, SIGNAL(editingFinished()), SLOT(onChange()));
// 			connect(this, SIGNAL(textChanged(const QString&)), SLOT(onChange()));
		}

		bool BQPlainTextEdit::set( const char* value )
		{
			QString s(value);
			appendPlainText( s );
			// if ( s != text() )
			// {
			// 	setText(s);
			// 	BEntity_string::set( value );
				return true;
			// }
			// return false;
		}


		bool BQPlainTextEdit::set( const Bstring& id, const char* value )
		{
			if ( id == "value" )
			{
				QString s(value);
				// if ( s != text() )
				// {
					appendPlainText( s );
					// setText(s);
					BEntity_string::set( value );
					return true;
				// }
				// return false;
				
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

		bool BQPlainTextEdit::set( const Bstring& id, const Buint& value )
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

		// void BQPlainTextEdit::onChange()
		// {
		// 	BEntity_string::set( text().toStdString().c_str() );
		// }