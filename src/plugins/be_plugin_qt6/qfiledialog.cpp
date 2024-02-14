#include "qfiledialog.h"
#include "kernel/be_entity_core_types.h"
#include <QCloseEvent>

	void BQFileDialog::construct()
	{
		m_title = addChild("title", "string");
		m_title->set("Open File");

		m_filetype = addChild("filetype", "string");
		m_filetype->set("*.*");
	}

	bool BQFileDialog::set()
	{
		std::string fileFull = "Files (";
		fileFull.append(m_filetype->get_string());
		fileFull.append(")");
		
		auto selected_file = addChild( "selected_file", new BEntity_string() );
		selected_file->set( QFileDialog::getOpenFileName( this, tr( m_title->get_string() ), "", tr( fileFull.c_str() ) ).toStdString().c_str() );
		// selected_file->set( QFileDialog::getOpenFileName( this, tr( m_title->get_string() ), "", tr( "Files (*.*)" ) ).toStdString().c_str() );
		return true;
	}
	

	// FIXME
	// void BQFileDialog::closeEvent(QCloseEvent *event)
	// {
	// 	if ( event )
	// 	{
	// 		// add remove command to the command buffer
	// 		BEntity* cmdbuffer = topParent()->getChild("_command_buffer");
	// 		if ( cmdbuffer )
	// 		{
	// 			cmdbuffer->addChild("remove", new BEntity_reference() )->set( m_destroy_entity_on_close );
	// 		}
 // 
	// 		event->ignore();
	// 	}
	// }
