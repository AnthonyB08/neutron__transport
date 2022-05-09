//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SourceTermG2_May8.h"

registerMooseObject("Neutron_TransportApp", SourceTermG2_May8);

template<>
InputParameters validParams<SourceTermG2_May8>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Source term kernel");
  params.addRequiredCoupledVar("coupledGroupA", "Coupled group A.");
  params.addParam<Real>("sourceS",0.0,"Source term");
  params.addParam<Real>("sigma_sa",0.0,"Scatter to A");
  return params;
}

SourceTermG2_May8::SourceTermG2_May8(const InputParameters & parameters): 
    Kernel(parameters),
    _coupledGroupA(coupledValue("coupledGroupA")),
    _sigma_sa(getParam<Real>("sigma_sa"))

{
}

Real
SourceTermG2_May8::computeQpResidual()
{
 return (_sigma_sa * _coupledGroupA[_qp] ) * _test[_i][_qp];
}

Real
SourceTermG2_May8::computeQpJacobian()
{
 return (_sigma_sa) * _phi[_j][_qp] * _test[_i][_qp];
}