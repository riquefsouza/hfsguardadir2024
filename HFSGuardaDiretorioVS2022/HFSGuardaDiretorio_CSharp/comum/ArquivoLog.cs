using System;
using System.IO;
using System.Text;

namespace HFSGuardaDiretorio.comum
{
	public class ArquivoLog : Log  {   
		
		private string _FileName = ""; 
		
		public string FileName   {     
			get { return this._FileName; }
			set { this._FileName = value; }   
		}   
		
		private string _FileLocation = "";   
  
		public string FileLocation   {     
			get { return this._FileLocation; }
			set      
			{        
				this._FileLocation = value;     
				if( this._FileLocation.LastIndexOf("\\") != (this._FileLocation.Length - 1) ){          
					this._FileLocation += "\\";       
				}
			}
		}
   
		public ArquivoLog()   {      
			this.FileLocation = "C:\\";
			this.FileName = "mylog.txt";   
		}

		public override void RecordMessage(Exception Message, Log.MessageType Severity)   {
			this.RecordMessage(Message.Message, Severity);   
		}   
		
		public override void RecordMessage(string Message,             
		                                   Log.MessageType Severity)   {     
			FileStream fileStream = null;     
			StreamWriter writer = null;    
			StringBuilder message = new StringBuilder();     
			try     {        
				fileStream = new FileStream(this._FileLocation +                  
				                            this._FileName, FileMode.OpenOrCreate,                  
				                            FileAccess.Write);      
				writer = new StreamWriter(fileStream);             
				writer.BaseStream.Seek(0, SeekOrigin.End);              
				message.Append(System.DateTime.Now.ToString())
					.Append(",").Append(Message);
				writer.WriteLine(message.ToString());      
				writer.Flush();     
			}     
			finally     
			{
				if( writer != null ) 
					writer.Close();
			}   
		}  
	}
}