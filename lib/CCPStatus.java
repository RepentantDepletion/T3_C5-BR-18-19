package t3_c5.br;

import org.json.JSONObject;
import java.util.HashMap;
import java.util.Map;

public class CCPStatus {

    private Map<String, Object> componentData;
    private Map<String, Object> carriageData;

    // Constructor
    public CCPStatus() {
        this.componentData = new HashMap<>();
        this.carriageData = new HashMap<>();
    }

    // Method to store data received from the Carriage Control Program
    public void storeCarriageData(JSONObject data) {
        carriageData.put("speed", data.optFloat("speed", 0.0f));
        carriageData.put("doorStatus", data.optString("doorStatus", "unknown"));
        carriageData.put("status", data.optString("status", "unknown"));
        carriageData.put("sensorStatus", data.optString("sensorStatus", "unknown"));
        carriageData.put("batteryLevel", data.optFloat("batteryLevel", 0.0f));
        carriageData.put("stationID", data.optString("stationID", "unknown"));
    }

    // Method to store data from other components
    public void storeComponentData(String key, Object value) {
        componentData.put(key, value);
    }

    // Method to sift through data and send relevant data to MCP
    public JSONObject prepareDataForMCP() {
        JSONObject mcpData = new JSONObject();
        mcpData.put("speed", carriageData.get("speed"));
        mcpData.put("doorStatus", carriageData.get("doorStatus"));
        mcpData.put("status", carriageData.get("status"));
        mcpData.put("sensorStatus", carriageData.get("sensorStatus"));
        mcpData.put("batteryLevel", carriageData.get("batteryLevel"));
        mcpData.put("stationID", carriageData.get("stationID"));

        if (componentData.containsKey("feedback")) {
            mcpData.put("feedback", componentData.get("feedback"));
        }

        // Additional data from other components
        // mcpData.put("additionalData", componentData.get("someKey"));

        return mcpData;
    }

    // Method to create command messages to MCP
    public JSONObject createMCPCommand(String commandType, Map<String, Object> params) {
        JSONObject command = new JSONObject();
        command.put("client_type", "ccp");
        command.put("client_id", "CC01");
        command.put("message", commandType);

        for (Map.Entry<String, Object> entry : params.entrySet()) {
            command.put(entry.getKey(), entry.getValue());
        }

        return command;
    }

    // Method to execute commands received from MCP
    public void executeCommandFromMCP(JSONObject command) {
        String action = command.optString("action");
        switch (action) {
            case "update_speed":
                carriageData.put("speed", command.optFloat("speed", 0.0f));
                break;
            case "open_door":
                carriageData.put("doorStatus", "open");
                break;
            case "close_door":
                carriageData.put("doorStatus", "closed");
                break;
            case "update_status":
                carriageData.put("status", command.optString("status", "unknown"));
                break;
            case "update_sensor":
                carriageData.put("sensorStatus", command.optString("sensorStatus", "unknown"));
                break;
            default:
                System.out.println("Unknown command received from MCP: " + action);
        }
    }

    // Method to send data to Carriage Control Program
    public void sendToCarriageControl(JSONObject data) {
        System.out.println("Sending data to Carriage Control Program: " + data.toString());
    }

    // Method to receive data from Carriage Control Program
    public JSONObject receiveFromCarriageControl() {
        System.out.println("Receiving data from Carriage Control Program...");
        // Simulation of receiving data
        return new JSONObject();
    }

    // Main method for demonstration
    public static void main(String[] args) {
        CCPStatus ccpStatus = new CCPStatus();

        // Example of storing carriage data
        JSONObject carriageData = new JSONObject();
        carriageData.put("speed", 25.0);
        carriageData.put("doorStatus", "closed");
        carriageData.put("status", "running");
        carriageData.put("sensorStatus", "normal");
        carriageData.put("batteryLevel", 85.0);
        carriageData.put("stationID", "ST01");

        ccpStatus.storeCarriageData(carriageData);

        // Example of preparing data for MCP
        JSONObject mcpData = ccpStatus.prepareDataForMCP();
        System.out.println("Prepared data for MCP: " + mcpData.toString());

        // Example of sending a command to MCP
        Map<String, Object> params = new HashMap<>();
        params.put("timestamp", System.currentTimeMillis());
        JSONObject command = ccpStatus.createMCPCommand("STAT", params);
        System.out.println("Command to MCP: " + command.toString());

        // Example of executing a command from MCP
        JSONObject execCommand = new JSONObject();
        execCommand.put("action", "open_door");
        ccpStatus.executeCommandFromMCP(execCommand);
    }
}