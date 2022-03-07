//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "Neutron_TransportTestApp.h"
#include "Neutron_TransportApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

InputParameters
Neutron_TransportTestApp::validParams()
{
  InputParameters params = Neutron_TransportApp::validParams();
  return params;
}

Neutron_TransportTestApp::Neutron_TransportTestApp(InputParameters parameters) : MooseApp(parameters)
{
  Neutron_TransportTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

Neutron_TransportTestApp::~Neutron_TransportTestApp() {}

void
Neutron_TransportTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  Neutron_TransportApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"Neutron_TransportTestApp"});
    Registry::registerActionsTo(af, {"Neutron_TransportTestApp"});
  }
}

void
Neutron_TransportTestApp::registerApps()
{
  registerApp(Neutron_TransportApp);
  registerApp(Neutron_TransportTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
Neutron_TransportTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  Neutron_TransportTestApp::registerAll(f, af, s);
}
extern "C" void
Neutron_TransportTestApp__registerApps()
{
  Neutron_TransportTestApp::registerApps();
}
