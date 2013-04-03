/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#ifndef _CASTARMARKER_H_
#define _CASTARMARKER_H_

#include <QPoint>

#define EMPTY_X 0x7FFFFFFF
#define EMPTY_Y 0x7FFFFFFF

class CAStarMarker
{
    /// @brief A marker-node using the A* algorithm

	public:

        typedef enum
        {
            Barrier=0,
            Navigation
        } tKind;
        CAStarMarker();
        CAStarMarker(QPoint pt, tKind kind=Barrier );
        CAStarMarker(const CAStarMarker& other);
        ~CAStarMarker();

        CAStarMarker&           operator=(const CAStarMarker& other);
        bool                    operator==(const CAStarMarker& other) const;
        bool                    operator!=(const CAStarMarker& other) const;
        bool                    operator==(const QPoint& other) const;
        bool                    operator!=(const QPoint& other) const;

        int                     x()								{return mPos.x();}
        int                     y()								{return mPos.y();}
        void					setX(int x)                 	{mPos.setX(x);}
        void					setY(int y)         			{mPos.setY(y);}
        void					setPos(int x, int y)    		{mPos.setX(x),mPos.setY(y);}
        void					setPos(QPoint pos)				{mPos=pos;}
        QPoint					pos()							{return mPos;}

        void                    setKind(tKind k)                {mKind=k;}
        bool                    kind()                          {return mKind;}

    protected:

        QPoint					mPos;
        tKind                   mKind;


};


#endif // _CAStarMarker_H
