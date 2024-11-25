'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 03/07/2015
' * Time: 14:47
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 


Namespace objetos
	''' <summary>
	''' Description of DiretorioOrdem.
	''' </summary>
	Public Class DiretorioOrdem
		Private m_ordem As Integer

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
