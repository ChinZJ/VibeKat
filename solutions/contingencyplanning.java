/*
https://open.kattis.com/problems/contingencyplanning

We need to use the permutate operation
P(n,r)=n!/(n-r)!
Sum of permutation gives you your total sum

Since our limit is 10^9, n=11 is the highest
We can precalculate all values into a hashtable
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class contingencyplanning{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		HashMap<Integer,Long> hm=new HashMap<>();
		hm.put(0,1l);
		hm.put(1,1l);
		for (int i=2;i<12;i++){
			hm.put(i,i*hm.get(i-1));
		}
		int t = Integer.parseInt(br.readLine());
		if (t>=12){pw.println("JUST RUN!!");}
		else{
			long ans=0;
			for (int i=1;i<=t;i++){
				ans+=(hm.get(t)/hm.get(t-i));
			}
			pw.println(ans);
		}
		pw.flush();
		pw.close();
	}
}