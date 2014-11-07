/***************************************************************************
                               component.h
                              -------------
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

#ifndef COMPONENT_H
#define COMPONENT_H

#include <Q3PtrList>
#include <QPen>
#include <QPoint>
#include <QWidget>

#include "element.h"

class Schematic;
class ViewPainter;
class QString;


class Component : public Element {
public:
  Component();
  virtual ~Component() {};

  virtual Component* newOne();
  virtual void recreate(Schematic*) {};
  QString getNetlist();
  QString get_VHDL_Code(int);
  QString get_Verilog_Code(int);
  void    paint(ViewPainter*);
  void    paintScheme(Schematic*);
  void    print(ViewPainter*, float);
  void    setCenter(int, int, bool relative=false);
  void    getCenter(int&, int&);
  int     textSize(int&, int&);
  void    Bounding(int&, int&, int&, int&);
  void    entireBounds(int&, int&, int&, int&, float);
  bool    getSelected(int, int);
  int     getTextSelected(int, int, float);
  void    rotate();
  void    mirrorX();  // mirror about X axis
  void    mirrorY();  // mirror about Y axis
  QString save();
  bool    load(const QString&);

  // to hold track of the component appearance for saving and copying
  /**
   * @brief mirroredX tells if the Component it mirrored on the X axis or not
   */
  bool mirroredX;

  /**
   * @brief rotated is the rotation angle divided by 90 degrees.
   *
   * \todo clarify direction of rotation and initial position
   */
  int  rotated;

  virtual QString getSubcircuitFile() { return ""; }

  /**
   * @brief setSchematic sets the pointer to the Schematic associated with the component.
   * @param p
   */
  virtual void setSchematic (Schematic* p) { containingSchematic = p; }

  QList<Line *>     Lines;
  QList<struct Arc *>      Arcs;
  QList<Area *>     Rects;
  QList<Area *>     Ellips;
  QList<Port *>     Ports;
  QList<Text *>     Texts;

  /**
   * @brief Props represents the properties of a Schematic.
   *
   * \todo Clarify: which properties can these be?
   * \bug Q3PtrList is deprecated
   */
  Q3PtrList<Property> Props;

  // TODO use an enumeration
  #define COMP_IS_OPEN    0
  #define COMP_IS_ACTIVE  1
  #define COMP_IS_SHORTEN 2
  int  isActive; // should it be used in simulation or not ?
  int  tx, ty;   // upper left corner of text (position)
  bool showName;
  QString  Model, Name;
  QString  Description;

protected:
  virtual QString netlist();
  virtual QString vhdlCode(int);
  virtual QString verilogCode(int);

  /**
   * @brief analyseLine
   * @return
   *
   * \todo Typo: analyze...
   */
  int  analyseLine(const QString&, int);
  bool getIntegers(const QString&, int *i1=0, int *i2=0, int *i3=0,
                   int *i4=0, int *i5=0, int *i6=0);
  bool getPen(const QString&, QPen&, int);
  bool getBrush(const QString&, QBrush&, int);

  void copyComponent(Component*);
  Property * getProperty(const QString&);
  Schematic* containingSchematic;
};

/**
 * @brief The MultiViewComponent class
 *
 * \todo Clarify: what does this class mean?
 */
class MultiViewComponent : public Component {
public:
  MultiViewComponent() {};
  virtual ~MultiViewComponent() {};

  void recreate(Schematic*);

protected:
  virtual void createSymbol() {};
};


class GateComponent : public MultiViewComponent {
public:
  GateComponent();
  QString netlist();
  QString vhdlCode(int);
  QString verilogCode(int);

protected:
  void createSymbol();
};

// prototype of independent function
Component* getComponentFromName(QString& Line, Schematic* p=NULL);

#endif
