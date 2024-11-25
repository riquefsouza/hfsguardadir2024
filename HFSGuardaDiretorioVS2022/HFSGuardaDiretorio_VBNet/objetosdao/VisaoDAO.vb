'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 03/07/2015
' * Time: 17:17
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.Data
Imports System.Data.SQLite
Imports HFSGuardaDiretorio.comum

Namespace objetosdao
	''' <summary>
	''' Description of VisaoDAO.
	''' </summary>
	Public NotInheritable Class VisaoDAO
		Private Shared m_instancia As New VisaoDAO()

		Private conexao As SQLiteConnection

		Private cmd As SQLiteCommand

		Public Shared ReadOnly Property Instancia() As VisaoDAO
			Get
				Return m_instancia
			End Get
		End Property

		Private Sub New()
		End Sub

		Public Function criarVisao(visao As String) As Integer
			Dim ret As Integer
			conexao = Rotinas.getConexao()
			cmd = New SQLiteCommand(sqlVisao(visao), conexao)
			ret = cmd.ExecuteNonQuery()
			Return ret
		End Function

		Private Function sqlVisao(visao As String) As [String]
			Dim sSQL As String = "create view " & visao & " as " & "SELECT d.aba,d.cod,d.ordem,d.coddirpai,d.nome,d.tam," & "d.tipo,d.modificado,d.atributos,d.caminho" & ",(select nome as nomeaba from Abas where cod=d.aba) as nomeaba" & ",(select nome as nomepai from Diretorios where cod=d.cod " & "  and ordem=d.coddirpai and aba=d.aba) as nomepai" & ",(select caminho as caminhopai from Diretorios where cod=d.cod " & " and ordem=d.coddirpai and aba=d.aba) as caminhopai " & "FROM Diretorios d "

			If visao.Equals("consultadirpai") Then
				sSQL += "where d.tipo='D' and d.coddirpai = 0"
			ElseIf visao.Equals("consultadirfilho") Then
				sSQL += "where d.tipo='D' and d.coddirpai > 0"
			End If

			Return sSQL
		End Function

	End Class
End Namespace
