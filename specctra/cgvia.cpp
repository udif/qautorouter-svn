/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#include "cgvia.h"

#define inherited CGPadstack

CGVia::CGVia(CPcbNet* net)
: inherited(net,NULL,QString(),NULL)
{
    mSegmentType=CGSegment::Via;
}

CGVia::~CGVia()
{
}

void CGVia::route()
{
}
