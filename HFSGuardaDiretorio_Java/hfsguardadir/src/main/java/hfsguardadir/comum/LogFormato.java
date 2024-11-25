package hfsguardadir.comum;

import java.util.Date;
import java.util.logging.Formatter;
import java.util.logging.LogRecord;

public class LogFormato extends Formatter {

    @Override
    public String format(LogRecord rec) {
        StringBuilder buf = new StringBuilder(1000);
        buf.append(Rotinas.formataDate(Rotinas.FORMATO_DATAHORA, new Date())
                + " " + rec.getLevel().toString() + ": "
                + formatMessage(rec) + "\n");
        return buf.toString();
    }

}
