'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 10/12/2014
' * Time: 17:41
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 


Namespace objetos
	''' <summary>
	''' Description of Arquivo.
	''' </summary>
	Public Class Arquivo
		Private m_nome As String
		Private m_tamanho As Decimal
		Private m_modificado As DateTime
		Private m_atributos As String

		Public Sub New()
			Me.m_nome = ""
			Me.m_tamanho = 0
			Me.m_modificado = DateTime.Now
			Me.m_atributos = ""
		End Sub

		Public Sub New(nome As String, tamanho As Decimal, modificado As DateTime, atributos As String)
			Me.m_nome = nome
			Me.m_tamanho = tamanho
			Me.m_modificado = modificado
			Me.m_atributos = atributos
		End Sub

		Public Property Nome() As String
			Get
				Return m_nome
			End Get
			Set
				m_nome = value
			End Set
		End Property

		Public Property Tamanho() As Decimal
			Get
				Return m_tamanho
			End Get
			Set
				m_tamanho = value
			End Set
		End Property

		Public Property Modificado() As DateTime
			Get
				Return m_modificado
			End Get
			Set
				m_modificado = value
			End Set
		End Property

		Public Property Atributos() As String
			Get
				Return m_atributos
			End Get
			Set
				m_atributos = value
			End Set
		End Property


	End Class
End Namespace
