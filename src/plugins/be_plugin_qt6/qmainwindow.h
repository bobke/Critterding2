#ifndef QMAINWINDOW_H_INCLUDED
#define QMAINWINDOW_H_INCLUDED

#include "kernel/be_entity_interface.h"
#include <QMainWindow>

	// QWINDOW
		class BQMainWindow : public QMainWindow, public BEntity
		{
			Q_OBJECT
			public:
				BQMainWindow();
				virtual ~BQMainWindow();
				const char* class_id() const { return "QMainWindow"; }
				virtual Bbool onAddChild( BEntity* entity );

				virtual bool set( const Bstring& id, const Buint& value );
				virtual Buint get_uint( const Bstring& id );
				virtual bool set( const Bstring& id, BEntity* value );
				virtual BEntity* get_reference( const Bstring& id );
				virtual bool set( const Bstring& id, const char* value );
				virtual const char* get_string( const Bstring& id );

			protected:
				virtual void closeEvent(QCloseEvent *event);
				virtual void moveEvent(QMoveEvent *event);
				virtual void resizeEvent(QResizeEvent *event);
// 				virtual void hideEvent(QHideEvent *event);
// 				virtual void showEvent(QShowEvent *event);
				virtual void changeEvent(QEvent *event);
				void dragEnterEvent(QDragEnterEvent *event);

				BEntity* m_destroy_entity_on_close;

			private:
				// PROPERTIES
				Buint m_x;
				Buint m_y;
				Buint m_width;
				Buint m_height;
				Bbool m_isFullscreen;
				Bbool m_isMaximized;
				Bbool m_isMinimized;
				Bbool m_isActiveWindow;
				Bbool m_isVisible;
				Bbool m_isHidden;
				Bbool m_isEnabled;
				
				QWidget* m_central_widget;
				char* m_title_value;


				
				
// 			void contextMenuEvent(QContextMenuEvent *event);

		};
		
#endif
