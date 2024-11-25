#ifndef PTRDIFF_MAX
#define PTRDIFF_MAX (std::numeric_limits<ptrdiff_t>::max())
#endif

#include <gtkmm/application.h>
#include <gtkmm/main.h>

#include "FrmPrincipal.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/catalogador/Catalogador.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::catalogador;

int main(int argc, char* argv[])
{
  //auto app = Gtk::Application::create("org.gtkmm.example");
  //return app->make_window_and_run<HelloWorld>(argc, argv);
  
  Gtk::Main kit(argc, argv);

  Rotinas::setArgumentos(argc, argv);

  //Rotinas::testar();

  Catalogador::iniciarSistema();
  FrmPrincipal::Mostrar();

  Gtk::Main::run(*frmPrincipal);

  return 0;  
}

