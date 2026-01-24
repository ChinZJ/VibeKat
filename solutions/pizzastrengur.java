/*
https://open.kattis.com/problems/pizzastrengur

Solution is to try 3 of each shuffled character.
It is guaranteed that the last character must be in the string if the first 3 fails.
At n == 0 if we have no result then the last character will similarly be in the final output

*/

import java.util.*;
import java.io.*;
import java.math.*;

public class Pizzastrengur{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		// Retrieving variables first
		int n = Integer.parseInt(br.readLine());
		List<Character> PIZZA = Arrays.asList('P', 'I', 'Z', 'A'); // for added luck
		String guess = "";
		int result = 0;

		while (n-- >0){
			Collections.shuffle(PIZZA);
			// Try all digits
			for (int i = 0; i < 3; i++) {
				pw.println(guess + PIZZA.get(i));
				pw.flush();
				result = Integer.parseInt(br.readLine());
				
				if (result > 0) {
					guess += PIZZA.get(i);
					break;
				}
			}
			if (result == 2) break;
			if (result == 0) {
				guess += PIZZA.get(3);
			}
			if (n == 0) {
				pw.println(guess);
				pw.flush();
			}
		}
		pw.close();
	}
}