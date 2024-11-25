package hfsguardadir.objetosgui;

import hfsguardadir.comum.Rotinas;

import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;

import javax.swing.ImageIcon;
import javax.swing.JComponent;
import javax.swing.JFileChooser;
import javax.swing.UIManager;
import javax.swing.border.BevelBorder;
import javax.swing.filechooser.FileFilter;
import javax.swing.filechooser.FileNameExtensionFilter;

public class EscolhaArquivo extends JFileChooser {
	private static final long serialVersionUID = 3644252320738434567L;

	public static final int PREVIEW_OPEN_DIALOG = 3;

	public static final int PREVIEW_SAVE_DIALOG = 4;

	public EscolhaArquivo(int tipoDialogo) {
		super();
		if (tipoDialogo == EscolhaArquivo.SAVE_DIALOG
				|| tipoDialogo == EscolhaArquivo.OPEN_DIALOG) {
			this.setDialogType(tipoDialogo);
			if (tipoDialogo == EscolhaArquivo.SAVE_DIALOG)
				this.setDialogTitle(Rotinas
						.getRecurso("EscolhaArquivo.saveButtonText"));
			else if (tipoDialogo == EscolhaArquivo.OPEN_DIALOG)
				this.setDialogTitle(Rotinas
						.getRecurso("EscolhaArquivo.openButtonText"));
			adicionarFiltro("EscolhaArquivo.filtroTXT", "txt");
                        adicionarFiltro("EscolhaArquivo.filtroCSV", "csv");
                        adicionarFiltro("EscolhaArquivo.filtroHTML", "html");
                        adicionarFiltro("EscolhaArquivo.filtroXML", "xml");
                        adicionarFiltro("EscolhaArquivo.filtroSQL", "sql");
			this.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);
			this.setAcceptAllFileFilterUsed(true);                        
		} else if (tipoDialogo == EscolhaArquivo.PREVIEW_OPEN_DIALOG
				|| tipoDialogo == EscolhaArquivo.PREVIEW_SAVE_DIALOG) {
			if (tipoDialogo == EscolhaArquivo.PREVIEW_SAVE_DIALOG)
				this.setDialogTitle(Rotinas
						.getRecurso("EscolhaArquivo.saveButtonText"));
			else if (tipoDialogo == EscolhaArquivo.PREVIEW_OPEN_DIALOG)
				this.setDialogTitle(Rotinas
						.getRecurso("EscolhaArquivo.openButtonText"));
			adicionarFiltro("EscolhaArquivo.filtroBMP", "bmp");
                        adicionarFiltro("EscolhaArquivo.filtroICO", "ico");                        
			adicionarFiltro("EscolhaArquivo.filtroJPG", "jpg");
                        adicionarFiltro("EscolhaArquivo.filtroGIF", "gif");
                        adicionarFiltro("EscolhaArquivo.filtroPNG", "png");
                        adicionarFiltro("EscolhaArquivo.filtroTIF", "tif");
			this.setAccessory(new FilePreviewer(this));
		} else {
			this.setDialogType(EscolhaArquivo.CUSTOM_DIALOG);
			this.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
			this.setApproveButtonText(Rotinas
					.getRecurso("EscolhaArquivo.ApproveButtonText"));
			this.setApproveButtonMnemonic(Rotinas.getRecurso(
					"EscolhaArquivo.ApproveButtonMnemonic").charAt(0));
			this.setApproveButtonToolTipText(Rotinas
					.getRecurso("EscolhaArquivo.ApproveButtonToolTipText"));
			this.setAcceptAllFileFilterUsed(false);
			this.addChoosableFileFilter(new Filtro());
		}
		this.setControlButtonsAreShown(true);

		this.setMultiSelectionEnabled(false);
		this.setVisible(true);
	}

	private void adicionarFiltro(String descricao, String extensao) {
		FileNameExtensionFilter filtro1 = new FileNameExtensionFilter(Rotinas
				.getRecurso(descricao), new String[] { extensao });
		this.addChoosableFileFilter(filtro1);
		// this.setFileFilter(filtro1);
	}

	public static void mudarLingua() {
		UIManager.put("FileChooser.lookInLabelText", Rotinas
				.getRecurso("EscolhaArquivo.lookInLabelText"));
		UIManager.put("FileChooser.lookInLabelMnemonic", Rotinas
				.getRecurso("EscolhaArquivo.lookInLabelMnemonic"));
		UIManager.put("FileChooser.saveInLabelMnemonic", Rotinas
				.getRecurso("EscolhaArquivo.saveInLabelMnemonic"));
		UIManager.put("FileChooser.saveInLabelText", Rotinas
				.getRecurso("EscolhaArquivo.saveInLabelText"));
		UIManager.put("FileChooser.fileNameLabelText", Rotinas
				.getRecurso("EscolhaArquivo.fileNameLabelText"));
		UIManager.put("FileChooser.fileNameLabelMnemonic", Rotinas
				.getRecurso("EscolhaArquivo.fileNameLabelMnemonic"));
		UIManager.put("FileChooser.filesOfTypeLabelText", Rotinas
				.getRecurso("EscolhaArquivo.filesOfTypeLabelText"));
		UIManager.put("FileChooser.filesOfTypeLabelMnemonic", Rotinas
				.getRecurso("EscolhaArquivo.filesOfTypeLabelMnemonic"));
		UIManager.put("FileChooser.upFolderToolTipText", Rotinas
				.getRecurso("EscolhaArquivo.upFolderToolTipText"));
		UIManager.put("FileChooser.upFolderAccessibleName", Rotinas
				.getRecurso("EscolhaArquivo.upFolderAccessibleName"));
		UIManager.put("FileChooser.homeFolderToolTipText", Rotinas
				.getRecurso("EscolhaArquivo.homeFolderToolTipText"));
		UIManager.put("FileChooser.homeFolderAccessibleName", Rotinas
				.getRecurso("EscolhaArquivo.homeFolderAccessibleName"));
		UIManager.put("FileChooser.newFolderToolTipText", Rotinas
				.getRecurso("EscolhaArquivo.newFolderToolTipText"));
		UIManager.put("FileChooser.newFolderAccessibleName", Rotinas
				.getRecurso("EscolhaArquivo.newFolderAccessibleName"));
		UIManager.put("FileChooser.listViewButtonToolTipText", Rotinas
				.getRecurso("EscolhaArquivo.listViewButtonToolTipText"));
		UIManager.put("FileChooser.listViewButtonAccessibleName", Rotinas
				.getRecurso("EscolhaArquivo.listViewButtonAccessibleName"));
		UIManager.put("FileChooser.detailsViewButtonToolTipText", Rotinas
				.getRecurso("EscolhaArquivo.detailsViewButtonToolTipText"));
		UIManager.put("FileChooser.detailsViewButtonAccessibleName", Rotinas
				.getRecurso("EscolhaArquivo.detailsViewButtonAccessibleName"));
		UIManager.put("FileChooser.cancelButtonText", Rotinas
				.getRecurso("EscolhaArquivo.cancelButtonText"));
		UIManager.put("FileChooser.cancelButtonToolTipText", Rotinas
				.getRecurso("EscolhaArquivo.cancelButtonToolTipText"));
		UIManager.put("FileChooser.cancelButtonMnemonic", Rotinas
				.getRecurso("EscolhaArquivo.cancelButtonMnemonic"));

		UIManager.put("FileChooser.fileNameHeaderText", Rotinas
				.getRecurso("EscolhaArquivo.fileNameHeaderText"));
		UIManager.put("FileChooser.fileSizeHeaderText", Rotinas
				.getRecurso("EscolhaArquivo.fileSizeHeaderText"));
		UIManager.put("FileChooser.fileTypeHeaderText", Rotinas
				.getRecurso("EscolhaArquivo.fileTypeHeaderText"));
		UIManager.put("FileChooser.fileDateHeaderText", Rotinas
				.getRecurso("EscolhaArquivo.fileDateHeaderText"));
		UIManager.put("FileChooser.fileAttrHeaderText", Rotinas
				.getRecurso("EscolhaArquivo.fileAttrHeaderText"));

		UIManager.put("FileChooser.openButtonText", Rotinas
				.getRecurso("EscolhaArquivo.openButtonText"));
		UIManager.put("FileChooser.openButtonMnemonic", Rotinas
				.getRecurso("EscolhaArquivo.openButtonMnemonic"));
		UIManager.put("FileChooser.openButtonToolTipText", Rotinas
				.getRecurso("EscolhaArquivo.openButtonToolTipText"));

		UIManager.put("FileChooser.saveButtonText", Rotinas
				.getRecurso("EscolhaArquivo.saveButtonText"));
		UIManager.put("FileChooser.saveButtonMnemonic", Rotinas
				.getRecurso("EscolhaArquivo.saveButtonMnemonic"));
		UIManager.put("FileChooser.saveButtonToolTipText", Rotinas
				.getRecurso("EscolhaArquivo.saveButtonToolTipText"));

		UIManager.put("FileChooser.updateButtonText", Rotinas
				.getRecurso("EscolhaArquivo.updateButtonText"));
		UIManager.put("FileChooser.updateButtonMnemonic", Rotinas
				.getRecurso("EscolhaArquivo.updateButtonMnemonic"));
		UIManager.put("FileChooser.updateButtonToolTipText", Rotinas
				.getRecurso("EscolhaArquivo.updateButtonToolTipText"));

		UIManager.put("FileChooser.helpButtonText", Rotinas
				.getRecurso("EscolhaArquivo.helpButtonText"));
		UIManager.put("FileChooser.helpButtonMnemonic", Rotinas
				.getRecurso("EscolhaArquivo.helpButtonMnemonic"));
		UIManager.put("FileChooser.helpButtonToolTipText", Rotinas
				.getRecurso("EscolhaArquivo.helpButtonToolTipText"));

		UIManager.put("FileChooser.acceptAllFileFilterText", Rotinas
				.getRecurso("EscolhaArquivo.acceptAllFileFilterText"));
	}

	public int mostrar(Component pai) {
		return this.showDialog(pai, null);
	}

	public int mostrarAbrir(Component pai) {
		return this.showOpenDialog(pai);
	}

	public int mostrarSalvar(Component pai) {
		return this.showSaveDialog(pai);
	}
}

class Filtro extends FileFilter {
	public boolean accept(File arquivo) {
		// String nomeArquivo = arquivo.getName();
		// return nomeArquivo.endsWith("*.java");
		return true;
	}

	public String getDescription() {
		return Rotinas.getRecurso("EscolhaArquivo.todosDiretorios");
		// return ".java";
	}
}

class FilePreviewer extends JComponent implements PropertyChangeListener {
	private static final long serialVersionUID = 419111212721417789L;
	ImageIcon thumbnail = null;

	public FilePreviewer(JFileChooser fc) {
		setPreferredSize(new Dimension(100, 50));
		fc.addPropertyChangeListener(this);
		setBorder(new BevelBorder(BevelBorder.LOWERED));
	}

	public void loadImage(File f) {
		if (f == null) {
			thumbnail = null;
		} else {
			ImageIcon tmpIcon = new ImageIcon(f.getPath());
			if (tmpIcon.getIconWidth() > 90) {
				thumbnail = new ImageIcon(tmpIcon.getImage().getScaledInstance(
						90, -1, Image.SCALE_DEFAULT));
			} else {
				thumbnail = tmpIcon;
			}
		}
	}

	public void propertyChange(PropertyChangeEvent e) {
		String prop = e.getPropertyName();
		if (prop == JFileChooser.SELECTED_FILE_CHANGED_PROPERTY) {
			if (isShowing()) {
				loadImage((File) e.getNewValue());
				repaint();
			}
		}
	}

	public void paint(Graphics g) {
		super.paint(g);
		if (thumbnail != null) {
			int x = getWidth() / 2 - thumbnail.getIconWidth() / 2;
			int y = getHeight() / 2 - thumbnail.getIconHeight() / 2;
			if (y < 0) {
				y = 0;
			}

			if (x < 5) {
				x = 5;
			}
			thumbnail.paintIcon(this, g, x, y);
		}
	}
}
