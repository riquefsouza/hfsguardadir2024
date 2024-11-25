#include "DateTime.h"
#include "Rotinas.h"

// ---------------------------------------------------------------------------
DateTime DateTime_aloca() {
    DateTime dt;

    dt = (DateTime) malloc(sizeof(struct SDateTime));
    dt->InfoTempo = (struct tm*)malloc(sizeof(struct tm));

    return dt;
}
//---------------------------------------------------------------------------
gboolean DateTime_comparar(const DateTime dt1, const DateTime dt2) {
	return (dt1->dia == dt2->dia
		&& dt1->mes == dt2->mes
		&& dt1->ano == dt2->ano
		&& dt1->hora == dt2->hora
		&& dt1->minuto == dt2->minuto
		&& dt1->segundo == dt2->segundo);
}
//---------------------------------------------------------------------------
DateTime DateTime_raw(const time_t rawTempo)
{
	DateTime dt = DateTime_aloca();

    dt->RawTempo = rawTempo;
    //dt->InfoTempo = localtime(&dt->RawTempo);
	localtime_s((struct tm * const)&dt->InfoTempo, &dt->RawTempo);
    dt = DateTime_atribuirCampos(dt);

	return dt;
}
//---------------------------------------------------------------------------
DateTime DateTime_datahora(int dia, int mes, int ano, int hora, int minuto, int segundo)
{
	DateTime dt;

    dt = DateTime_Today();

    dt->InfoTempo->tm_mday = dia;
    dt->InfoTempo->tm_mon = mes - 1;
    dt->InfoTempo->tm_year = ano - 1900;
    dt->InfoTempo->tm_hour = hora;
    dt->InfoTempo->tm_min = minuto;
    dt->InfoTempo->tm_sec = segundo;

    dt = DateTime_atribuirCampos(dt);

	return dt;
}
//---------------------------------------------------------------------------
DateTime DateTime_data(int dia, int mes, int ano)
{
	return DateTime_datahora(dia, mes, ano, 0, 0, 0);
}
//---------------------------------------------------------------------------
DateTime DateTime_StrToDateTime(const char* texto)
{
    unsigned int i = 0;
    DateTime dt = DateTime_aloca();
    char* parte;
    int conta = 0;

    if (strlen(texto) > 0){

        //dt = DateTime_aloca();
		parte = Rotinas_cNewStr(256);

        for (i = 0; i < strlen(texto); i++){
			parte += texto[i];
            conta++;

            if (texto[i]=='/' && conta == 3){
                dt->InfoTempo->tm_mday = Rotinas_cStrToInt(parte);
                parte = "";
            }
            if (texto[i]=='/' && conta == 6){
                dt->InfoTempo->tm_mon = Rotinas_cStrToInt(parte);
                dt->InfoTempo->tm_mon -= 1;
                parte = "";
            }
            if (texto[i]==' ' && conta == 11){
                dt->InfoTempo->tm_year = Rotinas_cStrToInt(parte);
                dt->InfoTempo->tm_year -= 1900;
                parte = "";
            }
            if (texto[i]==':' && conta == 14){
                dt->InfoTempo->tm_hour = Rotinas_cStrToInt(parte);
                parte = "";
            }
            if (texto[i]==':' && conta == 17){
                dt->InfoTempo->tm_min = Rotinas_cStrToInt(parte);
                parte = "";
            }
            if (conta > 18 && conta < 20){
                dt->InfoTempo->tm_sec = Rotinas_cStrToInt(parte);
                parte = "";
            }
        }
        dt = DateTime_atribuirCampos(dt);
    }

    return dt;
}
//---------------------------------------------------------------------------
void DateTime_FormatDateTime(const DateTime dateTime, const char* formato, char* retorno)
{
	//char* retorno;
    char tempo[20];

    if (strcmp(formato, "dd/mm/yyyy hh:nn:ss")==0){
        strftime(tempo, 20, "%d/%m/%Y %H:%M:%S", dateTime->InfoTempo);
        strcpy_s(retorno, sizeof retorno, tempo);
    }
    if (strcmp(formato, "dd/mm/yyyy")==0){
        strftime(tempo, 11, "%d/%m/%Y", dateTime->InfoTempo);
        strcpy_s(retorno, sizeof retorno, tempo);
    }
    if (strcmp(formato, "hh:nn:ss")==0){
        strftime(tempo, 11, "%H:%M:%S", dateTime->InfoTempo);
        strcpy_s(retorno, sizeof retorno, tempo);
    }
    //return retorno;
}
//---------------------------------------------------------------------------
DateTime DateTime_Today()
{
	DateTime dt;
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
    DateTime dt = DateTime_Today();

    return dt;
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
DateTime DateTime_atribuirCampos(const DateTime datetime){
	DateTime dt = DateTime_aloca();

    dt->dia = datetime->InfoTempo->tm_mday;
    dt->mes = datetime->InfoTempo->tm_mon + 1;
    dt->ano = datetime->InfoTempo->tm_year + 1900;
    dt->hora = datetime->InfoTempo->tm_hour;
    dt->minuto = datetime->InfoTempo->tm_min;
    dt->segundo = datetime->InfoTempo->tm_sec;

	return dt;
}
//---------------------------------------------------------------------------
