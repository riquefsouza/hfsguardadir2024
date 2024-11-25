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

    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider),
                                           GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_data(provider, "progress, trough { min-height: 30px; }", -1, NULL);

  Catalogador::iniciarSistema();
  FrmPrincipal::Mostrar();

  Gtk::Main::run(*frmPrincipal);

  return 0;
}
