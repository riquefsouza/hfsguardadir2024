'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 07/07/2015
' * Time: 10:55
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.Collections.Generic
Imports HFSGuardaDiretorio.comum
Imports HFSGuardaDiretorio.objetos

Namespace objetosbo
	''' <summary>
	''' Description of ImportarBO.
	''' </summary>
	Public NotInheritable Class ImportarBO
		Private Shared m_instancia As New ImportarBO()

		Public Shared ReadOnly Property Instancia() As ImportarBO
			Get
				Return m_instancia
			End Get
		End Property

		Private Sub New()
		End Sub

		Public Sub CarregarListaDiretorios(importar As Importar, dirOrdem As DiretorioOrdem, listaDiretorio As List(Of Diretorio), progressoLog As IProgressoLog)
			Dim arquivo As Arquivo
			Dim diretorio As Diretorio
			Dim pb As New Progresso()

			arquivo = New Arquivo()
			arquivo.Nome = importar.RotuloRaiz
			arquivo.Tamanho = 0
			arquivo.Modificado = DateTime.Now
			arquivo.Atributos = "[DIR]"

			diretorio = DiretorioBO.Instancia.atribuiDiretorio(importar.Aba, importar.CodDirRaiz, importar.NomeDirRaiz, "", True, listaDiretorio, _
				arquivo, dirOrdem)

			listaDiretorio.Add(diretorio)
			pb.Log = importar.Caminho

			DiretorioBO.Instancia.ImportarDiretorio(importar.Aba, importar.CodDirRaiz, importar.NomeDirRaiz, importar.Caminho, listaDiretorio, dirOrdem, _
				progressoLog)

			If progressoLog IsNot Nothing Then
				progressoLog.ProgressoLog(pb)
			End If
		End Sub

		Public Sub ImportacaoCompleta(importar As Importar, dirOrdem As DiretorioOrdem, listaExtensao As List(Of Extensao), progressoLog As IProgressoLog)
			Dim listaDiretorio As New List(Of Diretorio)()

			Try
				CarregarListaDiretorios(importar, dirOrdem, listaDiretorio, progressoLog)

				'
'		        //Por ser multiplataforma nao tem funcao para pegar icone de arquivo        
'		        ExtensaoBO.Instancia.salvarExtensoes(listaDiretorio,
'		                listaExtensao, progressoLog);
'		        

				DiretorioBO.Instancia.salvarDiretorio(listaDiretorio, progressoLog)

				listaDiretorio.Clear()
			Catch generatedExceptionName As Exception
				Throw
			End Try

		End Sub

	End Class
End Namespace
