package t3_c5.br;

import org.json.JSONObject;
import java.time.LocalDateTime;
import java.net.DatagramSocket;
import java.net.DatagramPacket;
import java.net.InetAddress;

public class Parser {
    
    private String doorStatus;
    private String status;
    private String stationID;
    private String ipAddress;
    private int port;

    public Parser(){

    }

    // Constructor
    public Parser(String doorStatus, String status, String stationID, String ipAddress, int port) {
        this.doorStatus = doorStatus;
        this.status = status;
        this.stationID = stationID;
        this.ipAddress = ipAddress;
        this.port = port;
    }

    // Method to create a JSON status message to send to the Master Carriage Program (MCP)
    public JSONObject toMCPStatus() {
        JSONObject statusMessage = new JSONObject();
        try {
            statusMessage.put("client_type:", "CarriageControlProgram");
            statusMessage.put("message:", "STAT");
            statusMessage.put("client_id:", "" + CommunicationMCP.client_id);
            statusMessage.put("timestamp:", LocalDateTime.now());
            statusMessage.optString("status:", this.status);
            statusMessage.optString("station_id:", this.stationID);
        } catch (Exception e) {
            System.out.println("Error creating status JSON: " + e.getMessage());
        }
        return statusMessage;
    }

    // Method to parse incoming JSON commands from the Master Carriage Program (MCP)
    public void fromMCP(JSONObject execCommand) {
        try {
            String action = execCommand.optString("action:");
            String message = execCommand.getString("message:");
            
            if (action != null && !action.isEmpty()) {
                DataProcessing.processCarriageCommand("" + action);
                sendUdpPacket(action);  // Send action as a UDP packet
            } else if(message.trim().equals("STAT")) {
                DataProcessing.processCarriageCommand("" + message);
                sendUdpPacket(message);  // Send STAT message as a UDP packet
            } else {
                CommunicationMCP.setMessage("" + message);
                sendUdpPacket(message);  // Send any other message as a UDP packet
            }
        } catch (Exception e) {
            System.out.println("Error processing execution JSON: " + e.getMessage());
        }
    }

    // Method to send a UDP packet
    private void sendUdpPacket(String message) {
        try {
            DatagramSocket socket = new DatagramSocket();
            byte[] buffer = message.getBytes();
            InetAddress address = InetAddress.getByName(ipAddress);
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length, address, port);
            socket.send(packet);
            socket.close();
        } catch (Exception e) {
            System.out.println("Error sending UDP packet: " + e.getMessage());
        }
    }

    public void receiveUdpPacket() {
        try {
            DatagramSocket socket = new DatagramSocket(port);  // Listen on the same port
            byte[] buffer = new byte[1024];  // Buffer to store received data
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
            
            System.out.println("Waiting for UDP packet...");
            socket.receive(packet);  // Receive packet (blocking call)
            
            String receivedMessage = new String(packet.getData(), 0, packet.getLength());
            System.out.println("Received message: " + receivedMessage);
            
            // Update the status based on the received message
            this.status = receivedMessage.trim();  // Trim any trailing whitespace
            System.out.println("Updated status: " + this.status);
            
            socket.close();
        } catch (Exception e) {
            System.out.println("Error receiving UDP packet: " + e.getMessage());
        }
    }


    // Getters and Setters for encapsulation

    public String getDoorStatus() {
        return doorStatus;
    }

    public void setDoorStatus(String doorStatus) {
        this.doorStatus = doorStatus;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStationID() {
        return stationID;
    }

    public void setStationID(String stationID) {
        this.stationID = stationID;
    }
}
