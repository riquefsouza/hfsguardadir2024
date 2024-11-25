/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 06/07/2015
 * Time: 11:14
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
	/// Description of ExtensaoDAO.
	/// </summary>
	public sealed class ExtensaoDAO
	{
		private static ExtensaoDAO instancia = new ExtensaoDAO();
		
	    private SQLiteConnection conexao;

	    private SQLiteCommand cmd;
	    
	    private SQLiteDataReader dr = null;
		
		public static ExtensaoDAO Instancia {
			get {
				return instancia;
			}
		}
		
		private ExtensaoDAO()
		{
		}
		
	    private void fecharSqlPreparado() {
	        if (dr != null) {
	            dr.Close();
	        }
	    }
	
	    private Extensao novoObjeto(SQLiteDataReader dr) {
	        Extensao ret = new Extensao();
	        ret.Codigo = dr.GetInt32(0);
	        ret.Nome = dr.GetString(1);	        
	        ret.Bmp16 = (byte[]) dr.GetValue(2);
	        ret.Bmp32 = (byte[]) dr.GetValue(3);
	        
	        return ret;
	    }
	
	    public int consultarTotal() {
	        int total = 0;
	        conexao = Rotinas.getConexao();
			cmd = new SQLiteCommand("select count(*) from Extensoes", conexao);	
			dr = cmd.ExecuteReader();
	
	        if (dr.Read()) {
	            total = dr.GetInt32(0);
	        }
	        this.fecharSqlPreparado();
	
	        return total;
	    }
		
	    public List<Extensao> consultarTudo(IProgressoLog progressoLog) {
	        Extensao obj;
	        List<Extensao> lista = new List<Extensao>();
	        Progresso pb;
	        int i = 0;
	        int total = this.consultarTotal();
	
	        conexao = Rotinas.getConexao();
	        cmd = new SQLiteCommand("select cod, nome, bmp16, bmp32 from Extensoes", conexao);	
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
		
	    public int incluir(Extensao obj) {
	        int ret;
	        conexao = Rotinas.getConexao();
	        cmd = new SQLiteCommand("insert into Extensoes(cod, nome, bmp16, bmp32) values(@1,@2,@3,@4)", conexao);	
			cmd.Parameters.Add("@1", DbType.Int32);
			cmd.Parameters.Add("@2", DbType.String, 20);
         	cmd.Parameters.Add("@3", DbType.Binary, 1000000);
         	cmd.Parameters.Add("@4", DbType.Binary, 1000000);
	        /*
	        cmd.Parameters.AddWithValue("@1", obj.Codigo);
	        cmd.Parameters.AddWithValue("@2", obj.Nome);
	        cmd.Parameters.AddWithValue("@3", obj.Bmp16);
	        cmd.Parameters.AddWithValue("@4", obj.Bmp32);
	        */	        
	       	cmd.Prepare();
	       	
	        cmd.Parameters["@1"].Value = obj.Codigo;
	        cmd.Parameters["@2"].Value = obj.Nome;
	        cmd.Parameters["@3"].Value = obj.Bmp16;
	        cmd.Parameters["@4"].Value = obj.Bmp32;
	        	        
	        ret = cmd.ExecuteNonQuery();
	        return ret;
	    }
	
	    public int excluir(int codigo) {
	        int ret;
	        conexao = Rotinas.getConexao();
				
	        cmd = new SQLiteCommand("delete from Extensoes where cod=@1", conexao);
	        cmd.Parameters.AddWithValue("@1", codigo);
	        cmd.Prepare();
	        ret = cmd.ExecuteNonQuery();
	        
	        return ret;
	    }
	
	    public int excluirTudo() {
	        int ret;
	        conexao = Rotinas.getConexao();
				
	        cmd = new SQLiteCommand("delete from Extensoes", conexao);
	        ret = cmd.ExecuteNonQuery();
	        
	        return ret;
	    }

		public int criarTabela() {
	        int ret;
	        conexao = Rotinas.getConexao();
	        cmd = new SQLiteCommand(
                "create table IF NOT EXISTS Extensoes("
                + "cod integer not null,"
                + "nome varchar(20) not null,"
                + "bmp16 BLOB COLLATE NOCASE null,"
                + "bmp32 BLOB COLLATE NOCASE null,"
                + "primary key (cod))", conexao);
	        ret = cmd.ExecuteNonQuery();
	        return ret;
	    }
		
	}
}
