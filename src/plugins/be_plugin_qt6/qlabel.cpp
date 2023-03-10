#include "qlabel.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QRegularExpression>
#include <iostream>

	// QLABEL
		BQLabel::BQLabel()
		: QLabel()
		{
// 			setText("label");
// 			setSizeConstraint(QLayout::SetMinimumSize);
			setAlignment(Qt::AlignVCenter | Qt::AlignRight);
			// setContentsMargins(10,5,5,5); // HACK
		}

		bool BQLabel::set( const Bstring& id, const Buint& value )
		{
			if ( id == "text" )
			{
				if ( value != text().toUInt() )
				{
					// setAlignment(Qt::AlignRight);
					QString s;
					s.setNum(value);
					setText(s);
					return true;
				}
			}
			else if ( id == "width" )
			{
				if ( width() != (int)value )
				{
					setFixedSize(QSize(value, height()));  //HACK
					return true;
				}
			}
			else if ( id == "height" )
			{
				if ( height() != (int)value )
				{
					setFixedSize(QSize(width(), value));  //HACK
					return true;
				}
			}
			return false;
		}

		bool BQLabel::set( const Bstring& id, const char* value )
		{
			if ( id == "text" )
			{
				if ( value != text() )
				{
					setAlignment(Qt::AlignLeft);
					setText(value);
					return true;
				}
			}
			return false;
		}
		
		bool BQLabel::set( const char* value )
		{
			if ( value != text() )
			{
				setAlignment(Qt::AlignLeft);
				setText( value );
				return true;
			}
		}

		bool BQLabel::set( const Buint& value )
		{
			if ( value != text().toUInt() )
			{
				setAlignment(Qt::AlignLeft);
				QString s;
				s.setNum(value);
				setText(s);
				return true;
			}
		}
		

	// QLABELDROPPABLE
		BQLabelDroppable::BQLabelDroppable()
		{
			setAcceptDrops(true);
// 			setFixedWidth(170);
			
		}

		void BQLabelDroppable::dragEnterEvent(QDragEnterEvent *event)
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

		void BQLabelDroppable::dragLeaveEvent(QDragLeaveEvent *event)
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

		void BQLabelDroppable::dropEvent(QDropEvent *event)
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
						std::cout << "dropped into("		<< id() 				<< ":" << name() << ")";
						std::cout << " source(" 			<< source_entity->id() 	<< ":" << source_entity->name() << ")";
						std::cout << " spawn("	 			<< ref_entity->id() 	<< ":" << piece.toStdString() << ")";
						std::cout << std::endl;
						
						// SPAWN NEW ENTITY
//						std::cout << id() << " " << BEntity::parent()->BEntity::parent()->name() << ": spawn ";
//						ref_entity->addChild(piece.toStdString(), piece.toStdString());
						topParent()->getChild("Scene", 3)->addChild(piece.toStdString(), piece.toStdString());

	// 					DragLabel *newLabel = new DragLabel(piece, this);
	// 					newLabel->move(position - hotSpot);
	// 					newLabel->show();
	// 					newLabel->setAttribute(Qt::WA_DeleteOnClose);
	// 
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
