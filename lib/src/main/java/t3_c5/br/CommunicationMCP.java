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

    public CommunicationMCP(DatagramSocket socket){
        this.socket=socket;
        THECCP = new Parser();

    }

    // read message and check if akin, if so run handshake
    public static void setMessage(String Message) {
        message = Message;
    }

    void handshake(){
        while(true){
        try {
            // Create a socket to listen on the port.
            // Buffer to receive incoming data
            byte[] buffer = new byte[1024];
    
            // Create a packet to receive data into the buffer. buffer.length is the number of bytes
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
    
            System.out.println("Waiting for packet...");
    
            // Receive the packet
            socket.receive(packet);
    
    
            InetAddress inetAddresses = packet.getAddress();
    
            int port = packet.getPort();
    
            String jsonString = new String(packet.getData(), 0, packet.getLength());
                System.out.println("Received JSON: " + jsonString);
    
                // Parse JSON string to JSONObject
                JSONObject jsonObject = new JSONObject(jsonString);
    
                recieveMessages(jsonObject);

            //parse
            THECCP.fromMCP(jsonObject);
    
            //send back
            JSONObject sendObject = new JSONObject();

            sendObject= THECCP.toMCPStatus();
    
                // Convert JSONObject back to JSON string
                String responseJson = sendObject.toString();
    
                byte[] sendBuffer = responseJson.getBytes();
    
            
            //send back
            DatagramPacket sendback = new DatagramPacket(sendBuffer, sendBuffer.length, inetAddresses, port);
              // Convert the JSON string to a Java object
            
              // Print the received data
          
    
            socket.send(sendback);
          
    
            // Close the socket
           
        } catch (Exception e) {
            e.printStackTrace();
            break;
        }
    
        }
        }

    public void recieveMessages(JSONObject array) {
        this.clienttype = (String) array.get("clienttype");
        CommunicationMCP.message = (String) array.get("message");
        CommunicationMCP.client_id = (String) array.get("client_id");
        this.timestamp = (String) array.get("timestamp");
        this.action = (String) array.get("action");
    }

}
