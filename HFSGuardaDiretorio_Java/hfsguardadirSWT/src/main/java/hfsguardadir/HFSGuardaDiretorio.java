package hfsguardadir;

import hfsguardadir.catalogador.Catalogador;
import hfsguardadir.comum.Rotinas;
import hfsguardadir.gui.FrmPrincipal;
import hfsguardadir.gui.FrmSplash;
import hfsguardadir.objetos.Parametro;
import hfsguardadir.objetosgui.Dialogo;

import java.io.IOException;
import java.sql.SQLException;
import java.util.logging.Logger;

import javax.xml.parsers.ParserConfigurationException;

import org.eclipse.swt.widgets.Display;
import org.xml.sax.SAXException;

public class HFSGuardaDiretorio {

	public static FrmPrincipal frmPrincipal;

	public static void main(String args[]) {
		Display display = new Display();
		Parametro param = Rotinas.getParams();
		Logger log = Logger.getLogger(Rotinas.HFSGUARDADIR);
		frmPrincipal = new FrmPrincipal();
		
		if (param.getJavaVersao() > 1.7) {
			try {
				Catalogador.iniciarSistema(param);
				Rotinas.iniciarLogArquivo(log);

				new FrmSplash(frmPrincipal.getCatalogador());

				frmPrincipal.iniciar();
				Rotinas.CentralizaFrm(frmPrincipal.getShell());

				while ((Display.getCurrent().getShells().length != 0)
						&& !Display.getCurrent().getShells()[0].isDisposed()) {
					if (!display.readAndDispatch()) {
						display.sleep();
					}
				}

			} catch (ClassNotFoundException e) {
				Dialogo.mensagemErro(frmPrincipal.getShell(),
						"HFSGuardaDir.ErroInicial", e.getLocalizedMessage());
			} catch (SQLException e) {
				Dialogo.mensagemErro(frmPrincipal.getShell(),
						"HFSGuardaDir.ErroInicial", e.getLocalizedMessage());
			} catch (SAXException e) {
				Dialogo.mensagemErro(frmPrincipal.getShell(),
						"HFSGuardaDir.ErroInicial", e.getLocalizedMessage());
			} catch (IOException e) {
				Dialogo.mensagemErro(frmPrincipal.getShell(),
						"HFSGuardaDir.ErroInicial", e.getLocalizedMessage());
			} catch (ParserConfigurationException e) {
				Dialogo.mensagemErro(frmPrincipal.getShell(),
						"HFSGuardaDir.ErroInicial", e.getLocalizedMessage());
			}
		} else {
			Dialogo.mensagemErro(frmPrincipal.getShell(), 
					"HFSGuardaDir.ValidaJavaVersao");
		}
	}

}