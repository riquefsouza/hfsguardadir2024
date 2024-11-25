#ifndef DATETIME_H
#define DATETIME_H

//---------------------------------------------------------------------------
#include <string>
#include <ctime>
#include <glib.h>
//---------------------------------------------------------------------------

namespace hfsguardadir {

namespace comum {

class DateTime
{
    public:
        unsigned int dia;
		unsigned int mes;
		unsigned int ano;
		unsigned int hora;
		unsigned int minuto;
		unsigned int segundo;

        DateTime();
        DateTime(const time_t rawTempo);
		DateTime(GDateTime *gdatahora);
        DateTime(unsigned int dia, unsigned int mes, unsigned int ano);
        DateTime(unsigned int dia, unsigned int mes, unsigned int ano, 
			unsigned int hora, unsigned int minuto, unsigned int segundo);
        virtual ~DateTime();
		static DateTime StrToDateTime(const std::string &texto);
        std::string FormatDateTime(const std::string &formato);
        static DateTime Now();		
		static DateTime RawToDateTime(const time_t rawTempo);
		static DateTime FromDateTime(unsigned int dia, unsigned int mes, unsigned int ano,
			unsigned int hora, unsigned int minuto, unsigned int segundo);
		bool operator==(const DateTime& dt);
		std::string toString();
    protected:
    private:
        time_t RawTempo;
        struct tm InfoTempo;

        struct tm RawToInfo(const time_t rawTempo);
        time_t InfoToRaw(const struct tm infoTempo);
		void setNow();
        void atribuirCampos();
};

}
}

#endif // DATETIME_H
