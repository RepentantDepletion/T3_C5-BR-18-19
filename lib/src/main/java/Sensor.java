interface lightInput { // these names will change based on other classes
    double getLedColour();
}

public class Sensor {

    double red;
    double green;
    double blue;
    private lightInput input;

    // constructors
    public Sensor(lightInput input) {
        this.input = input;
    }

}
