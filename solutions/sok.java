/*
https://open.kattis.com/problems/sok

Check maximum for each and find restraining factor
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class sok{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String[] temp1,temp2;
		int gcd,a,b,r;
		temp1 = br.readLine().split(" ");
		temp2 = br.readLine().split(" ");
		gcd=Integer.parseInt(temp2[0]);
		for (int i=1;i<temp1.length;i++){
			if (gcd==1){break;}
			if (Integer.parseInt(temp2[i])==gcd){continue;}
			if (Integer.parseInt(temp2[i])>gcd){a=Integer.parseInt(temp2[i]);b=gcd;}
			else {a=gcd;b=(Integer.parseInt(temp2[i]));}
			r=b;
			while (a%b !=0){
				r=a%b;
				a=b;
				b=r;
			}
			gcd=r;
		}
		PriorityQueue<Double> pq=new PriorityQueue<>();
		for (int i=0;i<temp1.length;i++){pq.add(Double.parseDouble(temp1[i])/(Double.parseDouble(temp2[i])/gcd));}
		Double max=pq.poll();
		for (int i=0;i<temp1.length;i++) {pw.print(Double.parseDouble(temp1[i]) - ((Double.parseDouble(temp2[i])/gcd)*max) + " ");}
		pw.println();
		pw.flush();
		pw.close();
	}
}
