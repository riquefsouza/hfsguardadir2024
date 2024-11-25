#include "HFSGuardaDiretorio.h"
#include "FrmPrincipal.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/objetosdao/AbaDAO.h"
#include "hfsguardadir/catalogador/Catalogador.h"
// ---------------------------------------------------------------------------

void testarDAO() {
	GString* sApp = Rotinas_AppDirPath();
	sApp = g_string_append(sApp, "GuardaDir.db");
	Rotinas_BancoConectar(sApp);

	ListaAba lista = AbaDAO_consultarTudo(NULL);

	guint tamlista = ListaAba_conta(lista);
	Aba aba1 = Aba_new();
	GString *saida = g_string_new("");
	if (tamlista > 0) {
		for (unsigned int i = 0; i < tamlista; i++) {
			aba1 = ListaAba_pesquisaItemOrd(lista, i);

			g_string_printf(saida, "sDir: [%s]\n", aba1->nome->str);
			OutputDebugString(Rotinas_charArrayToLPCWSTR(saida->str));
		}
	}

	ListaAba_removeTodos(&lista);

	tamlista = ListaAba_conta(lista);

	Aba aba = Aba_new();
	aba->codigo = 3;
	aba->nome = g_string_new("DISCO3");
	aba->ordem = 3;
	AbaDAO_incluir(aba);
	
	Rotinas_BancoDesconectar();

	Aba_free(&aba1);
	Aba_free(&aba);
}


int main(int argc, char *argv[]) {

  Rotinas_argumentos(argc, argv);

// --------------------------------------------------------------------------
  gtk_init(&argc, &argv);

  //Rotinas_testar();
  //testarDAO();

  GtkCssProvider* provider = gtk_css_provider_new();
  GdkDisplay* display = gdk_display_get_default();
  GdkScreen* screen = gdk_display_get_default_screen(display);
  gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider),
	  GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  gtk_css_provider_load_from_data(provider, "progress, trough { min-height: 30px; }", -1, NULL);

  Catalogador_iniciarSistema();
  FrmPrincipal_Mostrar();
  gtk_main();

// ---------------------------------------------------------------------------

  return 0;
}
// ---------------------------------------------------------------------------
