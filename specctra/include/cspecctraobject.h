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
#ifndef CSPECCTRAOBJECT_H
#define CSPECCTRAOBJECT_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include <QPaintEvent>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <math.h>

#define pi() (3.1415)
#define radian(d) (d*(pi()/180))

/**
  * @brief This is the baseclass for all objects that are derived from a specctra file. Any specctra object
  * @brief may become drawable by adding itself to the QGraphicsScene.
  */

class CPcb;
class CPcbRule;
class CSpecctraObject : public QObject, public QGraphicsItem /* QGraphicsPathItem */
{
	Q_OBJECT
	public:

		/**
		  * @brief tDrawableClass is used to address classes of drawable objects for changnig properties, etc.
		  */
		typedef enum {
			None,
			Track,
			Via,
			Pad,
			Plane,
			Outline,
			Border
		} tDrawableClass;

		CSpecctraObject(QGraphicsItem* parent=NULL);
		CSpecctraObject( const CSpecctraObject& other);
		virtual ~CSpecctraObject();

		virtual QString					name();
		virtual QString					description();
        virtual QString					toText(int lvl=0);
        virtual tDrawableClass			drawableClass();

		CSpecctraObject&				copy( const CSpecctraObject& other );
		CSpecctraObject&				operator=( const CSpecctraObject & other )		{return copy( other ); }

		virtual void					setParent(CSpecctraObject* p);
		virtual void					setObjectClass(QString& objectClass);
		virtual void					appendProperty(QString& property);
		virtual void					appendProperty(QStringList& property);
		virtual void					appendChild(CSpecctraObject* child);

		QList<CSpecctraObject*>			collect(QString oc);
		CSpecctraObject*				parentObject(QString o="");
		QString&						objectClass();
		QStringList&					properties();
		int								childCount(QString o);
		QList<CSpecctraObject*>&		children();
		CSpecctraObject*				child(QString o,int idx=0);
		CSpecctraObject*				root();
		CPcb*							pcb();

        virtual QString					toGeda(int lvl=0);
        virtual QString					gedaObjectClass();
        virtual QStringList				gedaProperties();
        virtual QList<CSpecctraObject*>	gedaChildren();


        virtual QRectF					boundingRect() const;
		virtual void					paint(QPainter*,const QStyleOptionGraphicsItem*, QWidget*);
		virtual void					dump(int lvl=0);

        virtual void                    setDirty(bool)              {}
        virtual bool                    dirty()                     {return false;}

		virtual CPcbRule*				rule();

		static QGraphicsScene*				globalScene();
		static QMap<tDrawableClass,double>&	globalOpacity() {return mOpacity;}
		static QMap<tDrawableClass,bool>&	globalVisibility() {return mVisibility;}

	public slots:
		void							setClassOpacity(tDrawableClass dClass,double opacity);
		void							setClassVisibility(tDrawableClass dClass,bool visible);

	signals:
		void							fault(QString txt);

	protected:

		QString							mObjectClass;			/** The class of spectra object i.e. pcb, component, payer, etc.. */
		QStringList						mProperties;			/** The properties of the object */
		QList<CSpecctraObject*>			mChildren;				/** The offspring of this object */
		CSpecctraObject*				mParentObject;			/** The parent object */
		static	QGraphicsScene*			mGlobalScene;			/** The graphics scheen */

		static	QMap<tDrawableClass,double>	mOpacity;			/** Object opacity map by drawable class */
		static	QMap<tDrawableClass,bool> mVisibility;			/** Object visibility map by drawable class */
};

#endif // CSPECCTRAOBJECT_H

