//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PostprocessorNeumannBC_custom.h"

registerMooseObject("Neutron_TransportApp", PostprocessorNeumannBC_custom);

defineLegacyParams(PostprocessorNeumannBC_custom);

InputParameters
PostprocessorNeumannBC_custom::validParams()
{
  InputParameters params = IntegratedBC::validParams();
  params.addClassDescription(
      "Neumann boundary condition with value prescribed by a Postprocessor value.");
  params.addParam<PostprocessorName>(
      "postprocessor", 0.0, "The postprocessor to use for value of the gradient on the boundary.");
  return params;
}

PostprocessorNeumannBC_custom::PostprocessorNeumannBC_custom(const InputParameters & parameters)
  : IntegratedBC(parameters), _value(getPostprocessorValue("postprocessor"))
{
}

Real
PostprocessorNeumannBC_custom::computeQpResidual()
{
  return -_test[_i][_qp] * 0.2 * _value;
}
