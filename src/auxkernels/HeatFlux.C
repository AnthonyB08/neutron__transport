//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
//*
//* Engy-5310: Computational Continuum Transport Phenomena
//* UMass Lowell, Nuclear Chemical Engineering
//* https://github.com/dpploy/engy-5310

#include "HeatFlux.h"

registerMooseObject("Neutron_TransportApp", HeatFlux);

InputParameters
HeatFlux::validParams()
{
  InputParameters params = VectorAuxKernel::validParams();
  params.addRequiredCoupledVar("field", "The dependent variable field to be used.");
  params.addClassDescription("Computes the heat flux vector.");

  return params;
}

HeatFlux::HeatFlux(const InputParameters & parameters): 
    VectorAuxKernel(parameters),
    _gradU(coupledGradient("field"))

{
}

RealVectorValue
HeatFlux::computeValue()
{
  return _gradU[_qp];
}
