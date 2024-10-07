package t3_c5.br;

import org.json.*;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.lang.ClassNotFoundException;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.net.DatagramSocket;
import java.net.DatagramPacket;

public class CommunicationMCP {

    String clienttype;
    static String message;
    static String client_id;
    String timestamp;
    String action;
    String station_id;

    DatagramSocket socket;

    Parser THECCP;

    JSONObject recieved;

    public CommunicationMCP(DatagramSocket socket, Parser THECCP, String client_id) {
        this.socket = socket;
        this.THECCP = THECCP;

    }

    // read message and check if akin, if so run handshake
    public static void setMessage(String Message) {
        message = Message;
    }

    void handshake() {
        try {
            // use parser method to send json init with CCIN messae
            JSONObject sendJson = THECCP.toMCP("CCIN");
            // Convert JSON object to byte array
            byte[] sendBuffer = sendJson.toString().getBytes();

            // Get the IP address and port
            InetAddress address = InetAddress.getByName("10.20.30.1");
            int port = 2000;

            // Create a DatagramPacket to send
            DatagramPacket sendPacket = new DatagramPacket(sendBuffer, sendBuffer.length, address, port);

            // Create a DatagramSocket
            // DatagramSocket socket = new DatagramSocket();

            // Send the packet
            socket.send(sendPacket);

            // overrided sendpacket from to be the message sent from MCP
            socket.receive(sendPacket);

            // Convert the received data to a JSON object
            String receivedData = new String(sendPacket.getData(), 0, sendPacket.getLength());
            JSONObject receiveJson = new JSONObject(receivedData);

            // Check if the received JSON matches the expected values
            if (receiveJson.getString("client_type").equals("CCP") &&
                    receiveJson.getString("message").equals("AKIN") &&
                    receiveJson.getString("client_id").equals("BR18") &&
                    receiveJson.getString("sequence_number").equals("s_mcp")) {
                System.out.println("Received expected JSON response.");
            } else {
                System.out.println("Received unexpected JSON response: " + receiveJson.toString());
            }
            // Close the socket
            socket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void recievePacket() {
        try {
            // Create a socket to listen on the port.
            // Buffer to receive incoming data
            byte[] buffer = new byte[1024];

            // Create a packet to receive data into the buffer. buffer.length is the number
            // of bytes
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length);

            System.out.println("Waiting for packet...");

            // Receive the packet
            socket.receive(packet);

            String jsonString = new String(packet.getData(), 0, packet.getLength());

            System.out.println("Received JSON: " + jsonString);

            // Parse JSON string to JSONObject
            JSONObject jsonObject = new JSONObject(jsonString);

            recieved = jsonObject;

        } catch (Exception e) {
            e.printStackTrace();
        }
        // return recieved;
    }

    void sendPacket(JSONObject isaac) {

        recieveMessages(recieved);

        if (message == "STRQ") {
            // send status message
            THECCP.toMCP(message);
        } else if (message == "EXEC") {
            // send Acknowledge Command
            THECCP.fromMCP(recieved);

        }

        return;
    }

    public void recieveMessages(JSONObject array) {
        this.clienttype = (String) array.get("clienttype");
        CommunicationMCP.message = (String) array.get("message");
        CommunicationMCP.client_id = (String) array.get("client_id");
        this.timestamp = (String) array.get("timestamp");
        this.action = (String) array.get("action");
    }

}
