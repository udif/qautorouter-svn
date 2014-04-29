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
#include "qautorouter-common.h"

/**
  * @brief called exactly once to setup UI actions.
  */
void QAutoRouter::setupActions()
{
	ui->actionOpen->setIcon(QIcon(":/icons/fileopen.png"));
	ui->actionSave->setIcon(QIcon(":/icons/filesave.png"));
    ui->actionSave_As->setIcon(QIcon(":/icons/filesaveas.png"));
    ui->actionExport->setIcon(QIcon(":/icons/document-export.png"));
    ui->actionQuit->setIcon(QIcon(":/icons/exit.png"));
	ui->actionZoom_Fit->setIcon(QIcon(":/icons/viewmagfit.png"));
	ui->actionZoom_In->setIcon(QIcon(":/icons/viewmag+.png"));
	ui->actionZoom_Out->setIcon(QIcon(":/icons/viewmag-.png"));
	ui->actionStart->setIcon(QIcon(":/icons/player_play.png"));
	ui->actionStop->setIcon(QIcon(":/icons/player_stop.png"));
	ui->actionOptions->setIcon(QIcon(":/icons/configure.png"));
	ui->actionAbout->setIcon(QIcon(":/icons/qautorouter.png"));

	ui->actionQuit->setShortcut(QKeySequence(QKeySequence::Quit));
	ui->actionOpen->setShortcut(QKeySequence(QKeySequence::Open));
	ui->actionSave->setShortcut(QKeySequence(QKeySequence::Save));
	ui->actionZoom_In->setShortcut(QKeySequence(QKeySequence::ZoomIn));
	ui->actionZoom_Out->setShortcut(QKeySequence(QKeySequence::ZoomOut));
	ui->actionZoom_Fit->setShortcut(QKeySequence(Qt::Key_F3));
	ui->actionStart->setShortcut(QKeySequence(Qt::Key_F7));
	ui->actionStop->setShortcut(QKeySequence(Qt::Key_Escape));

	QObject::connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(open()));
	QObject::connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(save()));
    QObject::connect(ui->actionSave_As,SIGNAL(triggered()),this,SLOT(saveAs()));
    QObject::connect(ui->actionExport,SIGNAL(triggered()),this,SLOT(exportAs()));
    QObject::connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(close()));
	QObject::connect(ui->actionZoom_In,SIGNAL(triggered()),this,SLOT(zoomIn()));
	QObject::connect(ui->actionZoom_Out,SIGNAL(triggered()),this,SLOT(zoomOut()));
	QObject::connect(ui->actionZoom_Fit,SIGNAL(triggered()),this,SLOT(zoomFit()));
	QObject::connect(ui->actionStart,SIGNAL(triggered()),this,SLOT(start()));
	QObject::connect(ui->actionStop,SIGNAL(triggered()),this,SLOT(stop()));
	QObject::connect(ui->actionOptions,SIGNAL(triggered()),this,SLOT(editPreferences()));
	QObject::connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(about()));

	QToolBar* file = addToolBar(tr("File"));
	file->addAction(ui->actionOpen);
	file->addAction(ui->actionSave);
    file->addAction(ui->actionSave_As);
    file->addAction(ui->actionExport);
    file->addAction(ui->actionQuit);

	QToolBar* view = addToolBar(tr("View"));
	view->addAction(ui->actionZoom_In);
	view->addAction(ui->actionZoom_Out);
	view->addAction(ui->actionZoom_Fit);

	QToolBar* action = addToolBar(tr("Action"));
	action->addAction(ui->actionStart);
	action->addAction(ui->actionStop);

	QToolBar* settings = addToolBar(tr("Settings"));
	settings->addAction(ui->actionOptions);

	QToolBar* help = addToolBar(("Help"));
	help->addAction(ui->actionAbout);

	ui->actionStop->setEnabled(false);
}



