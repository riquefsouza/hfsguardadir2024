'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 09/07/2015
' * Time: 17:06
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.Collections
Imports System.Windows.Forms

Namespace objetosgui
	''' <summary>
	''' Description of TabelaItemComparer.
	''' </summary>
	Public Class TabelaItemComparer
		Implements IComparer
		Private col As Integer
		Private ordem As SortOrder

		Public Sub New()
			col = 0
			ordem = SortOrder.Ascending
		End Sub

		Public Sub New(coluna As Integer, ordem As SortOrder)
			col = coluna
			Me.ordem = ordem
		End Sub

		Public Function Compare(x As Object, y As Object) As Integer Implements IComparer.Compare
			Dim retornoVal As Integer = -1
			retornoVal = [String].Compare(DirectCast(x, ListViewItem).SubItems(col).Text, DirectCast(y, ListViewItem).SubItems(col).Text)

			If ordem = SortOrder.Ascending Then
				retornoVal *= -1
			End If

			Return retornoVal
		End Function
	End Class
End Namespace
