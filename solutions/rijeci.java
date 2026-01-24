/*
https://open.kattis.com/problems/rijeci

A --> B
B --> BA

After K times of pressing button, how many A and B displayed?

A                       1 0
B                       0 1
B A                     1 1
BA B                    1 2
BA B BA                 2 3
BA B BA BA B            3 5
BA B BA BA B BA B BA    5 8

This is essentially separate fibonacci problems.
Excluding the first 2 cases, A trails behind B by one count
*/

import java.util.*;
import java.io.*;
import java.math.*;

public class Rijeci{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		int t = Integer.parseInt(br.readLine()); // Question has K <= 45 so no problem
		if (t == 0) pw.println("1 0");
		else if (t == 1) pw.println("0 1");
		// Note that from the 3rd, B starts with 1, next digit being 2
		else {
			int temp; // Temporary value used in update loop
			int a = 0; // Number of A
			int b = 1; // Number of B
			t -= 2; // subtract the first 2
			while (t-- >= 0) { // t-- ensures evaluation before subtraction
				temp = b;
				b += a;
				a = temp;
			}
			pw.println(a + " " + b);
		}
		pw.flush();
		pw.close();
	}
}