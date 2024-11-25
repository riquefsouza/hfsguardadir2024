/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 07/07/2015
 * Time: 10:55
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Collections.Generic;
using HFSGuardaDiretorio.comum;
using HFSGuardaDiretorio.objetos;

namespace HFSGuardaDiretorio.objetosbo
{
	/// <summary>
	/// Description of ImportarBO.
	/// </summary>
	public sealed class ImportarBO
	{
		private static ImportarBO instancia = new ImportarBO();
		
		public static ImportarBO Instancia {
			get {
				return instancia;
			}
		}
		
		private ImportarBO()
		{
		}
		
	    public void CarregarListaDiretorios(Importar importar,
	            DiretorioOrdem dirOrdem, List<Diretorio> listaDiretorio,
	            IProgressoLog progressoLog) {
	        Arquivo arquivo;
	        Diretorio diretorio;
	        Progresso pb = new Progresso();
	
	        arquivo = new Arquivo();
	        arquivo.Nome = importar.RotuloRaiz;
	        arquivo.Tamanho = 0;
	        arquivo.Modificado = DateTime.Now;
	        arquivo.Atributos = "[DIR]";
	
	        diretorio = DiretorioBO.Instancia.atribuiDiretorio(
	                importar.Aba, importar.CodDirRaiz,
	                importar.NomeDirRaiz, "", true, listaDiretorio,
	                arquivo, dirOrdem);
	
	        listaDiretorio.Add(diretorio);
	        pb.Log = importar.Caminho;
	
	        DiretorioBO.Instancia.ImportarDiretorio(importar.Aba,
	                importar.CodDirRaiz, importar.NomeDirRaiz,
	                importar.Caminho, listaDiretorio, dirOrdem, progressoLog);
	
	        if (progressoLog != null) {
	            progressoLog.ProgressoLog(pb);
	        }        
	    }
	
	    public void ImportacaoCompleta(Importar importar, DiretorioOrdem dirOrdem,
	            List<Extensao> listaExtensao,
	            IProgressoLog progressoLog) {
	        List<Diretorio> listaDiretorio = new List<Diretorio>();
	
	        try {	        	
		        CarregarListaDiretorios(importar, dirOrdem, listaDiretorio, progressoLog);
		
		        /*
		        //Por ser multiplataforma nao tem funcao para pegar icone de arquivo        
		        ExtensaoBO.Instancia.salvarExtensoes(listaDiretorio,
		                listaExtensao, progressoLog);
		        */                
		        DiretorioBO.Instancia.salvarDiretorio(listaDiretorio, 
		                progressoLog);
		
		        listaDiretorio.Clear();
	        } catch (Exception) {	        	
	        	throw;
	        }
	        
	    }
		
	}
}
