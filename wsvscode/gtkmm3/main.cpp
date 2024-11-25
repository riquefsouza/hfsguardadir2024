#include <gtkmm/main.h>

#include "FrmPrincipal.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/catalogador/Catalogador.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::catalogador;

int main (int argc, char *argv[])
{
  Gtk::Main kit(argc, argv);

  Rotinas::setArgumentos(argc, argv);

  //Rotinas::testar();

  Catalogador::iniciarSistema();
  FrmPrincipal::Mostrar();

  Gtk::Main::run(*frmPrincipal);

  return 0;
}
