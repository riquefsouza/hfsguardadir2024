#ifndef DATETIME_H
#define DATETIME_H

#include <time.h>

struct SDateTime {
	int dia;
	int mes;
	int ano;
	int hora;
	int minuto;
	int segundo;

	time_t RawTempo;
	struct tm *InfoTempo;
};

typedef struct SDateTime DateTime;

//---------------------------------------------------------------------------
DateTime DateTime_copiar(DateTime dateTime);
BOOL DateTime_comparar(DateTime dateTime1, DateTime dateTime2);

DateTime* DateTime_aloca();
DateTime DateTime_raw(const time_t rawTempo);
DateTime DateTime_data(int dia, int mes, int ano);
DateTime DateTime_datahora(int dia, int mes, int ano, int hora, int minuto, int segundo);
DateTime DateTime_StrToDateTime(LPCWSTR texto);
void DateTime_FormatDateTime(const DateTime dateTime, LPCWSTR formato, LPWSTR retorno);
DateTime* DateTime_Today();
DateTime DateTime_Now();

struct tm *DateTime_RawToInfo(const time_t rawTempo);
time_t DateTime_InfoToRaw(const struct tm *infoTempo);
DateTime* DateTime_atribuirCampos(DateTime* dt);

#endif // DATETIME_H
