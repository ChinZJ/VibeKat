/*
https://open.kattis.com/problems/apaxianparent
Brute force manipulation
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class apaxianparent{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));
		StringBuilder sb;
		String[] temp=br.readLine().split(" ");
		int len=temp[0].length();
		
		if (temp[0].charAt(len-1)=='x' && temp[0].charAt(len-2)=='e'){pw.println(temp[0]+temp[1]);}
		else if (temp[0].charAt(len-1)=='e') {pw.println(temp[0]+"x"+temp[1]);}
		else if (temp[0].charAt(len-1)=='a' || temp[0].charAt(len-1)=='i' || temp[0].charAt(len-1)=='o'|| temp[0].charAt(len-1)=='u'){
			sb=new StringBuilder(temp[0]);
			sb.deleteCharAt(len-1);
			sb.append('e');
			sb.append('x');
			sb.append(temp[1]);
			pw.println(sb);
		}
		else{pw.println(temp[0]+"ex"+temp[1]);}
		pw.flush();
		pw.close();
	}
}
