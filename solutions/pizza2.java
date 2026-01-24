/*
https://open.kattis.com/problems/pizza2

Area is pi*r*r
Thus the difference is C*C/R*R * 100
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class pizza2{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String[] temp= br.readLine().split(" ");
		Double r=Double.parseDouble(temp[0]);
		Double c=r-Double.parseDouble(temp[1]);
		pw.println( (Double)(c*c)/(r*r)*100);
		pw.flush();
		pw.close();
	}
}