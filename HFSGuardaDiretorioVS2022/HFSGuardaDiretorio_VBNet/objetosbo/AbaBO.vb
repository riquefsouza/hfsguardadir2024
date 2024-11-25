'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 06/07/2015
' * Time: 14:53
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.Collections.Generic
Imports HFSGuardaDiretorio.comum
Imports HFSGuardaDiretorio.objetos
Imports HFSGuardaDiretorio.objetosdao

Namespace objetosbo
	''' <summary>
	''' Description of AbaBO.
	''' </summary>
	Public NotInheritable Class AbaBO
		Private Shared m_instancia As New AbaBO()

		Public Shared ReadOnly Property Instancia() As AbaBO
			Get
				Return m_instancia
			End Get
		End Property

		Private Sub New()
		End Sub

		Public Function carregarAba(progressoLog As IProgressoLog) As List(Of Aba)
			Return AbaDAO.Instancia.consultarTudo(progressoLog)
		End Function

		Public Function retMaxCodAba(listaLocal As List(Of Aba)) As Integer
			Dim nMaior As Integer = 0
			For Each aba As Aba In listaLocal
				If aba.Codigo > nMaior Then
					nMaior = aba.Codigo
				End If
			Next
			Return nMaior + 1
		End Function

		Public Function abaToSQL(aba As Aba) As String
			Return "insert into Abas(cod, nome) values(" & aba.Codigo & "," & Rotinas.QuotedStr(aba.Nome) & ")"
		End Function

		Public Function incluirAba(aba As Aba) As Boolean
			Return (AbaDAO.Instancia.incluir(aba) > 0)
		End Function

		Public Function alterarAba(aba As Aba) As Boolean
			Return (AbaDAO.Instancia.alterar(aba) > 0)
		End Function

		Public Function excluirAba(aba As Aba) As Boolean
			Return (AbaDAO.Instancia.excluir(aba.Codigo) > 0)
		End Function

		Public Function criarTabelaAbas() As Boolean
			Return (AbaDAO.Instancia.criarTabela() > 0)
		End Function

		Public Function pegaAbaPorOrdem(lista As List(Of Aba), ordem As Integer) As Aba
			For Each aba As Aba In lista
				If aba.Ordem = ordem Then
					Return aba
				End If
			Next
			Return Nothing
		End Function

		Public Function getElemento(lista As List(Of Aba), codigo As Integer) As Aba
			For Each elemento As Aba In lista
				If elemento.Codigo = codigo Then
					Return elemento
				End If
			Next
			Return Nothing
		End Function

		Public Function pegaAbaPorNome(lista As List(Of Aba), nome As String) As Aba
			For Each aba As Aba In lista
				If aba.Nome.Equals(nome) Then
					Return aba
				End If
			Next
			Return Nothing
		End Function

	End Class
End Namespace
