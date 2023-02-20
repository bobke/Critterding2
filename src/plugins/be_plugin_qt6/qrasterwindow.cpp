#include "qrasterwindow.h"
// #include "kernel/be_plugin_base_entity_types.h"
#include "kernel/be_entity_core_types.h"
#include "qboxlayouts.h"
// #include "qmdiarea.h"

#include <iostream>
#include <QCloseEvent>
#include <QtGui>

// ENTIRE THING IS A HACK

	// QWINDOW THIS 
		BQRasterWindow::BQRasterWindow(QWindow *parent)
		: QWindow(parent)
		, m_destroy_entity_on_close(this)
		, m_x(0)
		, m_y(0)
		, m_width(0)
		, m_height(0)
		, m_isFullscreen(false)
		, m_isMaximized(false)
		, m_isMinimized(false)
		, m_isActiveWindow(false)
		, m_isVisible(false)
		, m_isHidden(false)
		, m_isEnabled(false)
		, m_backingStore(new QBackingStore(this))
		{
			// SET PROCESSING BIT
				setProcessing();
// 				m_flags.m_has_processing = true;

			setTitle("Engine Qt6 ");
			QWindow::setVisible(true);
		}

		BQRasterWindow::~BQRasterWindow()
		{
			delete m_backingStore;
		};
		
		void BQRasterWindow::process()
		{
			renderLater();
// 			requestUpdate();
// 			renderNow();
		}

	// PROPERTIES
		bool BQRasterWindow::set( const Bstring& id, const Buint& value )
		{
			if ( id == "x" )
			{
				if ( compareAndSetValue( m_x, value ) )
				{
					setX(value);
// 					move(value, y());
					return true;
				}
			}

			else if ( id == "y" )
			{
				if ( compareAndSetValue( m_y, value ) )
				{
					setY(value);
// 					move(x(), value);
					return true;
				}
			}

			else if ( id == "width" )
			{
				if ( compareAndSetValue( m_width, value ) )
				{
					resize(value, height());
					return true;
				}
			}

			else if ( id == "height" )
			{
				if ( compareAndSetValue( m_height, value ) )
				{
					resize(width(), value);
					return true;
				}
			}

			return false;
		}

		Buint BQRasterWindow::get_uint( const Bstring& id )
		{
			if ( id == "x" )
			{
				return x();
			}
			if ( id == "y" )
			{
				return y();
			}
			if ( id == "width" )
			{
				return width();
			}
			if ( id == "height" )
			{
				return height();
			}

			return 0;
		}
		
	// PROPERTIES
		bool BQRasterWindow::set( const Bstring& id, BEntity* value )
		{
// 			std::cout << "BQRasterWindow::set " << id << " " << value->id() << std::endl;
			if ( id == "on_close_destroy_entity" )
			{
				if ( compareAndSetValue( m_destroy_entity_on_close, value ) )
				{
// 					std::cout << " is now " << m_destroy_entity_on_close->id() << std::endl;
					return true;
				}
			}

			return false;
		}

		BEntity* BQRasterWindow::get_reference( const Bstring& id )
		{
			if ( id == "on_close_destroy_entity" )
			{
				return m_destroy_entity_on_close;
			}

			return 0;
		}		

		void BQRasterWindow::moveEvent(QMoveEvent *event)
		{
			// FIXME SEND SIGNALS
			if ( compareAndSetValue( m_x, (Buint)event->pos().x() ) )
			{
// 				std::cout << id() << " x: " << m_x << std::endl;
			}
			if ( compareAndSetValue( m_y, (Buint)event->pos().y() ) )
			{
// 				std::cout << id() << " y: " << m_y << std::endl;
			}
		}

		void BQRasterWindow::resizeEvent(QResizeEvent *event)
		{
			// FIXME SEND SIGNALS
			if ( compareAndSetValue( m_width, (Buint)event->size().width() ) )
			{
// 				std::cout << "width: " << m_width << std::endl;
			}
			if ( compareAndSetValue( m_height, (Buint)event->size().height() ) )
			{
// 				std::cout << "height: " << m_height << std::endl;
			}
			// FIXME DISABLED FOR NOW BECAUSE WARNING
// 			if ( compareAndSetValue( m_isFullscreen, isFullScreen() ) )
// 			{
// // 				std::cout << "fullscreen: " << m_isFullscreen << std::endl;
// 			}
			// FIXME DISABLED FOR NOW BECAUSE WARNING
// 			if ( compareAndSetValue( m_isMaximized, isMaximized() ) )
// 			{
// // 				std::cout << "maximized: " << m_isMaximized << std::endl;
// 			}

			m_backingStore->resize(event->size());
		}

// 		void BQRasterWindow::changeEvent(QEvent *event)
// 		{
// 			// FIXME DISABLED FOR NOW BECAUSE WARNING
// // 			if ( compareAndSetValue( m_isMinimized, isMinimized() ) )
// // 			{
// // // 				std::cout << "minimized: " << m_isMinimized << std::endl;
// // 			}
// 			// FIXME DISABLED FOR NOW BECAUSE WARNING
// // 			if ( compareAndSetValue( m_isActiveWindow, isActiveWindow() ) )
// // 			{
// // // 				std::cout << "active window: " << m_isActiveWindow << std::endl;
// // 			}
// 			// FIXME DISABLED FOR NOW BECAUSE WARNING
// // 			if ( compareAndSetValue( m_isVisible, isVisible() ) )
// // 			{
// // // 				std::cout << "visible: " << m_isVisible << std::endl;
// // 			}
// 			// FIXME DISABLED FOR NOW BECAUSE WARNING
// // 			if ( compareAndSetValue( m_isHidden, isHidden() ) )
// // 			{
// // // 				std::cout << "hidden: " << m_isHidden << std::endl;
// // 			}
// 			// FIXME DISABLED FOR NOW BECAUSE WARNING
// // 			if ( compareAndSetValue( m_isEnabled, isEnabled() ) )
// // 			{
// // // 				std::cout << "enabled: " << m_isEnabled << std::endl;
// // 			}
// 		}
		
// 		void BQRasterWindow::hideEvent(QHideEvent *event)
// 		{
// // 			// FIXME SEND SIGNALS
// // 			if ( compareAndSetValue( m_isMinimized, isMinimized() ) )
// // 			{
// // 				std::cout << "minimized: " << m_isMinimized << std::endl;
// // 			}
// 		}
// 
// 		void BQRasterWindow::showEvent(QShowEvent *event)
// 		{
// 		}
		
// 		void BQRasterWindow::dragEnterEvent(QDragEnterEvent *event)
// 		{
// 			(void)event;
// 			std::cout << "drag event" << std::endl;
// // 			if (event->mimeData()->hasText()) {
// // 				if (event->source() == this) {
// // 					event->setDropAction(Qt::MoveAction);
// // 					event->accept();
// // 				} else {
// // 					event->acceptProposedAction();
// // 				}
// // 			} else {
// // 				event->ignore();
// // 			}
// 		}

		void BQRasterWindow::closeEvent(QCloseEvent *event)
		{
			if ( event )
			{
				// add remove command to the command buffer
				BEntity* cmdbuffer = topParent()->getChild("_command_buffer");
				if ( cmdbuffer )
				{
					cmdbuffer->addChild("remove", new BEntity_reference() )->set( m_destroy_entity_on_close );
				}

				event->ignore();
			}
		}


		bool BQRasterWindow::event(QEvent *event)
		{
			if (event->type() == QEvent::UpdateRequest) {
				renderNow();
				return true;
			}
			return QWindow::event(event);
		}

		void BQRasterWindow::renderLater()
		{
			requestUpdate();
		}

		void BQRasterWindow::exposeEvent(QExposeEvent *)
		{
			renderNow();
		}

		void BQRasterWindow::renderNow()
		{
			if (!isExposed())
				return;

// 			std::cout << "yep" << std::endl;

			// PAINT BACKGROUND
				QRect rect(0, 0, width(), height());

				m_backingStore->beginPaint(rect);

				QPaintDevice* device = m_backingStore->paintDevice();
				QPainter painter(device);

				painter.fillRect( 0, 0, width(), height(), Qt::lightGray );
// 				painter.fillRect( 0, 0, width(), height(), QRgb("#AARRGGBB") );
				

				render(&painter);
				painter.end();

				m_backingStore->endPaint();
				m_backingStore->flush(rect);
		}

		void BQRasterWindow::render(QPainter *painter)
		{
				unsigned int spacing_mhz(1);
				unsigned int width_mhz = (this->width() - (33*spacing_mhz)) / 32  ;
// 				unsigned int width(26);
				unsigned int height_mhz( this->height() - spacing_mhz - spacing_mhz );
				unsigned int current_pos_x_mhz(0);
			
				unsigned int spacing_percent(1);
				unsigned int width_percent = (this->width() - (33*spacing_percent)) / 32  ;
// 				unsigned int width(26);
				unsigned int height_percent( this->height() - spacing_percent - spacing_percent );
				unsigned int current_pos_x_percent(0);

				unsigned int current_cpu(0);
				unsigned int height_converted_mhz( height_mhz );

				current_pos_x_percent += spacing_percent;
				current_pos_x_mhz += spacing_mhz; // because skip the first one (Composite)
				
				for ( auto child(BEntity::children().begin()); child != BEntity::children().end(); ++child )
				{
					if ( (*child)->name() == "mhz" )
					{
						if ( (*child)->get_uint() <= 5100 ) // FIXME FIND HIGHEST
						{
// 							unsigned int height_converted = height() - (((*child)->get_uint() / 50100) * height_mhz);
							
							height_converted_mhz = ((Bfloat)(*child)->get_uint() / 5100) * height_mhz;
// 							std::cout << (*child)->get_uint() << " -> " << height_converted_mhz << std::endl;

							painter->fillRect(
								current_pos_x_mhz,
								spacing_mhz + height_mhz - height_converted_mhz,
								width_mhz,
								height_converted_mhz,
// 								QGradient::RareWind
// 								QGradient::SnowAgain
								QGradient::HeavyRain
							);
						}

// 						QString to_print( QString::number( current_cpu++ ) );
// 						if ( to_print == "0" )
// 							to_print = "C";
// 						
// 						painter->drawText(
// 							QRectF(current_pos_x_percent, spacing_percent, width_percent, height_percent),
// 							Qt::AlignCenter,
// 							to_print
// 						);
						
// 						current_pos_x_mhz += spacing_mhz + width_mhz;
					}
					
					else if ( (*child)->name() == "mhz_highest" )
					{
						if ( (*child)->get_uint() <= 5100 ) // FIXME FIND HIGHEST
						{
// 							unsigned int height_converted = height() - (((*child)->get_uint() / 50100) * height_mhz);
							
							height_converted_mhz = ((Bfloat)(*child)->get_uint() / 5100) * height_mhz;
// 							std::cout << (*child)->get_uint() << " -> " << height_converted_mhz << std::endl;

							painter->fillRect(
								current_pos_x_mhz,
								spacing_mhz + height_mhz - height_converted_mhz,
								width_mhz,
								1,
								QGradient::RareWind
// 								QGradient::SnowAgain
// 								QGradient::HeavyRain
							);
						}

// 						QString to_print( QString::number( current_cpu++ ) );
// 						if ( to_print == "0" )
// 							to_print = "C";
// 						
// 						painter->drawText(
// 							QRectF(current_pos_x_percent, spacing_percent, width_percent, height_percent),
// 							Qt::AlignCenter,
// 							to_print
// 						);
						
						current_pos_x_mhz += spacing_mhz + width_mhz;
					}
					
					
					
					else if ( (*child)->name() == "perc_idle" && child != BEntity::children().begin() )
					{
						if ( (*child)->get_float() < 100.0f )
						{
							unsigned int height_converted_percent = height_converted_mhz - (((*child)->get_float() / 100) * height_converted_mhz);

							Buint height_adjusted_for_zero = height_converted_percent - spacing_percent - spacing_percent;
							
							if ( height_adjusted_for_zero > 0 )
							{
								painter->fillRect(
									current_pos_x_percent + spacing_percent,
									spacing_mhz + spacing_percent + height_percent - height_converted_percent,
									width_percent - spacing_percent - spacing_percent,
									height_adjusted_for_zero,

	// 								QGradient::JuicyPeach
	// 								QGradient::YoungPassion
	// 								QGradient::RainyAshville
	// 								QGradient::FrozenDreams
	// 								QGradient::WinterNeva
	// 								QGradient::DustyGrass
	// 								QGradient::TemptingAzure
	// 								QGradient::NewLife
	// 								QGradient::TrueSunset
// 									QGradient::MorpheusDen
	// 								QGradient::RareWind
	// 								QGradient::NearMoon
	// 								QGradient::WildApple
	// 								QGradient::SaintPetersburg
// 									QGradient::PlumPlate
// 									QGradient::EverlastingSky
// 									QGradient::HappyFisher
// 									QGradient::Blessing
									QGradient::FlyHigh
	// 								QGradient::StrongBliss
	// 								QGradient::FreshMilk
	// 								QGradient::SnowAgain

								);
							}
						}
						
						QString to_print( QString::number( ++current_cpu ) );
// 						if ( to_print == "0" )
// 							to_print = "C";

						{
							painter->drawText(
								QRectF(current_pos_x_percent, spacing_percent, width_percent, height_percent),
								Qt::AlignCenter,
								to_print
							);
						}
						
						current_pos_x_percent += spacing_percent + width_percent;
					}
				}
// 				painter.fillRect(0, 0, 50, 50, QGradient::WarmFlame	);
// 				painter.fillRect(55, 0, 50, 50, QGradient::NightFade);
// 
// 				painter.fillRect(57, 0, 46, 40, QGradient::SpringWarmth);
				
				// QGradient::JuicyPeach	
				// QGradient::YoungPassion				
			
// 			painter->drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, QStringLiteral("QWindow"));
			
		}
