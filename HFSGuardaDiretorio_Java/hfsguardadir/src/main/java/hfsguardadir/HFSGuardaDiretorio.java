package hfsguardadir;

import hfsguardadir.catalogador.Catalogador;
import hfsguardadir.comum.Rotinas;
import hfsguardadir.gui.FrmPrincipal;
import hfsguardadir.objetos.Parametro;
import hfsguardadir.objetosgui.Dialogo;
import java.io.IOException;
import java.sql.SQLException;
import java.util.logging.Logger;
import javax.swing.SwingUtilities;
import javax.xml.parsers.ParserConfigurationException;
import org.xml.sax.SAXException;

public class HFSGuardaDiretorio {

    public static void main(String args[]) {
        Parametro param = Rotinas.getParams();
        Logger log = Logger.getLogger(Rotinas.HFSGUARDADIR);

        if (param.getJavaVersao() > 1.7) {
            try {
                Catalogador.iniciarSistema(param);
                Rotinas.iniciarLogArquivo(log);

                SwingUtilities.invokeLater(new Runnable() {
                    @Override
                    public void run() {
                        FrmPrincipal frmPrincipal = new FrmPrincipal();
                        Rotinas.CentralizaFrm(frmPrincipal);
                        String laf = Rotinas.getParams().getLookAndFeel();
                        frmPrincipal.getCatalogador().setLookAndFeel(
                            frmPrincipal.getCatalogador().getLookAndFeel(laf));
                        frmPrincipal.setVisible(true);
                    }
                });

            } catch (ClassNotFoundException e) {
                Dialogo.mensagemErro(null, "HFSGuardaDir.ErroInicial", e
                        .getLocalizedMessage());
            } catch (SQLException e) {
                Dialogo.mensagemErro(null, "HFSGuardaDir.ErroInicial", e
                        .getLocalizedMessage());
            } catch (SAXException e) {
                Dialogo.mensagemErro(null, "HFSGuardaDir.ErroInicial", e
                        .getLocalizedMessage());
            } catch (IOException e) {
                Dialogo.mensagemErro(null, "HFSGuardaDir.ErroInicial", e
                        .getLocalizedMessage());
            } catch (ParserConfigurationException e) {
                Dialogo.mensagemErro(null, "HFSGuardaDir.ErroInicial", e
                        .getLocalizedMessage());
            }
        } else {
            Dialogo.mensagemErro(null, "HFSGuardaDir.ValidaJavaVersao");
        }
    }

}
