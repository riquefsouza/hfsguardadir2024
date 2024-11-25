'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 06/07/2015
' * Time: 11:30
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.Data
Imports System.Data.SQLite
Imports System.Collections.Generic
Imports HFSGuardaDiretorio.comum
Imports HFSGuardaDiretorio.objetos
Imports HFSGuardaDiretorio.objetosbo

Namespace objetosdao
	''' <summary>
	''' Description of DiretorioDAO.
	''' </summary>
	Public NotInheritable Class DiretorioDAO
		Private Shared m_instancia As New DiretorioDAO()

		Private conexao As SQLiteConnection

		Private cmd As SQLiteCommand

		Private dr As SQLiteDataReader = Nothing

		Public Shared ReadOnly Property Instancia() As DiretorioDAO
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

		Private Function novoObjeto(dr As SQLiteDataReader) As Diretorio
			Dim ret As New Diretorio()
			Dim aba As New Aba()
			Dim tipo As Tipo

			aba.Codigo = dr.GetInt32(0)
			ret.Codigo = dr.GetInt32(1)
			ret.Ordem = dr.GetInt32(2)

			If Not dr.IsDBNull(3) Then
				ret.CodDirPai = dr.GetInt32(3)
			Else
				ret.CodDirPai = -1
			End If

			If Not dr.IsDBNull(4) Then
				ret.Nome = dr.GetString(4)
			End If

			ret.Tamanho = dr.GetDecimal(5)

			tipo = New Tipo(dr.GetString(6)(0), "")
			ret.Modificado = Rotinas.StringToDate(dr.GetString(7))
			If Not dr.IsDBNull(8) Then
				ret.Atributos = dr.GetString(8)
			End If
			If Not dr.IsDBNull(9) Then
				ret.Caminho = dr.GetString(9)
			End If
			If Not dr.IsDBNull(10) Then
				aba.Nome = dr.GetString(10)
			End If
			ret.Aba = aba
			If Not dr.IsDBNull(11) Then
				ret.NomePai = dr.GetString(11)
			End If
			If Not dr.IsDBNull(12) Then
				ret.CaminhoPai = dr.GetString(12)
			End If
			ret.TamanhoFormatado = DiretorioBO.Instancia.MontaTamanho(ret.Tamanho)
			If tipo.Codigo = "D"C Then
				tipo.Nome = "Diretório"
			Else
				tipo.Nome = "Arquivo"
			End If
			ret.Tipo = tipo
			ret.ModificadoFormatado = Rotinas.formataDate(Rotinas.FORMATO_DATAHORA, ret.Modificado)

			Return ret
		End Function

		Public Function consultarTotal(sSQL As String, sCondicaoTotal As String) As Integer
			Dim sTabela As String

			If Rotinas.ContainsStr(sSQL, "consultadirpai") Then
				sTabela = "consultadirpai"
			ElseIf Rotinas.ContainsStr(sSQL, "consultadirfilho") Then
				sTabela = "consultadirfilho"
			ElseIf Rotinas.ContainsStr(sSQL, "consultaarquivo") Then
				sTabela = "consultaarquivo"
			Else
				sTabela = "Diretorios"
			End If

			sSQL = "select count(*) from " & sTabela
			If sCondicaoTotal.Trim().Length > 0 Then
				sSQL += " " & sCondicaoTotal
			End If
			Dim total As Integer = 0
			conexao = Rotinas.getConexao()
			cmd = New SQLiteCommand(sSQL, conexao)
			dr = cmd.ExecuteReader()

			If dr.Read() Then
				total = dr.GetInt32(0)
			End If
			Me.fecharSqlPreparado()

			Return total
		End Function

		Public Function consultarTudo(sSQL As [String], sCondicaoTotal As [String], progressoLog As IProgressoLog) As List(Of Diretorio)
			Dim obj As Diretorio
			Dim lista As New List(Of Diretorio)()
			Dim pb As Progresso
			Dim i As Integer = 0
			Dim total As Integer = Me.consultarTotal(sSQL, sCondicaoTotal)

			conexao = Rotinas.getConexao()
			cmd = New SQLiteCommand(sSQL, conexao)
			dr = cmd.ExecuteReader()

			If total > 0 Then
				pb = New Progresso()
				pb.Minimo = 0
				pb.Maximo = total - 1
				pb.Posicao = 0
				pb.Passo = 1

				While dr.Read()
					obj = novoObjeto(dr)

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

		Private Sub atribuirCampos(cmd As SQLiteCommand, obj As Diretorio)
			cmd.Parameters.AddWithValue("@1", obj.Aba.Codigo)
			cmd.Parameters.AddWithValue("@2", obj.Codigo)
			cmd.Parameters.AddWithValue("@3", obj.Ordem)
			cmd.Parameters.AddWithValue("@4", obj.CodDirPai)
			cmd.Parameters.AddWithValue("@5", obj.Nome)
			cmd.Parameters.AddWithValue("@6", obj.Tamanho)
			cmd.Parameters.AddWithValue("@7", obj.Tipo.Codigo.ToString())
			cmd.Parameters.AddWithValue("@8", Rotinas.formataDate(Rotinas.FORMATO_DATAHORA, obj.Modificado))
			cmd.Parameters.AddWithValue("@9", obj.Atributos)
			cmd.Parameters.AddWithValue("@10", obj.Caminho)
		End Sub

		Public Function incluir(obj As Diretorio) As Integer
			Dim ret As Integer

			Try
				conexao = Rotinas.getConexao()
				cmd = New SQLiteCommand("insert into Diretorios(aba, cod, ordem, coddirpai, nome, tam," & " tipo, modificado, atributos, caminho)" & " values (@1,@2,@3,@4,@5,@6,@7,@8,@9,@10)", conexao)
				atribuirCampos(cmd, obj)
				cmd.Prepare()
				ret = cmd.ExecuteNonQuery()
			Catch generatedExceptionName As Exception
				Throw
			End Try

			Return ret
		End Function

		Public Function excluir(aba As Aba, sCaminho As String) As Integer
			Dim ret As Integer
			conexao = Rotinas.getConexao()

			cmd = New SQLiteCommand("delete from Diretorios where caminho like @1 and aba=@2", conexao)
			cmd.Parameters.AddWithValue("@1", sCaminho & "%")
			cmd.Parameters.AddWithValue("@2", aba.Codigo)
			cmd.Prepare()
			ret = cmd.ExecuteNonQuery()

			Return ret
		End Function

		Public Function criarTabela() As Integer
			Dim sSQL As String
			Dim ret As Integer

			sSQL = "create table if NOT EXISTS Diretorios(" & "aba int not null," & "cod int not null," & "ordem int not null," & "nome varchar(255) not null," & "tam numeric not null," & "tipo char(1) not null," & "modificado date not null," & "atributos varchar(20) not null," & "coddirpai int not null," & "caminho varchar(255) not null," & "primary key (aba, cod, ordem))"

			conexao = Rotinas.getConexao()
			cmd = New SQLiteCommand(sSQL, conexao)
			ret = cmd.ExecuteNonQuery()
			Return ret
		End Function

	End Class
End Namespace
