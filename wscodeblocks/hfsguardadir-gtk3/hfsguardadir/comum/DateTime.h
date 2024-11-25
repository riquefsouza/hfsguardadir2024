#ifndef DATETIME_H
#define DATETIME_H
//---------------------------------------------------------------------------
#include "../../resource.h"
//---------------------------------------------------------------------------
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

typedef struct SDateTime* DateTime;
//---------------------------------------------------------------------------
DateTime DateTime_aloca();
gboolean DateTime_comparar(const DateTime dt1, const DateTime dt2);
DateTime DateTime_raw(const time_t rawTempo);
DateTime DateTime_data(int dia, int mes, int ano);
DateTime DateTime_datahora(int dia, int mes, int ano, int hora, int minuto, int segundo);
DateTime DateTime_StrToDateTime(const char* texto);
void DateTime_FormatDateTime(const DateTime dateTime, const char* formato, char* retorno);
DateTime DateTime_Today();
DateTime DateTime_Now();

struct tm *DateTime_RawToInfo(const time_t rawTempo);
time_t DateTime_InfoToRaw(const struct tm *infoTempo);
DateTime DateTime_atribuirCampos(const DateTime dt);


#endif // DATETIME_H
