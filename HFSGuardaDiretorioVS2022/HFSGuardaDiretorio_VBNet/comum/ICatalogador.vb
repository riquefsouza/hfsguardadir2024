'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 03/07/2015
' * Time: 14:54
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports HFSGuardaDiretorio.objetos

Namespace comum
	''' <summary>
	''' Description of ICatalogador.
	''' </summary>
	Public Interface ICatalogador
		Function getAbaSelecionada() As Aba
		Sub DuploCliqueLista(nome As String, tipo As String)
		Sub EncontrarItemLista(nomeAba As String, nome As String, caminho As String)
	End Interface
End Namespace
