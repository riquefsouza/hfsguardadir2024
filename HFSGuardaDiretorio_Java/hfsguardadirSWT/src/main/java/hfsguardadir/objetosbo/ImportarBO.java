package hfsguardadir.objetosbo;

import hfsguardadir.comum.IProgressoLog;
import hfsguardadir.comum.Progresso;
import hfsguardadir.objetos.Arquivo;
import hfsguardadir.objetos.Diretorio;
import hfsguardadir.objetos.DiretorioOrdem;
import hfsguardadir.objetos.Extensao;
import hfsguardadir.objetos.Importar;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Date;

public class ImportarBO {

    private static ImportarBO instancia;

    private ImportarBO() {
        super();
    }

    public static ImportarBO getInstancia() {
        if (instancia == null) {
            instancia = new ImportarBO();
        }
        return instancia;
    }

    public void CarregarListaDiretorios(Importar importar,
            DiretorioOrdem dirOrdem, ArrayList<Diretorio> listaDiretorio,
            IProgressoLog progressoLog) {
        Arquivo arquivo;
        Diretorio diretorio;
        Progresso pb = new Progresso();

        arquivo = new Arquivo();
        arquivo.setNome(importar.getRotuloRaiz());
        arquivo.setTamanho(0);
        arquivo.setModificado(new Date());
        arquivo.setAtributos("[DIR]");

        diretorio = DiretorioBO.getInstancia().atribuiDiretorio(
                importar.getAba(), importar.getCodDirRaiz(),
                importar.getNomeDirRaiz(), "", true, listaDiretorio,
                arquivo, dirOrdem);

        listaDiretorio.add(diretorio);
        pb.setLog(importar.getCaminho());

        DiretorioBO.getInstancia().ImportarDiretorio(importar.getAba(),
                importar.getCodDirRaiz(), importar.getNomeDirRaiz(),
                importar.getCaminho(), listaDiretorio, dirOrdem, progressoLog);

        if (progressoLog != null) {
            progressoLog.ProgressoLog(pb);
        }        
    }

    public void ImportacaoCompleta(Importar importar, DiretorioOrdem dirOrdem,
            ArrayList<Extensao> listaExtensao,
            IProgressoLog progressoLog) throws SQLException {
        ArrayList<Diretorio> listaDiretorio = new ArrayList<>();

        CarregarListaDiretorios(importar, dirOrdem, listaDiretorio, progressoLog);

        /*
        //Por ser multiplataforma não tem função para pegar icone de arquivo        
        ExtensaoBO.getInstancia().salvarExtensoes(listaDiretorio,
                listaExtensao, progressoLog);
        */                
        DiretorioBO.getInstancia().salvarDiretorio(listaDiretorio, 
                progressoLog);

        listaDiretorio.clear();
    }

}
