'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 03/07/2015
' * Time: 14:44
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 


Namespace objetos
	''' <summary>
	''' Description of Tipo.
	''' </summary>
	Public Class Tipo
		Private m_codigo As Char
		Private m_nome As String

		Public Sub New()
			Me.m_codigo = " "C
			Me.m_nome = ""
		End Sub

		Public Sub New(codigo As Char, nome As String)
			Me.m_codigo = codigo
			Me.m_nome = nome
		End Sub

		Public Property Codigo() As Char
			Get
				Return m_codigo
			End Get
			Set
				m_codigo = value
			End Set
		End Property

		Public Property Nome() As String
			Get
				Return m_nome
			End Get
			Set
				m_nome = value
			End Set
		End Property

	End Class
End Namespace
