/*
https://open.kattis.com/problems/krizaljka
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class krizaljka{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String[] temp=br.readLine().split(" ");
		String hori=temp[0];
		String vert=temp[1];
		int idx=0;
		int vidx=0;
		while (true){
			if (vert.contains(String.valueOf(hori.charAt(idx)))) {vidx=vert.indexOf(hori.charAt(idx));break;}
			idx++;
		}
		for (int i=0;i<vert.length();i++){
			if (i==vidx){pw.println(hori);}
			else{
				for (int j=0;j<idx;j++){pw.print('.');}
				pw.print(vert.charAt(i));
				for (int j=idx+1;j<hori.length();j++){pw.print('.');}
				pw.println();
			}
		}

		pw.flush();
		pw.close();
	}
}
