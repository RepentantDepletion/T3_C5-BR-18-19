import org.json.JSONObject;
import java.net.DatagramSocket;
import java.net.DatagramPacket;
import java.net.InetAddress;

public class Parser {

    private String status;
    private String ipAddress;
    private int port;
    private int sequenceNumber;

    public Parser() {

    }

    // Constructor
    public Parser(String status, String ipAddress, int port, int sequence) {
        this.status = status;
        this.ipAddress = ipAddress;
        this.port = port;
        this.sequenceNumber = sequence;
    }

    // Method to create a JSON status message to send to the Master Carriage Program
    // (MCP)
    public JSONObject toMCP(String message) {
        JSONObject statusMessage = new JSONObject();
        try {
            statusMessage.put("client_type:", "CCP");
            statusMessage.put("message:", message);
            statusMessage.put("client_id:", CommunicationMCP.client_id);
            statusMessage.put("sequence_number:", sequenceNumber);

            if (message.trim().equals("STAT")) {
                statusMessage.put("status:", this.status);
            }
            sequenceNumber++;
        } catch (Exception e) {
            System.out.println("Error creating status JSON: " + e.getMessage());
        }
        return statusMessage;
    }

    // Method to parse incoming JSON commands from the Master Carriage Program (MCP)
    public void fromMCP(JSONObject Command) {
        try {
            String action = Command.optString("action:");
            String message = Command.getString("message:");

            switch (message) {

                case "EXEC":
                    sendUdpPacket(action); // Send action as a UDP packet
                    break;
                case "STRQ":
                    sendUdpPacket(message); // Send STRQ message as a UDP packet
                    break;
                case "AKIN":
                    break;
                case "ASKT":
                    break;
                default:
                    toMCP("NOIP"); // Create a NOIP message
                    break;
            }

            sequenceNumber++;

        } catch (Exception e) {
            System.out.println("Error processing execution JSON: " + e.getMessage());
        }
    }

    // Method to send a UDP packet
    public void sendUdpPacket(String message) {
        int retryCount = 0;
        boolean success = false;

        while (retryCount < 5 && !success) {
            try {
                DatagramSocket socket = new DatagramSocket();
                byte[] buffer = message.getBytes();
                InetAddress address = InetAddress.getByName(ipAddress);
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length, address, port);
                socket.send(packet);
                socket.close();
                success = true; // Packet sent successfully, exit loop.
            } catch (Exception e) {
                retryCount++;
                System.out.println("Error sending UDP packet: " + e.getMessage());
                if (retryCount >= 5) {
                    System.out.println("Connection with BR lost");
                    CommunicationMCP.sendPacket(toMCP("ERR"));
                } else {
                    System.out.println("Retrying.....");
                }
            }
        }
    }

    public String receiveUdpPacket() {
        int retryCount = 0;
        boolean success = false;
        String receivedMessage = "";
    
        while (retryCount < 5 && !success) {
            try {
                DatagramSocket socket = new DatagramSocket(port); // Listen on the same port
                socket.setSoTimeout(3000); // Set timeout to 3000 milliseconds (3 seconds)
    
                byte[] buffer = new byte[1024]; // Buffer to store received data
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
    
                System.out.println("Waiting for UDP packet...");
                socket.receive(packet); // Receive packet
    
                receivedMessage = new String(packet.getData(), 0, packet.getLength());
                System.out.println("Received message: " + receivedMessage);
                socket.close();
                success = true; // Packet received successfully, exit loop.
            } catch (java.net.SocketTimeoutException e) {
                retryCount++;
                System.out.println("Receive timed out. Retrying... (Attempt " + retryCount + ")");
                if (retryCount >= 5) {
                    System.out.println("Connection with BR lost after multiple timeouts");
                    return "ERR";
                }
            } catch (Exception e) {
                retryCount++;
                System.out.println("Error receiving UDP packet: " + e.getMessage());
                if (retryCount >= 5) {
                    System.out.println("Connection with BR lost");
                    return "ERR";
                } else {
                    System.out.println("Retrying.....");
                }
            }
        }
        return receivedMessage;
    }
    

    // Getters and Setters for encapsulation
    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public int getSequenceNumber() {
        return sequenceNumber;
    }

    public void setSequenceNumber(int sequence) {
        this.sequenceNumber = sequence;
    }
}
