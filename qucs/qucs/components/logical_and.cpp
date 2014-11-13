/***************************************************************************
                               logical_and.cpp
                              -----------------
    begin                : Sun Sep 25 2005
    copyright            : (C) 2005 by Michael Margraf
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

#include "logical_and.h"
#include "node.h"

Logical_AND::Logical_AND()
{
  Description = QObject::tr("logical AND");
  Model = "AND";

  createSymbol();
  tx = x1+4;
  ty = y2+4;
}

Logical_AND::~Logical_AND()
{
}

Component* Logical_AND::newOne()
{
  Logical_AND* p = new Logical_AND();
  p->Props.getFirst()->Value = Props.getFirst()->Value;
  p->Props.getLast()->Value = Props.getLast()->Value;
  p->recreate(0);
  return p;
}

Element* Logical_AND::info(QString& Name, char* &BitmapFile, bool getNewOne)
{
  Name = QObject::tr("n-port AND");
  BitmapFile = (char *) "and";

  if(getNewOne)  return new Logical_AND();
  return 0;
}

QString
Logical_AND::convertToMarcoNetlist(){

    QString result = QString("AND(");
    QListIterator<Port*> portIterator(this->Ports);

    // there is only one output port and it is the first port
    Port* currentPort = portIterator.next();
    currentPort->Connection->Name = this->Name + "_out0";
    result += currentPort->Connection->Name;

    result +=" :: "; // no selection list

    // the rest are input ports
    int currentIndex = this->Ports.count() -2;
    // -1 for fencepost error,
    // -1 because output is already accounted for

    QString inputVariablesList = QString();
    while(portIterator.hasNext()){

        // intermediate comma, if needed
        if(!inputVariablesList.isEmpty()){
            inputVariablesList += ", ";
        }

        // name the ports
        currentPort = portIterator.next();
        currentPort->Connection->Name =
                this->Name + "_in" + QString::number(currentIndex);

        // and add them to the variables
        inputVariablesList += currentPort->Connection->Name;
        currentIndex--;
    }
    result += inputVariablesList + ")";
    return result;
}
