package t3_c5.br;

import java.net.DatagramSocket;

import org.checkerframework.checker.units.qual.Acceleration;

public class CCP {

    static float Time;
    CarriageControlProgram input;

   // CommunicationFromMCP mcpInput;
  //  CommunicationToMCP mcpOutput;

    DataProcessing data;
    Acceleration accInput;

    public static void main(String args[]) {

        Time = System.currentTimeMillis();
        
    DatagramSocket socket = new DatagramSocket(3018);
    CommunicationMCP BR18= new CommunicationMCP(socket);

    DatagramSocket socket2 = new DatagramSocket(3019);
    CommunicationMCP BR19= new CommunicationMCP(socket2);

    BR18.handshake();
    BR19.handshake();

        
        // Sensor senInput;
        // CCPStatus status;
    }
}
