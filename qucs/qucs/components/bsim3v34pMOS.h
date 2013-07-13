/*
 * bsim3v34pMOS.h - device definitions for bsim3v34pMOS module
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 */

#ifndef bsim3v34pMOS_H
#define bsim3v34pMOS_H

#include "component.h"

class bsim3v34pMOS : public Component
{
  public:
    bsim3v34pMOS();
    ~bsim3v34pMOS() { };
    Component* newOne();
    static Element* info(QString&, char* &, bool getNewOne=false);
    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget);    
  protected:
    void createSymbol();
};

#endif /* bsim3v34pMOS_H */
