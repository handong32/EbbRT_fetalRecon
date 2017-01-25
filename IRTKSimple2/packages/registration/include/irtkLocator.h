/*=========================================================================

  Library   : Image Registration Toolkit (IRTK)
  Module    : $Id: irtkLocator.h 2 2008-12-23 12:40:14Z dr $
  Copyright : Imperial College, Department of Computing
              Visual Information Processing (VIP), 2008 onwards
  Date      : $Date: 2008-12-23 12:40:14 +0000 (Tue, 23 Dec 2008) $
  Version   : $Revision: 2 $
  Changes   : $Author: dr $

=========================================================================*/

#ifdef HAS_VTK

#include <vtkPolyData.h>
#include <vtkCellLocator.h>
#include <vtkPointLocator.h>
#include "vtkKDTreePointLocator.h"
#include <vtkGenericCell.h>
#include <irtkImage.h>

#ifndef _IRTKLOCATOR_H

#define _IRTKLOCATOR_H

class irtkLocator : public irtkObject
{

protected:

  /// VTK cell locator
  vtkCellLocator *cell_locator;

  /// VTK point locator
  vtkPointLocator *point_locator;

  /// VTK KD-tree point locator
  vtkKDTreePointLocator *kd_locator;

  /// VTK Cell
  vtkGenericCell *cell;

  /// Cell id
  int cellId;

  /// Sub id
  int subId;

  /// Distance
  double dist2;

  /// Coordinates of closest point
  double closestPoint[3];

  /// Locator type
  int loc_type;

  /// Pointer to VTK dataset
  vtkPolyData *_dataset;

  /// Temp id
  int temp_id;

public:

  /// Default contructor
  irtkLocator(void);

  /// Set number of elements per bucket
  void SetElementsPerBucket(int);

  /// Set the locator type
  void SelectLocatorType(int type);

  int GetLocatorType();

  /// Set dataset
  void SetDataSet(vtkPolyData *);

  /// Find the closest point
  int FindClosestPoint(double *xyz);

  /// Return name of class
  const char *NameOfClass();
};

inline int irtkLocator::GetLocatorType()
{
  return loc_type;

}

#endif

#endif
