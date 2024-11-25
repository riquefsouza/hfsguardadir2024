'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 11/12/2014
' * Time: 11:11
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.Drawing
Imports System.Windows.Forms
Imports HFSGuardaDiretorio.objetos

Namespace gui
	''' <summary>
	''' Description of FrmInfoDiretorio.
	''' </summary>
	Public Partial Class FrmInfoDiretorio
		Inherits Form
		Private fonte As Font

		Public Sub New()
			'
			' The InitializeComponent() call is required for Windows Forms designer support.
			'
			InitializeComponent()

			fonte = New Font(lvInfo.Items(0).Font, FontStyle.Bold)
		End Sub

		Private Sub BtnOkClick(sender As Object, e As EventArgs)
			Me.Close()
		End Sub

		Public Sub setDiretorio(diretorio As Diretorio)
			If diretorio IsNot Nothing Then
				lvInfo.Items(0).SubItems.Add(diretorio.Aba.Nome)
				lvInfo.Items(1).SubItems.Add(diretorio.Nome)
				lvInfo.Items(2).SubItems.Add(diretorio.TamanhoFormatado)
				lvInfo.Items(3).SubItems.Add(diretorio.Tipo.Nome)
				lvInfo.Items(4).SubItems.Add(diretorio.ModificadoFormatado)
				lvInfo.Items(5).SubItems.Add(diretorio.Atributos)
				lvInfo.Items(6).SubItems.Add(diretorio.Caminho)

				lvInfo.Columns(1).Width = diretorio.Caminho.Length * 8
			End If
		End Sub


		Private Sub LvInfoDrawColumnHeader(sender As Object, e As DrawListViewColumnHeaderEventArgs)
			e.DrawDefault = True
		End Sub

		Private Sub LvInfoDrawItem(sender As Object, e As DrawListViewItemEventArgs)
			e.DrawBackground()

			If (e.State And ListViewItemStates.Selected) = ListViewItemStates.Selected Then
				e.Graphics.FillRectangle(SystemBrushes.Highlight, e.Bounds)
				e.Item.ForeColor = SystemColors.HighlightText
			Else
				e.Item.ForeColor = SystemColors.WindowText
			End If

			e.Item.Font = fonte

			e.DrawText()
		End Sub

		Private Sub LvInfoDrawSubItem(sender As Object, e As DrawListViewSubItemEventArgs)
			e.DrawBackground()

			If (e.ItemState And ListViewItemStates.Selected) = ListViewItemStates.Selected Then
				e.Graphics.FillRectangle(SystemBrushes.Highlight, e.Bounds)
				e.SubItem.ForeColor = SystemColors.HighlightText
			Else
				e.SubItem.ForeColor = SystemColors.WindowText
			End If

			e.DrawText()
		End Sub
	End Class
End Namespace
