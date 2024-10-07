package t3_c5.br;

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
    public void fromMCP(JSONObject execCommand) {
        try {
            String action = execCommand.optString("action:");
            String message = execCommand.getString("message:");

            switch(message){

            case "EXEC":
                sendUdpPacket(action); // Send action as a UDP packet
                break;
            case "STRQ":
                sendUdpPacket(message); // Send STAT message as a UDP packet
                break;
            case "AKIN":
                break;
            case "ASKT":
                break;
            default:
                toMCP("NOIP");
                break;
            }

            sequenceNumber++;

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
            DatagramSocket socket = new DatagramSocket(port); // Listen on the same port
            byte[] buffer = new byte[1024]; // Buffer to store received data
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length);

            System.out.println("Waiting for UDP packet...");
            socket.receive(packet); // Receive packet (blocking call)

            String receivedMessage = new String(packet.getData(), 0, packet.getLength());
            System.out.println("Received message: " + receivedMessage);

            // Update the status based on the received message
            this.status = receivedMessage.trim(); // Trim any trailing whitespace
            System.out.println("Updated status: " + this.status);

            socket.close();
        } catch (Exception e) {
            System.out.println("Error receiving UDP packet: " + e.getMessage());
        }
    }

    // Getters and Setters for encapsulation
    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public int getSequenceNumber(){
        return sequenceNumber;
    }

    public void setSequenceNumber(int sequence){
        this.sequenceNumber = sequence;
    }
}
