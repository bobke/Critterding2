
	#cmake_minimum_required(VERSION 3.20)
	#PROJECT ( bengine3-qt6 )

	set(CMAKE_AUTOMOC ON)
	#set(CMAKE_AUTORCC ON)
	#set(CMAKE_AUTOUIC ON)	

	find_package(Qt6 COMPONENTS Widgets Gui OpenGLWidgets REQUIRED)
	
	SET(
		plugin_SRCS 
		qwindow.h
		qwindow.cpp
		qwidget.h
		qwidget.cpp
		qmenu.h
		qmenu.cpp
		qaction.h
		qaction.cpp
		qrasterwindow.h
		qrasterwindow.cpp
		qboxlayouts.h
		qboxlayouts.cpp
		qmdiarea.h
		qmdiarea.cpp
		qlineedit.h
		qlineedit.cpp
		qgroupbox.h
		qgroupbox.cpp
		qgraphicsscene.h
		qgraphicsscene.cpp
		qgraphicsview.h
		qgraphicsview.cpp
		qopenglwidget.h
		qopenglwidget.cpp
		qgraphicsproxywidget.h
		qgraphicsproxywidget.cpp
		qmdiwindow.h
		qmdiwindow.cpp
		qmainwindow.h
		qmainwindow.cpp
		qpushbutton.h
		qpushbutton.cpp
		qlabel.h
		qlabel.cpp
		qcheckbox.h
		qcheckbox.cpp
		qpen.h
		qpen.cpp
		qfiledialog.h
		qfiledialog.cpp
		qplaintextedit.h
		qplaintextedit.cpp
		
		plugin.h
		plugin.cpp
	)

	ADD_LIBRARY( be_plugin_qt6 SHARED ${plugin_SRCS} )
	#TARGET_LINK_LIBRARIES( be_plugin_qt6 kernel be_base_entity_types Qt6::Widgets Qt6::Gui )
	TARGET_LINK_LIBRARIES( be_plugin_qt6 be_base_entity_types Qt6::Widgets Qt6::Gui Qt6::OpenGLWidgets )

