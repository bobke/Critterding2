#ifndef QRASTERWINDOW_H_INCLUDED
#define QRASTERWINDOW_H_INCLUDED

// FIXME YEAH THIS SHOULD JUST BE RETURNING THE INSIDES, NOT THE WINDOW TO BE EXACT
	// SHOULD NOT EVEN INHERIT FROM ANY QT OBJECT, JUST CONSTRUCT IT AND PROCESS
#include "kernel/be_entity_interface.h"
#include <QWindow>
#include <QWidget>

	// QRASTERWINDOW
		class BQRasterWindow : public QWindow, public BEntity
		{
			Q_OBJECT
			public:
				explicit BQRasterWindow(QWindow* parent = nullptr);
// 				BQRasterWindow();
				virtual ~BQRasterWindow();
				const char* class_id() const { return "QRasterWindow"; }

				virtual void process();

				virtual void render(QPainter *painter);

				virtual bool set( const Bstring& id, const Buint& value );
				virtual Buint get_uint( const Bstring& id );
				virtual bool set( const Bstring& id, BEntity* value );
				virtual BEntity* get_reference( const Bstring& id );

			protected:
				virtual void closeEvent(QCloseEvent *event);
				virtual void moveEvent(QMoveEvent *event);
				virtual void resizeEvent(QResizeEvent *event);
// 				virtual void hideEvent(QHideEvent *event);
// 				virtual void showEvent(QShowEvent *event);
// 				virtual void changeEvent(QEvent *event);
// 				void dragEnterEvent(QDragEnterEvent *event);

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

			public slots:
				void renderLater();
				void renderNow();

			protected:
				bool event(QEvent *event) override;

// 				void resizeEvent(QResizeEvent *event) override;
				void exposeEvent(QExposeEvent *event) override;

			private:
				QBackingStore* m_backingStore;
			
		};
		
#endif
