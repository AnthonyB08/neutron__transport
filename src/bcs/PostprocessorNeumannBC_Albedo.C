//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PostprocessorNeumannBC_Albedo.h"

registerMooseObject("Neutron_TransportApp", PostprocessorNeumannBC_Albedo);

defineLegacyParams(PostprocessorNeumannBC_Albedo);

InputParameters
PostprocessorNeumannBC_Albedo::validParams()
{
  InputParameters params = IntegratedBC::validParams();
  params.addClassDescription(
      "Neumann boundary condition with value prescribed by a Postprocessor value.");
  params.addParam<PostprocessorName>(
      "postprocessor", 0.0, "The postprocessor to use for value of the gradient on the boundary.");
  params.addRequiredParam<Real>("alpha", "Albedo alpha value");
  return params;
}

PostprocessorNeumannBC_Albedo::PostprocessorNeumannBC_Albedo(const InputParameters & parameters)
  : IntegratedBC(parameters),
  _value(getPostprocessorValue("postprocessor")),
  _alpha(getParam<Real>("alpha"))
{
}

Real
PostprocessorNeumannBC_Albedo::computeQpResidual()
{
  return -(((_alpha-1)/(_alpha + 1))/2 *_test[_i][_qp] * _value);
}
