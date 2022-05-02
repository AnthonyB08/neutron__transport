//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "AlbedoBC.h"

registerMooseObject("Neutron_TransportApp", AlbedoBC);

defineLegacyParams(AlbedoBC);

InputParameters
AlbedoBC::validParams()
{
  InputParameters params = IntegratedBC::validParams();
  params.addClassDescription("Vacuum boundary condition for neutron diffusion on the boundary.");
  params.addParam<Real>("alpha", 1, "No idea.");
  return params;
}

AlbedoBC::AlbedoBC(const InputParameters & parameters)
  : IntegratedBC(parameters), _alpha(getParam<Real>("alpha"))
{
}

Real
AlbedoBC::computeQpResidual()
{
  return - _test[_i][_qp] * (_alpha-1)/(_alpha+1) * _u[_qp] / 2;
}

Real
AlbedoBC::computeQpJacobian()
{
  return - _test[_i][_qp] * (_alpha-1)/(_alpha+1) * _phi[_j][_qp] / 2;
}
