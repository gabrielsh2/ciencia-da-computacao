import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class ContaBancaria extends UnicastRemoteObject implements InterfaceContaBancaria {
    private double saldo;

    public ContaBancaria() throws RemoteException {
        super();
        saldo = 0.0;
        System.out.println("Novo Servidor instanciado...");
    }

    public void deposita(double valor) throws RemoteException {
        saldo += valor;
        System.out.println("Depósito de R$ " + valor);
    }

    public void retira(double valor) throws RemoteException {
        if (saldo >= valor) {
            saldo -= valor;
            System.out.println("Saque de R$ " + valor);
        } else {
            System.out.println("Saldo insuficiente");
        }
    }

    public double saldo() throws RemoteException {
        return saldo;
    }
}
