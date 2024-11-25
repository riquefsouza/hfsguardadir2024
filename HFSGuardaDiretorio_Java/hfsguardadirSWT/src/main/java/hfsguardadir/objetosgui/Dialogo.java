package hfsguardadir.objetosgui;

import hfsguardadir.comum.Rotinas;

import java.util.logging.Logger;

import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.MessageBox;
import org.eclipse.swt.widgets.Shell;

public class Dialogo {
	private static Logger log = Logger.getLogger(Rotinas.HFSGUARDADIR);
	private static MessageBox msgBox;
	
	public Dialogo() {
		super();		
	}

	public static void mudarLingua() {
		/*		
		botao.setText(Rotinas.getRecurso("Dialogo.yesButtonText"));
		UIManager.put("OptionPane.yesButtonMnemonic", Rotinas
				.getRecurso("Dialogo.yesButtonMnemonic"));
		UIManager.put("OptionPane.cancelButtonText", Rotinas
				.getRecurso("Dialogo.cancelButtonText"));
		UIManager.put("OptionPane.cancelButtonMnemonic", Rotinas
				.getRecurso("Dialogo.cancelButtonMnemonic"));
		UIManager.put("OptionPane.noButtonText", Rotinas
				.getRecurso("Dialogo.noButtonText"));
		UIManager.put("OptionPane.noButtonMnemonic", Rotinas
				.getRecurso("Dialogo.noButtonMnemonic"));
		
		UIManager.put("OptionPane.okButtonMnemonic", Rotinas
				.getRecurso("Dialogo.okButtonMnemonic"));
*/				
	}

	public static void mensagemErro(Shell pai, String recurso, String texto) {
		log.warning(Rotinas.getRecurso(recurso) + " " + texto);
		
		msgBox = new MessageBox(pai, SWT.ICON_WARNING | SWT.OK);        
		msgBox.setText(Rotinas.getRecurso("Dialogo.erro"));
		msgBox.setMessage(Rotinas.getRecurso(recurso) + " " + texto);
        msgBox.open();        				
	}

	public static void mensagemErro(Shell pai, String recurso) {
		Dialogo.mensagemErro(pai, recurso, "");
	}

	public static void mensagemInfo(Shell pai, String recurso) {
		log.info(Rotinas.getRecurso(recurso));
		
		msgBox = new MessageBox(pai, SWT.ICON_INFORMATION | SWT.OK);        
		msgBox.setText(Rotinas.getRecurso("Dialogo.info"));
		msgBox.setMessage(Rotinas.getRecurso(recurso));
        msgBox.open();        				
	}

	public static int confirma(Shell pai, String recurso) {
		log.info(Rotinas.getRecurso(recurso));
		
		msgBox = new MessageBox(pai, SWT.ICON_QUESTION | SWT.YES | SWT.NO);        
		msgBox.setText(Rotinas.getRecurso("Dialogo.confirma"));
		msgBox.setMessage(Rotinas.getRecurso(recurso));
        return msgBox.open();        				
	}

	public static String entrada(Shell pai, String recurso,
			String valorInicial) {
		DialogoEntrada entradaDlg = new DialogoEntrada(pai, 
				Rotinas.getRecurso("Dialogo.entrada"), Rotinas.getRecurso(recurso),  
				valorInicial);												
        return entradaDlg.open();
        
		/* Para usar jface muita lib
		 
			lib/org.eclipse.core.commands_3.6.100.v20130515-1857.jar
			lib/org.eclipse.equinox.common_3.6.200.v20130402-1505.jar
			lib/org.eclipse.jface_3.9.1.v20130725-1141.jar
			lib/org.eclipse.osgi_3.9.1.v20140110-1610.jar
			lib/org.eclipse.ui.workbench_3.105.2.v20140211-1711.jar		  

        InputDialog dlg = new InputDialog(pai,
        		Rotinas.getRecurso("Dialogo.entrada"), Rotinas.getRecurso(recurso),
        		valorInicial, new ValidadorTamanho());
            if (dlg.open() == Window.OK) {
              return dlg.getValue();
            } else {
            	return "";
            }
		 */            
	}
	
	public static String entrada(Shell pai, String recurso) {
        return entrada(pai, recurso, "");        				
	}
	
}

/*
class ValidadorTamanho implements IInputValidator {
	public String isValid(String texto) {
		int tamanho = texto.length();
		if (tamanho <= 2)
			return "Tamanho do texto menor do que 2";
		if (tamanho >= 10)
			return "Tamanho do texto maior do que 10";
		return null;
	}
}
*/
