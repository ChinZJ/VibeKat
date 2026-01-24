/*
https://open.kattis.com/problems/zoo
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class zoo{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		TreeSet<String> ts= new TreeSet<>();
		HashMap<String,Integer> hm=new HashMap<>();
		int ctr=1;
		String[] temp;
		String str;
		int n;
		while (true){
			ts.clear();hm.clear();
			if ( (n = Integer.parseInt(br.readLine())) ==0){break;}
			pw.println("List "+ctr+":");
			
			for (int i=0;i<n;i++){
				temp = br.readLine().split(" ");
				str=temp[temp.length-1].toLowerCase();
				if (!ts.contains(str)){ts.add(str);hm.put(str,1);}
				else {hm.replace(str, hm.get(str)+1);}
			}
			for (String s : ts){
				pw.println(s + " | "+hm.get(s));
			}
			ctr++;
		}
		pw.flush();
		pw.close();
	}
}
