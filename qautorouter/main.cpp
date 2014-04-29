/*******************************************************************************
* Copyright (C) 2014 Pike Aerospace Research Corporation                       *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*                                                                              *
*   This program is free software: you can redistribute it and/or modify       *
*   it under the terms of the GNU General Public License as published by       *
*   the Free Software Foundation, either version 3 of the License, or          *
*   (at your option) any later version.                                        *
*                                                                              *
*   This program is distributed in the hope that it will be useful,            *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of             *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
*   GNU General Public License at <http://www.gnu.org/licenses/>               *
*   for more details.                                                          *
*                                                                              *
*******************************************************************************/
#include <QApplication>
#include <QString>
#include "qautorouter.h"
#include "cspecctrareader.h"
#include "cspecctraobject.h"
#include "cpcb.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Q_INIT_RESOURCE(qautorouter);
	QAutoRouter w;
	w.show();
	if ( argc == 2 )
	{
		QFile file(argv[1]);
		if ( !w.load(file) )
		{
			fprintf(stderr,"error loading file.");
			exit(-1);
		}
	}
	return a.exec();
}
