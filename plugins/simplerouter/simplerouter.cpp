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

#include "castarnode.h"

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
	netStack().clear();
	mPcb = pcb;
	setState(Idle);
	mStartTime = QDateTime::currentDateTime();
	mGridRez=0;
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


/// spy on what A* is doing for debugging, open nodes
void SimpleRouter::slotOpen(QPoint pt)
{
	QPoint gridTopLeft( pt.x()-(1), pt.y()-(1) );
	QPoint gridBottomRight( pt.x()+(1), pt.y()+(1) );
	QPointF sceneTopLeft = scenePt( gridTopLeft );
	QPointF sceneBottomRight = scenePt( gridBottomRight );
	QRectF sceneRect( sceneTopLeft, sceneBottomRight );
	CSpecctraObject::globalScene()->addEllipse(sceneRect,QPen(Qt::green));
}

/// spy on what A* is doing for debugging, closed nodes
void SimpleRouter::slotClose(QPoint pt)
{
	QPoint gridTopLeft( pt.x()-(1), pt.y()-(1) );
	QPoint gridBottomRight( pt.x()+(1), pt.y()+(1) );
	QPointF sceneTopLeft = scenePt( gridTopLeft );
	QPointF sceneBottomRight = scenePt( gridBottomRight );
	QRectF sceneRect( sceneTopLeft, sceneBottomRight );
	CSpecctraObject::globalScene()->addEllipse(sceneRect,QPen(Qt::red));
}

/// Translate from a grid point to a grid point suitable for A* search.
/// Each A* grid point represents a rectangle of size mGridRez.
QPointF SimpleRouter::scenePt(QPoint gridPt)
{
	QPointF rc( ((double)gridPt.x()*mGridRez), ((double)gridPt.y()*mGridRez) );
	return rc;
}

/// Translate from a sceen point to a grid point suitable for A* search.
/// Each A* grid point represents a rectangle of size mGridRez.
QPoint SimpleRouter::gridPt(QPointF scenePt)
{
	QPoint rc( (scenePt.x()/mGridRez), (scenePt.y()/mGridRez) );
	return rc;
}

/// Plot a point on the grid
void SimpleRouter::gridPlotPt(QList<CAStarMarker>& grid, QPoint gridPt)
{
	grid.append(gridPt);
}

/// Use Bresenham's line algorithm to plot a line on the grid between two points
void SimpleRouter::gridPlotLine(QList<CAStarMarker>& grid, QPoint gridPt1,QPoint gridPt2)
{
	double x1 = gridPt1.x();
	double y1 = gridPt1.y();
	double x2 = gridPt2.x();
	double y2 = gridPt2.y();
	bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if(steep)
	{
		qSwap(x1, y1);
		qSwap(x2, y2);
	}
	if(x1 > x2)
	{
		qSwap(x1, x2);
		qSwap(y1, y2);
	}
	double dx = x2 - x1;
	double dy = fabs(y2 - y1);
	double error = dx / 2.0f;
	double ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;
	int maxX = (int)x2;
	for(int x=(int)x1; x<maxX; x++)
	{
		if(steep)
			gridPlotPt(grid,QPoint(y,x));
		else
			gridPlotPt(grid,QPoint(x,y));
		if( (error -= dy) < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}

/// Generate the keepout list in A* grid coordinates, excluding the wire being routed.
/// @param exclude1 One end point of the wire being routed.
/// @param exclude2 One end point of the wire being routed.
/// @param mGridRez The current grid rezolution.
/// @return a reference to a marker array in A* grid coordinates.
QList<CAStarMarker>& SimpleRouter::keepOutList(CGSegment* exclude1, CGSegment* exclude2)
{
	mKeepOutList.clear();
	// genrate the board outline in A* grid coorinates
	QList<QPointF> polyBounds = pcb()->structure()->boundary()->path()->polygon();
	for(int n=0; n < polyBounds.count()-1; n++)
	{
		// render a grid-coordinate poly-line for each sceen-coordinate polyline.
		QPoint pt1 = gridPt(polyBounds[n]);
		QPoint pt2 = gridPt(polyBounds[n+1]);
		gridPlotLine(mKeepOutList,pt1,pt2);
	}
#if 0
	// FIXME - have each CSpecctraObject to maintain it's own keep-out shape (or, let's more correctly call it it's "copper shape"
	// FIXME - such that only things that are copper produce keep-outs (we are getting hung up here on silk screen shapes and all that crap)
	// FIXME - in this way we don't have to repeatedly figure that out at this stage and we can simply
	// FIXME - call on the root CSpecctraObject to prodddduce a keep-out mask for each layer.
	// FIXME - Will need a mechanism for "un-masking" the source and destinations such that A* can penetrate
	// FIXME the target footprint to get to the center point of it.

	// FIXME - Provide a means of obtaining a complete pad-list as shapes.
	// FIXME - provide a means of obtaining a complete copper shape list per layer.(pads + zones + routed wires)
	// FIXME - To simplify the implementation, can we query layers? Find the copper layers, and then query the shapes on those layers?


	// generate keep-outs for the other shapes (for initial testing/experimentation only)...
	if ( pcb() != NULL && pcb()->placement() != NULL )
	{
		for(int nPlacement=0; nPlacement < pcb()->placement()->places();nPlacement++)
		{
			CPcbPlace* place = pcb()->placement()->place(nPlacement);
			if ( !place->contains(exclude1) && !place->contains(exclude2) )
			{
				QPainterPath shape = place->shape();
				QPolygonF polygon = shape.toFillPolygon();
				for(int n=0;n<polygon.size()-1;n++)
				{
					// render a grid-coordinate poly-line for each sceen-coordinate polyline.
					QPoint pt1 = gridPt(polygon[n]);
					QPoint pt2 = gridPt(polygon[n+1]);
					gridPlotLine(mKeepOutList,pt1,pt2);
				}
			}
		}
	}
#endif
	return mKeepOutList;
}

/// draw a single rat line
void SimpleRouter::drawRatLine(CGSegment* seg1, CGSegment* seg2)
{
	QPainterPath painterPath;
	painterPath.moveTo( seg1->pos() );
	painterPath.lineTo( seg2->pos() );
	CSpecctraObject::globalScene()->addPath(painterPath);
}

/// route a path from A* nodes
void SimpleRouter::route( QList<CAStarNode>& path, CGSegment* seg1, CGSegment* seg2)
{
	// FIXME - make a CGWire follow the A* nodes...
	// FIXME - for now just paint a line...
	QPainterPath painterPath;
	for(int n=0; n < path.count(); n++)
	{
		CAStarNode node = path[n];
		QPointF pt = scenePt( node.pos());
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
	if( netStack().count() )
	{
		CPcbNet* net = netStack().pop();
		QList<CGPadstack*>& padstacks =	net->padstacksRef();
		//selectNet(net,true);

		// FIXME - Some kind of orientation problem with the padstacks, not getting the translated shape coordinates?
		// FIXME - Or is it an error translating between A* coordinates and scene coordinates?

		for( int n=0; running() && n < padstacks.count()-1; n++)
		{
			CGPadstack* padstack1 = padstacks[n];
			CGPadstack* padstack2 = padstacks[n+1];
			//mGridRez = net->width()/4;  // A* resolution maybe should be saller than the trace width, probably / 4 ?
			mGridRez = net->width();  // The resolution to use for the A* search.
			CAStar astar( keepOutList(padstack1,padstack2),
						  gridPt(padstack1->place()->centre()),
						  gridPt(padstack2->place()->centre()) );
			QObject::connect(&astar,SIGNAL(signalOpen(QPoint)),this,SLOT(slotOpen(QPoint)));
			QObject::connect(&astar,SIGNAL(signalClose(QPoint)),this,SLOT(slotClose(QPoint)));
			QList<CAStarNode> path = astar.path();
			//drawRatLine(padstack1,padstack2);
			route(path,padstack1,padstack2);
			emit status(currentStatus());
		}
		selectNet(net,false);
	}
	else
	{
		setState(Idle);
	}
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
			//if ( running() )
			//	setState(Selecting);
			break;
	}
	return rc;
}

Q_EXPORT_PLUGIN2(simplerouter, SimpleRouter);

