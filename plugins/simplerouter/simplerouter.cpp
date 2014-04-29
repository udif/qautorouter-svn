/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#include "simplerouter.h"

#include <cspecctraobject.h>
#include <cpcb.h>
#include <cpcbnetwork.h>
#include <cpcbnet.h>
#include <cpcbstructure.h>
#include <cpcbboundary.h>
#include <cpcbpath.h>
#include <cutil.h>
#include <cgsegment.h>
#include <cgwire.h>
#include <cgpadstack.h>
#include <cpcbplacement.h>
#include <cpcbplace.h>

#include <QPolygonF>
#include <QVector>

/**
  * @return plugin type
  */
CPluginInterface::tPluginType SimpleRouter::type()
{
	return CPluginInterface::RouterPlugin;
}

/**
  * @return A title for the plugin to display in user interface.
  */
QString SimpleRouter::title() const
{
	return "Simple Router";
}

/**
  * @return A version for the plugin to display in user interface.
  */
QString SimpleRouter::version() const
{
	return "0.2";
}

/**
  * @return A author for the plugin to display in user interface.
  */
QStringList SimpleRouter::credits() const
{
	QStringList rc;
	rc << "Mike Sharkey <mike@pikeaero.com>";
	return rc;
}

/**
  * @return A website for the plugin to display in user interface.
  */
QString SimpleRouter::website() const
{
	return "http://qautorouter.sourceforge.net";
}

/**
  * @return A short description of the plugin to display in user interface.
  */
QString SimpleRouter::description() const
{
	return "A Simple Auto Router Skeleton";
}

/**
  * @brief The license text
  */
QStringList SimpleRouter::license() const
{
	QStringList rc;
	rc << "GPL Version 2.0";
	rc << "This program is free software; you can redistribute it and/or modify\n"
			"it under the terms of the GNU General Public License as published\n"
			"by the Free Software Foundation; either version 2 of the License,\n"
			"or (at your option) any later version. \n"
			"\n"
			"This program is distributed in the hope that it will be useful, \n"
			"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
			"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the \n"
			"GNU General Public License for more details. \n"
			"\n"
			"You should have received a copy of the GNU General Public License \n"
			"along with this program; if not, write to the \n"
			"\n"
			"Free Software Foundation, Inc.,\n"
			"59 Temple Place - Suite 330,\nBoston, MA 02111-1307,\nU.S.A.\n";
	return rc;
}

/**
  * @return elapsed time to string
  */
QString SimpleRouter::elapsed()
{
	return CUtil::elapsed(mStartTime.secsTo(QDateTime::currentDateTime()));
}

/**
  * @return current state
  */
SimpleRouter::tRunState SimpleRouter::state()
{
	return mState;
}

/**
  * @brief set surrent run state
  */
void SimpleRouter::setState(tRunState state)
{
	mState=state;
}

/**
  * @return A status message for the status line
  */
QString SimpleRouter::currentStatus()
{
	QString msg="[";
	if ( pcb() != NULL && pcb()->network() != NULL )
	{
		switch(state())
		{
			default:
			case Idle:			msg+="Idle  ";	break;
			case Selecting:		msg+="Select";	break;
			case Routing:		msg+="Route ";	break;
		}
		msg += QString("] ")+elapsed()+tr(" Nets: ")+QString::number(pcb()->network()->nets()) + " " + tr("Routed: ")+QString::number(pcb()->network()->routed());
	}
	return msg;
}

/**
  * @brief perform initialization
  */
bool SimpleRouter::start(CPcb* pcb)
{
    mEndPoint[0]=mEndPoint[1]=NULL;
    mRatLine=NULL;
    mNet=NULL;
	mPcb = pcb;
	setState(Idle);
	mStartTime = QDateTime::currentDateTime();
	if ( mPcb != NULL && mPcb->network() != NULL )
	{
		setState(Selecting);
		QObject::connect(this,SIGNAL(status(QString)),mPcb,SIGNAL(status(QString)));
		QObject::connect(this,SIGNAL(clearCache()),mPcb,SLOT(clearCache()));
		return true;
	}
	return false;
}

/**
  * @brief stop processing
  */
void SimpleRouter::stop()
{
	setState(Idle);
	QObject::disconnect(this,SIGNAL(status(QString)),mPcb,SIGNAL(status(QString)));
	QObject::disconnect(this,SIGNAL(clearCache()),mPcb,SLOT(clearCache()));
}

/// draw a single rat line
QGraphicsPathItem* SimpleRouter::drawRatLine()
{
    mRatLine=NULL;
    if ( mNet && mEndPoint[0] && mEndPoint[1] )
    {
        QPainterPath painterPath;
        QPointF pointA = mEndPoint[0]->origin();
        QPointF pointB = mEndPoint[1]->origin();
        painterPath.moveTo( pointA );
        painterPath.lineTo( pointB );
        mRatLine = CSpecctraObject::globalScene()->addPath(painterPath);
    }
	return mRatLine;
}

/**
 * @brief SimpleRouter::selectNet select the next net to route.
 * @return 
 */
CPcbNet* SimpleRouter::selectNet()
{
    CPcbNet* rc=NULL;
    CPcbNetwork* network = pcb()->network();
    for(int n=0; !rc && n < network->nets(); n++)
    {
        CPcbNet* net = network->net(n);
        if ( !net->routed() )
        {
            rc = net;
        }
    }
    return rc;
}

/**
 * @brief Collect two endpoints.
 * @param points[] Array to contain the two end points as CPadStack pointers.
 * @return true on success.
 */
bool SimpleRouter::endPoints()
{
    bool rc=false;
    if ( !mNet->routed() )
    {
        for( int x=0; !rc && x < mNet->padstacks(); x++)
        {
            mEndPoint[0] = mNet->padstack(x);
            if ( !mEndPoint[0]->routed() )
            {
                for( int y=0; !rc && y < mNet->padstacks(); y++)
                {
                    mEndPoint[1] = mNet->padstack(y);
                    if ( mEndPoint[1] != mEndPoint[0] && 
                         mEndPoint[1]->origin() != mEndPoint[0]->origin() && 
                         !mEndPoint[1]->routed() )
                    {
                        rc = true;
                    }
                }
            }
        }
    }
    return rc;
}

/**
 * @brief route this net
 */
void SimpleRouter::route()
{
    if ( !mNet->routed() )
    {
        mNet->sort();
        if ( endPoints() )
        {
            drawRatLine();
            path();
            if ( mRatLine )
            {
                delete mRatLine;
                mRatLine=NULL;
            }
            mEndPoint[0]=mEndPoint[1]=NULL;
        }
    }
}

/**
 * @brief route a segment of this net.
 */
void SimpleRouter::path()
{
    for(int n=0; n < 100; n++)
        pcb()->yield();
}


/**
  * @brief Run for a little bit.
  */
bool SimpleRouter::exec()
{
	bool rc=true;
	emit status(currentStatus());
	switch(state())
	{
		default:
			setState(Selecting);
			break;
		case Idle:
			rc=false;
			break;
		case Selecting:
			setState( (mNet = selectNet()) ? Routing : Idle );
			break;
		case Routing:
			route();
			setState(Selecting);
			break;
	}
	return rc;
}


