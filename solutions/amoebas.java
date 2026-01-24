/*
https://open.kattis.com/problems/amoebas

Basic BFS graph traversal. Should account for surrounding 8 squares
We can use BFS here since we know each cell has 2 neighbors
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class amoebas{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String[] temp=br.readLine().split(" ");;
		char[] carr;
		int row=Integer.parseInt(temp[0]);
		int col=Integer.parseInt(temp[1]);
		TreeSet<node> ts= new TreeSet<node>(((n1, n2) -> (n1.dummy - n2.dummy)));
		node[][] narr=new node[row][col];
		node nde;
		boolean[][] visit=new boolean[row][col];
		Queue<node> q= new LinkedList<>();
		int laziness=0;
		for (int i=0;i<row;i++){
			carr=br.readLine().toCharArray();
			for (int j=0;j<col;j++){
				if (carr[j]=='#'){
					// System.out.println("hit at "+ i + " "+ j);
					nde=new node(laziness,i,j);
					ts.add(nde);
					// System.out.println(ts.size());
					narr[i][j]=nde;
					laziness++;
				}
			}
		}
		int ctr=0;
		while (!ts.isEmpty()){
			ctr++;
			nde=ts.pollFirst();
			q.add(nde);
			// System.out.println("count " + ctr);
			while (!q.isEmpty()){
				nde=q.poll();
				if (visit[nde.x][nde.y]){continue;}
				// System.out.println("coordinate " + nde.x + " " + nde.y);
				visit[nde.x][nde.y]=true;
				ts.remove(nde);
				if (nde.x-1 >=0 && nde.y-1 >= 0 && narr[nde.x-1][nde.y-1] != null){q.add(narr[nde.x-1][nde.y-1]);}
				if (nde.y-1 >= 0 && narr[nde.x][nde.y-1] != null){q.add(narr[nde.x][nde.y-1]);}
				if (nde.x+1 < row && nde.y-1 >= 0 && narr[nde.x+1][nde.y-1] != null){q.add(narr[nde.x+1][nde.y-1]);}
				if (nde.x-1 >=0 && narr[nde.x-1][nde.y] != null){q.add(narr[nde.x-1][nde.y]);}
				if (nde.x+1 < row && narr[nde.x+1][nde.y] != null){q.add(narr[nde.x+1][nde.y]);}
				if (nde.x-1 >=0 && nde.y+1 < col && narr[nde.x-1][nde.y+1] != null){q.add(narr[nde.x-1][nde.y+1]);}
				if (nde.y+1 < col && narr[nde.x][nde.y+1] != null){q.add(narr[nde.x][nde.y+1]);}
				if (nde.x+1 < row && nde.y+1 < col && narr[nde.x+1][nde.y+1] != null){q.add(narr[nde.x+1][nde.y+1]);}
			}
		}
		pw.println(ctr);
		pw.flush();
		pw.close();
	}
}
class node{
	public int dummy;
	public int x;
	public int y;
	public node(int dummy,int x, int y){
		this.dummy=dummy;
		this.x=x;
		this.y=y;
	}
}