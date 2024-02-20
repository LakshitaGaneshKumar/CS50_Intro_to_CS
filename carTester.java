import java.util.Scanner;
import java.util.ArrayList;

public class carTester {

    public static void main(String[] args) {

        // Create Scanner object and an ArrayList of cars, which acts as a new directory of a 100 cars
        Scanner input = new Scanner(System.in);
        ArrayList<carDirectory> cars = new ArrayList<>();

        System.out.println("How many cars do you want to add to directory?");
        int numCars = input.nextInt();
        input.nextLine();

        for (int i = 0; i < numCars; i++)
        {
            System.out.print("Enter Car Model: ");
            String model = input.nextLine();

            System.out.print("Enter Car Year: ");
            int year = input.nextInt();
            input.nextLine();

            System.out.print("Enter Car Color: ");
            String color = input.nextLine();

            System.out.print("Enter Car Price: ");
            int price = input.nextInt();
            input.nextLine();

            System.out.print("Is this a race car? (T or F): ");
            String raceCar = input.nextLine();
            boolean race;
            if (raceCar.equals("T"))
            {
                race = true;
            }
            else
            {
                race = false;
            }

            carDirectory car = new carDirectory(model, year, color, price, race);
            cars.add(car);
        }

        for (int i = 0; i < cars.size(); i++)
        {
            System.out.println(cars.get(i));
        }
    }
}
