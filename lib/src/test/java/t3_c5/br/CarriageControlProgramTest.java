// File path: src/test/java/CarriageControlProgramTest.java
package t3_c5.br;

import org.json.JSONObject;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class CarriageControlProgramTest {

    private CarriageControlProgram carriageControlProgram;

    @BeforeEach
    public void setUp() {
        carriageControlProgram = new CarriageControlProgram("closed", "normal", "all sensors OK", 80.0f, "StationA");
    }

    @Test
    public void testInitialization() {
        assertEquals(50.0f, carriageControlProgram.getSpeed());
        assertEquals("closed", carriageControlProgram.getDoorStatus());
        assertEquals("normal", carriageControlProgram.getStatus());
        assertEquals("all sensors OK", carriageControlProgram.getSensorStatus());
        assertEquals(80.0f, carriageControlProgram.getBatteryLevel());
        assertEquals("StationA", carriageControlProgram.getStationID());
    }

    @Test
    public void testToMCPStatus() {
        JSONObject statusJson = carriageControlProgram.toMCPStatus();

        assertEquals("CarriageControlProgram", statusJson.getString("client_type"));
        assertEquals("Status Update", statusJson.getString("message"));
        assertEquals("Carriage123", statusJson.getString("client_id"));
        assertNotNull(statusJson.getLong("timestamp"));
        assertEquals("closed", statusJson.getString("door_status"));
        assertEquals(80.0f, statusJson.getFloat("battery_level"));
        assertEquals("StationA", statusJson.getString("station_id"));
        assertEquals(50.0f, statusJson.getFloat("speed"));
        assertEquals("all sensors OK", statusJson.getString("sensor_status"));
    }

    @Test
    public void testFromMCPExecUpdateSpeed() {
        JSONObject execCommand = new JSONObject();
        execCommand.put("action", "update_speed");
        execCommand.put("speed", 70.0);

        carriageControlProgram.fromMCPExec(execCommand);
        assertEquals(70.0f, carriageControlProgram.getSpeed());
    }

    @Test
    public void testFromMCPExecOpenDoor() {
        JSONObject execCommand = new JSONObject();
        execCommand.put("action", "open_door");

        carriageControlProgram.fromMCPExec(execCommand);
        assertEquals("open", carriageControlProgram.getDoorStatus());
    }

    @Test
    public void testFromMCPExecCloseDoor() {
        JSONObject execCommand = new JSONObject();
        execCommand.put("action", "close_door");

        carriageControlProgram.fromMCPExec(execCommand);
        assertEquals("closed", carriageControlProgram.getDoorStatus());
    }

    @Test
    public void testFromMCPExecUpdateStatus() {
        JSONObject execCommand = new JSONObject();
        execCommand.put("action", "update_status");
        execCommand.put("status", "maintenance");

        carriageControlProgram.fromMCPExec(execCommand);
        assertEquals("maintenance", carriageControlProgram.getStatus());
    }

    @Test
    public void testFromMCPExecUpdateSensorStatus() {
        JSONObject execCommand = new JSONObject();
        execCommand.put("action", "update_sensor_status");
        execCommand.put("sensor_status", "sensor malfunction");

        carriageControlProgram.fromMCPExec(execCommand);
        assertEquals("sensor malfunction", carriageControlProgram.getSensorStatus());
    }
}
