#ifndef PLUGIN_H_INCLUDED
#define PLUGIN_H_INCLUDED

#include "kernel/be_entity_core_types.h"

#include <QWidget>
#include <QwtPlot>
#include <QwtPlotCurve>

// PLOT
		class BeEntityQwtPlot : public BEntity, public QwtPlot
		{
			// Q_OBJECT
			public:
				BeEntityQwtPlot();
				virtual ~BeEntityQwtPlot() {};
				virtual Bbool onAddChild( BEntity* entity );
// 				virtual Bbool onRemoveChild( BEntity* entity );
			protected:
		};


// CURVE
		class BeEntityQwtPlotCurve : public BEntity, public QwtPlotCurve
		{
			public:
				BeEntityQwtPlotCurve();
				virtual ~BeEntityQwtPlotCurve();
				void construct();

				virtual Bbool onAddChild( BEntity* entity );
				void addValue( float value );
			protected:
				// QVector<QPointF> m_list;
				QVector<double> m_list;
				unsigned int m_count;
				BEntity* m_size_max;
				void resizeList();
		};


// CURVE_FLOAT
		class BeEntityQwtPlotCurve_Float : public BeEntityQwtPlotCurve
		{
			public:
				BeEntityQwtPlotCurve_Float() : BeEntityQwtPlotCurve() {};
				virtual ~BeEntityQwtPlotCurve_Float() {};

				virtual bool set( const Bfloat& value );
				virtual bool set( const Buint& value );
		protected:
		};

// CURVE_FLOAT_POLL
		class BeEntityQwtPlotCurve_Float_Poll : public BeEntityQwtPlotCurve
		{
			public:
				BeEntityQwtPlotCurve_Float_Poll();
				virtual ~BeEntityQwtPlotCurve_Float_Poll() {};
				
				void process();
				bool set( const Bstring& id, BEntity* value );

		protected:
				BEntity* m_entity_to_poll;
		};

#endif
