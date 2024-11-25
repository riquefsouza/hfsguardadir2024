'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 10/12/2014
' * Time: 17:51
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 


Namespace objetos
	''' <summary>
	''' Description of Aba.
	''' </summary>
	Public Class Aba
		Private m_codigo As Integer
		Private m_nome As String
		Private m_ordem As Integer

		Public Sub New()
			Me.m_codigo = 0
			Me.m_nome = ""
			Me.m_ordem = 0
		End Sub

		Public Sub New(codigo As Integer, nome As String, ordem As Integer)
			Me.m_codigo = codigo
			Me.m_nome = nome
			Me.m_ordem = ordem
		End Sub

		Public Property Codigo() As Integer
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

		Public Property Ordem() As Integer
			Get
				Return m_ordem
			End Get
			Set
				m_ordem = value
			End Set
		End Property

	End Class
End Namespace
