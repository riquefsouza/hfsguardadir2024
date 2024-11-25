'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 03/07/2015
' * Time: 14:41
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 


Namespace objetos
	''' <summary>
	''' Description of Importar.
	''' </summary>
	Public Class Importar
		Private m_aba As Integer
		Private m_codDirRaiz As Integer
		Private m_rotuloRaiz As String
		Private m_nomeDirRaiz As String
		Private m_caminho As String

		Public Sub New()
			Me.m_aba = 0
			Me.m_codDirRaiz = 0
			Me.m_rotuloRaiz = ""
			Me.m_nomeDirRaiz = ""
			Me.m_caminho = ""
		End Sub

		Public Property Aba() As Integer
			Get
				Return m_aba
			End Get
			Set
				m_aba = value
			End Set
		End Property

		Public Property CodDirRaiz() As Integer
			Get
				Return m_codDirRaiz
			End Get
			Set
				m_codDirRaiz = value
			End Set
		End Property

		Public Property RotuloRaiz() As String
			Get
				Return m_rotuloRaiz
			End Get
			Set
				m_rotuloRaiz = value
			End Set
		End Property

		Public Property NomeDirRaiz() As String
			Get
				Return m_nomeDirRaiz
			End Get
			Set
				m_nomeDirRaiz = value
			End Set
		End Property

		Public Property Caminho() As String
			Get
				Return m_caminho
			End Get
			Set
				m_caminho = value
			End Set
		End Property

	End Class
End Namespace
