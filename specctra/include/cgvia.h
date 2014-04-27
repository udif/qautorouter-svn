/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#ifndef CGVIA_H
#define CGVIA_H

#include <QObject>
#include <QPainterPath>
#include <QString>
#include <QGraphicsItem>
#include <QMap>
#include <cgpadstack.h>

class CPcbNet;
class CGVia : public CGPadstack
{
	Q_OBJECT
	public:
		CGVia(CPcbNet* net);
		virtual ~CGVia();

        virtual Segment_t           segmentType() {return Via;}
        virtual bool				isA(CGSegment::Segment_t t) {t==Via || CGPadstack::isA(t);}

		virtual void				route();

	private:

};

#endif // CGVIA_H
