/*
https://open.kattis.com/problems/rationalsequence2

Traverse left is *2 
Traverse right is *2+1
Brute force recursion
Work backwards instead
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class rationalsequence2{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		int t = Integer.parseInt(br.readLine());
		String[] temp;
		int p,q,pcur,qcur;
		while (t-- >0){
			pcur=1;qcur=1;
			temp = br.readLine().split(" ");
			pw.print(Integer.parseInt(temp[0]) + " ");
			temp=temp[1].split("/");
			p=Integer.parseInt(temp[0]);
			q=Integer.parseInt(temp[1]);
			pw.println(solve(p,q));
		}
		pw.flush();
		pw.close();
	}
	public static long solve(int p, int q){
		if (p==q){return 1;}
		if (p > q) {return 2 * solve(p-q,q) + 1;}
		if (p<q) {return 2 * solve(p,q-p);}
		return 0;
	}
}