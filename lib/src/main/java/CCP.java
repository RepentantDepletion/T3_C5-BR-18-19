import java.net.DatagramSocket;
import org.checkerframework.checker.units.qual.Acceleration;

public class CCP {

    static float Time;
    static Parser input;
    static CommunicationMCP BR18;
    static CommunicationMCP BR19;

    public static void init(DatagramSocket socket, DatagramSocket socket2) {

        input = new Parser();

        BR18 = new CommunicationMCP(socket, input, "BR18");
        BR19 = new CommunicationMCP(socket2, input, "BR19");

    }

    // DataProcessing data;
    Acceleration accInput;

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

        } catch (java.net.SocketException e) {
            System.err.println(e);
        }
    }
}
