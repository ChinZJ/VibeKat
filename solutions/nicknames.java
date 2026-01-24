//NOTE IMPLEMENTATION OF PARTIAL AVL TREE IS USED HERE. This does not support delete operations
/*
Use 26 AVL trees to store them based on each of their starting characters
For each search performed, we will store the results in a hashmap
*/

import java.util.*;
import java.io.*;

public class Nicknames {
	public static void main (String[] args) throws IOException {
		//BufferedReader and PrintWriter
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		//Variables
		String temp;
		int no_cases = Integer.parseInt(br.readLine());
		Node temp_node;
		Node root_node;

		//Data Structures
		//Creating 26 AVL trees, one for each starting character. Insert a null node into all of 
		int tree_key;
		int a = 97;
		Node[] avl_trees = new Node[26];
		temp_node = new Node(null);
		for (int i = 0; i < 26; i++) {
			avl_trees[i] = temp_node;
		}

		//Memoization used only during searching
		String memo_key;
		HashMap<String, Integer> memo = new HashMap<String, Integer>();

		//This first iteration is to create my AVL trees
		for (int i = 0; i < no_cases; i++) {
			temp = br.readLine();
			temp_node = new Node(temp);
			tree_key = (int)temp.charAt(0) - a;
			root_node = avl_trees[tree_key];

			//Base case: my AVL tree is empty, just add it in
			if (root_node.name == null) {
				avl_trees[tree_key] = temp_node;
				continue;
			}

			//Else, a tree exists, and we have to perform the insert operation
			else{
				//Going down the tree
				while (true) {
					//We need to compare the string lexicographically using the compareTo method
					//if int is negative, the first String is smaller
					//All names are unique, there will never be a case where the comparison == 0

					//First case: smaller than the root
					if (temp_node.name.compareTo(root_node.name) < 0) {
						//If there exists a left child, we need to recursively go down the tree
						if (root_node.left != null){
							root_node = root_node.left;
							continue;
						}
						//If no left child exists
						//Assign .left of the root node, and .parent of the child node
						else {
							root_node.left = temp_node;
							temp_node.parent = root_node;
							break;
						}
					}

					//Second case: bigger than the root
					else {
						//Apply the same thing but in reverse
						if (root_node.right != null){
							root_node = root_node.right;
							continue;
						}
						//If no left child exists
						//Assign .left of the root node, and .parent of the child node
						else {
							root_node.right = temp_node;
							temp_node.parent = root_node;
							break;
						}
					}
				}


				//Now, my temp node is at the bottom of the tree, we will start updating the height and the size respective all the way up to the root
				while (true) {
					//Base case is when we are at the root of the tree and no rotations need to be performed
					if (temp_node.name.equals(temp_node.parent.name)) {
						update_hs(temp_node);
						if ((balfac(temp_node) > -2) && (balfac(temp_node) < 2)) {break;}
						else {
							if (balfac(temp_node) == -2) {
								if (balfac(temp_node.right) == 1) {
									// System.out.println("Right left case for node " + temp_node.name);
									RotateRight(temp_node.right, avl_trees); 
									RotateLeft(temp_node, avl_trees);}
								else{
									// System.out.println("Right right case for node " + temp_node.name);
									RotateLeft(temp_node, avl_trees);}
							}
							else if (balfac(temp_node) == 2) {
								if (balfac(temp_node.left) == -1) {
									// System.out.println("Left Right case for node " + temp_node.name);
									RotateLeft(temp_node.left, avl_trees); 
									RotateRight(temp_node, avl_trees);
								}
								else {
									// System.out.println("Left Left case for node " + temp_node.name);
									RotateRight(temp_node, avl_trees);
								}
							}
							break;
						}
					}	

					//Perform general calculations of height and size
					update_hs(temp_node);


					//4 rotation cases
					if (balfac(temp_node) == -2) {
						if (balfac(temp_node.right) == 1) {
							// System.out.println("Right left case for node " + temp_node.name);
							RotateRight(temp_node.right, avl_trees); 
							// System.out.println("rotate right completed, now performing rotate left with nodes " + temp_node.name + " and " + temp_node.right.name);
							RotateLeft(temp_node, avl_trees); 
							temp_node = temp_node.parent;}
						else{
							// System.out.println("Right right case for node " + temp_node.name);
							RotateLeft(temp_node, avl_trees); 
							//System.out.println(temp_node.right.name);
							temp_node = temp_node.parent;}
						continue;
					}
					else if (balfac(temp_node) == 2) {
						if (balfac(temp_node.left) == -1) {
							// System.out.println("Left Right case for node " + temp_node.name);
							RotateLeft(temp_node.left, avl_trees); 
							RotateRight(temp_node, avl_trees); 
							temp_node = temp_node.parent;}
						else {
							// System.out.println("Left Left case for node " + temp_node.name);
							RotateRight(temp_node, avl_trees); 
							temp_node = temp_node.parent;}
						continue;
					}
					else {
						// System.out.println("no rotation");
						temp_node = temp_node.parent;
					}
				}
			}

		}

		//Once everything in the tree is sorted I will begin the second half of the ops
		no_cases = Integer.parseInt(br.readLine());
		for (int i = 0; i < no_cases; i++) {
			memo_key = br.readLine();
			if (memo.containsKey(memo_key)) {pw.println(memo.get(memo_key)); continue;}

			
			else{
				//My base case is that the entire AVL tree does not exist, if so print 0, no need to add to hashmap
				root_node = avl_trees[(int)memo_key.charAt(0) - a];
				if (root_node.name == null) {pw.println(0); continue;}

				//Walk down the entire AVL tree until we find the first subsequence that matches
				//if there are none then we print 0, store the key and continue
				// System.out.println("finding key " + memo_key);
				temp_node = find_node(memo_key, root_node);
					

				//No key exists
				if (temp_node == null) {pw.println(0); memo.put(memo_key, 0);}

				else{
					//Note that the distinguishing factor here is between he left and the right branch
					//For the left branch, if you find any other key again, anything to the right of it will definitely be part of the nickname
					//For the right branch, if you find any other key again, aynthing to the left of it will definitely be part of the nickname
					int number_nicknames = 1 + checkleft(memo_key, temp_node.left) + checkright(memo_key, temp_node.right);
					
					memo.put(memo_key, number_nicknames);
					// System.out.println(number_nicknames);
					pw.println(number_nicknames);
				}
			}
		}
		pw.flush();
		pw.close();
	}

	public static int balfac (Node node) {
		return node.left_height - node.right_height;
	}

	public static void update_hs (Node temp_node) {
		temp_node.size = 1;
		temp_node.height = 1;
		if (temp_node != null) {
			if (temp_node.left != null) {
				// System.out.println("the left node of " + temp_node.name + " is " + temp_node.left.name + " with size " + temp_node.left.size);
				temp_node.size += temp_node.left.size;
				temp_node.left_height = temp_node.left.height;

			}
			else {temp_node.left_height = -1;}

			if (temp_node.right != null) {
				// System.out.println("the right node of " + temp_node.name + " is " + temp_node.right.name + " with size " + temp_node.right.size);
				temp_node.size += temp_node.right.size;
				temp_node.right_height = temp_node.right.height;
			}
			else {temp_node.right_height = -1;}
			temp_node.height += Integer.max(temp_node.left_height, temp_node.right_height);

			// System.out.println("the height of node " + temp_node.name + " is " + temp_node.height);
			// System.out.println("the size of node " + temp_node.name + " is " + temp_node.size);
		}
	}

	public static void RotateLeft (Node core, Node[] avl_trees) {
		Node parent = core.parent;
		Node right_node = core.right;

		//Assign parent pointers
		core.parent = right_node;
		if (parent.name.equals(core.name)) {
			//If the parent is the core itself, we only need to change right node
			right_node.parent = right_node;
			avl_trees[(int) right_node.name.charAt(0) - 97] = right_node;
		}
		else {
			right_node.parent = parent;
			
			if (parent.left != null){
				if (parent.left.name.equals(core.name)) {
					parent.left = right_node;
				}
			}
			if (parent.right != null) {
				if (parent.right.name.equals(core.name)) {
					parent.right = right_node;
				}
			}
			
		}

		//The only other thing that we need to manipulate is actually right_node.left
		//If node exists, we need to assign core as its parent
		core.right = right_node.left;
		if (right_node.left != null) {right_node.left.parent = core;}
		right_node.left = core;

		//only 2 nodes are affected by the rotation: the core and its right_node
		//update core before you can update right_node
		update_hs(core);
		update_hs(right_node);

	}


	public static void RotateRight (Node core, Node[] avl_trees){
		Node parent = core.parent;
		Node left_node = core.left;

		//Assign parent pointers
		core.parent = left_node;
		if (parent.name.equals(core.name)) {
			//If the parent is the core itself, we only need to change right node
			left_node.parent = left_node;
			avl_trees[(int) left_node.name.charAt(0) - 97] = left_node;
		}
		else {
			left_node.parent = parent;
			
			if (parent.left != null){
				if (parent.left.name.equals(core.name)) {
					parent.left = left_node;
				}
			}
			if (parent.right != null) {
				if (parent.right.name.equals(core.name)) {
					parent.right = left_node;
				}
			}
			
		}

		//The only other thing that we need to manipulate is actually right_node.left
		//If node exists, we need to assign core as its parent
		core.left = left_node.right;
		if (left_node.right != null) {left_node.right.parent = core;}
		left_node.right = core;

		//only 2 nodes are affected by the rotation: the core and its right_node
		//update core before you can update right_node
		update_hs(core);
		update_hs(left_node);
	}

	public static Node find_node (String memo_key, Node root_node){
		//Base case: the root_node does not exist, we return a null node
		if (root_node == null) {return null;}
		//If the key is a subset of the rootnode, we return it
		// System.out.println("the name of the node is " + root_node.name);
		// System.out.println("the value calculated is " + root_node.name.indexOf(memo_key));
		if (root_node.name.indexOf(memo_key) == 0) {return root_node;}

		//Go either left or right depending on the compare method
		if (memo_key.compareTo(root_node.name) < 0) {return find_node(memo_key, root_node.left);}
		else {return find_node(memo_key, root_node.right);}
	}

	public static int checkleft (String memo_key, Node temp_node) {
		//Base case, we hit the bottom
		if (temp_node == null) {return 0;}
		//First case: the name of the node is part of the memo_key
		if (temp_node.name.indexOf(memo_key) == 0) {
			//We take everything to the right of it, and branch leftwards
			if (temp_node.right != null) {return 1 + temp_node.right.size + checkleft(memo_key, temp_node.left);}
			return 1 + checkleft(memo_key, temp_node.left);
		}

		//Alternate case: the name of the node is not part of the memo key
		else {return checkleft(memo_key, temp_node.right);}
	}

	public static int checkright (String memo_key, Node temp_node) {
		//Base case, we hit the bottom
		if (temp_node == null) {return 0;}
		//First case: the name of the node is part of the memo_key
		if (temp_node.name.indexOf(memo_key) == 0) {
			//We take everything to the left of it, and branch rightwards
			if (temp_node.left != null) {return 1 + temp_node.left.size + checkright(memo_key, temp_node.right);}
			return 1 + checkright(memo_key, temp_node.right);
		}

		//Alternate case: the name of the node is not part of the memo key
		else {return checkright(memo_key, temp_node.left);}
	}

}

class Node {
	public Node parent = this;
	public Node left = null;
	public Node right = null;
	public int left_height = -1;
	public int right_height = -1;
	public int height = 0;
	public int size = 1;
	public String name;

	//Constructor
	public Node(String name) {
		this.name = name;
	}
}
/*

subadolescents
suballocations
subterraneanly
substitutional
substitutively
substantivally
substantivized
substantivizes
substantiation
substantiative
subcontractor
subpopulation
submandibular
subdiscipline
subliterature
subspecialize
subspecialist
substanceless
substantially
substantiated
substantiates
substantivize
substantively
subsidization
substructures
substructural
substitutions
substitutable
subterraneous
subtilenesses
subprincipals
subordinators
subordinating
subordination
subordinative
subparagraphs
subscriptions
subserviences
subserviently
subsaturation
subsatellites
subreptitious
suburbanising
subtreasuries
subtilization
subvocalizing
subversionary
subventionary
suburbanizing

51
substantialness
substantiations
substantiveness
substantivizing
subspecializing
substitutionary
subterraneously
subtherapeutic
subvocalization
suburbanization
subcontraoctave
subcategorizing
subcommissioned
subdevelopments
subordinatene
submicroscopic
subinfeudation
subinfeudating
subirrigations
subjectivising
subjectivities
subjectivistic
subjectivizing
subjectiveness
subgovernments
subgenerations
submetacentric
submissiveness
subnormalities
subliteratures
sublieutenants
submandibulars
submaxillaries
subdisciplines
subdevelopment
subdepartments
subcutaneously
subcontractors
subcontracting
subcontinental
subcommissions
subconsciouses
subconsciously
subemployments
subcategorized
subcategorizes
subcollections
subcommunities
subclassifying
subarachnoidal
subatmospheric

16
sub
subs
subt
subv
subu
subc
subd
subo
subm
subi
subj
subg
subn
subl
sube
suba
*/