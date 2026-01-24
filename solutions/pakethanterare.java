/*
https://open.kattis.com/problems/pakethanterare

Number packagetypes Number of stores
Number of packagetype each store has
Name Number version

*/
import java.util.*;
import java.io.*;
import java.math.*;

public class pakethanterare{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String[] temp=br.readLine().split(" ");
		int t = Integer.parseInt(temp[0]);
		int n=Integer.parseInt(temp[1]);
		temp=br.readLine().split(" ");
		String[] tmp;
		int sum;
		HashMap<String,Integer> hm=new HashMap<>();
		for (int i=0;i<t;i++){
			tmp=br.readLine().split(" ");
			hm.put(tmp[0],Integer.parseInt(tmp[1]));
		}

		for (int i=0;i<n;i++){
			sum=0;
			for (int j=0;j<Integer.parseInt(temp[i]);j++){
				tmp=br.readLine().split(" ");
				sum+=hm.get(tmp[0])-Integer.parseInt(tmp[1]);
			}
			pw.println(sum);
		}
		
		pw.flush();
		pw.close();
	}
}