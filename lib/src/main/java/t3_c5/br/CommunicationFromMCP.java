package t3_c5.br;
import java.io.FileReader;
import org.json.*;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.lang.ClassNotFoundException;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;


public class CommunicationFromMCP {
    // public static void main(String[] args) {
    //    // JSONParser jsonparser= new JSONParser();
    //   //String json =  "{commmandsto: [{ client_type: ccp,message: AKIN,client_id: BRXX, timestamp: 2019-09-07T15:50+00Z},{client_type: ccp,message: STAT,client_id: BRXX,timestamp: 2019-09-07T15:50+00Z},{client_type: ccp,message: EXEC,client_id: BRXX,timestamp: 2019-09-07T15:50+00Z,action: SLOW},{client_type: ccp, message: EXEC, client_id: BRXX, timestamp: 2019-09-07T15:50+00Z, action: FAST}, {client_type: ccp, message: EXEC,client_id: BRXX,timestamp: 2019-09-07T15:50+00Z,action: STOP},{client_type: ccp,message: DOOR,client_id: BRXX,timestamp: 2019-09-07T15:50+00Z, action: OPEN}, {client_type: ccp,message: DOOR,client_id: BRXX,timestamp: 2019-09-07T15:50+00Z,action: CLOSE}]}";
    // //FileReader reader = new FileReader(".\\main\\java\\t3_c5\\commands.json");

    //     //Object obj= jsonparser.parse(reader);

    // //     JSONObject obj = new JSONObject(json);

    // //     JSONArray array = (JSONArray)obj.get("commandsto");

    // //     System.err.println(obj.toString(5));
        

    //  }
    // read message and check if akin, if so run handshake 
    public static void setMessage(String Message) {
        message = Message;
    }


void handshakeBR18(){
    try {
            InetAddress host = InetAddress.getLocalHost();
            Socket ccpsocket = new Socket("10.20.30.1", 3018);
            Socket mcpsocket = new Socket("10.20.30.118", 3018);
            ObjectInputStream ois = new ObjectInputStream(mcpsocket.getInputStream());

            String message = (String) ois.readObject();
            System.out.println("Message: " + message);

            ois.close();
        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

    }

    void handshakeBR19(){
        try {
                InetAddress host = InetAddress.getLocalHost();
                Socket ccpsocket = new Socket("10.20.30.1", 3018);
                Socket mcpsocket = new Socket("10.20.30.119", 3018);
                ObjectInputStream ois = new ObjectInputStream(mcpsocket.getInputStream());
    
                String message = (String) ois.readObject();
                System.out.println("Message: " + message);
    
                ois.close();
            } catch (UnknownHostException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
    
        }


    String clienttype;
    static String message;
    String client_id;
    String timestamp;
    String action;
    String station_id;


        public void recieveMessages(JSONObject array){
                this.clienttype =(String)array.get("clienttype");
                this.message=(String)array.get("message");
                this.client_id=(String)array.get("client_id");
                this.timestamp=(String)array.get("timestamp");
                this.action=(String)array.get("action");
        }


}
