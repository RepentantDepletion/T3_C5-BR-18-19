import java.net.DatagramSocket;
import org.checkerframework.checker.units.qual.Acceleration;

public class CCP {

    static float Time;
    static Parser input18;
    static Parser input19;
    static Parser input;
    static CommunicationMCP BR18;
    static CommunicationMCP BR19;

    public static void init(DatagramSocket socket, DatagramSocket socket2) {

        BR18 = new CommunicationMCP(socket, input18, "BR18");
        BR19 = new CommunicationMCP(socket2, input19, "BR19");

        input18 = new Parser("OFLN", "10.20.30.118", 3018, (int) (Math.random() * (10000 - 3000) + 3000));
        input19 = new Parser("OFLN", "10.20.30.119", 3019, (int) (Math.random() * (10000 - 3000) + 3000));

    }

    // DataProcessing data;
    // Acceleration accInput;

    public static void main(String args[]) {

        Time = System.currentTimeMillis();

        try {
            // CCPStatus status;
            DatagramSocket socket = new DatagramSocket(3018);
            // CommunicationMCP BR18= new CommunicationMCP(socket);

            DatagramSocket socket2 = new DatagramSocket(3019);
            // CommunicationMCP BR19= new CommunicationMCP(socket2);

            init(socket, socket2);

            BR18.handshake(); // handshake for br18
            BR19.handshake(); // handshake for br19

            BR18.recievePacket();
            BR18.sendPacket(input18.toMCP(input18.receiveUdpPacket()));

            BR19.recievePacket();
            BR19.sendPacket(input19.toMCP(input19.receiveUdpPacket()));


        } catch (java.net.SocketException e) {
            System.err.println(e);
        }
    }

    public void heartbeat() {

        while (Time % 2 == 0) {
            input18.receiveUdpPacket();
            BR18.sendPacket(input18.toMCP(input18.receiveUdpPacket()));

            input19.receiveUdpPacket();
            BR19.sendPacket(input19.toMCP(input19.receiveUdpPacket()));
        }
    }

    public void call() {

        BR18.recievePacket();
        input18.fromMCP(BR18.recieved);

        BR19.recievePacket();
        input19.fromMCP(BR19.recieved);
    }

}
