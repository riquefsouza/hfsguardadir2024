package hfsguardadir.objetosgui;

import hfsguardadir.comum.Rotinas;

import java.awt.Dimension;
import java.awt.FontMetrics;

import javax.swing.JButton;

public class Botao extends JButton {
	private static final long serialVersionUID = 390266211838123290L;

	public Botao() {
		super();
		setMinimumSize(new Dimension(40, 23));
	}

	public void setPreferredSize(Dimension preferredSize) {
		if (this.getText().length() > 0) {
			FontMetrics fm = this.getFontMetrics(this.getFont());
			int nlargura = fm.getMaxAscent() + fm.getMaxDescent()
					+ fm.getMaxAdvance();
			nlargura += fm.stringWidth(this.getText());

			// if (nlargura > preferredSize.width)
			if (Rotinas.getParams().getLookAndFeel().equals("windows"))
				preferredSize.width = nlargura + 10;
			else if (Rotinas.getParams().getLookAndFeel().equals("motif")) {
				preferredSize.width = nlargura;
				preferredSize.height += 10; 
			} else
				preferredSize.width = nlargura;
		}
		super.setPreferredSize(preferredSize);
	}
}
