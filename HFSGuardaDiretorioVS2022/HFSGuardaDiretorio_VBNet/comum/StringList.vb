'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 03/07/2015
' * Time: 15:19
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.IO
Imports System.Collections.Generic

Namespace comum
	''' <summary>
	''' Description of StringList.
	''' </summary>
	Public Class StringList
		Inherits List(Of String)
		Public Sub New()
		End Sub

		Public Sub New(capacidadeInicial As Integer)
			Me.Capacity = capacidadeInicial
		End Sub

		Public Sub New(str As String, separador As Char)

			If str.IndexOf(separador) > 0 Then
				Dim partes As Char() = str.ToCharArray()
				Dim pedaco As String = ""
				For i As Integer = 0 To partes.Length - 1
					pedaco += partes(i)
					If partes(i) = separador Then
						MyBase.Add(pedaco.Substring(0, pedaco.Length - 1))
						pedaco = ""
					End If
				Next
				MyBase.Add(pedaco)
			End If
		End Sub

		Public Sub New(texto As String)
			Dim pedacos As String() = texto.Split(ControlChars.Lf)
			MyBase.AddRange(pedacos)
		End Sub

		Public Function getText() As String
			Dim ret As String = ""

			For i As Integer = 0 To MyBase.Count - 1
				ret += Me(i)
			Next

			Return ret
		End Function

		Public Sub LoadFromFile(arquivo As String)
			Dim fileStream As FileStream = Nothing
			Dim reader As StreamReader = Nothing
			Dim linha As [String] = Nothing

			Try
				fileStream = New FileStream(arquivo, FileMode.Open, FileAccess.Read)
				reader = New StreamReader(fileStream)
				While (InlineAssignHelper(linha, reader.ReadLine())) IsNot Nothing
					Me.Add(linha)
				End While
			Finally
				If reader IsNot Nothing Then
					reader.Close()
				End If
			End Try
		End Sub

		Public Sub SaveToFile(arquivo As [String])
			Dim fileStream As FileStream = Nothing
			Dim writer As StreamWriter = Nothing
			Try
				fileStream = New FileStream(arquivo, FileMode.OpenOrCreate, FileAccess.Write)
				writer = New StreamWriter(fileStream)
				For Each linha As [String] In Me
					writer.WriteLine(linha)
					writer.Flush()
				Next
			Finally
				If writer IsNot Nothing Then
					writer.Close()
				End If
			End Try
		End Sub
		Private Shared Function InlineAssignHelper(Of T)(ByRef target As T, value As T) As T
			target = value
			Return value
		End Function

	End Class
End Namespace
