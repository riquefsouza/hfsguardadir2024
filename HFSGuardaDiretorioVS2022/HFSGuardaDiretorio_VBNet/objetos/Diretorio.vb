'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 10/12/2014
' * Time: 17:48
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 


Namespace objetos
	''' <summary>
	''' Description of Diretorio.
	''' </summary>
	''' 

	Public Class Diretorio
		Inherits Arquivo
		Private m_aba As Aba
		Private m_codigo As Integer
		Private m_ordem As Integer
		Private m_codDirPai As Integer
		Private m_tipo As Tipo
		Private m_caminho As String
		Private m_nomePai As String
		Private m_caminhoPai As String
		Private m_tamanhoFormatado As String
		Private m_modificadoFormatado As String
		Private m_caminhoOriginal As String

		Public Sub New()
			Me.m_aba = New Aba()
			Me.m_codigo = 0
			Me.m_ordem = 0
			Me.m_codDirPai = 0
			Me.m_tipo = New Tipo()
			Me.m_caminho = ""
			Me.m_nomePai = ""
			Me.m_caminhoPai = ""
			Me.m_tamanhoFormatado = ""
			Me.m_modificadoFormatado = ""
			Me.m_caminhoOriginal = ""
		End Sub

		Public Property Aba() As Aba
			Get
				Return m_aba
			End Get
			Set
				m_aba = value
			End Set
		End Property

		Public Property Codigo() As Integer
			Get
				Return m_codigo
			End Get
			Set
				m_codigo = value
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

		Public Property CodDirPai() As Integer
			Get
				Return m_codDirPai
			End Get
			Set
				m_codDirPai = value
			End Set
		End Property

		Public Property Tipo() As Tipo
			Get
				Return m_tipo
			End Get
			Set
				m_tipo = value
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

		Public Property NomePai() As String
			Get
				Return m_nomePai
			End Get
			Set
				m_nomePai = value
			End Set
		End Property

		Public Property CaminhoPai() As String
			Get
				Return m_caminhoPai
			End Get
			Set
				m_caminhoPai = value
			End Set
		End Property

		Public Property TamanhoFormatado() As String
			Get
				Return m_tamanhoFormatado
			End Get
			Set
				m_tamanhoFormatado = value
			End Set
		End Property

		Public Property ModificadoFormatado() As String
			Get
				Return m_modificadoFormatado
			End Get
			Set
				m_modificadoFormatado = value
			End Set
		End Property

		Public Property CaminhoOriginal() As String
			Get
				Return m_caminhoOriginal
			End Get
			Set
				m_caminhoOriginal = value
			End Set
		End Property
	End Class
End Namespace
