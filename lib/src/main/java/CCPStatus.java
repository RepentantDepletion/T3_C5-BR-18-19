//package t3_c5.br;

import org.json.JSONObject;
import java.util.HashMap;
import java.util.Map;

public class CCPStatus {

    private CarriageControlProgram carriageControlProgram;
    private DoorControl doorControl;
    private SpeedTracking speedTracking;
    private SensorFeedback sensorFeedback;
    //private BatteryManagement batteryManagement;
    private Map<String, Object> componentData;

    // Constructor
    public CCPStatus(CarriageControlProgram carriageControlProgram) {
        this.carriageControlProgram = carriageControlProgram;
        this.doorControl = new DoorControl();
        this.speedTracking = new SpeedTracking();
        this.sensorFeedback = new SensorFeedback();
        //this.batteryManagement = new BatteryManagement();
        this.componentData = new HashMap<>();
    }

    // Method to store data from Carriage Control Program
    public void storeCarriageData() {
        try {
            componentData.put("speed", speedTracking.getSpeed());
            componentData.put("doorStatus", doorControl.getDoorStatus());
            componentData.put("status", carriageControlProgram.getStatus());
            componentData.put("sensorStatus", sensorFeedback.getSensorStatus());
            //componentData.put("batteryLevel", batteryManagement.getBatteryLevel());
            componentData.put("stationID", carriageControlProgram.getStationID());
        } catch (Exception e) {
            System.out.println("Error storing carriage data: " + e.getMessage());
        }
    }

    // Method to sift through data and prepare for MCP
    public JSONObject prepareDataForMCP() {
        JSONObject mcpData = new JSONObject();
        try {
            mcpData.put("speed", componentData.getOrDefault("speed", 0.0f));
            mcpData.put("doorStatus", componentData.getOrDefault("doorStatus", "unknown"));
            mcpData.put("status", componentData.getOrDefault("status", "unknown"));
            mcpData.put("sensorStatus", componentData.getOrDefault("sensorStatus", "unknown"));
            //mcpData.put("batteryLevel", componentData.getOrDefault("batteryLevel", 0.0f));
            mcpData.put("stationID", componentData.getOrDefault("stationID", "unknown"));

            if (componentData.containsKey("feedback")) {
                mcpData.put("feedback", componentData.get("feedback"));
            }
        } catch (Exception e) {
            System.out.println("Error preparing data for MCP: " + e.getMessage());
        }
        return mcpData;
    }

    // Method to create command messages to MCP
    public JSONObject createMCPCommand(String commandType, Map<String, Object> params) {
        JSONObject command = new JSONObject();
        try {
            command.put("client_type", "ccp");
            command.put("client_id", "CC01");
            command.put("message", commandType);

            for (Map.Entry<String, Object> entry : params.entrySet()) {
                command.put(entry.getKey(), entry.getValue());
            }
        } catch (Exception e) {
            System.out.println("Error creating MCP command: " + e.getMessage());
        }
        return command;
    }

    // Method to execute commands received from MCP
    public void executeCommandFromMCP(JSONObject command) {
        try {
            String action = command.optString("action");
            if (action != null && !action.isEmpty()) {
                carriageControlProgram.fromMCPExec(command); // Handle general actions in CarriageControlProgram

                // Handle specific component actions
                switch (action) {
                    case "OPEN":
                        doorControl.openDoor();
                        break;
                    case "CLOSE":
                        doorControl.closeDoor();
                        break;
                    case "SLOW":
                        speedTracking.setSpeed((float) command.getDouble("speed"));
                        break;
                    case "update_sensor_status":
                        sensorFeedback.updateSensorStatus(command.getString("sensor_status"));
                        break;
                    //case "update_battery":
                        //batteryManagement.setBatteryLevel((float) command.getDouble("battery_level"));
                        //break;
                    default:
                        System.out.println("Unknown command received from MCP: " + action);
                        break;
                }
            } else {
                System.out.println("Invalid command received from MCP.");
            }
        } catch (Exception e) {
            System.out.println("Error executing command from MCP: " + e.getMessage());
        }
    }

    // Main method for demonstration
    public static void main(String[] args) {
        // Initialize CarriageControlProgram with some test values
        CarriageControlProgram carriageControl = new CarriageControlProgram(25.0f, "closed", "running", "normal", 85.0f, "ST01");
        CCPStatus ccpStatus = new CCPStatus(carriageControl);

        // Store carriage data
        ccpStatus.storeCarriageData();

        // Prepare data for MCP
        JSONObject mcpData = ccpStatus.prepareDataForMCP();
        System.out.println("Prepared data for MCP: " + mcpData.toString());

        // Create a command to send to MCP
        Map<String, Object> params = new HashMap<>();
        params.put("timestamp", System.currentTimeMillis());
        JSONObject command = ccpStatus.createMCPCommand("STAT", params);
        System.out.println("Command to MCP: " + command.toString());

        // Execute a command received from MCP
        JSONObject execCommand = new JSONObject();
        execCommand.put("action", "OPEN");
        ccpStatus.executeCommandFromMCP(execCommand);

        // Print updated door status
        System.out.println("Updated Door Status: " + ccpStatus.doorControl.getDoorStatus());
    }
}