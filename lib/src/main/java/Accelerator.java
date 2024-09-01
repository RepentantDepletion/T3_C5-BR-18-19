// need to create interface file so sensor class can 

interface accelerateInput { // these names will change based on other classes
    double getXAcceleration();

    double getYAcceleration();
}

public class Accelerator {

    private double slow = 1.5; // example values, these will change based on live feedback values
    private double medium = 3;
    private double fast = 4.5;

    private double xAcceleration; // input for x y
    private double yAcceleration;
    private accelerateInput input;

    // constructors
    public Accelerator(accelerateInput input) {
        this.input = input;
        this.xAcceleration = xAcceleration;
        this.yAcceleration = yAcceleration;
    }

    public void updateAcceleration() { // update values of x y acceleration // will need to fix this part later
        if (input <= 500 || input >= 0) { // example line, update required
            this.xAcceleration = input.getXAcceleration();
            this.yAcceleration = input.getYAcceleration();
        }
    }

    // Getters
    public double getXAcceleration() {
        return xAcceleration;
    }

    public double getYAcceleration() {
        return yAcceleration;
    }

}
