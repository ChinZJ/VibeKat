
/*
https://open.kattis.com/problems/popularitycontest

1 based indexing as success
number of friends is popularity factor
Markebility is popularity-success
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class popularitycontest{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String[] temp= br.readLine().split(" ");
		int n=Integer.parseInt(temp[0]);
		int m=Integer.parseInt(temp[1]);
		int[] pop=new int[n+1];
		for (int i=1;i<=m;i++){
			temp=br.readLine().split(" ");
			pop[Integer.parseInt(temp[0])]++;
			pop[Integer.parseInt(temp[1])]++;
		}
		for (int i=1;i<=n;i++){
			pw.print((pop[i]-i)+" ");
		}
		pw.println();
		pw.flush();
		pw.close();
	}
}