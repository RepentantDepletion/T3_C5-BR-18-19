//package t3_c5.br;

public class DoorControl {
    private String doorStatus;

    public DoorControl() {
        this.doorStatus = "closed"; // Default status
    }

    public String getDoorStatus() {
        return doorStatus;
    }

    public void openDoor() {
        this.doorStatus = "open";
        System.out.println("Door opened.");
    }

    public void closeDoor() {
        this.doorStatus = "closed";
        System.out.println("Door closed.");
    }
}