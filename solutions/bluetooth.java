/*
https://open.kattis.com/problems/bluetooth

Cannot chew on side continaing a blue tooth
The side cannot have a blue tooth, and must have one tooth on the upper and lower jaw
Since it only appears once, we just need to count
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class bluetooth{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));


		int t = Integer.parseInt(br.readLine());
		String temp;
		int leftu=8,leftd=8,rightu=8,rightd=8;
		boolean leftb=false,rightb=false;
		while (t-- >0){
			temp = br.readLine();
			//Right has sign after the character
			//Positive is upper
			if (temp.charAt(1)=='+'){
				if (temp.charAt(3)=='b'){rightb=true;}
				else{rightu--;}
			}
			//Negative is lower
			else if (temp.charAt(1)=='-'){
				if (temp.charAt(3)=='b'){rightb=true;}
				else{rightd--;}
			}
			//Left has sign before the character
			//Positive is upper
			else if (temp.charAt(0)=='+'){
				if (temp.charAt(3)=='b'){leftb=true;}
				else{leftu--;}
			}
			//Negative is lower
			else if (temp.charAt(0)=='-'){
				if (temp.charAt(3)=='b'){leftb=true;}
				else{leftd--;}
			}
		}
		//Left 
		if (leftu>0 && leftd>0 && !leftb) {pw.println(0);}
		//Right
		else if (rightu>0 && rightd>0 && !rightb) {pw.println(1);}
		else{pw.println(2);}
		pw.flush();
		pw.close();
	}
}