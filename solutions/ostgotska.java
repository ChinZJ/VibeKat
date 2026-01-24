/*
https://open.kattis.com/problems/ostgotska

*/
import java.util.*;
import java.io.*;
import java.math.*;

public class ostgotska{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String[] temp=br.readLine().split(" ");;
		CharSequence seq=new StringBuilder("ae");
		int ctr=0;
		for (int i=0;i<temp.length;i++){
			if (temp[i].contains(seq)) {ctr++;}
		}
		double weight=(double)ctr/(double)temp.length;
		if (weight>=0.4){pw.println("dae ae ju traeligt va");}
		else {pw.println("haer talar vi rikssvenska");}
		pw.flush();
		pw.close();
	}
}
