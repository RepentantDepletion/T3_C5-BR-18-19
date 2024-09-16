//package t3_c5.br;

public class SensorFeedback {
    private String sensorStatus;

    public SensorFeedback() {
        this.sensorStatus = "normal"; // Default sensor status
    }

    public String getSensorStatus() {
        return sensorStatus;
    }

    public void updateSensorStatus(String status) {
        this.sensorStatus = status;
        System.out.println("Sensor status updated to: " + sensorStatus);
    }
}