/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 03/07/2015
 * Time: 14:41
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;

namespace HFSGuardaDiretorio.objetos
{
	/// <summary>
	/// Description of Importar.
	/// </summary>
	public class Importar
	{
	    private int aba;			    
	    private int codDirRaiz;	    
	    private string rotuloRaiz;	    
	    private string nomeDirRaiz;    		    
	    private string caminho;    	    

		public Importar()
		{
			this.aba = 0;
			this.codDirRaiz = 0;
			this.rotuloRaiz = "";
			this.nomeDirRaiz = "";
			this.caminho = "";
		}
		
		public int Aba {
			get { return aba; }
			set { aba = value; }
		}
		
		public int CodDirRaiz {
			get { return codDirRaiz; }
			set { codDirRaiz = value; }
		}
		
		public string RotuloRaiz {
			get { return rotuloRaiz; }
			set { rotuloRaiz = value; }
		}
		
		public string NomeDirRaiz {
			get { return nomeDirRaiz; }
			set { nomeDirRaiz = value; }
		}
		
		public string Caminho {
			get { return caminho; }
			set { caminho = value; }
		}
		
	}
}
