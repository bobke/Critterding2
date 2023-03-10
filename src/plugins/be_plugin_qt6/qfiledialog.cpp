#include "qfiledialog.h"
#include "kernel/be_entity_core_types.h"
#include <QCloseEvent>

	void BQFileDialog::construct()
	{
		auto selected_file = addChild( "selected_file", new BEntity_string() );
		selected_file->set( QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.ent)")).toStdString().c_str() );
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
