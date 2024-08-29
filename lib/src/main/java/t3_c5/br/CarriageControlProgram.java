package lib.src.main.java.t3_c5.br;
// File path: src/main/java/CarriageControlProgram.java

import org.json.JSONObject;

public class CarriageControlProgram {
    
    private float speed;
    private String doorStatus;
    private String status;
    private String sensorStatus;
    private float batteryLevel;
    private String stationID;
    
    // Constructor
    public CarriageControlProgram(float speed, String doorStatus, String status, String sensorStatus, float batteryLevel, String stationID) {
        this.speed = speed;
        this.doorStatus = doorStatus;
        this.status = status;
        this.sensorStatus = sensorStatus;
        this.batteryLevel = batteryLevel;
        this.stationID = stationID;
    }

    // Method to create a JSON status message to send to the Master Carriage Program (MCP)
    public JSONObject toMCPStatus() {
        JSONObject statusMessage = new JSONObject();
        try {
            statusMessage.put("client_type", "CarriageControlProgram");
            statusMessage.put("message", "Status Update");
            statusMessage.put("client_id", "Carriage123");
            statusMessage.put("timestamp", System.currentTimeMillis() / 1000L);
            statusMessage.put("door_status", this.doorStatus);
            statusMessage.put("battery_level", this.batteryLevel);
            statusMessage.put("station_id", this.stationID);
            statusMessage.put("speed", this.speed);
            statusMessage.put("sensor_status", this.sensorStatus);
        } catch (Exception e) {
            System.out.println("Error creating status JSON: " + e.getMessage());
        }
        return statusMessage;
    }

    // Method to parse incoming JSON commands from the Master Carriage Program (MCP)
    public void fromMCPExec(JSONObject execCommand) {
        try {
            String action = execCommand.optString("action");
            if (action != null && !action.isEmpty()) {
                switch (action) {
                    case "update_speed":
                        this.speed = (float) execCommand.getDouble("speed");
                        break;
                    case "open_door":
                        this.doorStatus = "open";
                        break;
                    case "close_door":
                        this.doorStatus = "closed";
                        break;
                    case "update_status":
                        this.status = execCommand.getString("status");
                        break;
                    case "update_sensor_status":
                        this.sensorStatus = execCommand.getString("sensor_status");
                        break;
                    default:
                        System.out.println("Unknown action: " + action);
                }
            }
        } catch (Exception e) {
            System.out.println("Error processing execution JSON: " + e.getMessage());
        }
    }

    // Getters and Setters for encapsulation
    public float getSpeed() {
        return speed;
    }

    public void setSpeed(float speed) {
        this.speed = speed;
    }

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

    public String getSensorStatus() {
        return sensorStatus;
    }

    public void setSensorStatus(String sensorStatus) {
        this.sensorStatus = sensorStatus;
    }

    public float getBatteryLevel() {
        return batteryLevel;
    }

    public void setBatteryLevel(float batteryLevel) {
        this.batteryLevel = batteryLevel;
    }

    public String getStationID() {
        return stationID;
    }

    public void setStationID(String stationID) {
        this.stationID = stationID;
    }
}
