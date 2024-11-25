'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 03/07/2015
' * Time: 15:12
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 


Namespace comum
	''' <summary>
	''' Description of Progresso.
	''' </summary>
	Public Class Progresso
		Private m_minimo As Integer
		Private m_maximo As Integer
		Private m_posicao As Integer
		Private m_passo As Integer
		Private m_log As String

		Public Sub New()
			Me.m_log = ""
		End Sub

		Public Property Minimo() As Integer
			Get
				Return m_minimo
			End Get
			Set
				m_minimo = value
			End Set
		End Property

		Public Property Maximo() As Integer
			Get
				Return m_maximo
			End Get
			Set
				m_maximo = value
			End Set
		End Property

		Public Property Posicao() As Integer
			Get
				Return m_posicao
			End Get
			Set
				m_posicao = value
			End Set
		End Property

		Public Property Passo() As Integer
			Get
				Return m_passo
			End Get
			Set
				m_passo = value
			End Set
		End Property

		Public Property Log() As String
			Get
				Return m_log
			End Get
			Set
				m_log = value
			End Set
		End Property

	End Class
End Namespace
