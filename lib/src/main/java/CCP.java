import java.net.DatagramSocket;
import java.net.SocketException;

public class CCP {

    static Parser input18;
    static Parser input19;
    static CommunicationMCP BR18;
    static CommunicationMCP BR19;

    public static void main(String[] args) {

        try {
            DatagramSocket socket18 = new DatagramSocket(3018);
            DatagramSocket socket19 = new DatagramSocket(3019);

            // Start threads for BR18 and BR19 sending/receiving communication
            Thread br18CommThread = new Thread(new CommunicationHandler("BR18", socket18, "10.20.30.118", 3018));
            Thread br19CommThread = new Thread(new CommunicationHandler("BR19", socket19, "10.20.30.119", 3019));

            // Start threads for heartbeat
            Thread heartbeatThread = new Thread(new HeartbeatHandler());

            br18CommThread.start();
            br19CommThread.start();
            heartbeatThread.start();

            // Optionally, join threads if you want the main thread to wait for them
            // br18CommThread.join();
            // br19CommThread.join();
            // heartbeatThread.join();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

class CommunicationHandler implements Runnable {

    private CommunicationMCP br;
    private Parser input;
    private DatagramSocket socket;
    private String brName;
    private String ip;
    private int port;

    public CommunicationHandler(String brName, DatagramSocket socket, String ip, int port) {
        this.brName = brName;
        this.socket = socket;
        this.ip = ip;
        this.port = port;

        int randomPort = (int) (Math.random() * (10000 - 3000) + 3000);
        this.input = new Parser("OFLN", ip, port, randomPort);
        this.br = new CommunicationMCP(socket, input, brName);
    }

    @Override
    public void run() {
        try {
            // Handshake
            br.handshake();

            // Continuous sending and receiving of messages
            while (true) {
                br.sendPacket(input.toMCP(input.receiveUdpPacket()));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

class HeartbeatHandler implements Runnable {

    private static final int HEARTBEAT_INTERVAL = 2000; // 2 seconds

    @Override
    public void run() {
        try {
            CCP.BR18 = new CommunicationMCP(new DatagramSocket(3018), CCP.input18, "BR18");
            CCP.BR19 = new CommunicationMCP(new DatagramSocket(3019), CCP.input19, "BR19");

            CCP.input18 = new Parser("OFLN", "10.20.30.118", 3018, (int) (Math.random() * (10000 - 3000) + 3000));
            CCP.input19 = new Parser("OFLN", "10.20.30.119", 3019, (int) (Math.random() * (10000 - 3000) + 3000));
            
            while (true) {
                long currentTime = System.currentTimeMillis();

                // Perform heartbeat logic
                System.out.println("Heartbeat at: " + currentTime);

                // Simulate heartbeat logic with input18 and input19 (as in original)
                CCP.input18.receiveUdpPacket();
                CommunicationMCP.sendPacket(CCP.input18.toMCP(CCP.input18.receiveUdpPacket()));

                CCP.input19.receiveUdpPacket();
                CommunicationMCP.sendPacket(CCP.input19.toMCP(CCP.input19.receiveUdpPacket()));

                // Sleep for 2 seconds before the next heartbeat
                Thread.sleep(HEARTBEAT_INTERVAL);
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (SocketException se){
            
        }
    }
}
