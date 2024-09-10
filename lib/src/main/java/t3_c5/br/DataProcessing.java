package t3_c5.br;

import java.util.HashMap;
import java.util.Map;

public class DataProcessing {

    private Map<String, Object> componentData; // Stores data from various components (e.g., feedback, Aryan's classes)
    private Map<String, Object> commandData;   // Stores commands and data received from the Carriage Control Program (CCP)
    private String stationID; // Variable to store station ID directly

    // Constructor initializes the componentData and commandData maps
    public DataProcessing() {
        this.componentData = new HashMap<>();
        this.commandData = new HashMap<>();
    }

    // Setter method for stationID
    public void setStationID(String stationID) {
        this.stationID = stationID;
        commandData.put("stationID", stationID); // Also store in commandData map
    }

    // Getter method for stationID
    public String getStationID() {
        return this.stationID;
    }

    // Method to store and process string commands received from the Carriage Control Program (CCP)
    public void processCarriageCommand(String command) {
        try {
            String[] parts = command.split(":");
            String commandType = parts[0].trim();
            String value = parts.length > 1 ? parts[1].trim() : "";

            switch (commandType) {
                case "set_speed":
                    commandData.put("speed", Float.parseFloat(value));
                    break;
                case "set_door_status":
                    commandData.put("doorStatus", value);
                    break;
                case "set_status":
                    commandData.put("status", value);
                    break;
                case "set_sensor_status":
                    commandData.put("sensorStatus", value);
                    break;
                case "set_battery_level":
                    commandData.put("batteryLevel", Float.parseFloat(value));
                    break;
                case "set_station_id":
                    setStationID(value); // Use the setter for stationID
                    break;
                default:
                    System.out.println("Unknown command: " + command);
            }
        } catch (Exception e) {
            System.out.println("Error processing command: " + e.getMessage());
        }
    }

    // Method to store data from other components (like feedback, Aryan's classes, etc.)
    public void storeComponentData(String key, Object data) {
        componentData.put(key, data);
    }

    // Method to sift through the data and send relevant data to the Master Control Program (MCP)
    public JSONObject sendRelevantDataToMCP() {
        JSONObject mcpData = new JSONObject(); // JSON object to send to MCP

        try {
            // Adding relevant data from commandData to the JSON object
            mcpData.put("speed", commandData.get("speed"));
            mcpData.put("door_status", commandData.get("doorStatus"));
            mcpData.put("status", commandData.get("status"));
            mcpData.put("sensor_status", commandData.get("sensorStatus"));
            mcpData.put("battery_level", commandData.get("batteryLevel"));
            mcpData.put("station_id", getStationID()); // Use the getter for stationID

            // Optionally add additional component data if it exists
            if (componentData.containsKey("feedback")) {
                mcpData.put("feedback", componentData.get("feedback"));
            }

        } catch (Exception e) {
            System.out.println("Error creating MCP data JSON: " + e.getMessage());
        }

        return mcpData; // Return the created JSON object to be sent to MCP
    }

    // Method to execute commands received from the Master Control Program (MCP)
    public void executeMCPCommand(JSONObject execCommand) {
        try {
            String action = execCommand.optString("action"); // Extract the action command from the JSON object
            if (action != null && !action.isEmpty()) {
                // Execute the appropriate command based on the action value
                switch (action) {
                    case "update_speed":
                        commandData.put("speed", (float) execCommand.getDouble("speed"));
                        break;
                    case "open_door":
                        commandData.put("doorStatus", "open");
                        break;
                    case "close_door":
                        commandData.put("doorStatus", "closed");
                        break;
                    case "update_status":
                        commandData.put("status", execCommand.getString("status"));
                        break;
                    case "update_sensor_status":
                        commandData.put("sensorStatus", execCommand.getString("sensor_status"));
                        break;
                    default:
                        System.out.println("Unknown action: " + action); // Handle unknown actions
                }
            }
        } catch (Exception e) {
            System.out.println("Error processing execution JSON: " + e.getMessage());
        }
    }

    // Method to simulate sending a message to the Carriage Control Program (CCP)
    public void sendCarriageMessage(JSONObject message) {
        System.out.println("Sending message to Carriage Control Program: " + message.toString());
        // Here you would actually send the message to the Carriage Control Program
    }

    // Method to simulate receiving a message from the Carriage Control Program (CCP)
    public String receiveCarriageCommand() {
        System.out.println("Receiving command from Carriage Control Program...");
        // Here you would actually receive the command from the Carriage Control Program
        return "set_speed:80.5"; // Returning a dummy command for simulation
    }
}


/* 
//code before setter - getter 
package t3_c5.br;

import org.json.JSONObject;
import java.util.HashMap;
import java.util.Map;

public class DataProcessing {

    private Map<String, Object> componentData; // Stores data from various components (e.g., feedback, Aryan's classes)
    private Map<String, Object> commandData;   // Stores commands and data received from the Carriage Control Program (CCP)

    // Constructor initializes the componentData and commandData maps
    public DataProcessing() {
        this.componentData = new HashMap<>();
        this.commandData = new HashMap<>();
    }

    // Method to store data received from the Carriage Control Program (CCP)
    public void storeCarriageData(JSONObject carriageData) {
        try {
            // Storing relevant data fields from the received JSON object
            commandData.put("speed", carriageData.getFloat("speed"));
            commandData.put("doorStatus", carriageData.getString("door_status"));
            commandData.put("status", carriageData.getString("status"));
            commandData.put("sensorStatus", carriageData.getString("sensor_status"));
            commandData.put("batteryLevel", carriageData.getFloat("battery_level"));
            commandData.put("stationID", carriageData.getString("station_id"));
        } catch (Exception e) {
            System.out.println("Error storing carriage data: " + e.getMessage());
        }
    }

    // Method to store data from other components (like feedback, Aryan's classes, etc.)
    public void storeComponentData(String key, Object data) {
        componentData.put(key, data);
    }

    // Method to sift through the data and send relevant data to the Master Control Program (MCP)
    public JSONObject sendRelevantDataToMCP() {
        JSONObject mcpData = new JSONObject(); // JSON object to send to MCP

        try {
            // Adding relevant data from commandData to the JSON object
            mcpData.put("speed", commandData.get("speed"));
            mcpData.put("door_status", commandData.get("doorStatus"));
            mcpData.put("status", commandData.get("status"));
            mcpData.put("sensor_status", commandData.get("sensorStatus"));
            mcpData.put("battery_level", commandData.get("batteryLevel"));
            mcpData.put("station_id", commandData.get("stationID"));

            // Optionally add additional component data if it exists
            if (componentData.containsKey("feedback")) {
                mcpData.put("feedback", componentData.get("feedback"));
            }

            // Placeholder for adding any other relevant data from Aryan's classes
            // Example: mcpData.put("aryan_class_data", componentData.get("aryan_class_key"));

        } catch (Exception e) {
            System.out.println("Error creating MCP data JSON: " + e.getMessage());
        }

        return mcpData; // Return the created JSON object to be sent to MCP
    }

    // Method to execute commands received from the Master Control Program (MCP)
    public void executeMCPCommand(JSONObject execCommand) {
        try {
            String action = execCommand.optString("action"); // Extract the action command from the JSON object
            if (action != null && !action.isEmpty()) {
                // Execute the appropriate command based on the action value
                switch (action) {
                    case "update_speed":
                        commandData.put("speed", (float) execCommand.getDouble("speed"));
                        break;
                    case "open_door":
                        commandData.put("doorStatus", "open");
                        break;
                    case "close_door":
                        commandData.put("doorStatus", "closed");
                        break;
                    case "update_status":
                        commandData.put("status", execCommand.getString("status"));
                        break;
                    case "update_sensor_status":
                        commandData.put("sensorStatus", execCommand.getString("sensor_status"));
                        break;
                    default:
                        System.out.println("Unknown action: " + action); // Handle unknown actions
                }
            }
        } catch (Exception e) {
            System.out.println("Error processing execution JSON: " + e.getMessage());
        }
    }

    // Method to simulate sending a message to the Carriage Control Program (CCP)
    public void sendCarriageMessage(JSONObject message) {
        System.out.println("Sending message to Carriage Control Program: " + message.toString());
        // Here you would actually send the message to the Carriage Control Program
    }

    // Method to simulate receiving a message from the Carriage Control Program (CCP)
    public JSONObject receiveCarriageMessage() {
        System.out.println("Receiving message from Carriage Control Program...");
        // Here you would actually receive the message from the Carriage Control Program
        return new JSONObject(); // Returning a dummy JSON object
    }
}
*/

/* 
package t3_c5.br;

import org.json.JSONObject;
import java.util.HashMap;
import java.util.Map;

public class DataProcessing {

    private Map<String, Object> componentData;
    private Map<String, Object> commandData;

    // Constructor
    public DataProcessing() {
        this.componentData = new HashMap<>();
        this.commandData = new HashMap<>();
    }

    // Method to store data received from the Carriage Control Program
    public void storeCarriageData(JSONObject carriageData) {
        try {
            commandData.put("speed", carriageData.getFloat("speed"));
            commandData.put("doorStatus", carriageData.getString("door_status"));
            commandData.put("status", carriageData.getString("status"));
            commandData.put("sensorStatus", carriageData.getString("sensor_status"));
            commandData.put("batteryLevel", carriageData.getFloat("battery_level"));
            commandData.put("stationID", carriageData.getString("station_id"));
        } catch (Exception e) {
            System.out.println("Error storing carriage data: " + e.getMessage());
        }
    }

    // Method to store data from other components (like feedback, Aryan's classes, etc.)
    public void storeComponentData(String key, Object data) {
        componentData.put(key, data);
    }

    // Method to sift through the data and send relevant data to MCP
    public JSONObject sendRelevantDataToMCP() {
        // Create a JSON object to send to MCP with relevant data
        JSONObject mcpData = new JSONObject();

        // Add data from commandData and componentData that is relevant to MCP
        try {
            mcpData.put("speed", commandData.get("speed"));
            mcpData.put("door_status", commandData.get("doorStatus"));
            mcpData.put("status", commandData.get("status"));
            mcpData.put("sensor_status", commandData.get("sensorStatus"));
            mcpData.put("battery_level", commandData.get("batteryLevel"));
            mcpData.put("station_id", commandData.get("stationID"));

            // Add any additional component data if needed
            if (componentData.containsKey("feedback")) {
                mcpData.put("feedback", componentData.get("feedback"));
            }

            // Add any other relevant data from Aryan's classes
            // Example: mcpData.put("aryan_class_data", componentData.get("aryan_class_key"));

        } catch (Exception e) {
            System.out.println("Error creating MCP data JSON: " + e.getMessage());
        }

        return mcpData;
    }

    // Method to execute commands from MCP
    public void executeMCPCommand(JSONObject execCommand) {
        try {
            String action = execCommand.optString("action");
            if (action != null && !action.isEmpty()) {
                switch (action) {
                    case "update_speed":
                        commandData.put("speed", (float) execCommand.getDouble("speed"));
                        break;
                    case "open_door":
                        commandData.put("doorStatus", "open");
                        break;
                    case "close_door":
                        commandData.put("doorStatus", "closed");
                        break;
                    case "update_status":
                        commandData.put("status", execCommand.getString("status"));
                        break;
                    case "update_sensor_status":
                        commandData.put("sensorStatus", execCommand.getString("sensor_status"));
                        break;
                    default:
                        System.out.println("Unknown action: " + action);
                }
            }
        } catch (Exception e) {
            System.out.println("Error processing execution JSON: " + e.getMessage());
        }
    }

    // Method to simulate sending a message to the Carriage Control Program
    public void sendCarriageMessage(JSONObject message) {
        System.out.println("Sending message to Carriage Control Program: " + message.toString());
        // Here you would actually send the message to the Carriage Control Program
    }

    // Method to simulate receiving a message from the Carriage Control Program
    public JSONObject receiveCarriageMessage() {
        System.out.println("Receiving message from Carriage Control Program...");
        // Here you would actually receive the message from the Carriage Control Program
        return new JSONObject(); // Returning a dummy JSON object
    }
}

*/


// old code - trystan - 3/9/24
/* 
//Data processing 

package t3_c5.br;
import org.json.JSONObject;
import java.util.HashMap;
import java.util.Map;

public class DataProcessing {
       // change "SystemController" name to whatever class youre extendinh

    private Map<String, Object> componentData;
    private Map<String, Object> commandData;
    
    // Constructor
    public DataProcessing() {
        this.componentData = new HashMap<>();
        this.commandData = new HashMap<>();
    }

    // Method to store data received from the Carriage Control Program
    public void storeCarriageData(JSONObject carriageData) {
        try {
            commandData.put("speed", carriageData.getFloat("speed"));
            commandData.put("doorStatus", carriageData.getString("door_status"));
            commandData.put("status", carriageData.getString("status"));
            commandData.put("sensorStatus", carriageData.getString("sensor_status"));
            commandData.put("batteryLevel", carriageData.getFloat("battery_level"));
            commandData.put("stationID", carriageData.getString("station_id"));
        } catch (Exception e) {
            System.out.println("Error storing carriage data: " + e.getMessage());
        }
    }

    // Method to store data from other components (like feedback, Aryan's classes, etc.)
    public void storeComponentData(String key, Object data) {
        componentData.put(key, data);
    }

    // Method to sift through the data and send relevant data to MCP
    public JSONObject sendRelevantDataToMCP() {
        // Create a JSON object to send to MCP with relevant data
        JSONObject mcpData = new JSONObject();

        // Add data from commandData and componentData that is relevant to MCP
        try {
            mcpData.put("speed", commandData.get("speed"));
            mcpData.put("door_status", commandData.get("doorStatus"));
            mcpData.put("status", commandData.get("status"));
            mcpData.put("sensor_status", commandData.get("sensorStatus"));
            mcpData.put("battery_level", commandData.get("batteryLevel"));
            mcpData.put("station_id", commandData.get("stationID"));

            // Add any additional component data if needed
            if (componentData.containsKey("feedback")) {
                mcpData.put("feedback", componentData.get("feedback"));
            }

            // Add any other relevant data from Aryan's classes
            // Example: mcpData.put("aryan_class_data", componentData.get("aryan_class_key"));

        } catch (Exception e) {
            System.out.println("Error creating MCP data JSON: " + e.getMessage());
        }

        return mcpData;
    }

    // Method to execute commands from MCP
    public void executeMCPCommand(JSONObject execCommand) {
        try {
            String action = execCommand.optString("action");
            if (action != null && !action.isEmpty()) {
                switch (action) {
                    case "update_speed":
                        commandData.put("speed", (float) execCommand.getDouble("speed"));
                        break;
                    case "open_door":
                        commandData.put("doorStatus", "open");
                        break;
                    case "close_door":
                        commandData.put("doorStatus", "closed");
                        break;
                    case "update_status":
                        commandData.put("status", execCommand.getString("status"));
                        break;
                    case "update_sensor_status":
                        commandData.put("sensorStatus", execCommand.getString("sensor_status"));
                        break;
                    default:
                        System.out.println("Unknown action: " + action);
                }
            }
        } catch (Exception e) {
            System.out.println("Error processing execution JSON: " + e.getMessage());
        }
    }

    // Method to simulate sending a message to the Carriage Control Program
    public void sendCarriageMessage(JSONObject message) {
        System.out.println("Sending message to Carriage Control Program: " + message.toString());
        // Here you would actually send the message to the Carriage Control Program
    }

    // Method to simulate receiving a message from the Carriage Control Program
    public JSONObject receiveCarriageMessage() {
        System.out.println("Receiving message from Carriage Control Program...");
        // Here you would actually receive the message from the Carriage Control Program
        return new JSONObject(); // Returning a dummy JSON object
    }
}
*/