#ifndef QWIDGET_H_INCLUDED
#define QWIDGET_H_INCLUDED

#include "kernel/be_entity_interface.h"
#include <QWidget>

		class BQWidget : public QWidget, public BEntity
		{
			Q_OBJECT
			public:
				BQWidget();
				virtual ~BQWidget() {};
				const char* class_id() const { return "QWidget"; }

		};

#endif
