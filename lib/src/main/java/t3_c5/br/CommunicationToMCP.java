package t3_c5.br;
import java.io.FileReader;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.lang.ClassNotFoundException;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class CommunicationToMCP {
 





 DataProcessing b = new DataProcessing();
      //JSONParser jsonparser= new JSONParser();
      String json =  "{commmandsto: [{ client_type: ccp,message: AKIN,client_id: BRXX, timestamp: 2019-09-07T15:50+00Z},{client_type: ccp,message: STAT,client_id: BRXX,timestamp: 2019-09-07T15:50+00Z},{client_type: ccp,message: EXEC,client_id: BRXX,timestamp: 2019-09-07T15:50+00Z,action: SLOW},{client_type: ccp, message: EXEC, client_id: BRXX, timestamp: 2019-09-07T15:50+00Z, action: FAST}, {client_type: ccp, message: EXEC,client_id: BRXX,timestamp: 2019-09-07T15:50+00Z,action: STOP},{client_type: ccp,message: DOOR,client_id: BRXX,timestamp: 2019-09-07T15:50+00Z, action: OPEN}, {client_type: ccp,message: DOOR,client_id: BRXX,timestamp: 2019-09-07T15:50+00Z,action: CLOSE}]}";
    //FileReader reader = new FileReader(".\\main\\java\\t3_c5\\commands.json");

       // Object obj= jsonparser.parse(reader);

         JSONObject obj = new JSONObject(json);

         JSONArray array = (JSONArray) obj.get("commandsto");
 CommunicationFromMCP c = new CommunicationFromMCP();
 

   //  CarriageControlProgram a = new CarriageControlProgram();

   
    String clienttype;
    String message;
    String client_id;
    String timestamp;
    String action;
    String station_id;

    // public static void main(String[] args) {
    // c.recieveMessages(Jobj)
    // }

    void sendMessagesStat(JSONObject array){
        // array.put(clienttype,"client_type");
        //         array.put(message,"message");
        //          array.put(timestamp, "timestamp");
        //          array.put(client_id,"client_id");
        //          array.put(timestamp, "timestamp");
        //          array.put(action,"action");
        //          array.put(station_id,"station_id");
        b.storeCarriageData(array);
        // or a.toMCPStatus();
         }

}
