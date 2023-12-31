import java.util.ArrayList;
import java.util.Collections;

public class Main {
    public static void main(String[] args) {
        int n = Teclado.leInt();
        while (n > 0) {
            ArrayList<Domino> dominoList = new ArrayList<>();

            for (int i = 0; i < n; i++) {
                String input = Teclado.leString();
                String[] dominos = input.split(" ");
                Domino domino = new Domino(Integer.parseInt(dominos[0]), Integer.parseInt(dominos[1]));
                dominoList.add(domino);
            }

            ComparadorDomino comparadorDomino = new ComparadorDomino();
            comparadorDomino.arrangeList(dominoList);
            Collections.sort(dominoList);

            comparadorDomino.setDominoList(dominoList);
            int somaCima = comparadorDomino.somaCima();
            int somaBaixo = comparadorDomino.somaBaixo();
            comparadorDomino.setDiff(somaCima - somaBaixo);
            comparadorDomino.buscarSolucao();
            n = Teclado.leInt();
        }

    }
}
