interface lightInput { // these names will change based on other classes
    double getLedColour();
}

public class Sensor {

    static double red;
    static double green;
    static double blue;
    private lightInput input;
    public float LedColor;

    // constructors
    public Sensor(lightInput input) {
        this.input = input;
    }

    // Getters
    public double getLedColour() {
        return LedColor;
    }

}
