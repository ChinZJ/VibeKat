
/*
https://open.kattis.com/problems/oktalni

Answer is provided in the description of the problem
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class oktalni{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String temp=br.readLine();
		StringBuilder sb=new StringBuilder(temp);
		int idx=0;
		HashMap<String,String> hm=new HashMap<>();
		hm.put("000","0");
		hm.put("001","1");
		hm.put("010","2");
		hm.put("011","3");
		hm.put("100","4");
		hm.put("101","5");
		hm.put("110","6");
		hm.put("111","7");

		//Pad string
		int len=sb.length();
		if (len%3!=0){
			for (int i=0;i<3-(len%3);i++){sb.insert(0,"0");}
		}
		// System.out.println(sb.toString());
		StringBuilder ans=new StringBuilder();
		for (int i=0;i<sb.length();i=i+3){
			// System.out.println(sb.substring(i,i+3));
			ans.append(hm.get(sb.substring(i,i+3)));
		}
		pw.println(ans.toString());
		pw.flush();
		pw.close();
	}
}