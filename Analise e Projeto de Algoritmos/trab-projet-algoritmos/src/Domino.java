public class Domino implements Comparable<Domino> {
    private int ladoX;
    private int ladoY;
    private int removerDiff;
    private int inverterDiff;

    public Domino(int ladoX, int ladoY) {
        this.ladoX = ladoX;
        this.ladoY = ladoY;
        removerDiff = ladoX - ladoY;
        inverterDiff = removerDiff * 2;
    }

    public int getLadoX() {
        return ladoX;
    }

    public int getLadoY() {
        return ladoY;
    }

    public int getRemoverDiff() {
        return removerDiff;
    }

    public int getInverterDiff() {
        return inverterDiff;
    }

    public void inverter() {
        int aux = ladoX;
        ladoX = ladoY;
        ladoY = aux;
        removerDiff = ladoX - ladoY;
        inverterDiff = removerDiff * 2;
    }

    @Override
    public String toString() {
        return "Domino{" +
                "ladoX=" + ladoX +
                ", ladoY=" + ladoY +
                '}';
    }

    @Override
    public int compareTo(Domino o) {
        return this.inverterDiff - o.getInverterDiff();
    }
}
