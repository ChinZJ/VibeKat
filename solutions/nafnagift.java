/*
https://open.kattis.com/problems/nafnagift

The idea is to find the Longest Common Subsequence (LCS) between the 2 strings first
Do it with a bottom up approach, and augment it to contain a node with the following properties
	- length
	- character (only when x_i == y_j)
	- pair (pointing to the previous character or itself when length == 1)

When forming z, start from the back, we append characters from x and y until we get a character of the LCS then we insert that
*/

import java.util.*;
import java.io.*;
import java.math.*;

public class Nafnagift{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		// Retrieving variables first
		String name1, name2;
		int n, m, length;
		name1 = br.readLine();
		name2 = br.readLine();
		n = name1.length();
		m = name2.length();


		// Initialize 2D array
		Node[][] table = new Node[n + 1][m + 1];
		Node dummy = new Node(0, Character.MIN_VALUE, 0, 0);
		Node tmp;
		for (int i = 0; i < n + 1; i++) {
			table[i][0] = dummy;
		}
		for (int j = 0; j < m + 1; j++) {
			table[0][j] = dummy;
		}

		// Perform LCS search on both strings
		for (int j = 1; j < m + 1; j++) {
			for (int i = 1; i < n + 1; i++) {
				if (name1.charAt(i - 1) == (name2.charAt(j - 1))) {
					// First case the 2 characters match
					// Take the length of the LCS in (i - 1, j -1)
					length = table[i - 1][j - 1].length;
					if (length  == 0){
						tmp = new Node(length + 1, name1.charAt(i - 1), i, j);
					} else {
						tmp = new Node(length + 1, name1.charAt(i - 1), i - 1, j - 1);
					}
					table[i][j] = tmp;
				} else {
					// Second case is no match
					// Then check the LCS of (i - 1, j) and (i, j - 1)
					if (table[i - 1][j].length >= table[i][j - 1].length) {
						// Here we trivially resolve the conflict when both lengths are equal
						// by always taking (i - 1, j)
						// The reverse can be done, there is no difference
						length = table[i - 1][j].length;
						tmp = new Node(length, Character.MIN_VALUE, i - 1, j);
						table[i][j] = tmp;
					} else {
						length = table[i][j - 1].length;
						tmp = new Node(length, Character.MIN_VALUE, i, j - 1);
						table[i][j] = tmp;
					}
				}
				// System.out.println("Entry " + i + " " + j + " " + table[i][j]);
			}
		}

		// Note that if there is no LCS, we can immediately return name1 + name2
		if (table[n][m].length == 0) {
			pw.println(name1 + name2);
		} else {
			// Now what we have is a chain in the table that will give us the LCS eventually
			// We need to add whatever characters that are from name1 and name2 in sequential order of whatever is not part of the LCS as well
			// Thus we start from the back
			int name1Idx = n - 1; 	
			int name2Idx = m - 1;
			int tablexIdx = n;
			int tableyIdx = m;
			String finalName = "";

			// Trace to the first character in the LCS first
			while (table[tablexIdx][tableyIdx].character == Character.MIN_VALUE) {
				// System.out.println(table[tablexIdx][tableyIdx]);
				tmp = table[tablexIdx][tableyIdx];
				tablexIdx = tmp.x;
				tableyIdx = tmp.y;
			}
			// System.out.println(table[tablexIdx][tableyIdx]);

			while (name1Idx >= 0 && name2Idx >= 0) {
				// Append everything form name 2 into the string until it reaches the LCS
				while (name2Idx >= 0 && name2.charAt(name2Idx) != table[tablexIdx][tableyIdx].character) {
					// System.out.println("Second name ");
					finalName = name2.charAt(name2Idx) + finalName;
					name2Idx--;
					// System.out.println(finalName);
				}
				name2Idx--;

				// Append everything from name1 into the string until it reaches the LCS
				while (name1Idx >= 0 && name1.charAt(name1Idx) != table[tablexIdx][tableyIdx].character) {
					// System.out.println("First name");
					finalName = name1.charAt(name1Idx) + finalName;
					name1Idx--;
					// System.out.println(finalName);
				}
				name1Idx--;

				// System.out.println(table[tablexIdx][tableyIdx]);
				// Append the LCS character and find the next character in the LCS
				finalName = table[tablexIdx][tableyIdx].character + finalName;
				// System.out.println(finalName);

				// Check if this is the last LCS in the table
				tmp = table[tablexIdx][tableyIdx];
				if (tablexIdx == tmp.x && tableyIdx == tmp.y) {
					// Last LCS, trivially add whatever is left in name1 and name2
					if (name2Idx >= 0) {
						finalName = name2.substring(0, name2Idx + 1) + finalName;
					}
					if (name1Idx >= 0) {
						finalName = name1.substring(0, name1Idx + 1) + finalName;
					}
					break;
				} else {
					// Find the next LCS and repeat the process
					while (true) {
						tmp = table[tablexIdx][tableyIdx];
						tablexIdx = tmp.x;
						tableyIdx = tmp.y;
						if (table[tablexIdx][tableyIdx].character != Character.MIN_VALUE) {
							// Reached the next character in the LCS
							break;
						}
					}
				}
				// System.out.println("next iteration with " + table[tablexIdx][tableyIdx]);
				// System.out.println("name2idx " + name2Idx);
				// System.out.println("name1idx " + name1Idx);
			}
			pw.println(finalName);
		}

		

		pw.flush();
		pw.close();
	}
}

class Node{
	// This stores the information found in an element of the array
	public int length, x, y;
	public char character;

	//Constructor
	public Node(int length, char character, int x, int y) { 
    	this.length = length;
    	this.character = character;
    	this.x = x;
    	this.y = y;
	}	

	public String toString() {
		return "Node " + this.x + ", " + this.y + " of length " + this.length + " of character " + this.character;
	}
}