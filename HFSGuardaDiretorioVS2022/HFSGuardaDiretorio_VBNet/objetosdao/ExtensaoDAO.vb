'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 06/07/2015
' * Time: 11:14
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
	''' Description of ExtensaoDAO.
	''' </summary>
	Public NotInheritable Class ExtensaoDAO
		Private Shared m_instancia As New ExtensaoDAO()

		Private conexao As SQLiteConnection

		Private cmd As SQLiteCommand

		Private dr As SQLiteDataReader = Nothing

		Public Shared ReadOnly Property Instancia() As ExtensaoDAO
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

		Private Function novoObjeto(dr As SQLiteDataReader) As Extensao
			Dim ret As New Extensao()
			ret.Codigo = dr.GetInt32(0)
			ret.Nome = dr.GetString(1)
			ret.Bmp16 = DirectCast(dr.GetValue(2), Byte())
			ret.Bmp32 = DirectCast(dr.GetValue(3), Byte())

			Return ret
		End Function

		Public Function consultarTotal() As Integer
			Dim total As Integer = 0
			conexao = Rotinas.getConexao()
			cmd = New SQLiteCommand("select count(*) from Extensoes", conexao)
			dr = cmd.ExecuteReader()

			If dr.Read() Then
				total = dr.GetInt32(0)
			End If
			Me.fecharSqlPreparado()

			Return total
		End Function

		Public Function consultarTudo(progressoLog As IProgressoLog) As List(Of Extensao)
			Dim obj As Extensao
			Dim lista As New List(Of Extensao)()
			Dim pb As Progresso
			Dim i As Integer = 0
			Dim total As Integer = Me.consultarTotal()

			conexao = Rotinas.getConexao()
			cmd = New SQLiteCommand("select cod, nome, bmp16, bmp32 from Extensoes", conexao)
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

		Public Function incluir(obj As Extensao) As Integer
			Dim ret As Integer
			conexao = Rotinas.getConexao()
			cmd = New SQLiteCommand("insert into Extensoes(cod, nome, bmp16, bmp32) values(@1,@2,@3,@4)", conexao)
			cmd.Parameters.Add("@1", DbType.Int32)
			cmd.Parameters.Add("@2", DbType.[String], 20)
			cmd.Parameters.Add("@3", DbType.Binary, 1000000)
			cmd.Parameters.Add("@4", DbType.Binary, 1000000)
			'
'	        cmd.Parameters.AddWithValue("@1", obj.Codigo);
'	        cmd.Parameters.AddWithValue("@2", obj.Nome);
'	        cmd.Parameters.AddWithValue("@3", obj.Bmp16);
'	        cmd.Parameters.AddWithValue("@4", obj.Bmp32);
'	        

			cmd.Prepare()

			cmd.Parameters("@1").Value = obj.Codigo
			cmd.Parameters("@2").Value = obj.Nome
			cmd.Parameters("@3").Value = obj.Bmp16
			cmd.Parameters("@4").Value = obj.Bmp32

			ret = cmd.ExecuteNonQuery()
			Return ret
		End Function

		Public Function excluir(codigo As Integer) As Integer
			Dim ret As Integer
			conexao = Rotinas.getConexao()

			cmd = New SQLiteCommand("delete from Extensoes where cod=@1", conexao)
			cmd.Parameters.AddWithValue("@1", codigo)
			cmd.Prepare()
			ret = cmd.ExecuteNonQuery()

			Return ret
		End Function

		Public Function excluirTudo() As Integer
			Dim ret As Integer
			conexao = Rotinas.getConexao()

			cmd = New SQLiteCommand("delete from Extensoes", conexao)
			ret = cmd.ExecuteNonQuery()

			Return ret
		End Function

		Public Function criarTabela() As Integer
			Dim ret As Integer
			conexao = Rotinas.getConexao()
			cmd = New SQLiteCommand("create table IF NOT EXISTS Extensoes(" & "cod integer not null," & "nome varchar(20) not null," & "bmp16 BLOB COLLATE NOCASE null," & "bmp32 BLOB COLLATE NOCASE null," & "primary key (cod))", conexao)
			ret = cmd.ExecuteNonQuery()
			Return ret
		End Function

	End Class
End Namespace
