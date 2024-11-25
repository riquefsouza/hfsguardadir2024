'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 03/07/2015
' * Time: 14:29
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 


Namespace objetos
	''' <summary>
	''' Description of ConexaoParams.
	''' </summary>
	Public Class ConexaoParams
		Private m_nome As String
		Private m_driver As String
		Private m_url As String
		Private m_login As String
		Private m_senha As String

		Public Sub New()
			Me.m_nome = ""
			Me.m_driver = ""
			Me.m_url = ""
			Me.m_login = ""
			Me.m_senha = ""
		End Sub

		Public Property Nome() As String
			Get
				Return m_nome
			End Get
			Set
				m_nome = value
			End Set
		End Property

		Public Property Driver() As String
			Get
				Return m_driver
			End Get
			Set
				m_driver = value
			End Set
		End Property

		Public Property Url() As String
			Get
				Return m_url
			End Get
			Set
				m_url = value
			End Set
		End Property

		Public Property Login() As String
			Get
				Return m_login
			End Get
			Set
				m_login = value
			End Set
		End Property

		Public Property Senha() As String
			Get
				Return m_senha
			End Get
			Set
				m_senha = value
			End Set
		End Property
	End Class
End Namespace
