package t3_c5.br;
import org.json.JSONObject;

public class CommunicationFromMCP{
        JSONParser jsonparser= new JSONParser();

        FileReader reader = new JSONParser(".\\main\java\t3_c5\commands.json");

        Object obj= jsonparser.parse(reader);

        JSONObject commands = (JSONObject)obj;





        void recieveMessages(JSONObject data){
            
        }
        void recieveCommands(){
              String akin= obj.get()

        }



}