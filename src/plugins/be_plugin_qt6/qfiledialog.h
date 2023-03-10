#ifndef QFILEDIALOG_H_INCLUDED
#define QFILEDIALOG_H_INCLUDED

#include "kernel/be_entity_interface.h"
#include <QFileDialog>

	class BQFileDialog : public QFileDialog, public BEntity
	{
		Q_OBJECT
		public:
			BQFileDialog()/* : m_destroy_entity_on_close(this)*/ {};
			virtual ~BQFileDialog() {};
			const char* class_id() const { return "QFileDialog"; }
			
			void construct();
			
			// virtual void closeEvent(QCloseEvent *event); // FIXME

			// BEntity* m_destroy_entity_on_close;
	};

#endif
