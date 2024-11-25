package hfsguardadir.objetosgui;

import javax.swing.JTextField;
import javax.swing.text.AttributeSet;
import javax.swing.text.BadLocationException;
import javax.swing.text.PlainDocument;

public class CampoTexto extends JTextField {
	private static final long serialVersionUID = -1373544010934248818L;

	private FiltraCampoTexto filtraCampoTexto;

	private int maxLength;

	private String filtro; // ex: abc123%$

	private boolean aceitaNumeroNegativo;

	public CampoTexto() {
		super();
		this.maxLength = Integer.MAX_VALUE;
		this.filtro = FiltraCampoTexto.SEM_FITRO;
		this.aceitaNumeroNegativo = false;
	}

	private void setFiltraCampoTexto() {
		filtraCampoTexto = new FiltraCampoTexto(this.maxLength, filtro);
		filtraCampoTexto.setAceitaNegativo(this.aceitaNumeroNegativo);
		this.setDocument(filtraCampoTexto);
	}

	public int getMaxLength() {
		return maxLength;
	}

	public void setMaxLength(int maxLength) {
		this.maxLength = maxLength;
		setFiltraCampoTexto();
	}

	public String getFiltro() {
		return filtro;
	}

	public void setFiltro(String filtro) {
		this.filtro = filtro;
		setFiltraCampoTexto();
	}

	public void setSomenteTexto() {
		this.filtro = FiltraCampoTexto.ALPHA_NUMERIC;
		setFiltraCampoTexto();
	}

	public void setFiltroExcessao() {
		this.filtro = FiltraCampoTexto.FITRO_EXCEPT;
		setFiltraCampoTexto();
	}
	
	public void setSomenteNumeroInteiro(boolean aceitaNegativo) {
		this.filtro = FiltraCampoTexto.NUMERIC;
		this.aceitaNumeroNegativo = aceitaNegativo;
		setFiltraCampoTexto();
	}

	public void setSomenteNumeroReal(boolean aceitaNegativo) {
		this.filtro = FiltraCampoTexto.FLOAT;
		this.aceitaNumeroNegativo = aceitaNegativo;
		setFiltraCampoTexto();
	}
}

class FiltraCampoTexto extends PlainDocument {
	private static final long serialVersionUID = 3821568943349434438L;

	public static final String SEM_FITRO = "SEM_FITRO";
	
	public static final String FITRO_EXCEPT = ":*?\"<>|%";	

	public static final String LOWERCASE = "abcdefghijklmnopqrstuvwxyz";

	public static final String UPPERCASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	public static final String SPACE = " ";

	public static final String ALPHA = LOWERCASE + UPPERCASE + SPACE;

	public static final String NUMERIC = "0123456789";

	public static final String FLOAT = NUMERIC + ".";

	public static final String ALPHA_NUMERIC = ALPHA + NUMERIC;

	protected String aceitaChars = null;

	protected boolean aceitaNegativo = false;

	private int limite;

	public FiltraCampoTexto(int limite) {
		this(limite, SEM_FITRO);
	}

	public FiltraCampoTexto(int limite, String aceitaChars) {
		this.limite = limite;
		this.aceitaChars = aceitaChars;
	}

	public void setAceitaNegativo(boolean aceitaNegativo) {
		if (aceitaChars.equals(NUMERIC) || aceitaChars.equals(FLOAT)
				|| aceitaChars.equals(ALPHA_NUMERIC)) {
			this.aceitaNegativo = aceitaNegativo;
			aceitaChars += "-";
		}
	}

	public void insertString(int offset, String str, AttributeSet attr)
			throws BadLocationException {
		if (str == null)
			return;

		if ((getLength() + str.length()) <= limite) {

			if (aceitaChars.equals(UPPERCASE))
				str = str.toUpperCase();
			else if (aceitaChars.equals(LOWERCASE))
				str = str.toLowerCase();

			if (aceitaChars.equals(FITRO_EXCEPT)) {
				for (int i = 0; i < str.length(); i++) {
					if (str.charAt(i)=='\\')
						return;
					if (str.charAt(i)=='/')
						return;
					if (aceitaChars.indexOf(String.valueOf(str.charAt(i))) > 0) {
						return;
					}
				}
			} else if (!aceitaChars.equals(SEM_FITRO)) {
				for (int i = 0; i < str.length(); i++) {
					if (aceitaChars.indexOf(String.valueOf(str.charAt(i))) == -1) {
						return;
					}
				}

				if (aceitaChars.equals(FLOAT)
						|| (aceitaChars.equals(FLOAT + "-") && aceitaNegativo)) {
					if (str.indexOf(".") != -1) {
						if (getText(0, getLength()).indexOf(".") != -1) {
							return;
						}
					}
				}

				if (aceitaNegativo && str.indexOf("-") != -1) {
					if (str.indexOf("-") != 0 || offset != 0) {
						return;
					}
				}
			}
			super.insertString(offset, str, attr);
		}
	}
}
