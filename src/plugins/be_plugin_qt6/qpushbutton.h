#ifndef QPUSHBUTTON_H_INCLUDED
#define QPUSHBUTTON_H_INCLUDED

// #include "kernel/be_entity_interface.h"
#include "kernel/be_plugin_base_entity_types.h"
#include <QPushButton>

	// QBUTTON
		class BQPushButton : public QPushButton, public BEntity_trigger
		{
			Q_OBJECT
			public:
				BQPushButton();
				virtual ~BQPushButton() {};
				const char* class_id() const { return "QPushButton"; }
				virtual bool set( const Bstring& id, const char* value );
				virtual bool set( const Bstring& id, const Buint& value );
			private Q_SLOTS:
				void onClick();
		};
		
		
	// QBUTTONDRAGGABLE
		class BQPushButtonDraggable : public BQPushButton
		{
			public:
				BQPushButtonDraggable();
				virtual ~BQPushButtonDraggable() {};
				const char* class_id() const { return "QPushButtonDraggable"; }
				bool set( const Bstring& id, const Bstring& value );
				void mousePressEvent(QMouseEvent *event);
		};

	// QBUTTONDROPPABLE
		class BQPushButtonDroppable : public BQPushButton
		{
			public:
				BQPushButtonDroppable();
				virtual ~BQPushButtonDroppable() {};
				const char* class_id() const { return "QPushButtonDroppable"; }
				virtual void dragEnterEvent(QDragEnterEvent *event);
				virtual void dragLeaveEvent(QDragLeaveEvent *event);
			    virtual void dropEvent(QDropEvent *event);
		};

	// QBUTTONDRAGANDDROPPABLE
		class BQPushButtonDragAndDroppable : public BQPushButtonDroppable
		{
			public:
				BQPushButtonDragAndDroppable();
				virtual ~BQPushButtonDragAndDroppable() {};
				const char* class_id() const { return "QPushButtonDragAndDroppable"; }
				bool set( const Bstring& id, const Bstring& value );
				void mousePressEvent(QMouseEvent *event);
		};

#endif
