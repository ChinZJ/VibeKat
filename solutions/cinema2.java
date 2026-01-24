/*
https://open.kattis.com/problems/cinema2

Basic Queue
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class cinema2{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String[] temp= br.readLine().split(" ");
		int n=Integer.parseInt(temp[0]);
		int m=Integer.parseInt(temp[1]);
		temp= br.readLine().split(" ");
		int grp;
		int idx=0;
		while (m>0){
			m--;
			n-=Integer.parseInt(temp[idx]);
			if (n<0){m++;break;}
			idx++;
		}
		pw.println(m);
		pw.flush();
		pw.close();
	}
}