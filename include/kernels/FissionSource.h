// Andrew Hamel May 1 2022

#pragma once

#include "FissionSource.h"
#include "Kernel.h"

class FissionSource : public Kernel
{
public:

  FissionSource(const InputParameters & parameters);

  // Residual
  virtual Real computeQpResidual() override;

  // Jacobian diagonal
  virtual Real computeQpJacobian() override;

  // Heating power density
  Real _Sigma_nu;
};
