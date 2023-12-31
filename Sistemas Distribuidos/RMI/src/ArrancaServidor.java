import java.rmi.Naming;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class ArrancaServidor {
    public static void main(String[] args) {
        try {
            ContaBancaria contaBancaria = new ContaBancaria();
            Registry registry = LocateRegistry.createRegistry(1099);
            registry.rebind("ContaBancaria", contaBancaria);
            System.out.println("Servidor instanciado...");
        } catch (Exception e) {
            System.out.println("Ocorreu um problema no arranque do servidor.\n"+e.toString());
        }
    }
}