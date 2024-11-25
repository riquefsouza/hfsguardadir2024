package hfsguardadir.comum;

public class Progresso {
    private int minimo;
    private int maximo;
    private int posicao;
    private int passo;
    private String log;
    
    public Progresso(){
        super();
        
        this.log = "";
    }

    /**
     * @return the minimo
     */
    public int getMinimo() {
        return minimo;
    }

    /**
     * @param minimo the minimo to set
     */
    public void setMinimo(int minimo) {
        this.minimo = minimo;
    }

    /**
     * @return the maximo
     */
    public int getMaximo() {
        return maximo;
    }

    /**
     * @param maximo the maximo to set
     */
    public void setMaximo(int maximo) {
        this.maximo = maximo;
    }

    /**
     * @return the posicao
     */
    public int getPosicao() {
        return posicao;
    }

    /**
     * @param posicao the posicao to set
     */
    public void setPosicao(int posicao) {
        this.posicao = posicao;
    }

    /**
     * @return the passo
     */
    public int getPasso() {
        return passo;
    }

    /**
     * @param passo the passo to set
     */
    public void setPasso(int passo) {
        this.passo = passo;
    }

    /**
     * @return the log
     */
    public String getLog() {
        return log;
    }

    /**
     * @param log the log to set
     */
    public void setLog(String log) {
        this.log = log;
    }
}
