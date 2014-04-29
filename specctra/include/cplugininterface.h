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
#ifndef INTERFACES_H
#define INTERFACES_H

#include <QtPlugin>

#define CPluginInterface_iid "com.pikeaero.QAutoRouter.Plugins.CPluginInterface"

class CPcb;
class CPluginInterface
{
    public:
		virtual ~CPluginInterface() {}

		typedef enum {
			RouterPlugin=0,
			PostRouterPlugin,
		} tPluginType;

		virtual tPluginType			type()=0;						/* is the a router or post-router */

		virtual QString				title() const = 0;				/* a brief name for the plugin */
		virtual QString				version() const = 0;			/* return a version number string */
		virtual QStringList			credits() const = 0;			/* name of author(s) + email */
		virtual QString				website() const = 0;			/* the author's website */
		virtual QString				description() const = 0;		/* a brief description of the plugin */
		virtual	QStringList			license() const = 0;			/* the text of the plugin license */

		virtual bool				start(CPcb* pcb)=0;				/** initialize, gets' called once prior to exec() being called */
		virtual void				stop()=0;						/** stop processing */
		virtual bool				exec()=0;						/** get's called repeatedly while exec() returns true, return false to stop */
		virtual QString				elapsed()=0;					/** elapsed time in seconds */
};

Q_DECLARE_INTERFACE(CPluginInterface, CPluginInterface_iid)

#endif  // INTERFACES_H

