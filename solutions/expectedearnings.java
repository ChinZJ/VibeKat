
/*
https://open.kattis.com/problems/expectedearnings

If probability of losing is high then spela
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class expectedearnings{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String[] temp= br.readLine().split(" ");
		double n=Double.parseDouble(temp[0]);
		double k=Double.parseDouble(temp[1]);
		double p=Double.parseDouble(temp[2]);
		double val=(-k * (1 - p)) + ((n - k) * p);
		if (val<0){pw.println("spela");}
		else{pw.println("spela inte!");}
		pw.flush();
		pw.close();
	}
}