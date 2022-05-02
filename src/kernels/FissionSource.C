// Andrew Hamel May 1 2022

#include "FissionSource.h"

registerMooseObject("Neutron_TransportApp", FissionSource);

template<>
InputParameters validParams<FissionSource>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Fission source term");
  params.addParam<Real>("Sigma_nu", 1.0, "fission macro cross section * nu");
  return params;
}

FissionSource::FissionSource(const InputParameters & parameters): 
  Kernel(parameters),
  _Sigma_nu(getParam<Real>("Sigma_nu"))
{
}

Real
FissionSource::computeQpResidual()
{
  // Residual
  return - _Sigma_nu * _u[_qp] * _test[_i][_qp];
}

Real
FissionSource::computeQpJacobian()
{
  // Jacobian diagonal
  return - _Sigma_nu * _phi[_j][_qp] * _test[_i][_qp];
}
