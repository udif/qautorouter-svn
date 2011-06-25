/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#ifndef CPCBNET_H
#define CPCBNET_H

#include <QObject>
#include <QString>

#include "cspecctraobject.h"
#include "cgpadstack.h"

class CPcbPins;
class CPcbClass;
class CPcbNet : public CSpecctraObject
{
	Q_OBJECT
	public:
		CPcbNet(QGraphicsItem *parent = 0);
		virtual ~CPcbNet();

		virtual QString				name();
		virtual QString				description();

		void						setWidth(double w) {mWidth=w;}
		double						width();
		bool						routed() {return mRouted;}
		CPcbClass*					netClass();
		virtual QRectF				boundingRect() const;
		virtual QPainterPath		shape() const;
		virtual void				paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
	private:
		QPainterPath				mShape;
		bool						mRouted;
		double						mWidth;			/* trace width */
};

#endif // CPCBNET_H

