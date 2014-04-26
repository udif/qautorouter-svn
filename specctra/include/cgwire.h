/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#ifndef CGWIRE_H
#define CGWIRE_H

#include <QObject>
#include <QList>
#include <QPointF>
#include <QPainterPath>

#include "cgsegment.h"

class CPcbNet;
class CGWire : public CGSegment
{
	Q_OBJECT
	public:
		CGWire(CPcbNet *net);
		virtual ~CGWire();

        virtual bool				isA(CGSegment::tSegmentType t) {t==Wire || CGSegment::isA(t);}

        virtual CPcbNet*			net();

        virtual bool				insertBreak(QPointF pt,CGSegment::tSegmentType style);

		virtual QPainterPath		shape() const;

		virtual void				route();
};

#endif // CGWIRE_H
