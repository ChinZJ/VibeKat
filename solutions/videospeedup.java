/*
https://open.kattis.com/problems/videospeedup

*/
import java.util.*;
import java.io.*;
import java.math.*;

public class videospeedup{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String[] temp=br.readLine().split(" ");
		String[] temp1=br.readLine().split(" ");
		double n=Double.parseDouble(temp[0]);
		double p=Double.parseDouble(temp[1])/100;
		double k=Double.parseDouble(temp[2]);
		double total=Double.parseDouble(temp1[0]);
		if (n==1){pw.println(total);}
		else{
			for (int i=1;i<temp1.length;i++){
				total+= ((Double.parseDouble(temp1[i])-Double.parseDouble(temp1[i-1])) * ((double)1 + ((double)i*p)));
				// System.out.println((Double.parseDouble(temp1[i])-Double.parseDouble(temp1[i-1])));
				// System.out.println(((double)1 + ((double)i*p)));
				// System.out.println(total);
			}
			total+= ((k-Double.parseDouble(temp1[temp1.length-1])) * ((double)1 + ((double)temp1.length*p)));
			pw.println(total);
		}
		pw.flush();
		pw.close();
	}
}