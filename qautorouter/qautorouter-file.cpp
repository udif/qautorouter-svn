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

QString gedaHeader()
{
    QString rc = "# Generated by qAutoRouter export.\n\n";
    return rc;
}

QString gedaFooter()
{
    QString rc;
    rc = " \n\
    Symbol[' ' 1800] \n\
    ( \n\
    ) \n\
    Symbol['!' 1200] \n\
    ( \n\
        SymbolLine[0 4500 0 5000 800] \n\
        SymbolLine[0 1000 0 3500 800] \n\
    ) \n\
    Symbol['\"' 1200] \n\
    ( \n\
        SymbolLine[0 1000 0 2000 800] \n\
        SymbolLine[1000 1000 1000 2000 800] \n\
    ) \n\
    Symbol['#' 1200] \n\
    ( \n\
        SymbolLine[0 3500 2000 3500 800] \n\
        SymbolLine[0 2500 2000 2500 800] \n\
        SymbolLine[1500 2000 1500 4000 800] \n\
        SymbolLine[500 2000 500 4000 800] \n\
    ) \n\
    Symbol['$' 1200] \n\
    ( \n\
        SymbolLine[1500 1500 2000 2000 800] \n\
        SymbolLine[500 1500 1500 1500 800] \n\
        SymbolLine[0 2000 500 1500 800] \n\
        SymbolLine[0 2000 0 2500 800] \n\
        SymbolLine[0 2500 500 3000 800] \n\
        SymbolLine[500 3000 1500 3000 800] \n\
        SymbolLine[1500 3000 2000 3500 800] \n\
        SymbolLine[2000 3500 2000 4000 800] \n\
        SymbolLine[1500 4500 2000 4000 800] \n\
        SymbolLine[500 4500 1500 4500 800] \n\
        SymbolLine[0 4000 500 4500 800] \n\
        SymbolLine[1000 1000 1000 5000 800] \n\
    ) \n\
    Symbol['%' 1200] \n\
    ( \n\
        SymbolLine[0 1500 0 2000 800] \n\
        SymbolLine[0 1500 500 1000 800] \n\
        SymbolLine[500 1000 1000 1000 800] \n\
        SymbolLine[1000 1000 1500 1500 800] \n\
        SymbolLine[1500 1500 1500 2000 800] \n\
        SymbolLine[1000 2500 1500 2000 800] \n\
        SymbolLine[500 2500 1000 2500 800] \n\
        SymbolLine[0 2000 500 2500 800] \n\
        SymbolLine[0 5000 4000 1000 800] \n\
        SymbolLine[3500 5000 4000 4500 800] \n\
        SymbolLine[4000 4000 4000 4500 800] \n\
        SymbolLine[3500 3500 4000 4000 800] \n\
        SymbolLine[3000 3500 3500 3500 800] \n\
        SymbolLine[2500 4000 3000 3500 800] \n\
        SymbolLine[2500 4000 2500 4500 800] \n\
        SymbolLine[2500 4500 3000 5000 800] \n\
        SymbolLine[3000 5000 3500 5000 800] \n\
    ) \n\
    Symbol['&' 1200] \n\
    ( \n\
        SymbolLine[0 4500 500 5000 800] \n\
        SymbolLine[0 1500 0 2500 800] \n\
        SymbolLine[0 1500 500 1000 800] \n\
        SymbolLine[0 3500 1500 2000 800] \n\
        SymbolLine[500 5000 1000 5000 800] \n\
        SymbolLine[1000 5000 2000 4000 800] \n\
        SymbolLine[0 2500 2500 5000 800] \n\
        SymbolLine[500 1000 1000 1000 800] \n\
        SymbolLine[1000 1000 1500 1500 800] \n\
        SymbolLine[1500 1500 1500 2000 800] \n\
        SymbolLine[0 3500 0 4500 800] \n\
    ) \n\
    Symbol['\'' 1200] \n\
    ( \n\
        SymbolLine[0 2000 1000 1000 800] \n\
    ) \n\
    Symbol['(' 1200] \n\
    ( \n\
        SymbolLine[0 4500 500 5000 800] \n\
        SymbolLine[0 1500 500 1000 800] \n\
        SymbolLine[0 1500 0 4500 800] \n\
    ) \n\
    Symbol[')' 1200] \n\
    ( \n\
        SymbolLine[0 1000 500 1500 800] \n\
        SymbolLine[500 1500 500 4500 800] \n\
        SymbolLine[0 5000 500 4500 800] \n\
    ) \n\
    Symbol['*' 1200] \n\
    ( \n\
        SymbolLine[0 2000 2000 4000 800] \n\
        SymbolLine[0 4000 2000 2000 800] \n\
        SymbolLine[0 3000 2000 3000 800] \n\
        SymbolLine[1000 2000 1000 4000 800] \n\
    ) \n\
    Symbol['+' 1200] \n\
    ( \n\
        SymbolLine[0 3000 2000 3000 800] \n\
        SymbolLine[1000 2000 1000 4000 800] \n\
    ) \n\
    Symbol[',' 1200] \n\
    ( \n\
        SymbolLine[0 6000 1000 5000 800] \n\
    ) \n\
    Symbol['-' 1200] \n\
    ( \n\
        SymbolLine[0 3000 2000 3000 800] \n\
    ) \n\
    Symbol['.' 1200] \n\
    ( \n\
        SymbolLine[0 5000 500 5000 800] \n\
    ) \n\
    Symbol['/' 1200] \n\
    ( \n\
        SymbolLine[0 4500 3000 1500 800] \n\
    ) \n\
    Symbol['0' 1200] \n\
    ( \n\
        SymbolLine[0 4500 500 5000 800] \n\
        SymbolLine[0 1500 0 4500 800] \n\
        SymbolLine[0 1500 500 1000 800] \n\
        SymbolLine[500 1000 1500 1000 800] \n\
        SymbolLine[1500 1000 2000 1500 800] \n\
        SymbolLine[2000 1500 2000 4500 800] \n\
        SymbolLine[1500 5000 2000 4500 800] \n\
        SymbolLine[500 5000 1500 5000 800] \n\
        SymbolLine[0 4000 2000 2000 800] \n\
    ) \n\
    Symbol['1' 1200] \n\
    ( \n\
        SymbolLine[500 5000 1500 5000 800] \n\
        SymbolLine[1000 1000 1000 5000 800] \n\
        SymbolLine[0 2000 1000 1000 800] \n\
    ) \n\
    Symbol['2' 1200] \n\
    ( \n\
        SymbolLine[0 1500 500 1000 800] \n\
        SymbolLine[500 1000 2000 1000 800] \n\
        SymbolLine[2000 1000 2500 1500 800] \n\
        SymbolLine[2500 1500 2500 2500 800] \n\
        SymbolLine[0 5000 2500 2500 800] \n\
        SymbolLine[0 5000 2500 5000 800] \n\
    ) \n\
    Symbol['3' 1200] \n\
    ( \n\
        SymbolLine[0 1500 500 1000 800] \n\
        SymbolLine[500 1000 1500 1000 800] \n\
        SymbolLine[1500 1000 2000 1500 800] \n\
        SymbolLine[2000 1500 2000 4500 800] \n\
        SymbolLine[1500 5000 2000 4500 800] \n\
        SymbolLine[500 5000 1500 5000 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
        SymbolLine[500 3000 2000 3000 800] \n\
    ) \n\
    Symbol['4' 1200] \n\
    ( \n\
        SymbolLine[0 3000 2000 1000 800] \n\
        SymbolLine[0 3000 2500 3000 800] \n\
        SymbolLine[2000 1000 2000 5000 800] \n\
    ) \n\
    Symbol['5' 1200] \n\
    ( \n\
        SymbolLine[0 1000 2000 1000 800] \n\
        SymbolLine[0 1000 0 3000 800] \n\
        SymbolLine[0 3000 500 2500 800] \n\
        SymbolLine[500 2500 1500 2500 800] \n\
        SymbolLine[1500 2500 2000 3000 800] \n\
        SymbolLine[2000 3000 2000 4500 800] \n\
        SymbolLine[1500 5000 2000 4500 800] \n\
        SymbolLine[500 5000 1500 5000 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
    ) \n\
    Symbol['6' 1200] \n\
    ( \n\
        SymbolLine[1500 1000 2000 1500 800] \n\
        SymbolLine[500 1000 1500 1000 800] \n\
        SymbolLine[0 1500 500 1000 800] \n\
        SymbolLine[0 1500 0 4500 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
        SymbolLine[1500 3000 2000 3500 800] \n\
        SymbolLine[0 3000 1500 3000 800] \n\
        SymbolLine[500 5000 1500 5000 800] \n\
        SymbolLine[1500 5000 2000 4500 800] \n\
        SymbolLine[2000 3500 2000 4500 800] \n\
    ) \n\
    Symbol['7' 1200] \n\
    ( \n\
        SymbolLine[0 5000 2500 2500 800] \n\
        SymbolLine[2500 1000 2500 2500 800] \n\
        SymbolLine[0 1000 2500 1000 800] \n\
    ) \n\
    Symbol['8' 1200] \n\
    ( \n\
        SymbolLine[0 4500 500 5000 800] \n\
        SymbolLine[0 3500 0 4500 800] \n\
        SymbolLine[0 3500 500 3000 800] \n\
        SymbolLine[500 3000 1500 3000 800] \n\
        SymbolLine[1500 3000 2000 3500 800] \n\
        SymbolLine[2000 3500 2000 4500 800] \n\
        SymbolLine[1500 5000 2000 4500 800] \n\
        SymbolLine[500 5000 1500 5000 800] \n\
        SymbolLine[0 2500 500 3000 800] \n\
        SymbolLine[0 1500 0 2500 800] \n\
        SymbolLine[0 1500 500 1000 800] \n\
        SymbolLine[500 1000 1500 1000 800] \n\
        SymbolLine[1500 1000 2000 1500 800] \n\
        SymbolLine[2000 1500 2000 2500 800] \n\
        SymbolLine[1500 3000 2000 2500 800] \n\
    ) \n\
    Symbol['9' 1200] \n\
    ( \n\
        SymbolLine[0 5000 2000 3000 800] \n\
        SymbolLine[2000 1500 2000 3000 800] \n\
        SymbolLine[1500 1000 2000 1500 800] \n\
        SymbolLine[500 1000 1500 1000 800] \n\
        SymbolLine[0 1500 500 1000 800] \n\
        SymbolLine[0 1500 0 2500 800] \n\
        SymbolLine[0 2500 500 3000 800] \n\
        SymbolLine[500 3000 2000 3000 800] \n\
    ) \n\
    Symbol[':' 1200] \n\
    ( \n\
        SymbolLine[0 2500 500 2500 800] \n\
        SymbolLine[0 3500 500 3500 800] \n\
    ) \n\
    Symbol[';' 1200] \n\
    ( \n\
        SymbolLine[0 5000 1000 4000 800] \n\
        SymbolLine[1000 2500 1000 3000 800] \n\
    ) \n\
    Symbol['<' 1200] \n\
    ( \n\
        SymbolLine[0 3000 1000 2000 800] \n\
        SymbolLine[0 3000 1000 4000 800] \n\
    ) \n\
    Symbol['=' 1200] \n\
    ( \n\
        SymbolLine[0 2500 2000 2500 800] \n\
        SymbolLine[0 3500 2000 3500 800] \n\
    ) \n\
    Symbol['>' 1200] \n\
    ( \n\
        SymbolLine[0 2000 1000 3000 800] \n\
        SymbolLine[0 4000 1000 3000 800] \n\
    ) \n\
    Symbol['?' 1200] \n\
    ( \n\
        SymbolLine[1000 3000 1000 3500 800] \n\
        SymbolLine[1000 4500 1000 5000 800] \n\
        SymbolLine[0 1500 0 2000 800] \n\
        SymbolLine[0 1500 500 1000 800] \n\
        SymbolLine[500 1000 1500 1000 800] \n\
        SymbolLine[1500 1000 2000 1500 800] \n\
        SymbolLine[2000 1500 2000 2000 800] \n\
        SymbolLine[1000 3000 2000 2000 800] \n\
    ) \n\
    Symbol['@' 1200] \n\
    ( \n\
        SymbolLine[0 1000 0 4000 800] \n\
        SymbolLine[0 4000 1000 5000 800] \n\
        SymbolLine[1000 5000 4000 5000 800] \n\
        SymbolLine[5000 3500 5000 1000 800] \n\
        SymbolLine[5000 1000 4000 0 800] \n\
        SymbolLine[4000 0 1000 0 800] \n\
        SymbolLine[1000 0 0 1000 800] \n\
        SymbolLine[1500 2000 1500 3000 800] \n\
        SymbolLine[1500 3000 2000 3500 800] \n\
        SymbolLine[2000 3500 3000 3500 800] \n\
        SymbolLine[3000 3500 3500 3000 800] \n\
        SymbolLine[3500 3000 4000 3500 800] \n\
        SymbolLine[3500 3000 3500 1500 800] \n\
        SymbolLine[3500 2000 3000 1500 800] \n\
        SymbolLine[2000 1500 3000 1500 800] \n\
        SymbolLine[2000 1500 1500 2000 800] \n\
        SymbolLine[4000 3500 5000 3500 800] \n\
    ) \n\
    Symbol['A' 1200] \n\
    ( \n\
        SymbolLine[0 1500 0 5000 800] \n\
        SymbolLine[0 1500 500 1000 800] \n\
        SymbolLine[500 1000 2000 1000 800] \n\
        SymbolLine[2000 1000 2500 1500 800] \n\
        SymbolLine[2500 1500 2500 5000 800] \n\
        SymbolLine[0 3000 2500 3000 800] \n\
    ) \n\
    Symbol['B' 1200] \n\
    ( \n\
        SymbolLine[0 5000 2000 5000 800] \n\
        SymbolLine[2000 5000 2500 4500 800] \n\
        SymbolLine[2500 3500 2500 4500 800] \n\
        SymbolLine[2000 3000 2500 3500 800] \n\
        SymbolLine[500 3000 2000 3000 800] \n\
        SymbolLine[500 1000 500 5000 800] \n\
        SymbolLine[0 1000 2000 1000 800] \n\
        SymbolLine[2000 1000 2500 1500 800] \n\
        SymbolLine[2500 1500 2500 2500 800] \n\
        SymbolLine[2000 3000 2500 2500 800] \n\
    ) \n\
    Symbol['C' 1200] \n\
    ( \n\
        SymbolLine[500 5000 2000 5000 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
        SymbolLine[0 1500 0 4500 800] \n\
        SymbolLine[0 1500 500 1000 800] \n\
        SymbolLine[500 1000 2000 1000 800] \n\
    ) \n\
    Symbol['D' 1200] \n\
    ( \n\
        SymbolLine[500 1000 500 5000 800] \n\
        SymbolLine[2000 1000 2500 1500 800] \n\
        SymbolLine[2500 1500 2500 4500 800] \n\
        SymbolLine[2000 5000 2500 4500 800] \n\
        SymbolLine[0 5000 2000 5000 800] \n\
        SymbolLine[0 1000 2000 1000 800] \n\
    ) \n\
    Symbol['E' 1200] \n\
    ( \n\
        SymbolLine[0 3000 1500 3000 800] \n\
        SymbolLine[0 5000 2000 5000 800] \n\
        SymbolLine[0 1000 0 5000 800] \n\
        SymbolLine[0 1000 2000 1000 800] \n\
    ) \n\
    Symbol['F' 1200] \n\
    ( \n\
        SymbolLine[0 1000 0 5000 800] \n\
        SymbolLine[0 1000 2000 1000 800] \n\
        SymbolLine[0 3000 1500 3000 800] \n\
    ) \n\
    Symbol['G' 1200] \n\
    ( \n\
        SymbolLine[2000 1000 2500 1500 800] \n\
        SymbolLine[500 1000 2000 1000 800] \n\
        SymbolLine[0 1500 500 1000 800] \n\
        SymbolLine[0 1500 0 4500 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
        SymbolLine[500 5000 2000 5000 800] \n\
        SymbolLine[2000 5000 2500 4500 800] \n\
        SymbolLine[2500 3500 2500 4500 800] \n\
        SymbolLine[2000 3000 2500 3500 800] \n\
        SymbolLine[1000 3000 2000 3000 800] \n\
    ) \n\
    Symbol['H' 1200] \n\
    ( \n\
        SymbolLine[0 1000 0 5000 800] \n\
        SymbolLine[2500 1000 2500 5000 800] \n\
        SymbolLine[0 3000 2500 3000 800] \n\
    ) \n\
    Symbol['I' 1200] \n\
    ( \n\
        SymbolLine[0 1000 1000 1000 800] \n\
        SymbolLine[500 1000 500 5000 800] \n\
        SymbolLine[0 5000 1000 5000 800] \n\
    ) \n\
    Symbol['J' 1200] \n\
    ( \n\
        SymbolLine[0 1000 1500 1000 800] \n\
        SymbolLine[1500 1000 1500 4500 800] \n\
        SymbolLine[1000 5000 1500 4500 800] \n\
        SymbolLine[500 5000 1000 5000 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
    ) \n\
    Symbol['K' 1200] \n\
    ( \n\
        SymbolLine[0 1000 0 5000 800] \n\
        SymbolLine[0 3000 2000 1000 800] \n\
        SymbolLine[0 3000 2000 5000 800] \n\
    ) \n\
    Symbol['L' 1200] \n\
    ( \n\
        SymbolLine[0 1000 0 5000 800] \n\
        SymbolLine[0 5000 2000 5000 800] \n\
    ) \n\
    Symbol['M' 1200] \n\
    ( \n\
        SymbolLine[0 1000 0 5000 800] \n\
        SymbolLine[0 1000 1500 2500 800] \n\
        SymbolLine[1500 2500 3000 1000 800] \n\
        SymbolLine[3000 1000 3000 5000 800] \n\
    ) \n\
    Symbol['N' 1200] \n\
    ( \n\
        SymbolLine[0 1000 0 5000 800] \n\
        SymbolLine[0 1000 0 1500 800] \n\
        SymbolLine[0 1500 2500 4000 800] \n\
        SymbolLine[2500 1000 2500 5000 800] \n\
    ) \n\
    Symbol['O' 1200] \n\
    ( \n\
        SymbolLine[0 1500 0 4500 800] \n\
        SymbolLine[0 1500 500 1000 800] \n\
        SymbolLine[500 1000 1500 1000 800] \n\
        SymbolLine[1500 1000 2000 1500 800] \n\
        SymbolLine[2000 1500 2000 4500 800] \n\
        SymbolLine[1500 5000 2000 4500 800] \n\
        SymbolLine[500 5000 1500 5000 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
    ) \n\
    Symbol['P' 1200] \n\
    ( \n\
        SymbolLine[500 1000 500 5000 800] \n\
        SymbolLine[0 1000 2000 1000 800] \n\
        SymbolLine[2000 1000 2500 1500 800] \n\
        SymbolLine[2500 1500 2500 2500 800] \n\
        SymbolLine[2000 3000 2500 2500 800] \n\
        SymbolLine[500 3000 2000 3000 800] \n\
    ) \n\
    Symbol['Q' 1200] \n\
    ( \n\
        SymbolLine[0 1500 0 4500 800] \n\
        SymbolLine[0 1500 500 1000 800] \n\
        SymbolLine[500 1000 1500 1000 800] \n\
        SymbolLine[1500 1000 2000 1500 800] \n\
        SymbolLine[2000 1500 2000 4500 800] \n\
        SymbolLine[1500 5000 2000 4500 800] \n\
        SymbolLine[500 5000 1500 5000 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
        SymbolLine[1000 4000 2000 5000 800] \n\
    ) \n\
    Symbol['R' 1200] \n\
    ( \n\
        SymbolLine[0 1000 2000 1000 800] \n\
        SymbolLine[2000 1000 2500 1500 800] \n\
        SymbolLine[2500 1500 2500 2500 800] \n\
        SymbolLine[2000 3000 2500 2500 800] \n\
        SymbolLine[500 3000 2000 3000 800] \n\
        SymbolLine[500 1000 500 5000 800] \n\
        SymbolLine[500 3000 2500 5000 800] \n\
    ) \n\
    Symbol['S' 1200] \n\
    ( \n\
        SymbolLine[2000 1000 2500 1500 800] \n\
        SymbolLine[500 1000 2000 1000 800] \n\
        SymbolLine[0 1500 500 1000 800] \n\
        SymbolLine[0 1500 0 2500 800] \n\
        SymbolLine[0 2500 500 3000 800] \n\
        SymbolLine[500 3000 2000 3000 800] \n\
        SymbolLine[2000 3000 2500 3500 800] \n\
        SymbolLine[2500 3500 2500 4500 800] \n\
        SymbolLine[2000 5000 2500 4500 800] \n\
        SymbolLine[500 5000 2000 5000 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
    ) \n\
    Symbol['T' 1200] \n\
    ( \n\
        SymbolLine[0 1000 2000 1000 800] \n\
        SymbolLine[1000 1000 1000 5000 800] \n\
    ) \n\
    Symbol['U' 1200] \n\
    ( \n\
        SymbolLine[0 1000 0 4500 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
        SymbolLine[500 5000 1500 5000 800] \n\
        SymbolLine[1500 5000 2000 4500 800] \n\
        SymbolLine[2000 1000 2000 4500 800] \n\
    ) \n\
    Symbol['V' 1200] \n\
    ( \n\
        SymbolLine[0 1000 0 4000 800] \n\
        SymbolLine[0 4000 1000 5000 800] \n\
        SymbolLine[1000 5000 2000 4000 800] \n\
        SymbolLine[2000 1000 2000 4000 800] \n\
    ) \n\
    Symbol['W' 1200] \n\
    ( \n\
        SymbolLine[0 1000 0 5000 800] \n\
        SymbolLine[0 5000 1500 3500 800] \n\
        SymbolLine[1500 3500 3000 5000 800] \n\
        SymbolLine[3000 1000 3000 5000 800] \n\
    ) \n\
    Symbol['X' 1200] \n\
    ( \n\
        SymbolLine[0 1000 0 1500 800] \n\
        SymbolLine[0 1500 2500 4000 800] \n\
        SymbolLine[2500 4000 2500 5000 800] \n\
        SymbolLine[0 4000 0 5000 800] \n\
        SymbolLine[0 4000 2500 1500 800] \n\
        SymbolLine[2500 1000 2500 1500 800] \n\
    ) \n\
    Symbol['Y' 1200] \n\
    ( \n\
        SymbolLine[0 1000 0 1500 800] \n\
        SymbolLine[0 1500 1000 2500 800] \n\
        SymbolLine[1000 2500 2000 1500 800] \n\
        SymbolLine[2000 1000 2000 1500 800] \n\
        SymbolLine[1000 2500 1000 5000 800] \n\
    ) \n\
    Symbol['Z' 1200] \n\
    ( \n\
        SymbolLine[0 1000 2500 1000 800] \n\
        SymbolLine[2500 1000 2500 1500 800] \n\
        SymbolLine[0 4000 2500 1500 800] \n\
        SymbolLine[0 4000 0 5000 800] \n\
        SymbolLine[0 5000 2500 5000 800] \n\
    ) \n\
    Symbol['[' 1200] \n\
    ( \n\
        SymbolLine[0 1000 500 1000 800] \n\
        SymbolLine[0 1000 0 5000 800] \n\
        SymbolLine[0 5000 500 5000 800] \n\
    ) \n\
    Symbol['\' 1200] \n\
    ( \n\
        SymbolLine[0 1500 3000 4500 800] \n\
    ) \n\
    Symbol[']' 1200] \n\
    ( \n\
        SymbolLine[0 1000 500 1000 800] \n\
        SymbolLine[500 1000 500 5000 800] \n\
        SymbolLine[0 5000 500 5000 800] \n\
    ) \n\
    Symbol['^' 1200] \n\
    ( \n\
        SymbolLine[0 1500 500 1000 800] \n\
        SymbolLine[500 1000 1000 1500 800] \n\
    ) \n\
    Symbol['_' 1200] \n\
    ( \n\
        SymbolLine[0 5000 2000 5000 800] \n\
    ) \n\
    Symbol['a' 1200] \n\
    ( \n\
        SymbolLine[1500 3000 2000 3500 800] \n\
        SymbolLine[500 3000 1500 3000 800] \n\
        SymbolLine[0 3500 500 3000 800] \n\
        SymbolLine[0 3500 0 4500 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
        SymbolLine[2000 3000 2000 4500 800] \n\
        SymbolLine[2000 4500 2500 5000 800] \n\
        SymbolLine[500 5000 1500 5000 800] \n\
        SymbolLine[1500 5000 2000 4500 800] \n\
    ) \n\
    Symbol['b' 1200] \n\
    ( \n\
        SymbolLine[0 1000 0 5000 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
        SymbolLine[500 5000 1500 5000 800] \n\
        SymbolLine[1500 5000 2000 4500 800] \n\
        SymbolLine[2000 3500 2000 4500 800] \n\
        SymbolLine[1500 3000 2000 3500 800] \n\
        SymbolLine[500 3000 1500 3000 800] \n\
        SymbolLine[0 3500 500 3000 800] \n\
    ) \n\
    Symbol['c' 1200] \n\
    ( \n\
        SymbolLine[500 3000 2000 3000 800] \n\
        SymbolLine[0 3500 500 3000 800] \n\
        SymbolLine[0 3500 0 4500 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
        SymbolLine[500 5000 2000 5000 800] \n\
    ) \n\
    Symbol['d' 1200] \n\
    ( \n\
        SymbolLine[2000 1000 2000 5000 800] \n\
        SymbolLine[1500 5000 2000 4500 800] \n\
        SymbolLine[500 5000 1500 5000 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
        SymbolLine[0 3500 0 4500 800] \n\
        SymbolLine[0 3500 500 3000 800] \n\
        SymbolLine[500 3000 1500 3000 800] \n\
        SymbolLine[1500 3000 2000 3500 800] \n\
    ) \n\
    Symbol['e' 1200] \n\
    ( \n\
        SymbolLine[500 5000 2000 5000 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
        SymbolLine[0 3500 0 4500 800] \n\
        SymbolLine[0 3500 500 3000 800] \n\
        SymbolLine[500 3000 1500 3000 800] \n\
        SymbolLine[1500 3000 2000 3500 800] \n\
        SymbolLine[0 4000 2000 4000 800] \n\
        SymbolLine[2000 4000 2000 3500 800] \n\
    ) \n\
    Symbol['f' 1000] \n\
    ( \n\
        SymbolLine[500 1500 500 5000 800] \n\
        SymbolLine[500 1500 1000 1000 800] \n\
        SymbolLine[1000 1000 1500 1000 800] \n\
        SymbolLine[0 3000 1000 3000 800] \n\
    ) \n\
    Symbol['g' 1200] \n\
    ( \n\
        SymbolLine[1500 3000 2000 3500 800] \n\
        SymbolLine[500 3000 1500 3000 800] \n\
        SymbolLine[0 3500 500 3000 800] \n\
        SymbolLine[0 3500 0 4500 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
        SymbolLine[500 5000 1500 5000 800] \n\
        SymbolLine[1500 5000 2000 4500 800] \n\
        SymbolLine[0 6000 500 6500 800] \n\
        SymbolLine[500 6500 1500 6500 800] \n\
        SymbolLine[1500 6500 2000 6000 800] \n\
        SymbolLine[2000 3000 2000 6000 800] \n\
    ) \n\
    Symbol['h' 1200] \n\
    ( \n\
        SymbolLine[0 1000 0 5000 800] \n\
        SymbolLine[0 3500 500 3000 800] \n\
        SymbolLine[500 3000 1500 3000 800] \n\
        SymbolLine[1500 3000 2000 3500 800] \n\
        SymbolLine[2000 3500 2000 5000 800] \n\
    ) \n\
    Symbol['i' 1000] \n\
    ( \n\
        SymbolLine[0 2000 0 2500 800] \n\
        SymbolLine[0 3500 0 5000 800] \n\
    ) \n\
    Symbol['j' 1000] \n\
    ( \n\
        SymbolLine[500 2000 500 2500 800] \n\
        SymbolLine[500 3500 500 6000 800] \n\
        SymbolLine[0 6500 500 6000 800] \n\
    ) \n\
    Symbol['k' 1200] \n\
    ( \n\
        SymbolLine[0 1000 0 5000 800] \n\
        SymbolLine[0 3500 1500 5000 800] \n\
        SymbolLine[0 3500 1000 2500 800] \n\
    ) \n\
    Symbol['l' 1000] \n\
    ( \n\
        SymbolLine[0 1000 0 4500 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
    ) \n\
    Symbol['m' 1200] \n\
    ( \n\
        SymbolLine[500 3500 500 5000 800] \n\
        SymbolLine[500 3500 1000 3000 800] \n\
        SymbolLine[1000 3000 1500 3000 800] \n\
        SymbolLine[1500 3000 2000 3500 800] \n\
        SymbolLine[2000 3500 2000 5000 800] \n\
        SymbolLine[2000 3500 2500 3000 800] \n\
        SymbolLine[2500 3000 3000 3000 800] \n\
        SymbolLine[3000 3000 3500 3500 800] \n\
        SymbolLine[3500 3500 3500 5000 800] \n\
        SymbolLine[0 3000 500 3500 800] \n\
    ) \n\
    Symbol['n' 1200] \n\
    ( \n\
        SymbolLine[500 3500 500 5000 800] \n\
        SymbolLine[500 3500 1000 3000 800] \n\
        SymbolLine[1000 3000 1500 3000 800] \n\
        SymbolLine[1500 3000 2000 3500 800] \n\
        SymbolLine[2000 3500 2000 5000 800] \n\
        SymbolLine[0 3000 500 3500 800] \n\
    ) \n\
    Symbol['o' 1200] \n\
    ( \n\
        SymbolLine[0 3500 0 4500 800] \n\
        SymbolLine[0 3500 500 3000 800] \n\
        SymbolLine[500 3000 1500 3000 800] \n\
        SymbolLine[1500 3000 2000 3500 800] \n\
        SymbolLine[2000 3500 2000 4500 800] \n\
        SymbolLine[1500 5000 2000 4500 800] \n\
        SymbolLine[500 5000 1500 5000 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
    ) \n\
    Symbol['p' 1200] \n\
    ( \n\
        SymbolLine[500 3500 500 6500 800] \n\
        SymbolLine[0 3000 500 3500 800] \n\
        SymbolLine[500 3500 1000 3000 800] \n\
        SymbolLine[1000 3000 2000 3000 800] \n\
        SymbolLine[2000 3000 2500 3500 800] \n\
        SymbolLine[2500 3500 2500 4500 800] \n\
        SymbolLine[2000 5000 2500 4500 800] \n\
        SymbolLine[1000 5000 2000 5000 800] \n\
        SymbolLine[500 4500 1000 5000 800] \n\
    ) \n\
    Symbol['q' 1200] \n\
    ( \n\
        SymbolLine[2000 3500 2000 6500 800] \n\
        SymbolLine[1500 3000 2000 3500 800] \n\
        SymbolLine[500 3000 1500 3000 800] \n\
        SymbolLine[0 3500 500 3000 800] \n\
        SymbolLine[0 3500 0 4500 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
        SymbolLine[500 5000 1500 5000 800] \n\
        SymbolLine[1500 5000 2000 4500 800] \n\
    ) \n\
    Symbol['r' 1200] \n\
    ( \n\
        SymbolLine[500 3500 500 5000 800] \n\
        SymbolLine[500 3500 1000 3000 800] \n\
        SymbolLine[1000 3000 2000 3000 800] \n\
        SymbolLine[0 3000 500 3500 800] \n\
    ) \n\
    Symbol['s' 1200] \n\
    ( \n\
        SymbolLine[500 5000 2000 5000 800] \n\
        SymbolLine[2000 5000 2500 4500 800] \n\
        SymbolLine[2000 4000 2500 4500 800] \n\
        SymbolLine[500 4000 2000 4000 800] \n\
        SymbolLine[0 3500 500 4000 800] \n\
        SymbolLine[0 3500 500 3000 800] \n\
        SymbolLine[500 3000 2000 3000 800] \n\
        SymbolLine[2000 3000 2500 3500 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
    ) \n\
    Symbol['t' 1000] \n\
    ( \n\
        SymbolLine[500 1000 500 4500 800] \n\
        SymbolLine[500 4500 1000 5000 800] \n\
        SymbolLine[0 2500 1000 2500 800] \n\
    ) \n\
    Symbol['u' 1200] \n\
    ( \n\
        SymbolLine[0 3000 0 4500 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
        SymbolLine[500 5000 1500 5000 800] \n\
        SymbolLine[1500 5000 2000 4500 800] \n\
        SymbolLine[2000 3000 2000 4500 800] \n\
    ) \n\
    Symbol['v' 1200] \n\
    ( \n\
        SymbolLine[0 3000 0 4000 800] \n\
        SymbolLine[0 4000 1000 5000 800] \n\
        SymbolLine[1000 5000 2000 4000 800] \n\
        SymbolLine[2000 3000 2000 4000 800] \n\
    ) \n\
    Symbol['w' 1200] \n\
    ( \n\
        SymbolLine[0 3000 0 4500 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
        SymbolLine[500 5000 1000 5000 800] \n\
        SymbolLine[1000 5000 1500 4500 800] \n\
        SymbolLine[1500 3000 1500 4500 800] \n\
        SymbolLine[1500 4500 2000 5000 800] \n\
        SymbolLine[2000 5000 2500 5000 800] \n\
        SymbolLine[2500 5000 3000 4500 800] \n\
        SymbolLine[3000 3000 3000 4500 800] \n\
    ) \n\
    Symbol['x' 1200] \n\
    ( \n\
        SymbolLine[0 3000 2000 5000 800] \n\
        SymbolLine[0 5000 2000 3000 800] \n\
    ) \n\
    Symbol['y' 1200] \n\
    ( \n\
        SymbolLine[0 3000 0 4500 800] \n\
        SymbolLine[0 4500 500 5000 800] \n\
        SymbolLine[2000 3000 2000 6000 800] \n\
        SymbolLine[1500 6500 2000 6000 800] \n\
        SymbolLine[500 6500 1500 6500 800] \n\
        SymbolLine[0 6000 500 6500 800] \n\
        SymbolLine[500 5000 1500 5000 800] \n\
        SymbolLine[1500 5000 2000 4500 800] \n\
    ) \n\
    Symbol['z' 1200] \n\
    ( \n\
        SymbolLine[0 3000 2000 3000 800] \n\
        SymbolLine[0 5000 2000 3000 800] \n\
        SymbolLine[0 5000 2000 5000 800] \n\
    ) \n\
    Symbol['{' 1200] \n\
    ( \n\
        SymbolLine[500 1500 1000 1000 800] \n\
        SymbolLine[500 1500 500 2500 800] \n\
        SymbolLine[0 3000 500 2500 800] \n\
        SymbolLine[0 3000 500 3500 800] \n\
        SymbolLine[500 3500 500 4500 800] \n\
        SymbolLine[500 4500 1000 5000 800] \n\
    ) \n\
    Symbol['|' 1200] \n\
    ( \n\
        SymbolLine[0 1000 0 5000 800] \n\
    ) \n\
    Symbol['}' 1200] \n\
    ( \n\
        SymbolLine[0 1000 500 1500 800] \n\
        SymbolLine[500 1500 500 2500 800] \n\
        SymbolLine[500 2500 1000 3000 800] \n\
        SymbolLine[500 3500 1000 3000 800] \n\
        SymbolLine[500 3500 500 4500 800] \n\
        SymbolLine[0 5000 500 4500 800] \n\
    ) \n\
    Symbol['~' 1200] \n\
    ( \n\
        SymbolLine[0 3500 500 3000 800] \n\
        SymbolLine[500 3000 1000 3000 800] \n\
        SymbolLine[1000 3000 1500 3500 800] \n\
        SymbolLine[1500 3500 2000 3500 800] \n\
        SymbolLine[2000 3500 2500 3000 800] \n\
    ) \n\n";
    return rc;
}

/**
  * @brief load a file by filename
  */
bool QAutoRouter::load(QFile& file)
{
	bool rc=false;
	stop();
	if ( file.open(QIODevice::ReadOnly))
	{
		QTextStream in(&file);
		clear();
		CSpecctraReader reader(in,this);
		mRoot = reader.root();
		if ( root() != NULL )
		{
			root()->dump(); /** DEBUG */
			if ( root()->objectClass() == "pcb" )
			{
				QFileInfo fi(file.fileName());
				setWindowTitle(fi.fileName());
				QObject::connect(pcb(),SIGNAL(status(QString)),this,SLOT(status(QString)));
				readSettings();
				populateLayersForm();
				populateNetsForm();
				populateNetClassesForm();
				zoomFit();
				rc=true;
			}
			else
			{
				emit fault(tr("root class 'pcb'' expected."));
				clear();
				rc=false;
			}
		}
		else
		{
			emit fault(tr("load problem."));
		}
		file.close();
	}
	return rc;
}

bool QAutoRouter::save()
{
	return saveAs();
}

bool QAutoRouter::saveAs()
{
    QString filename = mFileName;
    filename.replace(".dsn",".ses");
    if (pcb()!=NULL)
    {
        QFileDialog dialog(this,tr("Save As"),QDir::currentPath(),tr("Specctra Session (*.ses)"));
        dialog.selectFile(filename);
        if ( dialog.exec() && dialog.selectedFiles().count())
        {
            QFile file(dialog.selectedFiles().at(0));
            if ( file.exists() )
            {
                if ( QMessageBox::warning ( NULL, filename+tr(" exists."), filename+tr(" exists. Overwrite it?"), QMessageBox::Ok, QMessageBox::Cancel ) != QMessageBox::Ok )
                {
                    return false;
                }
            }
            if ( file.open(QIODevice::ReadWrite|QIODevice::Truncate))
            {
                file.write(pcb()->toText(0).toLocal8Bit());
                file.close();
                return true;
            }
            else
            {
                emit fault(tr("error saving '")+mFileName+"'");
                return false;
            }
        }
    }
    return true;
}

bool QAutoRouter::exportAs()
{
    QString filename = mFileName;
    filename.replace(".dsn",".pcb");
    if (pcb()!=NULL)
    {
        QFileDialog dialog(this,tr("Export"),QDir::currentPath(),tr("gEDA (*.pcb)"));
        dialog.selectFile(filename);
        if ( dialog.exec() && dialog.selectedFiles().count())
        {
            QFile file(dialog.selectedFiles().at(0));
            if ( file.exists() )
            {
                if ( QMessageBox::warning ( NULL, filename+tr(" exists."), filename+tr(" exists. Overwrite it?"), QMessageBox::Ok, QMessageBox::Cancel ) != QMessageBox::Ok )
                {
                    return false;
                }
            }
            if ( file.open(QIODevice::ReadWrite|QIODevice::Truncate))
            {
                file.write(gedaHeader().toLocal8Bit());
                file.write(pcb()->toGeda(0).toLocal8Bit());
                file.write(gedaFooter().toLocal8Bit());
                file.close();
                return true;
            }
            else
            {
                emit fault(tr("error exporting '")+mFileName+"'");
                return false;
            }
        }
    }
    return true;
}

/**
  * @brief open a file by dialog
  */
void QAutoRouter::open()
{
	if ( maybeSave() )
	{
		QFileDialog dialog(this,tr("Open"),QDir::currentPath(),tr("Specctra Files (*.dsn)"));
		if (dialog.exec())
		{
			mFileName = dialog.selectedFiles().at(0);
			QFile file(mFileName);
			if ( !load(file) )
			{
				emit fault(tr("load file failed."));
			}
		}
	}
}

/**
  * @brief prior to discarding current work, call this...
  */
bool QAutoRouter::maybeSave()
{
	if (CGPadstack::padstacks().count())
	{
		QMessageBox::StandardButton ret;
		ret = QMessageBox::warning(this, tr("QAutoRouter"),tr("The document has been modified.\nDo you want to save your changes?"),QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		if (ret == QMessageBox::Save)
			return save();
		else if (ret == QMessageBox::Cancel)
			return false;
	}
	return true;
}


