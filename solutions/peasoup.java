import java.util.*;

public class peasoup {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int number_of_restaurants = sc.nextInt();
        String result = "";
        Boolean has_pea_soup = false;
        Boolean has_pancakes = false;
        String restaurant_name ="";

        for (int i = 1; i <= number_of_restaurants; i++) {
            int number_of_items = sc.nextInt();
            sc.nextLine();
            restaurant_name = sc.nextLine();
            for (int j = 0; j < number_of_items; j++) {
                String item_name = sc.nextLine();

                if (item_name.equals("pea soup")) {
                    has_pea_soup = true;
                }
                if (item_name.equals("pancakes")) {
                    has_pancakes = true;
                }
            }
            if (has_pea_soup && has_pancakes) {
                result = restaurant_name;
                break;
            } else {
                has_pancakes = false;
                has_pea_soup = false;
            }
        }
        result = (result.equals("")) ? "Anywhere is fine I guess": result;
        System.out.println(result);
    }
}