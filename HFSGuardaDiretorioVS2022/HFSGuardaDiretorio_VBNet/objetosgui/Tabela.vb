'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 08/07/2015
' * Time: 10:45
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.Collections.Generic
Imports System.Windows.Forms
Imports HFSGuardaDiretorio.comum
Imports HFSGuardaDiretorio.objetos
Imports HFSGuardaDiretorio.objetosbo

Namespace objetosgui
	''' <summary>
	''' Description of Tabela.
	''' </summary>
	Public NotInheritable Class Tabela
		Private Shared m_instancia As New Tabela()

		Public Shared ReadOnly Property Instancia() As Tabela
			Get
				Return m_instancia
			End Get
		End Property

		Private Sub New()
		End Sub

		Public Sub AdicionaItemLista(bTabelaDir As Boolean, lvTabela As ListView, dir As Diretorio, extensoes As List(Of Extensao))
			Dim item As ListViewItem

			item = lvTabela.Items.Add(dir.Nome)
			If dir.Tipo.Codigo = "D"C Then
				item.SubItems.Add("")
				item.ImageIndex = 0
			Else
				item.SubItems.Add(dir.TamanhoFormatado)
				item.ImageIndex = ExtensaoBO.Instancia.indiceExtensao(extensoes, dir.Nome)
			End If
			item.SubItems.Add(dir.Tipo.Nome)
			item.SubItems.Add(dir.ModificadoFormatado)
			item.SubItems.Add(dir.Atributos)
			item.SubItems.Add(dir.Caminho)
			If Not bTabelaDir Then
				item.SubItems.Add(dir.Aba.Nome)
			End If
		End Sub

		Public Sub Carregar(bTabelaDir As Boolean, lvTabela As ListView, diretorios As List(Of Diretorio), extensoes As List(Of Extensao), pb As ProgressBar)
			If diretorios.Count > 0 Then
				pb.Minimum = 0
				pb.Maximum = diretorios.Count
				pb.Value = 0
				pb.[Step] = 1

				For Each dir As Diretorio In diretorios
					AdicionaItemLista(bTabelaDir, lvTabela, dir, extensoes)
					pb.Value += 1
				Next
			End If
		End Sub

		Public Function encontrarLinha(lvTabela As ListView, nome As String) As Integer
			Dim slinha As String
			Dim nlinha As Integer = 0
			For i As Integer = 0 To lvTabela.Items.Count - 1
				slinha = lvTabela.Items(i).SubItems(0).Text
				If slinha.Equals(nome) Then
					nlinha = i
					Exit For
				End If
			Next
			Return nlinha
		End Function

		Public Function getLinhaSelecionada(lvTabela As ListView, bTabelaDir As Boolean) As Diretorio
			Dim dir As Diretorio = Nothing

			If lvTabela.SelectedItems.Count > 0 Then
				dir = New Diretorio()
				dir.Nome = lvTabela.SelectedItems(0).SubItems(0).Text
				dir.TamanhoFormatado = lvTabela.SelectedItems(0).SubItems(1).Text
				dir.Tipo = New Tipo("D"C, lvTabela.SelectedItems(0).SubItems(2).Text)
				dir.ModificadoFormatado = lvTabela.SelectedItems(0).SubItems(3).Text
				dir.Atributos = lvTabela.SelectedItems(0).SubItems(4).Text
				dir.Caminho = lvTabela.SelectedItems(0).SubItems(5).Text
				If bTabelaDir Then
					dir.Aba.Nome = lvTabela.SelectedItems(0).SubItems(6).Text
				End If
			End If

			Return dir
		End Function

	End Class
End Namespace
