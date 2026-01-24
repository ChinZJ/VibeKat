
/*
https://open.kattis.com/problems/locustlocus

Cycle 13 and 17
Last saw in 1992

Lowest common multiple and add it to the year
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class locustlocus{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		int t = Integer.parseInt(br.readLine());
		String[] temp;
		int ans=Integer.MAX_VALUE,year,cyc1,cyc2;
		while (t-- >0){
			temp = br.readLine().split(" ");
			year=Integer.parseInt(temp[0]);
			cyc1=Integer.parseInt(temp[1]);
			cyc2=Integer.parseInt(temp[2]);
			ans=Math.min(ans,year+lcm(cyc1,cyc2));
		}
		pw.println(ans);
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