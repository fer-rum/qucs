/***************************************************************************
                         ipulse.h  -  description
                             -------------------
    begin                : Sat Sep 18 2004
    copyright            : (C) 2004 by Michael Margraf
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

#ifndef IPULSE_H
#define IPULSE_H

#include "component.h"


class iPulse : public Component  {
public:
  iPulse();
  ~iPulse();
  Component* newOne();
  static Element* info(QString&, char* &, bool getNewOne=false);
  QRectF boundingRect() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget);  
};

#endif
