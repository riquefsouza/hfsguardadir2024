'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 03/07/2015
' * Time: 14:53
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports HFSGuardaDiretorio.objetos

Namespace comum
	''' <summary>
	''' Description of DiretorioXML.
	''' </summary>
	Public Class DiretorioXML
		Private m_diretorio As Diretorio

		Public Sub New()
			Me.m_diretorio = New Diretorio()
		End Sub

		Public Property Diretorio() As Diretorio
			Get
				Return m_diretorio
			End Get
			Set
				m_diretorio = value
			End Set
		End Property

	End Class
End Namespace
