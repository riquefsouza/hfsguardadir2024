'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 07/07/2015
' * Time: 11:01
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Namespace catalogador
	''' <summary>
	''' Description of RotuloRaiz.
	''' </summary>
	Public Class RotuloRaiz
		Private m_rotulo As String

		Public Sub New()
		End Sub

		Public Property Rotulo() As String
			Get
				Return m_rotulo
			End Get
			Set
				m_rotulo = value
			End Set
		End Property

	End Class
End Namespace
