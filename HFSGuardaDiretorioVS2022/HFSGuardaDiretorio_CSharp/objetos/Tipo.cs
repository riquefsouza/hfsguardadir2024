/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 03/07/2015
 * Time: 14:44
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;

namespace HFSGuardaDiretorio.objetos
{
	/// <summary>
	/// Description of Tipo.
	/// </summary>
	public class Tipo
	{
		private char codigo;		
		private string nome;
		
		public Tipo(){
	        this.codigo = ' ';
	        this.nome = "";			
		}
		
	    public Tipo(char codigo, string nome) {
	        this.codigo = codigo;
	        this.nome = nome;
	    }
		
		public char Codigo {
			get { return codigo; }
			set { codigo = value; }
		}
		
		public string Nome {
			get { return nome; }
			set { nome = value; }
		}
				
	}
}
