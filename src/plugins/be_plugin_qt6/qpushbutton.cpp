#include "qpushbutton.h"
// #include "kernel/be_entity_core_types.h"
#include "kernel/be_lib_handler.h"
#include <iostream>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
// #include <QDragEnterEvent>
#include <QRegularExpression>


	// QBUTTON
		BQPushButton::BQPushButton()
		: QPushButton()
		{
// 			BEntity_trigger::setOutput( new BEOutput(this) );
			connect(this, SIGNAL(clicked()), SLOT(onClick()));
// 		    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		}

		bool BQPushButton::set( const Bstring& id, const char* value )
		{
			if ( id == "text" )
			{
				QString s(value);
				if ( s != text() )
				{
					setText(s);
					setFixedSize(QSize(10 * s.size(), 15));  //HACK
					return true;
				}
			}
			return false;
		}

		void BQPushButton::onClick()
		{
// 			execute_commands();

			// FIXME MAKE A NICE LITTLE FUNCTION FOR THIS IN ENTITY_INTERFACE
			// HACK MAKE A COPY FUNCTION FINALLY
			auto actions = getChild("_commands", 1);
			if ( actions )
			{
				auto cmdbuffer = topParent()->getChild("_command_buffer", 1);
				if ( cmdbuffer )
				{
					for_all_children_of(actions)
					{
						auto cmdref = cmdbuffer->addChild("reference", new BEntity_reference() ); // FIXME make this a reference when adding to the actions too
						cmdref->set(*child);
					}
				}
			}
			onUpdate();
		}

		bool BQPushButton::set( const Bstring& id, const Buint& value )
		{
			if ( id == "value" )
			{
				QString s;
					s.setNum(value);
				
				if ( s != text() )
				{
					setText(s);
				}
			}
			
			else if ( id == "width" )
			{
				if ( width() != (int)value )
				{
					setFixedSize(QSize(value, height()));  //HACK
				}
			}

			else if ( id == "height" )
			{
				if ( height() != (int)value )
				{
					setFixedSize(QSize(width(), value));  //HACK
				}
			}
			else
				return false;
			
			return true;
		}


	// QBUTTONDRAGABLE
		BQPushButtonDraggable::BQPushButtonDraggable()
		: BQPushButton()
		{
		}

		void BQPushButtonDraggable::mousePressEvent(QMouseEvent *event)
		{
// 			QPushButton *child = static_cast<QPushButton*>(childAt(event->pos()));
// 			if (!child)
// 				return;

// 			const auto& childAt(event->pos());
			BQPushButtonDraggable* child(this);
			
// 			std::cout << "ok" << std::endl;
// 			QPoint hotSpot = event->pos() - child->pos();
			QPoint hotSpot = event->pos();

			QMimeData *mimeData = new QMimeData;
			mimeData->setText(child->text());
			mimeData->setData("application/x-hotspot", QByteArray::number(hotSpot.x()) + " " + QByteArray::number(hotSpot.y()));

			QPixmap pixmap(child->size());
			child->render(&pixmap);

			QDrag *drag = new QDrag(this);
			drag->setMimeData(mimeData);
			drag->setPixmap(pixmap);
			drag->setHotSpot(hotSpot);

			Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);

			if (dropAction == Qt::MoveAction)
			{
				std::cout << "dropped into itself?" << std::endl;
// 				child->close();
			}
		}

		
	// QBUTTONDROPPABLE
		BQPushButtonDroppable::BQPushButtonDroppable()
		{
			setAcceptDrops(true);
// 			setFixedWidth(170);
			
		}

		void BQPushButtonDroppable::dragEnterEvent(QDragEnterEvent *event)
		{
// 			std::cout << "drag event entered" << std::endl;
			if (event->mimeData()->hasText()) {
				if (event->source() == this) {
					event->setDropAction(Qt::MoveAction);
					event->accept();
				} else {
					setStyleSheet("QLabel { background-color : white }");
					event->acceptProposedAction();
				}
			} else {
				std::cout << "ignored" << std::endl;
				event->ignore();
			}
		}

		void BQPushButtonDroppable::dragLeaveEvent(QDragLeaveEvent *event)
		{
			(void) event;
			setStyleSheet("QLabel { background-color : none }");
// 			std::cout << "drag event left" << std::endl;
// 			if (event->mimeData()->hasText()) {
// 				if (event->source() == this) {
// 					event->setDropAction(Qt::MoveAction);
// 					event->accept();
// 				} else {
// 					event->acceptProposedAction();
// 				}
// 			} else {
// 				std::cout << "ignored" << std::endl;
				event->ignore();
// 			}
		}

		void BQPushButtonDroppable::dropEvent(QDropEvent *event)
		{
			if (event->mimeData()->hasText()) {
				const QMimeData *mime = event->mimeData();
// 				QStringList pieces = mime->text().split(QRegExp("\\s+"), QString::SkipEmptyParts);
				QStringList pieces = mime->text().split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
				
				QPoint hotSpot;

				QList<QByteArray> hotSpotPos = mime->data("application/x-hotspot").split(' ');
				if (hotSpotPos.size() == 2) {
					hotSpot.setX(hotSpotPos.first().toInt());
					hotSpot.setY(hotSpotPos.last().toInt());
				}

// 				QPoint position = event->position().toPoint();
// 				foreach (QString piece, pieces) {
// 					DragLabel *newLabel = new DragLabel(piece, this);
// 					newLabel->move(position - hotSpot);
// 					newLabel->show();
// 					newLabel->setAttribute(Qt::WA_DeleteOnClose);
// 
// 					position += QPoint(newLabel->width(), 0);
// 				}

				foreach (QString piece, pieces)
				{
					auto source_entity = dynamic_cast<BEntity*>(event->source());
					if ( source_entity )
					{
						BEntity* ref_entity( source_entity->getChild("reference", 1)->get_reference() );
						BEntity* target_entity( getChild("reference", 1)->get_reference() );
						std::cout << "dropped into("		<< id() 				<< ":" << name() << ")";
						std::cout << " source(" 			<< source_entity->id() 	<< ":" << source_entity->name() << ")";
						std::cout << " target(" 			<< target_entity->id() 	<< ":" << target_entity->name() << ")";
						std::cout << " spawn("	 			<< ref_entity->id() 	<< ":" << piece.toStdString() << ")";
						std::cout << std::endl;
						
						// SPAWN NEW ENTITY
						// target_entity->addChild( piece.toStdString(), piece.toStdString() );
						
						// SPAWN NEW ENTITY
						// get the parent of parent of ref_entity, which is a plugin
						// let that generate our new object, then pass to param 2
						BEntity_Plugin* p = dynamic_cast<BEntity_Plugin*>( ref_entity->parent()->parent() );
						if ( p )
						{
							auto plugin_function = p->create( 0, ref_entity->get_uint() );
							target_entity->addChild( piece.toStdString(), plugin_function );
						}
						else
						{
							std::cout << "warning: not from a library" << std::endl;
						}


	// 					DragLabel *newLabel = new DragLabel(piece, this);
	// 					newLabel->move(position - hotSpot);
	// 					newLabel->show();
	// 					newLabel->setAttribute(Qt::WA_DeleteOnClose);
	// 					position += QPoint(newLabel->width(), 0);
					}
				}

				if (event->source() == this)
				{
					event->setDropAction(Qt::MoveAction);
					event->accept();
				}
				else
				{
					event->acceptProposedAction();
				}
			}
			else
			{
				event->ignore();
			}

			foreach (QObject *child, QObject::children())
			{
				if (child->inherits("QWidget"))
				{
					QWidget *widget = static_cast<QWidget *>(child);
					if (!widget->isVisible())
						widget->deleteLater();
				}
			}
			setStyleSheet("QLabel { background-color : none }");
		}		

		
	// QBUTTONDRAGANDDROPABLE
		BQPushButtonDragAndDroppable::BQPushButtonDragAndDroppable()
		: BQPushButtonDroppable()
		{
		}

		void BQPushButtonDragAndDroppable::mousePressEvent(QMouseEvent *event)
		{
// 			QPushButton *child = static_cast<QPushButton*>(childAt(event->pos()));
// 			if (!child)
// 				return;

// 			const auto& childAt(event->pos());
			BQPushButtonDragAndDroppable* child(this);
			
// 			std::cout << "ok" << std::endl;
// 			QPoint hotSpot = event->pos() - child->pos();
			QPoint hotSpot = event->pos();

			QMimeData *mimeData = new QMimeData;
			mimeData->setText(child->text());
			mimeData->setData("application/x-hotspot", QByteArray::number(hotSpot.x()) + " " + QByteArray::number(hotSpot.y()));

			QPixmap pixmap(child->size());
			child->render(&pixmap);

			QDrag *drag = new QDrag(this);
			drag->setMimeData(mimeData);
			drag->setPixmap(pixmap);
			drag->setHotSpot(hotSpot);

			Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);

			if (dropAction == Qt::MoveAction)
			{
				std::cout << "dropped into itself?" << std::endl;
// 				child->close();
			}
		}		
