package t3_c5.br;
import java.net.DatagramSocket;
import org.json.JSONObject;
import java.net.DatagramPacket;
import java.net.InetAddress;



public class Main {

    private static final String SERVER_IP = "10.20.30.1";
    private static final int SERVER_PORT_BR18 = 3018;
    private static final int SERVER_PORT_BR19 = 3019;
    
    public static void main(String[] args) {
        try {
            // UDP sockets for communication
            DatagramSocket socketBR18 = new DatagramSocket(SERVER_PORT_BR18);
            DatagramSocket socketBR19 = new DatagramSocket(SERVER_PORT_BR19);

            // Initialize the Parser and CommunicationMCP for each socket
            Parser parserBR18 = new Parser();
            CommunicationMCP mcpBR18 = new CommunicationMCP(socketBR18, parserBR18, "BR18");
            CommunicationMCP mcpBR19 = new CommunicationMCP(socketBR19, parserBR19, "BR19");      // not to sure why i cant call parser or comms mcp

            //handshake with MCP
            mcpBR18.handshake();
            mcpBR19.handshake();

            // data process
            DataProcessing dataProcessing = new DataProcessing();
            initDataProcessing(dataProcessing);

            // listener
            while (true) {
                // Listen for incoming commands
                mcpBR18.recievePacket();
                String receivedCommand = mcpBR18.getMessage(); 
                executeCommand(dataProcessing, receivedCommand);

             
                JSONObject statusMessage = parserBR18.toMCP("STAT");
                mcpBR18.sendPacket(statusMessage);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    // Function to initialize DataProcessing system
    private static void initDataProcessing(DataProcessing dp) {
        initSpeedManagement(dp.speedManager);
        initDoorControl(dp.doorManager);
        initSensorFeedback(dp.sensorManager);
        System.arraycopy("Station-01".toCharArray(), 0, dp.stationID, 0, "Station-01".length());
    }

    // Function to execute commands based on received input
    private static void executeCommand(DataProcessing dp, String command) {
        switch (command) {
            case "fast":
                setSpeed(dp.speedManager, 5.0f);
                closeDoor(dp.doorManager);
                break;
            case "slow":
                setSpeed(dp.speedManager, 2.5f);
                closeDoor(dp.doorManager);
                break;
            case "reverseSlow":
                setSpeed(dp.speedManager, -2.5f);
                closeDoor(dp.doorManager);
                break;
            case "stopClose":
                setSpeed(dp.speedManager, 0);
                closeDoor(dp.doorManager);
                break;
            case "stopOpen":
                setSpeed(dp.speedManager, 0);
                openDoor(dp.doorManager);
                break;
            case "disconnect":
                sendCarriageMessage("OFLN");
                break;
            default:
                System.out.println("Unknown command: " + command);
                break;
        }
    }

    private static void setSpeed(SpeedManagement sm, float speed) {

        /////////////

    }

    private static void closeDoor(DoorControl dc) {

        ///////////
    }

    private static void openDoor(DoorControl dc) {

        /////////////
    }

    private static void sendCarriageMessage(String message) {

        ////////////
    }
}
