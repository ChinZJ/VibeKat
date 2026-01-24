/*
https://open.kattis.com/problems/halfacookie

Shortest cord will be a horizontal / vertical line depending on where the point is
Calculating the area of the chord will be the area from origin - area of triangle
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class halfacookie{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String chk;
		String[] temp;
		double r,x,y,strln,chrdln,angle,artg,arc,ars,rem;
		while ( (chk = br.readLine()) != null){
			temp=chk.split(" ");
			r=Double.parseDouble(temp[0]);
			x=Double.parseDouble(temp[1]);
			y=Double.parseDouble(temp[2]);
			strln=Math.sqrt( Math.pow(0-x, 2) + Math.pow(0-y, 2) );
			// System.out.println("strln is " + strln);
			if (strln>=r){pw.println("miss");continue;}
			chrdln=2*Math.sqrt( Math.pow(r,2) - Math.pow(strln,2) );
			// System.out.println("chordln is " + chrdln);
			angle=Math.acos( ((2 * Math.pow(r,2) ) - Math.pow(chrdln,2)) / (2*r*r) );
			// System.out.println("angle is " + angle);
			artg=(r*r*Math.sin(angle))/2;
			// System.out.println("area of triangle is " + artg);
			arc=Math.PI*r*r;
			// System.out.println("area of circle is " + arc);
			ars= (arc*angle/ Math.toRadians(360)) - artg;
			// System.out.println("area of segment is " + ars);
			rem=arc-ars;
			// System.out.println("area of remainder is " + ars);
			pw.println(Math.max(ars,rem)+" "+Math.min(ars,rem));

		}
		pw.flush();
		pw.close();
	}
}
