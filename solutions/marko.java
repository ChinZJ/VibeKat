/*
https://open.kattis.com/problems/marko
Default hashmap settings
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class marko{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));
		StringBuilder sb;

		String[] temp;
		String tmp;
		HashMap<String,Integer> hm=new HashMap<>();
		int n;
		hm.clear();
		n=Integer.parseInt(br.readLine());
		for (int i=0;i<n;i++){
			tmp=br.readLine();
			sb=new StringBuilder();
			for (int j=0;j<tmp.length();j++){
				if (tmp.charAt(j)=='a'){sb.append("2");}
				if (tmp.charAt(j)=='b'){sb.append("2");}
				if (tmp.charAt(j)=='c'){sb.append("2");}
				if (tmp.charAt(j)=='d'){sb.append("3");}
				if (tmp.charAt(j)=='e'){sb.append("3");}
				if (tmp.charAt(j)=='f'){sb.append("3");}
				if (tmp.charAt(j)=='g'){sb.append("4");}
				if (tmp.charAt(j)=='h'){sb.append("4");}
				if (tmp.charAt(j)=='i'){sb.append("4");}
				if (tmp.charAt(j)=='j'){sb.append("5");}
				if (tmp.charAt(j)=='k'){sb.append("5");}
				if (tmp.charAt(j)=='l'){sb.append("5");}
				if (tmp.charAt(j)=='m'){sb.append("6");}
				if (tmp.charAt(j)=='n'){sb.append("6");}
				if (tmp.charAt(j)=='o'){sb.append("6");}
				if (tmp.charAt(j)=='p'){sb.append("7");}
				if (tmp.charAt(j)=='q'){sb.append("7");}
				if (tmp.charAt(j)=='r'){sb.append("7");}
				if (tmp.charAt(j)=='s'){sb.append("7");}
				if (tmp.charAt(j)=='t'){sb.append("8");}
				if (tmp.charAt(j)=='u'){sb.append("8");}
				if (tmp.charAt(j)=='v'){sb.append("8");}
				if (tmp.charAt(j)=='w'){sb.append("9");}
				if (tmp.charAt(j)=='x'){sb.append("9");}
				if (tmp.charAt(j)=='y'){sb.append("9");}
				if (tmp.charAt(j)=='z'){sb.append("9");}
			}
			if (!hm.containsKey(sb.toString())) {hm.put(sb.toString(),1);}
			else {hm.replace( sb.toString(), hm.get(sb.toString())+1 );}
		}
		tmp=br.readLine();
		if (!hm.containsKey(tmp)) {pw.println(0);}
		else {pw.println(hm.get(tmp));}
		pw.flush();
		pw.close();
	}
}
