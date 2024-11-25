'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 11/12/2014
' * Time: 11:24
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.IO
Imports System.Drawing
Imports System.Collections.Generic
Imports System.Windows.Forms
Imports HFSGuardaDiretorio.comum
Imports HFSGuardaDiretorio.objetos
Imports HFSGuardaDiretorio.objetosbo
Imports HFSGuardaDiretorio.objetosgui
Imports HFSGuardaDiretorio.catalogador

Namespace gui
	''' <summary>
	''' Description of FrmImportarDiretorio.
	''' </summary>
	Public Partial Class FrmImportarDiretorio
		Inherits Form
		Private ReadOnly frmPrincipal As FrmPrincipal
		Private ReadOnly frmImportarDiretorioProgresso As FrmImportarDiretorioProgresso
		Private ReadOnly catalogador As catalogador.Catalogador

		Public bSubDiretorio As Boolean
		Public listaImportar As List(Of Importar)
		Public listaDiretorio As List(Of Diretorio)

		Public Sub New(frmPrincipal As FrmPrincipal)
			'
			' The InitializeComponent() call is required for Windows Forms designer support.
			'
			InitializeComponent()

			frmImportarDiretorioProgresso = New FrmImportarDiretorioProgresso(Me)
			listaImportar = New List(Of Importar)()

			Me.frmPrincipal = frmPrincipal
			catalogador = frmPrincipal.Catalogador
		End Sub

		Private Sub FrmImportarDiretorioShown(sender As Object, e As EventArgs)
			Dim sLog As String

			For Each importar As Importar In Me.listaImportar
				catalogador.diretorioOrdem.Ordem = 1

				If Not bSubDiretorio Then
					Cursor = Cursors.WaitCursor

					Try
						ImportarBO.Instancia.ImportacaoCompleta(importar, catalogador.diretorioOrdem, catalogador.listaExtensoes, frmImportarDiretorioProgresso)
					Catch ex As Exception
						Dialogo.mensagemErro(ex.Message)
					End Try

					Cursor = Cursors.[Default]
				Else
					If Not DiretorioBO.Instancia.verificaCodDir(importar.Aba, importar.RotuloRaiz, catalogador.listaDiretorioPai) Then
						Cursor = Cursors.WaitCursor

						Try
							ImportarBO.Instancia.ImportacaoCompleta(importar, catalogador.diretorioOrdem, catalogador.listaExtensoes, frmImportarDiretorioProgresso)
						Catch ex As Exception
							Dialogo.mensagemErro(ex.Message)
						End Try

						Cursor = Cursors.[Default]
					Else
						Dialogo.mensagemInfo("O diretório já existe no catálogo!")
					End If
				End If
			Next

			If frmPrincipal.menuGravarLogImportacao.Selected Then
				If memoImportaDir.Lines.Length > 0 Then
					sLog = Rotinas.ExtractFilePath(Application.ExecutablePath) & Path.DirectorySeparatorChar & Rotinas.formataDate(Rotinas.FORMATO_DHARQUIVO, DateTime.Now) & "_Importacao.log"

					Dim log As New StringList()
					log.AddRange(memoImportaDir.Lines)
					log.SaveToFile(sLog)
				End If
			End If

			Me.Close()

		End Sub

	End Class
End Namespace
