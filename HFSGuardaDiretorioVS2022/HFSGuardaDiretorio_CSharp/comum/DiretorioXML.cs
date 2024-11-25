/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 03/07/2015
 * Time: 14:53
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using HFSGuardaDiretorio.objetos; 

namespace HFSGuardaDiretorio.comum
{
	/// <summary>
	/// Description of DiretorioXML.
	/// </summary>
	public class DiretorioXML
	{
	    private Diretorio diretorio;	    

		public DiretorioXML()
		{
	        this.diretorio = new Diretorio();
		}
		
		public Diretorio Diretorio {
			get { return diretorio; }
			set { diretorio = value; }
		}
		
	}
}
