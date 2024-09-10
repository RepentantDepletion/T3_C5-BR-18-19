//package t3_c5.br;

public class SpeedTracking {
    private float speed;

    public SpeedTracking() {
        this.speed = 0.0f; // Default speed
    }

    public float getSpeed() {
        return speed;
    }

    public void setSpeed(float speed) {
        this.speed = speed;
        System.out.println("Speed set to: " + speed);
    }

    public void increaseSpeed(float increment) {
        this.speed += increment;
        System.out.println("Speed increased to: " + speed);
    }

    public void decreaseSpeed(float decrement) {
        this.speed -= decrement;
        if (this.speed < 0) this.speed = 0; // Ensure speed is not negative
        System.out.println("Speed decreased to: " + speed);
    }
}