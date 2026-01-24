
/*
https://open.kattis.com/problems/mathhomework


*/
import java.util.*;
import java.io.*;
import java.math.*;

public class mathhomework{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String[] temp= br.readLine().split(" ");
		int b=Integer.parseInt(temp[0]);
		int c=Integer.parseInt(temp[1]);
		int d=Integer.parseInt(temp[2]);
		int l=Integer.parseInt(temp[3]);
		boolean solve=false;
		for (int i=0;i<=l/b;i++){
			for (int j=0;j<=l/c;j++){
				for (int k=0;k<=l/d;k++){
					// System.out.println(i+" "+j+" "+k);
					if (((b*i)+(c*j)+(d*k))==l){pw.println(i+" "+j+" "+k);solve=true;}
				}
			}
		}

		if (!solve){pw.println("impossible");}
		pw.flush();
		pw.close();
	}
}