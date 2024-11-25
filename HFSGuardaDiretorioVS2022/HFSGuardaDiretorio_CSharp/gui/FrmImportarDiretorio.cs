/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 11/12/2014
 * Time: 11:24
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.IO;
using System.Drawing;
using System.Collections.Generic;
using System.Windows.Forms;
using HFSGuardaDiretorio.comum;
using HFSGuardaDiretorio.objetos;
using HFSGuardaDiretorio.objetosbo;
using HFSGuardaDiretorio.objetosgui;
using HFSGuardaDiretorio.catalogador;

namespace HFSGuardaDiretorio.gui
{
	/// <summary>
	/// Description of FrmImportarDiretorio.
	/// </summary>
	public partial class FrmImportarDiretorio : Form
	{
		private readonly FrmPrincipal frmPrincipal;
	    private readonly FrmImportarDiretorioProgresso frmImportarDiretorioProgresso;    
	    private readonly Catalogador catalogador;
	    
	    public bool bSubDiretorio;
	    public List<Importar> listaImportar;
	    public List<Diretorio> listaDiretorio;
		
		public FrmImportarDiretorio(FrmPrincipal frmPrincipal)
		{
			//
			// The InitializeComponent() call is required for Windows Forms designer support.
			//
			InitializeComponent();
			
	        frmImportarDiretorioProgresso = new FrmImportarDiretorioProgresso(this);
	        listaImportar = new List<Importar>();
	        
	        this.frmPrincipal = frmPrincipal;
	        catalogador = frmPrincipal.Catalogador;
		}
		
		void FrmImportarDiretorioShown(object sender, EventArgs e)
		{
			string sLog;

			foreach (Importar importar in this.listaImportar) {
				catalogador.diretorioOrdem.Ordem = 1;

				if (!bSubDiretorio) {
					Cursor = Cursors.WaitCursor;

					try {
						ImportarBO.Instancia.ImportacaoCompleta(importar,
							catalogador.diretorioOrdem, catalogador.listaExtensoes,
							frmImportarDiretorioProgresso);
					} catch (Exception ex) {
						Dialogo.mensagemErro(ex.Message);
					}					

					Cursor = Cursors.Default;
				} else {
					if (!DiretorioBO.Instancia.verificaCodDir(importar.Aba,
							importar.RotuloRaiz, catalogador.listaDiretorioPai)) {
						Cursor = Cursors.WaitCursor;

						try {
							ImportarBO.Instancia.ImportacaoCompleta(importar,
									catalogador.diretorioOrdem, catalogador.listaExtensoes,
									frmImportarDiretorioProgresso);							
						} catch (Exception ex) {							
							Dialogo.mensagemErro(ex.Message);
						}
						
						Cursor = Cursors.Default;
					} else {
						Dialogo.mensagemInfo("O diretório já existe no catálogo!");
					}
				}
			}

			if (frmPrincipal.menuGravarLogImportacao.Selected) {
				if (memoImportaDir.Lines.Length > 0) {
					sLog = Rotinas.ExtractFilePath(Application.ExecutablePath)+
						Path.DirectorySeparatorChar +
						Rotinas.formataDate(Rotinas.FORMATO_DHARQUIVO, DateTime.Now) +
						"_Importacao.log";
					
		            StringList log = new StringList();
	            	log.AddRange(memoImportaDir.Lines);
		            log.SaveToFile(sLog);
				}
			} 
			
			this.Close();
			
		}
		
	}
}
