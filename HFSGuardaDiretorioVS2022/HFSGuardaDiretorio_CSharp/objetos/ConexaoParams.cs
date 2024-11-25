/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 03/07/2015
 * Time: 14:29
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;

namespace HFSGuardaDiretorio.objetos
{
	/// <summary>
	/// Description of ConexaoParams.
	/// </summary>
	public class ConexaoParams
	{
		private string nome;		
		private string driver;			
		private string url;	
		private string login;	
		private string senha;
		
		public ConexaoParams()
		{
			this.nome = "";
			this.driver = "";
			this.url = "";
			this.login = "";
			this.senha = "";
		}
		
		public string Nome {
			get { return nome; }
			set { nome = value; }
		}		
		
		public string Driver {
			get { return driver; }
			set { driver = value; }
		}
		
		public string Url {
			get { return url; }
			set { url = value; }
		}

		public string Login {
			get { return login; }
			set { login = value; }
		}

		public string Senha {
			get { return senha; }
			set { senha = value; }
		}		
	}
}
