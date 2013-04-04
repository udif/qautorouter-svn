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

#include "castarnode.h"

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
	return "1.0";
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
	netStack().clear();
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

/**
  * @brief select a net
  */
void SimpleRouter::selectNet(CPcbNet *net, bool selected)
{
	net->setSelected(selected);
	net->update();
	pcb()->yield();				/* give up some CPU to the main app */
}

/**
  * @brief Select nets for routing and push onto a stack.
  */
void SimpleRouter::select()
{
	netStack().clear();
	if ( pcb() != NULL && pcb()->network() != NULL )
	{
		for(int n=0; running() && n < pcb()->network()->nets(); n++)
		{
			CPcbNet* net = pcb()->network()->net(n);
			if ( !net->routed() )
			{
				netStack().push(net);
				setState(Routing);
			}
		}
	}
	if (netStack().isEmpty())
		stop();
}

/// Translate from a grid point to a grid point suitable for A* search.
/// Each A* grid point represents a rectangle of size gridRez.
QPointF SimpleRouter::scenePt(QPoint gridPt, double gridRez)
{
	QPointF rc( ((double)gridPt.x()*gridRez), ((double)gridPt.y()*gridRez) );
	return rc;
}

/// Translate from a sceen point to a grid point suitable for A* search.
/// Each A* grid point represents a rectangle of size gridRez.
QPoint SimpleRouter::gridPt(QPointF scenePt, double gridRez)
{
	QPoint rc( (scenePt.x()/gridRez), (scenePt.y()/gridRez) );
	return rc;
}

/// Generate the keepout list in A* grid coordinates
QList<CAStarMarker>& SimpleRouter::keepOutList(double gridRez)
{
	mKeepOutList.clear();
	// genrate the board outline in A* grid coorinates
	QList<QPointF> polyBounds = pcb()->structure()->boundary()->path()->polygon();
	for(int n=0; n < polyBounds.count(); n++)
	{
		mKeepOutList.append( gridPt(polyBounds[n],gridRez) );
	}
	// FIXME -- generate for the other stuff...
	return mKeepOutList;
}

/// draw a single rat line
void SimpleRouter::drawRatLine(CGSegment* seg1, CGSegment* seg2)
{
	QPainterPath painterPath;
	painterPath.moveTo( seg1->origin() );
	painterPath.lineTo( seg2->origin() );
	CSpecctraObject::globalScene()->addPath(painterPath);
}

/// route a path from A* nodes
void SimpleRouter::route( QList<CAStarNode>& path, CGSegment* seg1, CGSegment* seg2, double gridRez )
{
	// FIXME - make a CGWire follow the A* nodes...
	// FIXME - for now just paint a line...
	QPainterPath painterPath;
	for(int n=0; n < path.count(); n++)
	{
		CAStarNode node = path[n];
		QPointF pt = scenePt( node.pos(), gridRez );
		printf( "node[%d,%d]\n",node.pos().x(),node.pos().y());
		if ( n==0 )
			painterPath.moveTo( pt );
		else
			painterPath.lineTo( pt );
	}
	CSpecctraObject::globalScene()->addPath(painterPath);
}

/// route some nets...
void SimpleRouter::route()
{
	while( netStack().count() )
	{
		CPcbNet* net = netStack().pop();
		QList<CGPadstack*>& padstacks =	net->padstacksRef();
		//selectNet(net,true);
		for( int n=0; running() && n < padstacks.count()-1; n++)
		{
			CGPadstack* padstack1 = padstacks[n];
			CGPadstack* padstack2 = padstacks[n+1];
			double gridRez = net->width();
			CAStar astar( keepOutList(gridRez), gridPt(padstack1->origin(),gridRez), gridPt(padstack2->origin(),gridRez) ); // ?origin
			QList<CAStarNode> path = astar.path();
			//drawRatLine(padstack1,padstack2);
			route(path,padstack1,padstack2,gridRez);
			emit status(currentStatus());
		}
		selectNet(net,false);
	}
	setState(Idle);
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
			select();
			if ( running() )
				setState(Routing);
			break;
		case Routing:
			route();
			if ( running() )
				setState(Selecting);
			break;
	}
	return rc;
}

Q_EXPORT_PLUGIN2(simplerouter, SimpleRouter);

