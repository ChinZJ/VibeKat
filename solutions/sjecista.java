
/*
https://open.kattis.com/problems/sjecista

To form intersection points would be n Choose 4
(Require 4 points to form one intersecting point)
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class sjecista{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		int t = Integer.parseInt(br.readLine());
		if (t==3){pw.println(0);}
		else{
			HashMap<Integer,BigInteger> hm=new HashMap<>();
			hm.put(0,new BigInteger("1"));
			hm.put(1,new BigInteger("1"));
			for(int i=2;i<=t;i++){
				hm.put(i,hm.get(i-1).multiply(new BigInteger(Integer.toString(i))));
				// System.out.println(hm.get(i));
			}
			// System.out.println(hm.get(60));
			pw.println(hm.get(t).divide((hm.get(4).multiply(hm.get(t-4)))));
		}
		pw.flush();
		pw.close();
	}
}