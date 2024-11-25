#include "DateTime.h"
#include "Rotinas.h"

#include <sstream>

namespace hfsguardadir {

namespace comum {

//---------------------------------------------------------------------------
DateTime::DateTime()
{
    this->setNow();
}
//---------------------------------------------------------------------------
DateTime::DateTime(const time_t rawTempo)
{
    this->RawTempo = rawTempo;
    //this->InfoTempo = localtime(&this->RawTempo);
	localtime_s((struct tm * const)&this->InfoTempo, &this->RawTempo);
    atribuirCampos();
}
DateTime::DateTime(GDateTime *gdatahora)
{
	gint dia, mes, ano, hora, min, seg;
	//gint dia = g_date_time_get_day_of_month(gdatahora);
	//gint mes = g_date_time_get_month(gdatahora);
	g_date_time_get_ymd(gdatahora, &ano, &mes, &dia);
	hora = g_date_time_get_hour(gdatahora);
	min = g_date_time_get_minute(gdatahora);
	seg = g_date_time_get_second(gdatahora);


	new DateTime(dia, mes, ano, hora, min, seg);
}
//---------------------------------------------------------------------------
DateTime::DateTime(unsigned int dia, unsigned int mes, unsigned int ano)
{
    new DateTime(dia, mes, ano, 0, 0, 0);
}
//---------------------------------------------------------------------------
DateTime::DateTime(unsigned int dia, unsigned int mes, unsigned int ano,
	unsigned int hora, unsigned int minuto, unsigned int segundo)
{
    this->setNow();

    this->InfoTempo.tm_mday = dia;
    this->InfoTempo.tm_mon = mes - 1;
    this->InfoTempo.tm_year = ano - 1900;
    this->InfoTempo.tm_hour = hora;
    this->InfoTempo.tm_min = minuto;
    this->InfoTempo.tm_sec = segundo;

    atribuirCampos();
}
//---------------------------------------------------------------------------
DateTime::~DateTime()
{
	//delete this->InfoTempo;
}
//---------------------------------------------------------------------------
DateTime DateTime::FromDateTime(unsigned int dia, unsigned int mes, unsigned int ano, 
	unsigned int hora, unsigned int minuto, unsigned int segundo)
{
    DateTime *dt = new DateTime(dia, mes, ano, hora, minuto, segundo);

    return *dt;
}
//---------------------------------------------------------------------------
DateTime DateTime::StrToDateTime(const std::string &texto)
{
    DateTime dt;
    std::string parte;
    int conta = 0;

    if (texto.length() > 0){

        for (unsigned int i = 0; i < texto.length(); i++){
            parte += texto[i];
            conta++;

            if (texto[i]=='/' && conta == 3){
                dt.InfoTempo.tm_mday = Rotinas::StrToInt(parte);
                parte = "";
            }
            if (texto[i]=='/' && conta == 6){
				dt.InfoTempo.tm_mon = Rotinas::StrToInt(parte);
				dt.InfoTempo.tm_mon -= 1;
                parte = "";
            }
            if (texto[i]==' ' && conta == 11){
				dt.InfoTempo.tm_year = Rotinas::StrToInt(parte);
				dt.InfoTempo.tm_year -= 1900;
                parte = "";
            }
            if (texto[i]==':' && conta == 14){
				dt.InfoTempo.tm_hour = Rotinas::StrToInt(parte);
                parte = "";
            }
            if (texto[i]==':' && conta == 17){
				dt.InfoTempo.tm_min = Rotinas::StrToInt(parte);
                parte = "";
            }
            if (conta > 18 && conta < 20){
				dt.InfoTempo.tm_sec = Rotinas::StrToInt(parte);
                parte = "";
            }
        }
		dt.atribuirCampos();
    }

    return dt;
}
//---------------------------------------------------------------------------
std::string DateTime::FormatDateTime(const std::string &formato)
{
    char tempo[20];
	std::stringstream retorno;

	tempo[0] = '\0';
    retorno << "";

    if (formato == Rotinas::FORMATO_DATAHORA){	
        strftime(tempo, 20, "%d/%m/%Y %H:%M:%S", &this->InfoTempo);
        retorno << tempo;
    }
	if (formato == Rotinas::FORMATO_DHARQUIVO) {
		strftime(tempo, 20, "%Y-%m-%d_%H_%M_%S", &this->InfoTempo);
		retorno << tempo;
	}
	if (formato == Rotinas::FORMATO_DATA){
        strftime(tempo, 11, "%d/%m/%Y", &this->InfoTempo);
        retorno << tempo;
    }
    if (formato == Rotinas::FORMATO_HORA) {
        strftime(tempo, 11, "%H:%M:%S", &this->InfoTempo);
        retorno << tempo;
    }

	return retorno.str();
}
//---------------------------------------------------------------------------
DateTime DateTime::Now()
{
	DateTime dt;
	return dt;
}
//---------------------------------------------------------------------------
void DateTime::setNow()
{
	this->RawTempo = time(0);
	//this->InfoTempo = *(localtime(&this->RawTempo));
	localtime_s((struct tm * const)&this->InfoTempo, &this->RawTempo);
	this->atribuirCampos();
}
//---------------------------------------------------------------------------
struct tm DateTime::RawToInfo(const time_t rawTempo)
{
    struct tm *infoTempo;
    //infoTempo = localtime(&rawTempo);
	localtime_s((struct tm * const)&infoTempo, &rawTempo);

    return *infoTempo;
}
//---------------------------------------------------------------------------
time_t DateTime::InfoToRaw(const struct tm infoTempo)
{
    time_t rawTempo;
    struct tm localTempo;

    localTempo = (struct tm)infoTempo;

    rawTempo = mktime(&localTempo);
    return rawTempo;
}
//---------------------------------------------------------------------------
void DateTime::atribuirCampos(){
    this->dia = this->InfoTempo.tm_mday;
    this->mes = this->InfoTempo.tm_mon + 1;
    this->ano = this->InfoTempo.tm_year + 1900;
    this->hora = this->InfoTempo.tm_hour;
    this->minuto = this->InfoTempo.tm_min;
    this->segundo = this->InfoTempo.tm_sec;
}
//---------------------------------------------------------------------------
DateTime DateTime::RawToDateTime(const time_t rawTempo)
{
    DateTime *dt = new DateTime(rawTempo);
    return *dt;
}
//---------------------------------------------------------------------------
bool DateTime::operator==(const DateTime & dt)
{
	return (this->dia == dt.dia &&
	this->mes == dt.mes &&
	this->ano == dt.ano &&
	this->hora == dt.hora &&
	this->minuto == dt.minuto &&
	this->segundo == dt.segundo);
}
//---------------------------------------------------------------------------
std::string DateTime::toString() 
{
	return FormatDateTime(Rotinas::FORMATO_DATAHORA);
}

}
}
