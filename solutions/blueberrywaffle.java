
/*
https://open.kattis.com/problems/blueberrywaffle

Every r it will alternate
Every 2r then it will face up

Thus if f%2r >r/2~3r/2 down
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class BlueberryWaffle{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String[] temp= br.readLine().split(" ");
		int r=Integer.parseInt(temp[0]);
		int f=Integer.parseInt(temp[1]);
		double val=f%(2*r);
		if (val> (r/2) && val < (3*r/2)){pw.println("down");}
		else{pw.println("up");}
		pw.flush();
		pw.close();
	}
}