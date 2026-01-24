/*
https://open.kattis.com/problems/fontan

if water above air it turns to water
if water above stone cells left and right turn to water
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class fontan{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String[] temp= br.readLine().split(" ");
		int row=Integer.parseInt(temp[0]);
		int col=Integer.parseInt(temp[1]);
		boolean[][] visit=new boolean[row][col];
		char[][] arr=new char[row][col];
		node nde,newnde;
		Queue<node> q=new LinkedList<node>();
		for (int i=0;i<row;i++){
			arr[i]=br.readLine().toCharArray();
			for (int j=0;j<col;j++){
				if (arr[i][j]=='V'){
					nde=new node(i,j);
					q.add(nde);
				}
			}
		}
		while (!q.isEmpty()){
			nde=q.poll();
			// System.out.println("coordinate "+ nde.x +" "+nde.y);
			if (visit[nde.x][nde.y]){continue;}
			else{
				visit[nde.x][nde.y]=true;
				//First case, below is air
				if (nde.x+1<row){
					if (arr[nde.x+1][nde.y]=='.'){
						nde=new node(nde.x+1,nde.y);
						q.add(nde);
						// System.out.println("added "+(nde.x) + " "+(nde.y));
						arr[nde.x][nde.y]='V';
					}
					//Second case, below is rock
					else if (arr[nde.x+1][nde.y]=='#'){
						if (nde.y-1 >=0){
							if (arr[nde.x][nde.y-1]=='.'){
								newnde=new node(nde.x,nde.y-1);
								q.add(newnde);
								arr[newnde.x][newnde.y]='V';
							}
						}
						if (nde.y+1 < col){
							if (arr[nde.x][nde.y+1]=='.'){
								newnde=new node(nde.x,nde.y+1);
								q.add(newnde);
								arr[newnde.x][newnde.y]='V';
							}
						}
					}
				}
			}
		}
		for (int i=0;i<row;i++){
			for (int j=0;j<col;j++){
				pw.print(arr[i][j]);
			}
			pw.println();
		}
		pw.flush();
		pw.close();
	}
}
class node{
	public int x;
	public int y;
	public node (int x, int y){
		this.x=x;
		this.y=y;
	}
}