#ifndef QMDIWINDOW_H_INCLUDED
#define QMDIWINDOW_H_INCLUDED

#include <QMdiSubWindow>
#include <QCloseEvent>

#include "kernel/be_entity_interface.h"

	class BQMdiWindow : public QMdiSubWindow, public BEntity
	{
		public:
			BQMdiWindow();
			virtual ~BQMdiWindow() {};
			const char* class_id() const { return "QMdiWindow"; }
			virtual Bbool onAddChild( BEntity* entity );
			virtual void closeEvent(QCloseEvent *event);
			void windowClosed();
	};
 
#endif
