/***************************************************************************
                          subcircuit.cpp  -  description
                             -------------------
    begin                : Sat Aug 23 2003
    copyright            : (C) 2003 by Michael Margraf
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

#include "subcircuit.h"
#include "qucs.h"

#include <qdir.h>
#include <qfileinfo.h>

extern QDir QucsWorkDir;


Subcircuit::Subcircuit()
{
  Description = QObject::tr("subcircuit");

  Ports.append(new Port(0,  0));  // dummy port because of being device

  Model = "Sub";
  Name  = "SUB";

  Props.append(new Property("File", "", true,
		QObject::tr("name of qucs schematic file")));

//  makeSymbol(No);
}

Subcircuit::~Subcircuit()
{
}

Component* Subcircuit::newOne()
{
  Subcircuit *p = new Subcircuit();
  p->Props.getFirst()->Value = Props.getFirst()->Value;
  p->remakeSymbol(Ports.count());
  return p;
}

/*Component* Subcircuit::info(QString& Name, char* &BitmapFile, bool getNewOne)
{
  Name = QObject::tr("Subcircuit");
  BitmapFile = "";  // has no bitmap

  if(getNewOne)  return new Subcircuit(Props.getLast()->Value.toInt());
  return 0;
}*/

// Makes the schematic symbol subcircuit with the correct number
// of ports.
void Subcircuit::recreate()
{
  int No;
  QFileInfo Info(Props.getFirst()->Value);
  if(Info.isRelative())
    No = QucsApp::testFile(QucsWorkDir.filePath(Props.getFirst()->Value));
  else  No = QucsApp::testFile(Props.getFirst()->Value);
  if(No < 0) No = 0;

  remakeSymbol(No);
}

void Subcircuit::remakeSymbol(int No)
{
  Lines.clear();
  Texts.clear();
  Ports.clear();

  int h = 30*((No-1)/2) + 15;
  Lines.append(new Line(-15, -h, 15, -h,QPen(QPen::darkBlue,2)));
  Lines.append(new Line( 15, -h, 15,  h,QPen(QPen::darkBlue,2)));
  Lines.append(new Line(-15,  h, 15,  h,QPen(QPen::darkBlue,2)));
  Lines.append(new Line(-15, -h,-15,  h,QPen(QPen::darkBlue,2)));
  Texts.append(new Text( -7,  0,"sub"));

  int i=0, y = 15-h;
  while(i<No) {
    i++;
    Lines.append(new Line(-30,  y,-15,  y,QPen(QPen::darkBlue,2)));
    Ports.append(new Port(-30,  y));
    Texts.append(new Text(-25,y-3,QString::number(i)));

    if(i == No) break;
    i++;
    Lines.append(new Line( 15,  y, 30,  y,QPen(QPen::darkBlue,2)));
    Ports.append(new Port( 30,  y));
    Texts.append(new Text( 20,y-3,QString::number(i)));
    y += 60;
  }

  x1 = -30; y1 = -h-2;
  x2 =  30; y2 =  h+2;

  tx = x1+4;
  ty = y2+4;

  bool mmir = mirroredX;
  int  rrot = rotated;
  if(mmir)  mirrorX();   // mirror
  for(int z=0; z<rrot; z++)  rotate(); // rotate


  rotated = rrot;   // restore properties (were changed by rotate/mirror)
  mirroredX = mmir;
}
