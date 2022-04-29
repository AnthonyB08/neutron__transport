//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "Kernel.h"

/**
 * The forward declaration is so that we can declare the validParams() function
 * before we actually define the class... that way the definition isn't lost
 * at the bottom of the file.
 */

/// Forward Declarations
class FissionTerm2G;

/**
 * validParams returns the parameters that this Kernel accepts / needs
 * The actual body of the function MUST be in the .C file.
 */
template <>
InputParameters validParams<FissionTerm2G>();

/**
 * This kernel implements the scaled Laplacian operator:
 *
 * $\nabla u \cdot \nabla v$
 *
 * where v is test function and u is an admissible solution
 */



/// FissionTerm2G class inherits from Kernel class
class FissionTerm2G : public Kernel
{
public:
  /**
   * This is the constructor declaration.  This class takes a
   * InputParameters object, just like other
   * Kernel-derived classes.
   */
   // Type = Input parameters,
  FissionTerm2G(const InputParameters & parameters);

protected:
  /// Required residual for standard kernels in MOOSE
  /// Evaluation of residual at quadrature points (Qp) over finite domain
  virtual Real computeQpResidual() override;

  /// Required Jacobian for standard kernels in MOOSE
  /** This function returns the diagonal of the Jacobian to be used as a preconditioner
   * in the linear sub-problem.
   */
  virtual Real computeQpJacobian() override;

  /// The variables which holds the value for the FissionTerm2G coefficient
  const Real _sigmaF;
  const Real _k;
  const Real _v;
  const Real _chi;
};