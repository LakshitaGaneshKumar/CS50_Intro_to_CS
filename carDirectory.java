public class carDirectory {
    private String model;
    private int year;
    private String color;
    private int price;
    private boolean raceCar;

    public carDirectory(String model, int year, String color, int price, boolean raceCar) {
        this.model = model;
        this.year = year;
        this.color = color;
        this.price = price;
        this.raceCar = raceCar;
    }

    public String getModel() {
        return this.model;
    }

    public int getYear() {
        return this.year;
    }

    public String getColor() {
        return this.color;
    }

    public int getPrice() {
        return this.price;
    }

    public boolean isRaceCar() {
        return this.raceCar;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public void setYear(int year) {
        this.year = year;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public void setPrice(int price) {
        this.price = price;
    }

    public void setRaceCar(boolean raceCar) {
        this.raceCar = raceCar;
    }

    public String toString() {
        return "\nA " + this.year + " " + this.color + " " + this.model + " that costs $" + this.price + "." + " This car is a raceCar: " + this.raceCar + "\n";
    }
}