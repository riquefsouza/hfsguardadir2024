/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 07/07/2015
 * Time: 13:47
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using HFSGuardaDiretorio.comum;

namespace HFSGuardaDiretorio.gui
{
	/// <summary>
	/// Description of FrmSplashProgresso.
	/// </summary>
	public class FrmSplashProgresso : IProgressoLog
	{
		
		FrmSplash form;
		    
		public FrmSplashProgresso(FrmSplash form)
		{
			this.form = form;
		}
		
		public void ProgressoLog(Progresso progresso)
		{
	        if (progresso.Posicao == 0) {
	            this.form.pb.Minimum = progresso.Minimo;
	            this.form.pb.Maximum = progresso.Maximo;
	            this.form.pb.Step = progresso.Passo;
	        }
	        this.form.pb.Value = progresso.Posicao;
	        this.form.pb.Update();
		}
	}
}
