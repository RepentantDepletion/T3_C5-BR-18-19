package t3_c5.br;
// File path: src/main/java/CarriageControlProgram.java

import org.json.JSONObject;
import java.time.LocalDateTime;

public class CarriageControlProgram {
    
    private String doorStatus;
    private String status;
    private String stationID;
    
    // Constructor
    public CarriageControlProgram(String doorStatus, String status, String stationID) {
        this.doorStatus = doorStatus;
        this.status = status;
        this.stationID = stationID;
    }

    // Method to create a JSON status message to send to the Master Carriage Program (MCP)
    public JSONObject toMCPStatus() {
        JSONObject statusMessage = new JSONObject();
        try {
            statusMessage.put("client_type:", "CarriageControlProgram");
            statusMessage.put("message:", "Status Update");
            statusMessage.put("client_id:", "" + CommunicationFromMCP.client_id);
            statusMessage.put("timestamp:", LocalDateTime.now());
            statusMessage.optString("status:", this.status);
            statusMessage.optString("station_id:", this.stationID);
        } catch (Exception e) {
            System.out.println("Error creating status JSON: " + e.getMessage());
        }
        return statusMessage;
    }

    // Method to parse incoming JSON commands from the Master Carriage Program (MCP)
    public void fromMCPExec(JSONObject execCommand) {
        try {
            String action = execCommand.optString("action");
            String message = execCommand.getString("message");
            if (action != null && !action.isEmpty()) {
                DataProcessing.processCarriageCommand("" + action);
            }
            else if(message.trim() == "STAT"){
                DataProcessing.processCarriageCommand("" + message);
            }
            else{
                CommunicationFromMCP.setMessage("" + message);
            }
        } catch (Exception e) {
            System.out.println("Error processing execution JSON: " + e.getMessage());
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
