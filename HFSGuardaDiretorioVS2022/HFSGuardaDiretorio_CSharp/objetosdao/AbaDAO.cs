/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 03/07/2015
 * Time: 17:27
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Data;
using System.Data.SQLite;
using System.Collections.Generic;
using HFSGuardaDiretorio.comum;
using HFSGuardaDiretorio.objetos;

namespace HFSGuardaDiretorio.objetosdao
{
	/// <summary>
	/// Description of AbaDAO.
	/// </summary>
	public sealed class AbaDAO
	{
		private static AbaDAO instancia = new AbaDAO();
		
	    private SQLiteConnection conexao;

	    private SQLiteCommand cmd;
	    
	    private SQLiteDataReader dr = null;
		
		public static AbaDAO Instancia {
			get {
				return instancia;
			}
		}
		
		private AbaDAO()
		{
		}
		
	    private void fecharSqlPreparado() {
	        if (dr != null) {
	            dr.Close();
	        }
	    }
	
	    private Aba novoObjeto(SQLiteDataReader dr) {
	        Aba ret = new Aba();
	        ret.Codigo = dr.GetInt32(0);
	        ret.Nome = dr.GetString(1);
	        return ret;
	    }
	
	    public int consultarTotal() {
	        int total = 0;
	        conexao = Rotinas.getConexao();
			cmd = new SQLiteCommand("select count(*) from Abas", conexao);	
			dr = cmd.ExecuteReader();
	
	        if (dr.Read()) {
	            total = dr.GetInt32(0);
	        }
	        this.fecharSqlPreparado();
	
	        return total;
	    }
	
	    public List<Aba> consultarTudo(IProgressoLog progressoLog) {
	        Aba obj;
	        List<Aba> lista = new List<Aba>();
	        Progresso pb;
	        int i = 0;
	        int total = this.consultarTotal();
	
	        conexao = Rotinas.getConexao();
	        cmd = new SQLiteCommand("select cod, nome from Abas", conexao);	
			dr = cmd.ExecuteReader();
	        	
	        if (total > 0) {
	            pb = new Progresso();
	            pb.Minimo = 0;
	            pb.Maximo = total - 1;
	            pb.Posicao = 0;
	            pb.Passo = 1;
	
	            while (dr.Read()) {
	                obj = novoObjeto(dr);
	                obj.Ordem = i + 1;
	
	                lista.Add(obj);
	
	                pb.Posicao = i;
	
	                if (progressoLog != null) {
	                    progressoLog.ProgressoLog(pb);
	                }
	
	                i++;
	            }
	        }
	
	        this.fecharSqlPreparado();
	
	        return lista;
	    }
	
	    public int incluir(Aba obj) {
	        int ret;
	        conexao = Rotinas.getConexao();
	        cmd = new SQLiteCommand("insert into Abas(cod, nome) values(@1,@2)", conexao);	        
	        cmd.Parameters.AddWithValue("@1", obj.Codigo);
	        cmd.Parameters.AddWithValue("@2", obj.Nome);
	        cmd.Prepare();
	        ret = cmd.ExecuteNonQuery();
	        return ret;
	    }
	
	    public int alterar(Aba obj) {
	        int ret;
	        conexao = Rotinas.getConexao();
	        cmd = new SQLiteCommand("update Abas set nome=@1 where cod=@2", conexao);
	        cmd.Parameters.AddWithValue("@1", obj.Nome);
	        cmd.Parameters.AddWithValue("@2", obj.Codigo);
	        cmd.Prepare();
	        ret = cmd.ExecuteNonQuery();
	        return ret;
	    }
	
	    public int excluir(int codigo) {
	        int ret;
	        conexao = Rotinas.getConexao();
			
	        cmd = new SQLiteCommand("delete from Diretorios where aba=@1", conexao);
	        cmd.Parameters.AddWithValue("@1", codigo);
	        cmd.Prepare();
	        cmd.ExecuteNonQuery();
	
	        cmd = new SQLiteCommand("delete from Abas where cod=@1", conexao);
	        cmd.Parameters.AddWithValue("@1", codigo);
	        cmd.Prepare();
	        ret = cmd.ExecuteNonQuery();
	        
	        return ret;
	    }
	
	    public int criarTabela() {
	        int ret;
	        conexao = Rotinas.getConexao();
	        cmd = new SQLiteCommand("create table IF NOT EXISTS Abas("
	                + "cod integer not null, nome varchar(10) not null, "
	                + "primary key (cod))", conexao);
	        ret = cmd.ExecuteNonQuery();
	        return ret;
	    }
		
	}
}
