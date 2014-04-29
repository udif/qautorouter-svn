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
#ifndef CSPECCTRAREADER_H
#define CSPECCTRAREADER_H

#include "cspecctraobject.h"

#include <QObject>
#include <QTextStream>

#define MAX_SPECCTRA_FILESIZE 5000000

class QAutoRouter;
class CSpecctraReader : public QObject
{
	Q_OBJECT
	public:
		CSpecctraReader(QAutoRouter *parent);
		CSpecctraReader(QTextStream& stream,QAutoRouter *parent);
		virtual ~CSpecctraReader();

		CSpecctraObject*			read(QTextStream& stream);
		CSpecctraObject*			read();
		CSpecctraObject*			root()	{return mRoot;}

	signals:
		void						fault(QString txt);

	protected:
		CSpecctraObject*			parse();
		QString						token();
		QChar						peek();
		QChar						next();
		QChar						prev();
		QChar						span();
		QString						word();
		bool						white(QChar ch);
		bool						bof();
		bool						eof();
		CSpecctraObject*			make(QString& oClass,CSpecctraObject* parentObject);

		QString						mTextBuffer;
		unsigned int				mTextIndex;
		CSpecctraObject*			mRoot;
};

#endif // CSPECTRAREADER_H

