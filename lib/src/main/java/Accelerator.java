// need to create interface file so sensor class can 

interface accelerateInput { // these names will change based on other classes
    double getXAcceleration();

    double getYAcceleration();
}

public class Accelerator { // may need to extend ccp

  //  private double desiredSpeed;
  //  private double desiredVoltage;
    private double redSpeed = 0;
    private double blueSpeed = 1.5;
    private double greenSpeed = 3;

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
         if (input != null) { 
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

    // setters  // note: 

    public void setXAcceleration(Sensor input) {
        
    }

    public void setYAcceleration(Sensor input) {
     
    }

}
