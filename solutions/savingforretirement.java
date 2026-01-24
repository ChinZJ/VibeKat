/*
https://open.kattis.com/problems/savingforretirement


*/
import java.util.*;
import java.io.*;
import java.math.*;

public class savingforretirement{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String[] temp= br.readLine().split(" ");
		int bs= (Integer.parseInt(temp[1]) - Integer.parseInt(temp[0])) * Integer.parseInt(temp[2]);
		int ans=bs/Integer.parseInt(temp[4]);
		if (ans*Integer.parseInt(temp[4]) <= bs){ans++;}
		pw.println(Integer.parseInt(temp[3])+ans);
		pw.flush();
		pw.close();
	}
}
