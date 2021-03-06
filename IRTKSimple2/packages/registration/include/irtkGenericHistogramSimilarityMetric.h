/*=========================================================================

  Library   : Image Registration Toolkit (IRTK)
  Module    : $Id: irtkGenericHistogramSimilarityMetric.h 660 2012-08-20 17:22:48Z dr $
  Copyright : Imperial College, Department of Computing
              Visual Information Processing (VIP), 2008 onwards
  Date      : $Date: 2012-08-20 18:22:48 +0100 (Mon, 20 Aug 2012) $
  Version   : $Revision: 660 $
  Changes   : $Author: dr $

=========================================================================*/

#ifndef _IRTKGENERICHISTOGRAMSIMILARITYMETRIC_H

#define _IRTKGENERICHISTOGRAMSIMILARITYMETRIC_H

#include <irtkRegistration.h>

/**
 * Generic class for histogram-based voxel similarity measures.
 *
 * This class implements various voxel similarity measures, including
 * sums-of-squared differences, cross-correlation, correlation ratio, mutual
 * information and normalised mutual information.
 *
 */

class irtkGenericHistogramSimilarityMetric : public irtkHistogramSimilarityMetric
{

  /// Which similarity measure are we using
  irtkSimilarityMeasure _SimilarityMeasure;

public:

  /// Constructor
  irtkGenericHistogramSimilarityMetric(irtkSimilarityMeasure = MI, int = 64, int = 64);

  /// Resets the metric.
  virtual void Reset();

  /** Resets the metric.
      \param metric To metric to reset with. */
  virtual void ResetAndCopy(irtkSimilarityMetric *metric);

  /** Puts the min for the metric.
      \param targetMin The target min.
      \param sourceMin The source min. */
  virtual void PutMin(double targetMin, double sourceMin);

  /** Gets the min for the metric.
      \param targetMin The target min.
      \param sourceMin The source min. */
  virtual void GetMin(double *targetMin, double *sourceMin) const;

  /** Puts the max for the metric.
      \param targetMax The target max.
      \param sourceMax The source max. */
  virtual void PutMax(double targetMax, double sourceMax);

  /** Gets the max for the metric.
      \param targetMax The target max.
      \param sourceMax The source max. */
  virtual void GetMax(double *targetMax, double *sourceMax) const;

  /** Adds to a bin for a particular time.
      \param targetBin Index to target bin.
      \param sourceBin Index to source bin */
  virtual void Add(int targetBin, int sourceBin);

  /** Deletes from a bin for a particular time.
      \param targetBin Index to target bin.
      \param sourceBin Index to source bin */
  virtual void Delete(int targetBin, int sourceBin);

  /// Returns number of bins in histogram
  virtual int GetNumberOfBinsX() const;

  /// Returns number of bins in histogram
  virtual int GetNumberOfBinsY() const;

  /// Returns number of samples in histogram
  virtual int NumberOfSamples() const;

  /** Sets the similarity measure.
      \param measure The similarity measure. */
  virtual void SetMeasure(irtkSimilarityMeasure measure);

  /** Gets the similarity measure. */
  virtual irtkSimilarityMeasure GetMeasure() const;

  /// Evaluate similarity measure
  virtual double Evaluate();

};

inline irtkGenericHistogramSimilarityMetric::irtkGenericHistogramSimilarityMetric(irtkSimilarityMeasure SimilarityMeasure, int target_nbins, int source_nbins) : irtkHistogramSimilarityMetric(target_nbins, source_nbins)
{
  _SimilarityMeasure = SimilarityMeasure;
}

inline void irtkGenericHistogramSimilarityMetric::Reset()
{
  this->_histogram->Reset();
}

inline void irtkGenericHistogramSimilarityMetric::ResetAndCopy(irtkSimilarityMetric* metric)
{
	irtkGenericHistogramSimilarityMetric *m = dynamic_cast<irtkGenericHistogramSimilarityMetric *>(metric);

  if (m == NULL) {
    cerr << "irtkGenericHistogramSimilarityMetric::Reset: Dynamic cast failed" << endl;
    exit(1);
  }

  this->_histogram->Reset(*(m->_histogram));
}

inline void irtkGenericHistogramSimilarityMetric::PutMin(double targetMin, double sourceMin)
{
  this->_histogram->PutMin(targetMin, sourceMin);
}

inline void irtkGenericHistogramSimilarityMetric::GetMin(double *targetMin, double *sourceMin) const
{
  this->_histogram->GetMin(targetMin, sourceMin);
}

inline void irtkGenericHistogramSimilarityMetric::PutMax(double targetMax, double sourceMax)
{
  this->_histogram->PutMax(targetMax, sourceMax);
}

inline void irtkGenericHistogramSimilarityMetric::GetMax(double *targetMax, double *sourceMax) const
{
  this->_histogram->GetMax(targetMax, sourceMax);
}

inline void irtkGenericHistogramSimilarityMetric::SetMeasure(irtkSimilarityMeasure measure)
{
  _SimilarityMeasure = measure;
}

inline irtkSimilarityMeasure irtkGenericHistogramSimilarityMetric::GetMeasure() const
{
  return _SimilarityMeasure;
}

inline int irtkGenericHistogramSimilarityMetric::GetNumberOfBinsX() const
{
  return this->_histogram->NumberOfBinsX();
}

inline int irtkGenericHistogramSimilarityMetric::GetNumberOfBinsY() const
{
  return this->_histogram->NumberOfBinsY();
}

inline int irtkGenericHistogramSimilarityMetric::NumberOfSamples() const
{
  return this->_histogram->NumberOfSamples();
}

inline void irtkGenericHistogramSimilarityMetric::Add(int i, int j)
{
  this->_histogram->Add(i, j);
}

inline void irtkGenericHistogramSimilarityMetric::Delete(int i, int j)
{
  this->_histogram->Delete(i, j);
}

inline double irtkGenericHistogramSimilarityMetric::Evaluate()
{
  // Evaluate similarity from histogram
  switch (_SimilarityMeasure) {
  case K:
    return +this->_histogram->Kappa();
    break;
  case LC:
    return +this->_histogram->LabelConsistency();
    break;
  case JE:
    return -this->_histogram->JointEntropy();
    break;
  case CC:
    return +this->_histogram->CrossCorrelation();
    break;
  case MI:
    return +this->_histogram->MutualInformation();
    break;
  case NMI:
    return +this->_histogram->NormalizedMutualInformation();
    break;
  case SSD:
    return -this->_histogram->SumsOfSquaredDifferences() /
           (double)this->_histogram->NumberOfSamples();
    break;
  case CR_XY:
    return +this->_histogram->CorrelationRatioXY();
    break;
  case CR_YX:
    return +this->_histogram->CorrelationRatioYX();
    break;
  default:
    return 0;
    break;
  }
}
#endif
