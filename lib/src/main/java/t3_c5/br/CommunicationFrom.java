package t3_c5.br;
import java.io.FileReader;
import org.json.*;



public class CommunicationFrom {
    public static void main(String[] args) {
       // JSONParser jsonparser= new JSONParser();
      String json =  "{commmandsto: [{ client_type: ccp,message: AKIN,client_id: BRXX, timestamp: 2019-09-07T15:50+00Z},{client_type: ccp,message: STAT,client_id: BRXX,timestamp: 2019-09-07T15:50+00Z},{client_type: ccp,message: EXEC,client_id: BRXX,timestamp: 2019-09-07T15:50+00Z,action: SLOW},{client_type: ccp, message: EXEC, client_id: BRXX, timestamp: 2019-09-07T15:50+00Z, action: FAST}, {client_type: ccp, message: EXEC,client_id: BRXX,timestamp: 2019-09-07T15:50+00Z,action: STOP},{client_type: ccp,message: DOOR,client_id: BRXX,timestamp: 2019-09-07T15:50+00Z, action: OPEN}, {client_type: ccp,message: DOOR,client_id: BRXX,timestamp: 2019-09-07T15:50+00Z,action: CLOSE}]}";
    //FileReader reader = new FileReader(".\\main\\java\\t3_c5\\commands.json");

        //Object obj= jsonparser.parse(reader);

        JSONObject obj = new JSONObject(json);

        //JSONArray array = (JSONArray)obj.get("commandsto");

        System.err.println(obj.toString(5));

    //    // for(int i=0;array.size();i++){
    //         JSONObject commandsto = array.get(i);
    //         String clienttype =(String)commandsto.get("clienttype");
    //         String message=(String)commandsto.get("message");
    //         String client_id=(String)commandsto.get("client_id");
    //         String timestamp=(String)commandsto.get("timestamp");
    //         String action=(String)commandsto.get("action");




    //     }

        
    }
 




        void recieveMessages(JSONObject data){
            

        }
        void recieveCommands(){
              

        }
}
