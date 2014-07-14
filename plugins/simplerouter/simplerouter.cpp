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
#include <cpcblayer.h>

#include <QPolygonF>
#include <QVector>
#include <QEventLoop>

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
SimpleRouter::runState_t SimpleRouter::state()
{
	return mState;
}

/**
  * @brief set surrent run state
  */
void SimpleRouter::setState(runState_t state)
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
        resizeGrid();
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
	QEventLoop loop;
    mRatLine=NULL;
    if ( mNet && mEndPoint[0] && mEndPoint[1] )
    {
        QPainterPath painterPath;
        QPointF pointA = mEndPoint[0]->origin();
        QPointF pointB = mEndPoint[1]->origin();
        painterPath.moveTo( pointA );
        painterPath.lineTo( pointB );
        mRatLine = CSpecctraObject::globalScene()->addPath(painterPath);
        loop.processEvents();
    }
	return mRatLine;
}

/// draw a single rat line
void SimpleRouter::drawPath(QPoint ptA, QPoint ptB)
{
    QPainterPath painterPath;
    painterPath.moveTo(QPointF(mGrid.translate(ptA)));
    painterPath.lineTo(QPointF(mGrid.translate(ptB)));
    //painterPath.moveTo(ptA);
    //painterPath.lineTo(ptB);
    CSpecctraObject::globalScene()->addPath(painterPath);
}

/// draw a single rat line
void SimpleRouter::drawPath()
{
    for(int n=0; n < mPath.count()-1; n++)
    {
        QPoint ptA = mPath.at(n);
        QPoint ptB = mPath.at(n+1);
        drawPath(ptA,ptB);
    }
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
                         ( (mEndPoint[1]->layer() != mEndPoint[0]->layer()) ||
                             (mEndPoint[1]->layer() == mEndPoint[0]->layer() && 
                                mEndPoint[1]->origin() != mEndPoint[0]->origin()) ) && 
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
            QPoint src = mGrid.translate(mEndPoint[0]->origin());
            QPoint dst = mGrid.translate(mEndPoint[1]->origin());

            drawPath(src,dst);
            getPath(src,dst);
            drawPath();

            if ( mPath.count() > 1 )
            {
                mEndPoint[0]->setRouted(true);
                mEndPoint[1]->setRouted(true);
            }
        }
    }
}

/**
 * @brief Resize the routing grid to fit the currebt PCB, and fill with
 * nOpen node states.
 */
void SimpleRouter::resizeGrid()
{
    QPoint topLeft;
    QPoint bottomRight;

    /* Extract PCB boundaries from specctra object in order to size the grid */
    topLeft.setX(mPcb->structure()->boundary()->boundingRect().topLeft().x());
    topLeft.setY(mPcb->structure()->boundary()->boundingRect().topLeft().y());
    bottomRight.setX(mPcb->structure()->boundary()->boundingRect().bottomRight().x());
    bottomRight.setY(mPcb->structure()->boundary()->boundingRect().bottomRight().y());

    /* Apply the grid offset to account for negative offsets in specctra coordinates */
    int translationX = topLeft.x()<0 ? abs(topLeft.x()) : -topLeft.x();
    int translationY = topLeft.y()<0 ? abs(topLeft.y()) : -topLeft.y();
    //int translationX = topLeft.x();
    //int translationY = topLeft.y();
    mGrid.resize(QSize(bottomRight.x()-topLeft.x(),bottomRight.y()-topLeft.y()));
    mGrid.setTranslation(QPoint(translationX,translationY));
    mGrid.fill(SimpleRouterGrid::nOpen);
}

bool SimpleRouter::endPath(QPoint src, QPoint dst)
{
    if ( src.x() == dst.x()-1 || src.x() == dst.x()+1 || src.x() == dst.x() )
    {
        if ( src.y() == dst.y()-1 || src.y() == dst.y()+1 || src.y() == dst.y() )
        {
            return true;
        }
    }
    return false;
}

void SimpleRouter::getPath(QPoint src, QPoint dst)
{
    QPoint next;
    //push source
    mPath.clear();
    mPath.push_back(src);
    mGrid.set(src.x(),src.y(),SimpleRouterGrid::nSeen);

    while( !endPath(mPath.back(),dst) )
    {
        //printf( "%d,%d %d,%d\n", mPath.back().x(), mPath.back().y(), dst.x(), dst.y() );
        if ( nextNode(dst,next) >= 0 )
        {
            mPath.push_back(next);
            mGrid.set(mPath.back().x(),mPath.back().y(),SimpleRouterGrid::nSeen);
        }
        else
        {
            mPath.clear();
            mPath.push_back(src);
        }
    }
}

int SimpleRouter::nextNode(QPoint dst, QPoint& next)
{
    /**
     * get the distance + manhattan length of all adjacent nodes and then return the one with the shortest distance.
     */
    int smallest = -1;
    QPoint temp;
    int result;

    for(int n=0; n < 8; n++)
    {
        result = -1;
        switch(n)
        {
            case 0:     result = CheckN(dst, temp);     break;
            case 1:     result = CheckE(dst, temp);     break;
            case 2:     result = CheckS(dst, temp);     break;
            case 3:     result = CheckW(dst, temp);     break;
            case 4:     result = CheckNE(dst, temp);    break;
            case 5:     result = CheckSE(dst, temp);    break;
            case 6:     result = CheckSW(dst, temp);    break;
            case 7:     result = CheckNW(dst, temp);    break;
        }
        if(result >= 0 && (smallest == -1 || result < smallest))
        {
            smallest = result;
            next = temp;
        }
    }
    return smallest;
}

int SimpleRouter::CheckN(QPoint& dst, QPoint &outNode)
{
    if ( mPath.back().y() > 0 )
    {
        if ( traversable(mPath.back().x(), mPath.back().y() - 1) )
        {
            outNode.setX( mPath.back().x() );
            outNode.setY( mPath.back().y() - 1 );
            return sDistance(outNode,dst);
        }
    }
    return -1;
}

int SimpleRouter::CheckE(QPoint& dst, QPoint &outNode)
{
    if ( mPath.back().x() < mGrid.width()-1 )
    {
        if ( traversable(mPath.back().x() + 1, mPath.back().y()) )
        {
            outNode.setX(mPath.back().x() + 1);
            outNode.setY(mPath.back().y());
            return sDistance(outNode,dst);
        }
    }
    return -1;
}

int SimpleRouter::CheckS(QPoint& dst, QPoint &outNode)
{
    if ( mPath.back().y() < mGrid.height()-1 )
    {
        if ( traversable(mPath.back().x(), mPath.back().y() + 1) )
        {
            outNode.setX( mPath.back().x() );
            outNode.setY( mPath.back().y() + 1 );
            return sDistance(outNode,dst);
        }
    }
    return -1;
}

int SimpleRouter::CheckW(QPoint& dst, QPoint &outNode)
{
    if(mPath.back().x() > 0)
    {
        if ( traversable(mPath.back().x() - 1, mPath.back().y()) )
        {
            outNode.setX(mPath.back().x() - 1);
            outNode.setY(mPath.back().y());
            return sDistance(outNode,dst);
        }
    }
    return -1;
}

int SimpleRouter::CheckNE(QPoint& dst, QPoint &outNode)
{
    if ( mPath.back().x() < mGrid.width()-1 && mPath.back().y() > 0 )
    {
        if ( traversable(mPath.back().x() + 1, mPath.back().y() - 1) )
        {
            outNode.setX( mPath.back().x() + 1 );
            outNode.setY( mPath.back().y() - 1 );
            return dDistance(outNode,dst);
        }
    }
    return -1;
}

int SimpleRouter::CheckSE(QPoint& dst, QPoint &outNode)
{
    if ( mPath.back().x() < mGrid.width()-1 && mPath.back().y() < mGrid.height()-1 )
    {
        if ( traversable(mPath.back().x() + 1, mPath.back().y() + 1) )
        {
            outNode.setX( mPath.back().x() + 1 );
            outNode.setY( mPath.back().y() + 1 );
            return dDistance(outNode,dst);
        }
    }
    return -1;
}

int SimpleRouter::CheckNW(QPoint& dst, QPoint &outNode)
{
    if ( mPath.back().x() > 0 && mPath.back().y() > 0)
    {
        if ( traversable(mPath.back().x() - 1, mPath.back().y() - 1) )
        {
            outNode.setX( mPath.back().x() - 1 );
            outNode.setY( mPath.back().y() - 1 );
            return dDistance(outNode,dst);
        }
    }
    return -1;
}

int SimpleRouter::CheckSW(QPoint& dst, QPoint &outNode)
{
    if ( mPath.back().x() > 0 && mPath.back().y() < mGrid.height()-1 )
    {
        if ( traversable(mPath.back().x() - 1, mPath.back().y() + 1) )
        {
            outNode.setX( mPath.back().x() - 1 );
            outNode.setY( mPath.back().y() + 1 );
            return dDistance(outNode,dst);
        }
    }
    return -1;
}

/**
  * @brief Run for a little bit.
  */
bool SimpleRouter::exec()
{
	bool rc=true;
    QEventLoop loop;
	emit status(currentStatus());
    loop.processEvents();
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


