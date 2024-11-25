'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 10/12/2014
' * Time: 17:58
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 


Namespace objetos
	''' <summary>
	''' Description of Extensao.
	''' </summary>
	Public Class Extensao
		Private m_codigo As Integer
		Private m_nome As String
		Private m_ordem As Integer
		Private m_bmp16 As Byte()
		Private m_bmp32 As Byte()

		Public Sub New()
			Me.m_codigo = 0
			Me.m_nome = ""
			Me.m_ordem = 0
			Me.m_bmp16 = Nothing
			Me.m_bmp32 = Nothing
		End Sub

		Public Sub New(codigo As Integer, nome As [String], ordem As Integer, bmp16 As Byte(), bmp32 As Byte())
			Me.m_codigo = codigo
			Me.m_nome = nome
			Me.m_ordem = ordem
			Me.m_bmp16 = bmp16
			Me.m_bmp32 = bmp32
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

		Public Property Bmp16() As Byte()
			Get
				Return m_bmp16
			End Get
			Set
				m_bmp16 = value
			End Set
		End Property

		Public Property Bmp32() As Byte()
			Get
				Return m_bmp32
			End Get
			Set
				m_bmp32 = value
			End Set
		End Property
	End Class
End Namespace
