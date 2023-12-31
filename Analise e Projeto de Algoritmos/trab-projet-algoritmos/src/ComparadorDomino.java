import java.util.ArrayList;

public class ComparadorDomino {
    ArrayList<Domino> dominoList = new ArrayList<>();
    ArrayList<Domino> listaSucesso = new ArrayList<>();
    ArrayList<ArrayList<Domino>> listaSucessoComDescarte = new ArrayList<>();
    ArrayList<Domino> listaDescarte = new ArrayList<>();
    int diff;
    int bestRemoverDiff = 0;

    public void setDiff(int diff) {
        this.diff = diff;
    }

    public void setDominoList(ArrayList<Domino> dominoList) {
        this.dominoList = dominoList;
    }

    public int somaCima() {
        int sum = 0;

        for (int i = 0; i < dominoList.size(); i++) {
            sum += dominoList.get(i).getLadoX();
        }

        return sum;
    }

    public int somaBaixo() {
        int sum = 0;

        for (int i = 0; i < dominoList.size(); i++) {
            sum += dominoList.get(i).getLadoY();
        }

        return sum;
    }

    public void arrangeList(ArrayList<Domino> dominoList) {
        for (int i = 0; i < dominoList.size(); i++) {
            Domino domino = dominoList.get(i);
            if (domino.getLadoY() > domino.getLadoX()) domino.inverter();
        }

    }

    private void acabou() {
        if (listaSucesso.size() > 0) {
            for (int i = 0; i < listaSucesso.size(); i++) {
                Domino domino = listaSucesso.get(i);
                domino.inverter();
            }
            int sum = somaCima();
            System.out.println(sum + " nenhum dominó descartado");
        } else if (listaDescarte.size() > 0) {
            int bestIndex = getBestIndexResult();
            ArrayList<Domino> invertList = listaSucessoComDescarte.get(bestIndex);
            Domino discardDomino = listaDescarte.get(bestIndex);

            for (int i = 0; i < invertList.size(); i++) {
                Domino domino = invertList.get(i);
                domino.inverter();
            }

            dominoList.remove(discardDomino);

            int sum = somaCima();
            System.out.println(sum + "  descartado o dominó " + discardDomino.getLadoX() + " " + discardDomino.getLadoY());
        } else {
            System.out.println("impossível");
        }
    }

    private int getBestIndexResult() {
        int bestResult = 0;
        int bestSum = 0;

        for (int i = 0; i < listaDescarte.size(); i++) {
            int sum = somaCima();
            ArrayList<Domino> currentList = listaSucessoComDescarte.get(i);

            for (int j = 0; j < currentList.size(); j++) {
                sum -= currentList.get(j).getLadoX();
                sum += currentList.get(j).getLadoY();
            }

            sum -= listaDescarte.get(i).getLadoX();

            if (sum > bestSum) {
                bestResult = i;
            } else if (sum == bestSum) {
                Domino currentBest = listaDescarte.get(bestResult);
                Domino newBest = listaDescarte.get(i);

                if ((bestResult == 0 || newBest.getLadoX() <= newBest.getLadoY()) && newBest.getLadoX() < currentBest.getLadoX()) {
                    bestResult = i;
                }
            }
        }

        return bestResult;
    }

    private int getSomaInverter(ArrayList<Domino> tempDominoList) {
        int soma = 0;

        for (int i = 0; i < tempDominoList.size(); i++) {
            Domino domino = tempDominoList.get(i);
            soma += domino.getInverterDiff();
        }

        return soma;
    }

    private void compararValores(ArrayList<Domino> restanteAtual, ArrayList<Domino> tempDominoList) {
        if (listaSucesso.size() == 0) {
            int soma = getSomaInverter(tempDominoList);

            if (soma == diff) {
                listaSucesso.addAll(tempDominoList);
                return;
            }

            if(soma + bestRemoverDiff >= diff) {
                for (int i = 0; i < dominoList.size(); i++) {
                    if (soma + dominoList.get(i).getRemoverDiff() == diff) {
                        ArrayList<Domino> sucesso = new ArrayList<>(tempDominoList);
                        listaSucessoComDescarte.add(sucesso);
                        listaDescarte.add(dominoList.get(i));
                    }
                }
            }

            if (soma >= diff) return;
            for (int i = 0; i < restanteAtual.size(); i++) {

                ArrayList<Domino> newRestante = new ArrayList<>();
                for (int j = i + 1; j < restanteAtual.size(); j++) {
                    newRestante.add(restanteAtual.get(j));
                }

                tempDominoList.add(restanteAtual.get(i));
                compararValores(newRestante, tempDominoList);
                tempDominoList.remove(tempDominoList.size() - 1);
            }
        }
    }

    public void buscarSolucao() {
        setBestRemoverDiff();
        compararValores(dominoList, new ArrayList<>());
        acabou();
    }

    private void setBestRemoverDiff() {
        for (int i = 0; i < dominoList.size(); i++) {
            Domino domino = dominoList.get(i);
            if (domino.getRemoverDiff() > bestRemoverDiff) bestRemoverDiff = domino.getRemoverDiff();
        }
    }
}
