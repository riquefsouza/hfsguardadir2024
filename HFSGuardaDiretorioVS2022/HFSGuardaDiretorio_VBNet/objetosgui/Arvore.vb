'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 08/07/2015
' * Time: 10:51
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.Windows.Forms

Namespace objetosgui
	''' <summary>
	''' Description of Arvore.
	''' </summary>
	Public NotInheritable Class Arvore
		Private Shared m_instancia As New Arvore()

		Public Shared ReadOnly Property Instancia() As Arvore
			Get
				Return m_instancia
			End Get
		End Property

		Private Sub New()
		End Sub

		Public Function encontrarCaminhoPorNome(tvArvore As TreeView, nomes As String()) As TreeNode
			For Each item As TreeNode In tvArvore.Nodes
				If item.Text.Equals(nomes(0)) Then
					Return encontrarCaminho(item, nomes, 0)
				End If
			Next
			Return Nothing
		End Function

		Public Function encontrarCaminho(pai As TreeNode, nomes As String(), nivel As Integer) As TreeNode
			If pai.Text.Equals(nomes(nivel)) Then

				If nivel = (nomes.Length - 1) Then
					Return pai
				End If

				If pai.GetNodeCount(True) > 0 Then
					For Each filho As TreeNode In pai.Nodes
						Dim res As TreeNode = encontrarCaminho(filho, nomes, nivel + 1)

						If res IsNot Nothing Then
							Return res
						End If
					Next
				End If
			End If
			Return Nothing
		End Function

	End Class
End Namespace
