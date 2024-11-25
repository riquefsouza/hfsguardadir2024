/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 08/07/2015
 * Time: 11:26
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using HFSGuardaDiretorio.comum;

namespace HFSGuardaDiretorio.gui
{
	/// <summary>
	/// Description of FrmImportarDiretorioProgresso.
	/// </summary>
	public class FrmImportarDiretorioProgresso : IProgressoLog
	{
	    FrmImportarDiretorio form;

	    public FrmImportarDiretorioProgresso(FrmImportarDiretorio form) 
	    {
	        this.form = form;
		}
	    
		public void ProgressoLog(Progresso progresso)
		{
	        if (progresso.Posicao == 0) {
	            this.form.pbImportar.Minimum = progresso.Minimo;
	            this.form.pbImportar.Maximum = progresso.Maximo;
	            this.form.pbImportar.Step = progresso.Passo;
	        }
	        this.form.pbImportar.Value = progresso.Posicao;	        
	        
	        if (progresso.Log.Length > 0) {
	            int pos = form.memoImportaDir.TextLength;
	            form.memoImportaDir.AppendText(progresso.Log+"\n");
	            form.memoImportaDir.Select(pos, pos);
	            form.barraStatus.Items[1].Text = Convert.ToString(pos);
	            form.barraStatus.Update();
	        }
	        
		}
	    
	}
}
