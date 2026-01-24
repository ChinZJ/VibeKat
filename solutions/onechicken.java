/*
https://open.kattis.com/problems/onechicken

Two cases, brute force
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class onechicken{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String[] temp=br.readLine().split(" ");;
		int n=Integer.parseInt(temp[0]);
		int m=Integer.parseInt(temp[1]);
		if (n<m){
			if (m-n == 1){pw.println("Dr. Chaz will have 1 piece of chicken left over!");}
			else {pw.println("Dr. Chaz will have "+ (m-n) +" pieces of chicken left over!");}
		}
		else{
			if (n-m == 1){pw.println("Dr. Chaz needs 1 more piece of chicken!");}
			else{pw.println("Dr. Chaz needs "+ (n-m) +" more pieces of chicken!");}
		}
		pw.flush();
		pw.close();
	}
}
