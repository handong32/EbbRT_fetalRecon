/*=========================================================================

  Library   : Image Registration Toolkit (IRTK)
  Module    : $Id: irtkPoint4D.cc 2 2008-12-23 12:40:14Z dr $
  Copyright : Imperial College, Department of Computing
              Visual Information Processing (VIP), 2008 onwards
  Date      : $Date: 2008-12-23 12:40:14 +0000 (Tue, 23 Dec 2008) $
  Version   : $Revision: 2 $
  Changes   : $Author: dr $

=========================================================================*/

#include <irtkGeometry.h>

#include <irtkPoint4D.h>

ostream& operator<< (ostream& o, const irtkPoint4D &p)
{
  return o << p._x <<  " " << p._y << " " << p._z<<p._t;
}

istream& operator>> (istream& i, irtkPoint4D &p)
{
  char c;

  c = i.peek();
  while ((c == ',') || (c == ' ') || (c == '\t') || (c == '\n')) {
    c = i.get();
    if (!i.eof()) {
      c = i.peek();
    } else {
      break;
    }
  }
  return i >> p._x >> p._y >> p._z >> p._t;
}

