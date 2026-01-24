
/*
https://open.kattis.com/problems/antipalindrome

First case: two of the same letters
Second case: two of the same letters interspaced by one character
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class antipalindrome{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		char[] temp= br.readLine().toLowerCase().toCharArray();
		char prev,curr;
		int curridx;
		int idx=0;
		boolean solve=false;
		while (idx<temp.length){
			if (temp[idx]<'a'||temp[idx]>'z'){idx++;}
			else{
				prev=temp[idx];
				idx++;
				if (idx>=temp.length){break;}
				while (temp[idx]<'a'||temp[idx]>'z'){
					idx++;
					if (idx>=temp.length){break;}
				}
				if (idx>=temp.length){break;}
				if (temp[idx]!=prev){
					curridx=idx;
					idx++;
					if (idx>=temp.length){break;}
					while (temp[idx]<'a'||temp[idx]>'z'){
						idx++;
						if (idx>=temp.length){break;}
					}
					if (idx>=temp.length){break;}
					if (temp[idx]!=prev){
						idx=curridx;
					}
					else{pw.println("Palindrome");solve=true;}
				}
				else{pw.println("Palindrome");solve=true;}
			}
			if (solve){break;}
		}
		if (!solve){pw.println("Anti-palindrome");}

		pw.flush();
		pw.close();
	}
}