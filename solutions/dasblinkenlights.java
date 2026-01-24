
/*
https://open.kattis.com/problems/dasblinkenlights
Find lowest common multiple based on gcd
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class dasblinkenlights{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String[] temp=br.readLine().split(" ");
		if (lcm(Integer.parseInt(temp[0]),Integer.parseInt(temp[1])) <= Integer.parseInt(temp[2])) {pw.println("yes");}
		else {pw.println("no");}
		pw.flush();
		pw.close();
	}

	static int gcd(int a, int b) {
	    while (b != 0) {
	        int temp = b;
	        b = a % b;
	        a = temp;
	    }
	    return a;
	}

	static int lcm(int a, int b) {
		return a * b / gcd(a, b);
	}
}