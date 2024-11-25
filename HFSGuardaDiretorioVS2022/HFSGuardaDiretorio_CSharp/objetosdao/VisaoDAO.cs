/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 03/07/2015
 * Time: 17:17
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Data;
using System.Data.SQLite;
using HFSGuardaDiretorio.comum;

namespace HFSGuardaDiretorio.objetosdao
{
	/// <summary>
	/// Description of VisaoDAO.
	/// </summary>
	public sealed class VisaoDAO
	{
		private static VisaoDAO instancia = new VisaoDAO();
		
	    private SQLiteConnection conexao;

	    private SQLiteCommand cmd;
		
		public static VisaoDAO Instancia {
			get {
				return instancia;
			}
		}
		
	    private VisaoDAO(){	
		}
		
	    public int criarVisao(string visao) {
	        int ret;
	        conexao = Rotinas.getConexao();
	        cmd = new SQLiteCommand(sqlVisao(visao), conexao);
	        ret = cmd.ExecuteNonQuery();
	        return ret;
	    }
	 
	    private String sqlVisao(string visao) {
	        string sSQL = "create view " + visao + " as "
	                + "SELECT d.aba,d.cod,d.ordem,d.coddirpai,d.nome,d.tam,"
	                + "d.tipo,d.modificado,d.atributos,d.caminho"
	                + ",(select nome as nomeaba from Abas where cod=d.aba) as nomeaba"
	                + ",(select nome as nomepai from Diretorios where cod=d.cod "
	                + "  and ordem=d.coddirpai and aba=d.aba) as nomepai"
	                + ",(select caminho as caminhopai from Diretorios where cod=d.cod "
	                + " and ordem=d.coddirpai and aba=d.aba) as caminhopai "
	                + "FROM Diretorios d ";
	
	        if (visao.Equals("consultadirpai")) {
	            sSQL += "where d.tipo='D' and d.coddirpai = 0";
	        } else if (visao.Equals("consultadirfilho")) {
	            sSQL += "where d.tipo='D' and d.coddirpai > 0";
	        }
	
	        return sSQL;
	    }
		
	}
}
