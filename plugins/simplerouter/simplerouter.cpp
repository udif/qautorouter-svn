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
QList<SimpleRouterNode>& SimpleRouter::path()
{
	QEventLoop loop;
	int loopcounter=0;
	int idx;
	SimpleRouterNode node(mEndPoint[0]->pos(), 0 /* mEndPoint[0]->layer()->index() */ ); /* FIXME */
	insort(mOpenList,node);
    while(!mOpenList.isEmpty() && mOpenList.at(0) != mEndPoint[1]->pos() )
	{
        node = mOpenList.takeFirst();
		if (++loopcounter >= 10)
		{
			loop.processEvents();
			loopcounter=0;
		}
        QList<SimpleRouterNode> children = neighbours(node);
		for(int n=0; n < children.count(); n++)
		{
            SimpleRouterNode child = children[n];
			// child node already in the open list?
			int oIdx = mOpenList.indexOf(child);
			if ( oIdx >=0 )
			{
				// the existing node is better?
                SimpleRouterNode other = mOpenList[oIdx];
				if ( other <= child )
					continue;
			}
			// child node already in the closed list?
			int cIdx = mClosedList.indexOf(child);
			if ( cIdx >= 0 )
			{
				// the existing node is better?
                SimpleRouterNode other = mClosedList[cIdx];
				if ( other <= child )
					continue;
			}
			// remove child from open and closed lists
			if ( oIdx >= 0 )
				mOpenList.takeAt(oIdx);
			if ( cIdx >= 0 )
				mClosedList.takeAt(cIdx);
			// add child to open list
			open(child);

		}
		close(node);
	}
    // FIXME FIXME was: follow parent nodes from goal back to start
	do
	{
        SimpleRouterNode other(node.parent());
		mPath.append(node);
		if ( ( idx = mClosedList.indexOf( other ) ) >= 0 )
			other = mClosedList.takeAt(idx);
		else
		if ( ( idx = mOpenList.indexOf( other ) ) >= 0 )
			other = mOpenList.takeAt(idx);
		else
			break;
		node = other;
	} while( node.parent() != NULL );
	return mPath;
}

/**
 * @brief Retrieve a list of neighbours of the node that do not collide with uncollidable objects.
 * @param node The nod ein question.
 * @return A list of the potential move directions.
 */
QList<SimpleRouterNode> SimpleRouter::neighbours(SimpleRouterNode node)
{
	QList<SimpleRouterNode> rc;
	for(int x=-1; x<=1; x++)
	{
		for(int y=-1; y<=1; y++)
		{
			SimpleRouterNode child(QPointF(node.pos().x()+x,node.pos().y()+y));
            child.setScore( cost( child ) );
            rc.append(child);
		}
	}
	return rc;
}

/**
 * @brief insort a node into a list in sorted by cost method.
 * @param list The list to which to insort.
 * @param node The insorted node.
 */
void SimpleRouter::insort(QList<SimpleRouterNode>& list, SimpleRouterNode& node)
{
	int idx = list.indexOf(node);
	if ( idx < 0 ) // insorted already?
	{
		for(int n=0; n < list.length(); n++)
		{
			SimpleRouterNode other = list[n];
			if ( node < other )
			{
				list.insert(n,node);
				return;
			}
		}
		list.append(node);
	}

}

/**
 * @brief Make a copy of the node into the open list
 * @param node The source node to copy from 
 */
void SimpleRouter::open(SimpleRouterNode& node)
{
	insort(mOpenList,node);
}

/**
 * @brief Make a copy of the node into the open list
 * @param node The source node to copy from 
 */
void SimpleRouter::close(SimpleRouterNode& node)
{
	insort(mClosedList,node);
}

/**
 * @brief Calculate the sum of the absolute values of x() and y(), traditionally known as the "Manhattan length"
 *        of the vector from the point A to point B.
 */
double SimpleRouter::manhattanLength(QPointF a, QPointF b)
{
	QPointF delta = (b - a);
	return delta.manhattanLength();
}

/** 
 * @brief Calculate the cost between two adjacent points.
 *        We will assign a cost of 10 to each horizontal or vertical square moved, and a cost of 14.14 for a diagonal move.
 *        We use these numbers because the actual distance to move diagonally is the square root of 2,
 *        or roughly 1.414 times the cost of moving horizontally or vertically.
 */
double SimpleRouter::adjacentCost(QPointF a, QPointF b)
{
	double diffX = fabs(a.x()-b.x());
	double diffY = fabs(a.y()-b.y());
	double rc = ( diffX && diffY ) ? 14.14 : 10.0;
	return rc;
}

/**
 * @brief Calculate the cost of this node
 * @param node
 * @param parent
 */
double SimpleRouter::cost(SimpleRouterNode node)
{
	double rc = g(node) + h(node);
	return rc;
}

/** 
 * @brief Calculate G, the movement cost to move from the starting point A
 *         to this cell of the grid, following the path generated to get there.
 */
double SimpleRouter::g(SimpleRouterNode node)
{
	double rc=0.0;
	while( node.parent() != NULL )
	{
		rc += adjacentCost( node.parent()->pos(), node.pos() );
		node = *node.parent();
	}
	return rc;
}

/**
 * @brief The estimated movement cost to move from that given square on the grid to the final destination
 */
double SimpleRouter::h(SimpleRouterNode node)
{
	double rc = manhattanLength( node.pos(), mEndPoint[1]->pos() ) * 10.0;
	return rc;
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


