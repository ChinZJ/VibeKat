/*
https://open.kattis.com/problems/acm

Primary sorting is number of solved
Secondary is based on score
	Sum of submission time for right answer
	Add 20minute penalty for wrong submission ultimately solved
	If wrong, 0
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class acm{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String t;
		String[] temp;
		int time,ans=0,solved=0,pblm;
		int[] wrong=new int[26];
		boolean[] solve=new boolean[26];
		while ( !(t=br.readLine()).equals("-1")){
			temp = t.split(" ");
			time=Integer.parseInt(temp[0]);
			pblm=Character.getNumericValue(temp[1].charAt(0)) -10;
			if (solve[pblm]) {continue;}
			else {
				if (temp[2].equals("right")){
					solve[pblm]=true;
					solved++;
					ans+=time+wrong[pblm];
				}
				if (temp[2].equals("wrong")){
					wrong[pblm]+=20;
				}
			}
			// System.out.println("score is "+ans);
		}
		pw.println(solved+ " "+ans);
		pw.flush();
		pw.close();
	}
}