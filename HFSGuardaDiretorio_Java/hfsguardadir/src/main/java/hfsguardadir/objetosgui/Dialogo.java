package hfsguardadir.objetosgui;

import hfsguardadir.comum.Rotinas;

import java.awt.Component;
import java.util.logging.Logger;

import javax.swing.Icon;
import javax.swing.JOptionPane;
import javax.swing.UIManager;

public class Dialogo extends JOptionPane {
	private static final long serialVersionUID = 8344900276967442817L;

	private static Logger log = Logger.getLogger(Rotinas.HFSGUARDADIR);
	
	public Dialogo() {
		super();
	}

	public static void mudarLingua() {
		UIManager.put("OptionPane.yesButtonText", Rotinas
				.getRecurso("Dialogo.yesButtonText"));
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
		UIManager.put("OptionPane.okButtonText", Rotinas
				.getRecurso("Dialogo.okButtonText"));
		UIManager.put("OptionPane.okButtonMnemonic", Rotinas
				.getRecurso("Dialogo.okButtonMnemonic"));
	}

	public static void mensagemErro(Component pai, String recurso, String texto) {
		Dialogo.showMessageDialog(pai, Rotinas.getRecurso(recurso) + " "
				+ texto, Rotinas.getRecurso("Dialogo.erro"),
				Dialogo.ERROR_MESSAGE);
		log.warning(Rotinas.getRecurso(recurso) + " " + texto);
	}

	public static void mensagemErro(Component pai, String recurso) {
		Dialogo.mensagemErro(pai, recurso, "");
	}

	public static void mensagemInfo(Component pai, String recurso) {
		Dialogo.showMessageDialog(pai, Rotinas.getRecurso(recurso), Rotinas
				.getRecurso("Dialogo.info"), Dialogo.INFORMATION_MESSAGE);
		log.info(Rotinas.getRecurso(recurso));
	}

	public static int confirma(Component pai, String recurso) {
		return Dialogo.showConfirmDialog(pai, Rotinas.getRecurso(recurso),
				Rotinas.getRecurso("Dialogo.confirma"), Dialogo.YES_NO_OPTION);
	}

	public static String entrada(Component pai, String recurso) {
		return Dialogo
				.showInputDialog(pai, Rotinas.getRecurso(recurso), Rotinas
						.getRecurso("Dialogo.entrada"),
						Dialogo.QUESTION_MESSAGE);
	}

	public static String entrada(Component pai, String recurso,
			String valorInicial) {
		return (String) Dialogo.showInputDialog(pai, Rotinas
				.getRecurso(recurso), Rotinas.getRecurso("Dialogo.entrada"),
				Dialogo.QUESTION_MESSAGE, (Icon) UIManager
						.get("OptionPane.inputIcon"), null, valorInicial);
	}
}
