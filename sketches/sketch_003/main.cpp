//------------------------------------------------------------------------
//
// File generated by The Emerger from emergent.io
//
// Sun Jan 24 14:02:53 2016
//
// Conner Lacy <conner@emergent.io>
//
//------------------------------------------------------------------------

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
QSurfaceFormat format;
format.setDepthBufferSize( 24 );
format.setSamples( 8 );

QSurfaceFormat::setDefaultFormat(format);
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}

