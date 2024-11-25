package hfsguardadir.objetosgui;

import java.io.File;

import hfsguardadir.comum.Rotinas;

import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.DirectoryDialog;
import org.eclipse.swt.widgets.FileDialog;
import org.eclipse.swt.widgets.Shell;

public class EscolhaArquivo {
	public static final int CUSTOM_DIALOG = 0;
	
	public static final int OPEN_DIALOG = 1;

	public static final int SAVE_DIALOG = 2;	
	
	public static final int PREVIEW_OPEN_DIALOG = 3;

	public static final int PREVIEW_SAVE_DIALOG = 4;
	
	private DirectoryDialog dirDialog;
	
	private FileDialog arqDialog;
	
	private int tipoDialogo;

	public EscolhaArquivo(Shell parent, int tipoDialogo) {
		this.tipoDialogo = tipoDialogo;
		
		if (tipoDialogo == EscolhaArquivo.SAVE_DIALOG
				|| tipoDialogo == EscolhaArquivo.OPEN_DIALOG) {
			
			if (tipoDialogo == EscolhaArquivo.SAVE_DIALOG) {
				arqDialog = new FileDialog(parent, SWT.SAVE);			
				arqDialog.setText(Rotinas.getRecurso("EscolhaArquivo.saveButtonText"));
			} else if (tipoDialogo == EscolhaArquivo.OPEN_DIALOG) {
				arqDialog = new FileDialog(parent, SWT.OPEN);			
				arqDialog.setText(Rotinas.getRecurso("EscolhaArquivo.openButtonText"));
			}
			
			arqDialog.setFilterNames(new String[] { 
					Rotinas.getRecurso("EscolhaArquivo.filtroTXT"),
					Rotinas.getRecurso("EscolhaArquivo.filtroCSV"),
					Rotinas.getRecurso("EscolhaArquivo.filtroHTML"),
					Rotinas.getRecurso("EscolhaArquivo.filtroXML"),
					Rotinas.getRecurso("EscolhaArquivo.filtroSQL"),
			        Rotinas.getRecurso("EscolhaArquivo.todosDiretorios") 
			       });

			arqDialog.setFilterExtensions(new String[] { 
					"*.txt", "*.csv", "*.html", "*.xml", "*.sql", "*.*" });
			
		} else if (tipoDialogo == EscolhaArquivo.PREVIEW_OPEN_DIALOG
				|| tipoDialogo == EscolhaArquivo.PREVIEW_SAVE_DIALOG) {
			
			if (tipoDialogo == EscolhaArquivo.PREVIEW_SAVE_DIALOG) {
				arqDialog = new FileDialog(parent, SWT.SAVE);			
				arqDialog.setText(Rotinas.getRecurso("EscolhaArquivo.saveButtonText"));
			} else if (tipoDialogo == EscolhaArquivo.PREVIEW_OPEN_DIALOG) {
				arqDialog = new FileDialog(parent, SWT.OPEN);			
				arqDialog.setText(Rotinas.getRecurso("EscolhaArquivo.openButtonText"));
			}
			
			arqDialog.setFilterNames(new String[] { 
					Rotinas.getRecurso("EscolhaArquivo.filtroBMP"),
					Rotinas.getRecurso("EscolhaArquivo.filtroICO"),
					Rotinas.getRecurso("EscolhaArquivo.filtroJPG"),
					Rotinas.getRecurso("EscolhaArquivo.filtroGIF"),
					Rotinas.getRecurso("EscolhaArquivo.filtroPNG"),
					Rotinas.getRecurso("EscolhaArquivo.filtroTIF"),
			        Rotinas.getRecurso("EscolhaArquivo.todosDiretorios") 
			       });

			arqDialog.setFilterExtensions(new String[] { 
					"*.bmp", "*.ico", "*.jpg", "*.gif", "*.png", "*.tif", "*.*" });
		} else {
			dirDialog = new DirectoryDialog(parent);
			//dirDialog.setFilterPath("C:/");
			//dirDialog.setText("");
			//dirDialog.setMessage("");
		}
	}

	public static void mudarLingua() {
		/*
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
		*/
	}

	public String mostrar() {
		String ret;
		
		if (tipoDialogo == EscolhaArquivo.CUSTOM_DIALOG)
			ret = dirDialog.open();
		else
			ret = arqDialog.open();
		
		if (ret==null)
			ret = "";
		
		return ret;
	}
	
	public String mostrar(File caminho) {
		String ret;
		
		if (tipoDialogo == EscolhaArquivo.CUSTOM_DIALOG) {
			dirDialog.setFilterPath(caminho.getPath());
			ret = dirDialog.open();
		} else {
			arqDialog.setFilterPath(caminho.getPath());
			ret = arqDialog.open();
		}

		if (ret==null)
			ret = "";
		
		return ret;
	}
}
