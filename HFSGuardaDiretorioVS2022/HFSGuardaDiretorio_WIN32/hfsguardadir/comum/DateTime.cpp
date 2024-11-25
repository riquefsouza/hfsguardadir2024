#include "stdafx.h"

#include "DateTime.h"
#include "Rotinas.h"

DateTime DateTime_copiar(DateTime datetime) {
	DateTime ldatetime;

	ldatetime.dia = datetime.dia;
	ldatetime.mes = datetime.mes;
	ldatetime.ano = datetime.ano;
	ldatetime.hora = datetime.hora;
	ldatetime.minuto = datetime.minuto;
	ldatetime.segundo = datetime.segundo;
	ldatetime.RawTempo = datetime.RawTempo;
	ldatetime.InfoTempo = datetime.InfoTempo;

	return ldatetime;
}

BOOL DateTime_comparar(DateTime datetime1, DateTime datetime2) {
	return
		(datetime1.dia == datetime2.dia
			&& datetime1.mes == datetime2.mes
			&& datetime1.ano == datetime2.ano
			&& datetime1.hora == datetime2.hora
			&& datetime1.minuto == datetime2.minuto
			&& datetime1.segundo == datetime2.segundo);
}

// ---------------------------------------------------------------------------
DateTime* DateTime_aloca() {
    DateTime* dt;

    dt = (DateTime*) malloc(sizeof(DateTime*));
	dt->InfoTempo = (struct tm *)malloc(sizeof(struct tm *));

    return dt;
}
//---------------------------------------------------------------------------
DateTime DateTime_raw(const time_t rawTempo)
{
	DateTime* dt = DateTime_aloca();

    dt->RawTempo = rawTempo;
    //dt->InfoTempo = localtime(&dt->RawTempo);
	localtime_s((struct tm * const)&dt->InfoTempo, &dt->RawTempo);
    dt = DateTime_atribuirCampos(dt);

	return *dt;
}
//---------------------------------------------------------------------------
DateTime DateTime_datahora(int dia, int mes, int ano, int hora, int minuto, int segundo)
{
	DateTime* dt;

    dt = DateTime_Today();

    dt->InfoTempo->tm_mday = dia;
    dt->InfoTempo->tm_mon = mes - 1;
    dt->InfoTempo->tm_year = ano - 1900;
    dt->InfoTempo->tm_hour = hora;
    dt->InfoTempo->tm_min = minuto;
    dt->InfoTempo->tm_sec = segundo;

    dt = DateTime_atribuirCampos(dt);

	return *dt;
}
//---------------------------------------------------------------------------
DateTime DateTime_data(int dia, int mes, int ano)
{
	return DateTime_datahora(dia, mes, ano, 0, 0, 0);
}
//---------------------------------------------------------------------------
DateTime DateTime_StrToDateTime(String texto)
{
    unsigned int i = 0;
    DateTime* dt;
    String parte;
    int conta = 0;

    if (texto.length > 0){

        dt = DateTime_aloca();
		parte = String_iniciar("");

        for (i = 0; i < texto.length; i++){
			parte = String_concatenar(parte, texto.str[i]);
            conta++;

            if (texto.str[i]=='/' && conta == 3){
                dt->InfoTempo->tm_mday = String_ToInt(parte);
				parte = String_limpar();
				//wcscpy_s(parte, 1, _T(""));
            }
            if (texto.str[i]=='/' && conta == 6){
                dt->InfoTempo->tm_mon = String_ToInt(parte);
                dt->InfoTempo->tm_mon -= 1;
				parte = String_limpar();
				//wcscpy_s(parte, 1, _T(""));
			}
            if (texto.str[i]==' ' && conta == 11){
                dt->InfoTempo->tm_year = String_ToInt(parte);
                dt->InfoTempo->tm_year -= 1900;
				parte = String_limpar();
				//wcscpy_s(parte, 1, _T(""));
			}
            if (texto.str[i]==':' && conta == 14){
                dt->InfoTempo->tm_hour = String_ToInt(parte);
				parte = String_limpar();
				//wcscpy_s(parte, 1, _T(""));
			}
            if (texto.str[i]==':' && conta == 17){
                dt->InfoTempo->tm_min = String_ToInt(parte);
				parte = String_limpar();
				//wcscpy_s(parte, 1, _T(""));
			}
            if (conta > 18 && conta < 20){
                dt->InfoTempo->tm_sec = String_ToInt(parte);
				parte = String_limpar();
				//wcscpy_s(parte, 1, _T(""));
			}
        }
        dt = DateTime_atribuirCampos(dt);
    }

    return *dt;
}
//---------------------------------------------------------------------------
void DateTime_FormatDateTime(const DateTime dateTime, String formato, String retorno)
{
	String tempo = String_iniciar("");

    if (String_comparar(formato, Rotinas_FORMATO_DATAHORA)){
		wcsftime(tempo.wstr, 20, _T("%d/%m/%Y %H:%M:%S"), dateTime.InfoTempo);
		retorno = String_iniciar(tempo.wstr);
    }
	if (String_comparar(formato, Rotinas_FORMATO_DHARQUIVO)) {
		wcsftime(tempo.wstr, 20, _T("%Y-%m-%d_%H_%M_%S"), dateTime.InfoTempo);
		retorno = String_iniciar(tempo.wstr);
	}
	if (String_comparar(formato, Rotinas_FORMATO_DATA)){
		wcsftime(tempo.wstr, 11, _T("%d/%m/%Y"), dateTime.InfoTempo);
		retorno = String_iniciar(tempo.wstr);
	}
    if (String_comparar(formato, Rotinas_FORMATO_HORA)){
		wcsftime(tempo.wstr, 11, _T("%H:%M:%S"), dateTime.InfoTempo);
		retorno = String_iniciar(tempo.wstr);
	}
    //return retorno;
}
//---------------------------------------------------------------------------
DateTime* DateTime_Today()
{
	DateTime* dt;
    time_t rawtime;
    struct tm *info;

    time( &rawtime );
    //info = localtime( &rawtime );
	localtime_s((struct tm * const)&info, &rawtime);

    dt = DateTime_aloca();
    dt->RawTempo = rawtime;
    dt->InfoTempo = info;

    dt = DateTime_atribuirCampos(dt);

	return dt;
}
//---------------------------------------------------------------------------
DateTime DateTime_Now()
{
    DateTime* dt = DateTime_Today();

    return *dt;
}
//---------------------------------------------------------------------------
struct tm * DateTime_RawToInfo(const time_t rawTempo)
{
    struct tm *infoTempo;
    //infoTempo = localtime(&rawTempo);
	localtime_s((struct tm * const)&infoTempo, &rawTempo);
	
    return infoTempo;
}
//---------------------------------------------------------------------------
time_t DateTime_InfoToRaw(const struct tm *infoTempo)
{
    time_t rawTempo;
    struct tm *localTempo;

    localTempo = (struct tm *)infoTempo;

    rawTempo = mktime(localTempo);
    return rawTempo;
}
//---------------------------------------------------------------------------
DateTime* DateTime_atribuirCampos(DateTime* dt){
	//DateTime* dt = DateTime_aloca();

    dt->dia = dt->InfoTempo->tm_mday;
    dt->mes = dt->InfoTempo->tm_mon + 1;
    dt->ano = dt->InfoTempo->tm_year + 1900;
    dt->hora = dt->InfoTempo->tm_hour;
    dt->minuto = dt->InfoTempo->tm_min;
    dt->segundo = dt->InfoTempo->tm_sec;

	return dt;
}

