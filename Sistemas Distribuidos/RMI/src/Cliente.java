import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Cliente {
    private InterfaceContaBancaria msi;

    public Cliente()
    {

        System.out.println("Arrancando o Cliente...");
        // Vamos tentar ir aceder ao Servidor de Registos para recolher a interface
        try
        {
            Registry registry = LocateRegistry.getRegistry("localhost", 1099);
            msi = (InterfaceContaBancaria) registry.lookup("ContaBancaria");
        }
        catch (Exception e)
        {
            System.out.println("Falhou o arranque do Cliente.\n"+e);
            System.out.println("Certifique-se que tanto o Servidor de Registos como a Aplicação Servidora estão a correr correctamente.\n");
            System.exit(0);
        }

    }

    public void deposita(double valor) throws RemoteException {
        msi.deposita(valor);
    }

    public void retira(double valor) throws RemoteException {
        msi.retira(valor);
    }

    public void saldo() throws RemoteException {
        double saldo = msi.saldo();
        System.out.println("Saldo atual: R$ " + saldo);
    }

    public static void main(String[] args) {
        Cliente c = new Cliente();
        try
        {
            c.deposita(100);
            c.retira(25);
            c.saldo();
        }
        catch (Exception e)
        {
            System.out.println("Excepção durante chamadas remotas:" +e);
        }
    }
}