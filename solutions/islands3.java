/*
Input  row and column
Then the 2D grid

We initialize 2 2D grids, one for the map and one as a visited state

After initializing, we perform a dfs
Iterate row by row

For every cloud we see, if it is connected to an island, we change it to land
This will maximize the number of islands we can form

For every land that we have visited, we update the board so we no longer need to look at it

We append to a counter for every new land we reach that we havve not visited
*/

//import
import java.util.*;
import java.io.*;

public class Islands {
	public static void main (String[] args) throws IOException {
		//BufferedReader and PrintWriter
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		//Variables
		String[] input = br.readLine().split(" ");
		String map_input;
		int row = Integer.parseInt(input[0]);
		int col = Integer.parseInt(input[1]);

		Character[][] map = new Character[row][col];
		boolean[][] visit = new boolean[row][col];
		int counter = 0;

		//Filling in the map
		for (int i = 0; i < row; i++) {
			//Take in the entire row
			map_input = br.readLine(); //this is a string

			for (int j = 0; j < col; j++) {
				map[i][j] = map_input.charAt(j);
				visit[i][j] = false;
			}
		}

		//Perform DFS on every node if it has not been visited
		//If have not visited a land node, we increment the counter and perform a DFS
		//We only check for land nodes because those are guaranteed, 
		for (int i = 0; i < row; i++){
			for (int j = 0; j < col; j++) {
				if ( !(visit[i][j]) && (map[i][j].equals('L')) ) {
					counter++;
					dfs(i, j, row, col, map, visit);
				}
			}
		}

		//Print
		pw.println(counter);
		pw.flush();
		pw.close();
	}

	public static void dfs (int i, int j, int row, int col, Character[][] map, boolean[][] visit) {
		//From the row and column, we need to traverse up, down, left and right if that state exists
		//If that state is a cloud, we change the visit to True
		//If that state is water, we exit the loop

		//Set the visited node to be true
		visit[i][j] = true;

		int top_row = i-1;
		int bot_row = i+1;
		int topbot_col= j;

		int lr_row = i;
		int left_col = j-1;
		int right_col = j+1;

		//Check top row
		if (top_row >= 0 && top_row < row) {
			//If land or cloud, we call dfs on that node
			if (!(map[top_row][topbot_col].equals('W')) && !(visit[top_row][topbot_col])) {
				dfs(top_row, topbot_col, row, col, map, visit);
			}
		}

		//Check bot row
		if (bot_row >= 0 && bot_row < row) {
			//If land or cloud, we call dfs on that node
			if (!(map[bot_row][topbot_col].equals('W')) && !(visit[bot_row][topbot_col])) {
				dfs(bot_row, topbot_col, row, col, map, visit);
			}
		}

		//Check left col
		if (left_col >= 0 && left_col < col) {
			//If land or cloud, we call dfs on that node
			if (!(map[lr_row][left_col].equals('W')) && !(visit[lr_row][left_col])) {
				dfs(lr_row, left_col, row, col, map, visit);
			}
		}

		//Check right col
		if (right_col >= 0 && right_col < col) {
			//If land or cloud, we call dfs on that node
			if (!(map[lr_row][right_col].equals('W')) && !(visit[lr_row][right_col])) {
				dfs(lr_row, right_col, row, col, map, visit);
			}
		}
	}
}