/*
https://open.kattis.com/problems/quickbrownfox
Brute force implementation of slowly subtracting each character from hashset
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class quickbrownfox{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		int t = Integer.parseInt(br.readLine());
		String temp;
		char[] arr;
		HashSet<Character> hs=new HashSet<>();
		while (t-- >0){
			temp = br.readLine().toLowerCase();
			arr=temp.toCharArray();
			hs.add('a');
			hs.add('b');
			hs.add('c');
			hs.add('d');
			hs.add('e');
			hs.add('f');
			hs.add('g');
			hs.add('h');
			hs.add('i');
			hs.add('j');
			hs.add('k');
			hs.add('l');
			hs.add('m');
			hs.add('n');
			hs.add('o');
			hs.add('p');
			hs.add('q');
			hs.add('r');
			hs.add('s');
			hs.add('t');
			hs.add('u');
			hs.add('v');
			hs.add('w');
			hs.add('x');
			hs.add('y');
			hs.add('z');
			for (int i=0;i<arr.length;i++){
				hs.remove(arr[i]);
			}
			if (hs.size()==0){pw.println("pangram");}
			else {
				pw.print("missing ");
				for (char ans:hs){
					pw.print(ans);
				}
				pw.println();
			}
		}
		pw.flush();
		pw.close();
	}
}