/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 03/07/2015
 * Time: 14:54
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using HFSGuardaDiretorio.objetos;

namespace HFSGuardaDiretorio.comum
{
	/// <summary>
	/// Description of ICatalogador.
	/// </summary>
	public interface ICatalogador
	{
	    Aba getAbaSelecionada();
	    void DuploCliqueLista(string nome, string tipo);
	    void EncontrarItemLista(string nomeAba, string nome, string caminho);		
	}
}
