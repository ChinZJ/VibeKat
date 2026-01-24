
/*
https://open.kattis.com/problems/scalingrecipe

Basic proportions
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class scalingrecipe{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String[] temp= br.readLine().split(" ");
		int n=Integer.parseInt(temp[0]);
		double x=Double.parseDouble(temp[2])/Double.parseDouble(temp[1]);
		for (int i=0;i<n;i++){
			pw.println(Math.round(Double.parseDouble(br.readLine())*x));
		}
		pw.flush();
		pw.close();
	}
}