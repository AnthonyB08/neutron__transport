//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "FissionTerm.h"

/**
 * All MOOSE based object classes you create must be registered using this macro.
 * The first argument is the name of the App you entered in when running the stork.sh
 * script with an "App" suffix. If you ran "stork.sh Example", then the argument here
 * becomes "ExampleApp". The second argument is the name of the C++ class you created.
 */
registerMooseObject("Neutron_TransportApp", FissionTerm);

/**
 * This function defines the valid parameters for
 * this Kernel and their default values
 */
template<>
InputParameters validParams<FissionTerm>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("The weak form of the neutron intensity fission term");
  params.addParam<Real>("sigmaF",0.0,"Macroscopic fission cross-section");
  params.addParam<Real>("v",0.0,"neutron emission");
  params.addParam<Real>("k",0.0,"mutiplicity factor");
  return params;
}

FissionTerm::FissionTerm(const InputParameters & parameters) : Kernel(parameters),
    // Set the coefficient for the equation term
    _sigmaF(getParam<Real>("sigmaF")),
	_v(getParam<Real>("v")),
	_k(getParam<Real>("k"))

{
}

Real
FissionTerm::computeQpResidual()
{
	
  return -(_v/_k)*(  _sigmaF * _u[_qp] * _test[_i][_qp] );
  //return _sigmaF * _test[_i][_qp];
}

Real
FissionTerm::computeQpJacobian()
{
  return -(_v/_k)*(  _sigmaF * _phi[_j][_qp] * _test[_i][_qp] );
  //return 0.0;
}