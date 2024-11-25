package hfsguardadir.objetosgui;

import javax.swing.JPasswordField;
import javax.swing.text.AttributeSet;
import javax.swing.text.BadLocationException;
import javax.swing.text.PlainDocument;

public class CampoSenha extends JPasswordField {
	private static final long serialVersionUID = -3827217611858895682L;

	private FiltraCampoSenha filtraCampoSenha;

	private int maxLength;

	public CampoSenha() {
		super();
		this.maxLength = Integer.MAX_VALUE;
	}

	public int getMaxLength() {
		return maxLength;
	}

	public void setMaxLength(int maxLength) {
		this.maxLength = maxLength;
		filtraCampoSenha = new FiltraCampoSenha(this.maxLength);
		this.setDocument(filtraCampoSenha);
	}

	public String getTexto() {
		String texto = "";
		char[] chars = this.getPassword();
		if (chars.length > 0){
			texto = new String(chars);
		}
		
		return texto;
	}

	public void setTexto(String texto) {
		this.setText(texto);
	}

}

class FiltraCampoSenha extends PlainDocument {
	private static final long serialVersionUID = 3821568943349434438L;

	private int limite;

	public FiltraCampoSenha(int limite) {
		this.limite = limite;
	}

	public void insertString(int offset, String str, AttributeSet attr)
			throws BadLocationException {
		if (str == null)
			return;

		if ((getLength() + str.length()) <= limite) {
			super.insertString(offset, str, attr);
		}
	}
}
