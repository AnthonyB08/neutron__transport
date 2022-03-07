#include "Neutron_TransportApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
Neutron_TransportApp::validParams()
{
  InputParameters params = MooseApp::validParams();

  // Do not use legacy material output, i.e., output properties on INITIAL as well as TIMESTEP_END
  params.set<bool>("use_legacy_material_output") = false;

  return params;
}

Neutron_TransportApp::Neutron_TransportApp(InputParameters parameters) : MooseApp(parameters)
{
  Neutron_TransportApp::registerAll(_factory, _action_factory, _syntax);
}

Neutron_TransportApp::~Neutron_TransportApp() {}

void
Neutron_TransportApp::registerAll(Factory & f, ActionFactory & af, Syntax & syntax)
{
  ModulesApp::registerAll(f, af, syntax);
  Registry::registerObjectsTo(f, {"Neutron_TransportApp"});
  Registry::registerActionsTo(af, {"Neutron_TransportApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
Neutron_TransportApp::registerApps()
{
  registerApp(Neutron_TransportApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
Neutron_TransportApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  Neutron_TransportApp::registerAll(f, af, s);
}
extern "C" void
Neutron_TransportApp__registerApps()
{
  Neutron_TransportApp::registerApps();
}
