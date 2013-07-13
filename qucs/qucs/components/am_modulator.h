/***************************************************************************
                               am_modulator.h
                              ----------------
    begin                : Sat Feb 25 2006
    copyright            : (C) 2006 by Michael Margraf
    email                : michael.margraf@alumni.tu-berlin.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef AM_MODULATOR_H
#define AM_MODULATOR_H

#include "component.h"


class AM_Modulator : public Component  {
public:
  AM_Modulator();
 ~AM_Modulator();
  Component* newOne();
  static Element* info(QString&, char* &, bool getNewOne=false);
  QRectF boundingRect() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget);
  
};

#endif
