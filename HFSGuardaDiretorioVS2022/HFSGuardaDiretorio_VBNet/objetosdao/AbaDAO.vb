'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 03/07/2015
' * Time: 17:27
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.Data
Imports System.Data.SQLite
Imports System.Collections.Generic
Imports HFSGuardaDiretorio.comum
Imports HFSGuardaDiretorio.objetos

Namespace objetosdao
	''' <summary>
	''' Description of AbaDAO.
	''' </summary>
	Public NotInheritable Class AbaDAO
		Private Shared m_instancia As New AbaDAO()

		Private conexao As SQLiteConnection

		Private cmd As SQLiteCommand

		Private dr As SQLiteDataReader = Nothing

		Public Shared ReadOnly Property Instancia() As AbaDAO
			Get
				Return m_instancia
			End Get
		End Property

		Private Sub New()
		End Sub

		Private Sub fecharSqlPreparado()
			If dr IsNot Nothing Then
				dr.Close()
			End If
		End Sub

		Private Function novoObjeto(dr As SQLiteDataReader) As Aba
			Dim ret As New Aba()
			ret.Codigo = dr.GetInt32(0)
			ret.Nome = dr.GetString(1)
			Return ret
		End Function

		Public Function consultarTotal() As Integer
			Dim total As Integer = 0
			conexao = Rotinas.getConexao()
			cmd = New SQLiteCommand("select count(*) from Abas", conexao)
			dr = cmd.ExecuteReader()

			If dr.Read() Then
				total = dr.GetInt32(0)
			End If
			Me.fecharSqlPreparado()

			Return total
		End Function

		Public Function consultarTudo(progressoLog As IProgressoLog) As List(Of Aba)
			Dim obj As Aba
			Dim lista As New List(Of Aba)()
			Dim pb As Progresso
			Dim i As Integer = 0
			Dim total As Integer = Me.consultarTotal()

			conexao = Rotinas.getConexao()
			cmd = New SQLiteCommand("select cod, nome from Abas", conexao)
			dr = cmd.ExecuteReader()

			If total > 0 Then
				pb = New Progresso()
				pb.Minimo = 0
				pb.Maximo = total - 1
				pb.Posicao = 0
				pb.Passo = 1

				While dr.Read()
					obj = novoObjeto(dr)
					obj.Ordem = i + 1

					lista.Add(obj)

					pb.Posicao = i

					If progressoLog IsNot Nothing Then
						progressoLog.ProgressoLog(pb)
					End If

					i += 1
				End While
			End If

			Me.fecharSqlPreparado()

			Return lista
		End Function

		Public Function incluir(obj As Aba) As Integer
			Dim ret As Integer
			conexao = Rotinas.getConexao()
			cmd = New SQLiteCommand("insert into Abas(cod, nome) values(@1,@2)", conexao)
			cmd.Parameters.AddWithValue("@1", obj.Codigo)
			cmd.Parameters.AddWithValue("@2", obj.Nome)
			cmd.Prepare()
			ret = cmd.ExecuteNonQuery()
			Return ret
		End Function

		Public Function alterar(obj As Aba) As Integer
			Dim ret As Integer
			conexao = Rotinas.getConexao()
			cmd = New SQLiteCommand("update Abas set nome=@1 where cod=@2", conexao)
			cmd.Parameters.AddWithValue("@1", obj.Nome)
			cmd.Parameters.AddWithValue("@2", obj.Codigo)
			cmd.Prepare()
			ret = cmd.ExecuteNonQuery()
			Return ret
		End Function

		Public Function excluir(codigo As Integer) As Integer
			Dim ret As Integer
			conexao = Rotinas.getConexao()

			cmd = New SQLiteCommand("delete from Diretorios where aba=@1", conexao)
			cmd.Parameters.AddWithValue("@1", codigo)
			cmd.Prepare()
			cmd.ExecuteNonQuery()

			cmd = New SQLiteCommand("delete from Abas where cod=@1", conexao)
			cmd.Parameters.AddWithValue("@1", codigo)
			cmd.Prepare()
			ret = cmd.ExecuteNonQuery()

			Return ret
		End Function

		Public Function criarTabela() As Integer
			Dim ret As Integer
			conexao = Rotinas.getConexao()
			cmd = New SQLiteCommand("create table IF NOT EXISTS Abas(" & "cod integer not null, nome varchar(10) not null, " & "primary key (cod))", conexao)
			ret = cmd.ExecuteNonQuery()
			Return ret
		End Function

	End Class
End Namespace
